#include "opal/synth.h"

#include <math.h>

OpalResult opalSynth(void* buffer, uint64_t offset, uint64_t sampleRate, uint64_t duration, OpalSampleFormat format, float frequency, float amplitude, OpalSynthType type) {
    if (buffer == NULL) {
        return OPAL_FAILURE;
    }
    if (sampleRate == 0) {
        return OPAL_FAILURE;
    }
    if (duration == 0) {
        return OPAL_FAILURE;
    }
    if (frequency == 0) {
        return OPAL_FAILURE;
    }
    if (amplitude == 0) {
        return OPAL_FAILURE;
    }
    if (type < OPAL_SYNTH_SINE || type > OPAL_SYNTH_TRIANGLE) {
        return OPAL_FAILURE;
    }
    if (format < OPAL_FLOAT32 || format > OPAL_INT8) {
        return OPAL_FAILURE;
    }
    // TODO: other formats
    if (format == OPAL_INT24) {
        return OPAL_FAILURE;
    }
    if (format == OPAL_INT16) {
        return OPAL_FAILURE;
    }
    if (format == OPAL_INT8) {
        return OPAL_FAILURE;
    }
    if (type == OPAL_SYNTH_SINE) {
        float* bufferFloat = (float*)buffer;
        for (uint64_t i = 0; i < duration; i++) {
            bufferFloat[i + offset] = sinf(2 * M_PI * frequency * i / sampleRate) * amplitude;
        }
    } else if (type == OPAL_SYNTH_SQUARE) {
        float* bufferFloat = (float*)buffer;
        for (uint64_t i = 0; i < duration; i++) {
            bufferFloat[i + offset] = sinf(2 * M_PI * frequency * i / sampleRate) > 0 ? amplitude : -amplitude;
        }
    } else if (type == OPAL_SYNTH_SAWTOOTH) {
        float* bufferFloat = (float*)buffer;
        for (uint64_t i = 0; i < duration; i++) {
            bufferFloat[i + offset] = 2 * amplitude * (i * frequency / sampleRate - floorf(i * frequency / sampleRate + 0.5));
        }
    } else if (type == OPAL_SYNTH_TRIANGLE) {
        float* bufferFloat = (float*)buffer;
        for (uint64_t i = 0; i < duration; i++) {
            bufferFloat[i + offset] = 2 * amplitude * (2 * fabsf(2 * i * frequency / sampleRate - 2 * floorf(i * frequency / sampleRate + 0.5)) - 1);
        }
    }

    return OPAL_SUCCESS;
}