#include "opal/sound.h"

OpalStreamResult callback(OpalStreamData* data, void* userData) {
    OpalSound* sound = (OpalSound*)userData;

    if (data->formatOut != OPAL_FLOAT32) {
        return OPAL_ABORT;
    }

    float* output = (float*)data->outputBuffer;

    for (uint64_t i = 0; i < data->numFrames; i++) {
        for (uint64_t j = 0; j < data->channelsOut; j++) {
            if (sound->offset+i*data->channelsOut+j >= sound->duration) {
                break;
            }
            output[i*data->channelsOut+j] = ((float*)sound->buffer)[sound->offset+i*data->channelsOut+j];
        }
    }

    if (sound->offset+data->numFrames*data->channelsOut >= sound->duration) {
        opalStopSound(sound);
    }

    sound->offset += data->numFrames*data->channelsOut;
    return OPAL_CONTINUE;
}

OpalSound* opalCreateSoundFromBuffer(void* buffer, uint64_t offset, uint64_t sampleRate, uint64_t duration, OpalSampleFormat format, uint64_t channels) {
    OpalSound* sound = (OpalSound*)malloc(sizeof(OpalSound));
    sound->stream = opalCreateStreamAdvanced(callback, sound, sampleRate, channels, format, 1, OPAL_FLOAT32);
    sound->buffer = buffer;
    sound->offset = offset;
    sound->duration = duration;
    sound->numFrames = duration;
    sound->frameSize = 2;
    if (sound->stream == NULL) {
        free(sound);
        return NULL;
    }

    return sound;
}

OpalResult opalPlaySound(OpalSound* sound) {
    return opalStartStream(sound->stream);
}

OpalResult opalPlaySoundSync(OpalSound* sound) {
    return opalStartStreamSync(sound->stream);
}

bool opalSoundIsPlaying(OpalSound* sound) {
    return opalStreamIsPlaying(sound->stream);
}

void opalStopSound(OpalSound* sound) {
    opalStopStream(sound->stream);
}

void opalDestroySound(OpalSound* sound) {
    opalDestroyStream(sound->stream);
    free(sound);
}