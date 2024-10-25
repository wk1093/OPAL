#pragma once
#ifndef _OPAL_SYNTH_H_
#define _OPAL_SYNTH_H_

#include "pch.h"
#include "stream.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef OPAL_DECL_ENUM enum {
    OPAL_SYNTH_SINE,
    OPAL_SYNTH_SQUARE,
    OPAL_SYNTH_SAWTOOTH,
    OPAL_SYNTH_TRIANGLE
} OpalSynthType;

OPAL_DECL_FUNC_ND OpalResult opalSynth(void* buffer, uint64_t offset, uint64_t sampleRate, uint64_t duration, OpalSampleFormat format, float frequency, float amplitude, OpalSynthType type);


#ifdef __cplusplus
}
#endif

#endif