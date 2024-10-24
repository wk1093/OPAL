#include "opal.h"

#ifdef OPAL_PORTAUDIO

#include <portaudio.h>

OpalResult opalInit() {
    if (Pa_Initialize() != paNoError) {
        return OPAL_FAILURE;
    }
    return OPAL_SUCCESS;
}

OpalResult opalTerminate() {
    if (Pa_Terminate() != paNoError) {
        return OPAL_FAILURE;
    }
    return OPAL_SUCCESS;
}

#endif