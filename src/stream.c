#include "opal/stream.h"

#ifdef OPAL_PORTAUDIO

#include <portaudio.h>

struct OpalStream {
    PaStream* stream;
    OpalStreamCallback callback;
    void* userData;
    uint32_t sampleRate;
};

static int opalPortAudioCallback(const void* inputBuffer, void* outputBuffer, unsigned long numFrames, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData) {
    OpalStream* stream = (OpalStream*)userData;
    OpalStreamData data = {
        .outputBuffer = outputBuffer,
        .inputBuffer = inputBuffer,
        .numFrames = numFrames,
        .sampleRate = stream->sampleRate,
        .time = timeInfo->currentTime,

    };
    OpalStreamResult result = stream->callback(&data, stream->userData);
    switch (result) {
    case OPAL_CONTINUE:
        return paContinue;
    case OPAL_COMPLETE:
        return paComplete;
    case OPAL_ABORT:
        return paAbort;
    }
}

OpalStream* opalCreateStream(OpalStreamCallback callback, void* userData) {
    OpalStream* stream = malloc(sizeof(OpalStream));
    stream->callback = callback;
    stream->userData = userData;
    stream->sampleRate = 44100;
    PaError error = Pa_Initialize();
    if (error != paNoError) {
        free(stream);
        return NULL;
    }
    PaStreamParameters outputParameters = {
        .device = Pa_GetDefaultOutputDevice(),
        .channelCount = 2,
        .sampleFormat = paFloat32,
        .suggestedLatency = Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice())->defaultLowOutputLatency,
        .hostApiSpecificStreamInfo = NULL
    };
    PaStreamParameters inputParameters = {
        .device = Pa_GetDefaultInputDevice(),
        .channelCount = 2,
        .sampleFormat = paFloat32,
        .suggestedLatency = Pa_GetDeviceInfo(Pa_GetDefaultInputDevice())->defaultLowInputLatency,
        .hostApiSpecificStreamInfo = NULL
    };
    error = Pa_OpenStream(&stream->stream, &inputParameters, &outputParameters, stream->sampleRate, 256, paClipOff, opalPortAudioCallback, stream);
    if (error != paNoError) {
        Pa_Terminate();
        free(stream);
        return NULL;
    }
    return stream;
}

OpalResult opalStartStream(OpalStream* stream) {
    // make a few checks first, we want to prevent causing a PortAudio error
    if (stream == NULL) {
        return OPAL_FAILURE;
    }
    if (stream->stream == NULL) {
        return OPAL_FAILURE;
    }
    if (Pa_IsStreamActive(stream->stream)) {
        return OPAL_FAILURE;
    }
    PaError error = Pa_StartStream(stream->stream);
    if (error != paNoError) {
        return OPAL_FAILURE;
    }
    return OPAL_SUCCESS;
}

OpalResult opalStartStreamSync(OpalStream* stream) {
    if (stream == NULL) {
        return OPAL_FAILURE;
    }
    if (stream->stream == NULL) {
        return OPAL_FAILURE;
    }
    if (Pa_IsStreamActive(stream->stream)) {
        return OPAL_FAILURE;
    }
    PaError error = Pa_StartStream(stream->stream);
    if (error != paNoError) {
        return OPAL_FAILURE;
    }
    while (Pa_IsStreamActive(stream->stream)) {
        Pa_Sleep(100);
    }
    return OPAL_SUCCESS;
}

bool opalStreamIsPlaying(OpalStream* stream) {
    if (stream == NULL) {
        return false;
    }
    if (stream->stream == NULL) {
        return false;
    }
    return Pa_IsStreamActive(stream->stream);
}

void opalDestroyStream(OpalStream* stream) {
    if (stream == NULL) {
        return;
    }
    if (stream->stream == NULL) {
        return;
    }
    if (Pa_IsStreamActive(stream->stream)) {
        Pa_StopStream(stream->stream);
    }
    Pa_CloseStream(stream->stream);
    free(stream);
}


#else
#error Only PortAudio is supported at the moment
#endif