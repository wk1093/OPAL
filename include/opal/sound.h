#pragma once
#ifndef _OPAL_SOUND_H_
#define _OPAL_SOUND_H_

#include "pch.h"
#include "stream.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef OPAL_DECL_STRUCT struct {
    OpalStream* stream;
    void* buffer;
    uint64_t offset;
    uint64_t duration;
    uint64_t numFrames;
    uint64_t frameSize;
} OpalSound;

OPAL_DECL_FUNC_ND OpalSound* opalCreateSoundFromBuffer(void* buffer, uint64_t offset, uint64_t sampleRate, uint64_t duration, OpalSampleFormat format, uint64_t channels);
OPAL_DECL_FUNC_ND OpalResult opalPlaySound(OpalSound* sound);
OPAL_DECL_FUNC_ND OpalResult opalPlaySoundSync(OpalSound* sound);
OPAL_DECL_FUNC_ND bool opalSoundIsPlaying(OpalSound* sound);
OPAL_DECL_FUNC void opalStopSound(OpalSound* sound);
OPAL_DECL_FUNC void opalDestroySound(OpalSound* sound);


#ifdef __cplusplus
}
#endif

#endif