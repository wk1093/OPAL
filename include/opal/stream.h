#pragma once
#ifndef _OPAL_STREAM_H_
#define _OPAL_STREAM_H_

#include "pch.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef OPAL_DECL_ENUM enum {
    OPAL_CONTINUE,
    OPAL_COMPLETE,
    OPAL_ABORT
} OpalStreamResult;

typedef OPAL_DECL_ENUM enum {
    OPAL_FLOAT32,
    OPAL_INT32,
    OPAL_INT24,
    OPAL_INT16,
    OPAL_INT8
} OpalSampleFormat;

typedef OPAL_DECL_STRUCT struct {
    void* outputBuffer;
    const void* inputBuffer;
    uint64_t numFrames;
    uint64_t sampleRate;
    OpalSampleFormat formatIn;
    OpalSampleFormat formatOut;
    uint64_t channelsIn;
    uint64_t channelsOut;
} OpalStreamData;

typedef OPAL_DECL_STRUCT struct OpalStream OpalStream;

typedef OpalStreamResult (*OpalStreamCallback)(OpalStreamData*, void*);

// TODO: more advanced functions that specify device, sample rate, and format
OPAL_DECL_FUNC_ND OpalStream* opalCreateStream(OpalStreamCallback callback, void* userData);
OPAL_DECL_FUNC_ND OpalStream* opalCreateStreamAdvanced(OpalStreamCallback callback, void* userData, uint64_t sampleRate, uint64_t channelsIn, OpalSampleFormat formatIn, uint64_t channelsOut, OpalSampleFormat formatOut);
OPAL_DECL_FUNC_ND OpalResult opalStartStream(OpalStream* stream);
OPAL_DECL_FUNC_ND OpalResult opalStartStreamSync(OpalStream* stream);
OPAL_DECL_FUNC_ND bool opalStreamIsPlaying(OpalStream* stream);
OPAL_DECL_FUNC_ND void opalStopStream(OpalStream* stream);
OPAL_DECL_FUNC void opalDestroyStream(OpalStream* stream);

#ifdef __cplusplus
}
#endif

#endif