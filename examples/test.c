#include "opal.h"
#include <math.h>



// OpalStreamResult callback(OpalStreamData* data, void* userData) {
//     // pass input to output
//     float* output = (float*)data->outputBuffer;
//     float* input = (float*)data->inputBuffer;
//     for (uint32_t i = 0; i < data->numFrames; i++) {
//         output[i*2] = input[i*2];
//         output[i*2+1] = input[i*2+1];
//     }
//     return OPAL_CONTINUE;
// }

int main() {
    OpalResult result = opalInit();
    opalErrorHandle(result); // checks for errors, and prints them to stderr if there are any, but doesn't stop execution

    // // exmaple of the lower level API (streams)

    // // sample rate, channels_in, format_in, channels_out, format_out
    // OpalStream* stream = opalCreateStreamAdvanced(callback, NULL, 44100, 2, OPAL_FLOAT32, 2, OPAL_FLOAT32);

    // if (stream == NULL) {
    //     return 1;
    // }

    // result = opalStartStream(stream); // has an alternate opalStartStreamSync that blocks until the stream is done
    // opalErrorHandle(result);

    // while (true) {
    //     if (!opalStreamIsPlaying(stream)) {
    //         printf("Done\n");
    //         break;
    //     }
    // }

    // opalDestroyStream(stream);

    // stream = NULL;

    // opalDestroyStream(stream);

    // Higher level api

    // synthesize
    // into a buffer
    float* buffer = (float*)malloc(44100 * sizeof(float));
    // buffer, offset, sample rate, duration, format, frequency, amplitude, type
    result = opalSynth(buffer, 0, 44100, 44100, OPAL_FLOAT32, 440, 0.5, OPAL_SYNTH_SINE);
    opalErrorHandle(result);
    
    // buffer, offset, sample rate, duration, format
    OpalSound* sound = opalCreateSoundFromBuffer(buffer, 0, 44100, 44100, OPAL_FLOAT32, 2);
    free(buffer);
    opalErrorHandle(result);

    result = opalPlaySound(sound); // has an alternate version opalPlaySoundSync that blocks until the sound is done
    opalErrorHandle(result);

    while (true) {
        if (!opalSoundIsPlaying(sound)) {
            break;
        }
    }

    opalDestroySound(sound);

    result = opalTerminate();
    opalErrorHandle(result);
    return 0;
}