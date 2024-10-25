#pragma once
#ifndef _OPAL_H_
#define _OPAL_H_

#include "opal/pch.h"

#include "opal/stream.h"
#include "opal/synth.h"
#include "opal/sound.h"

#ifdef __cplusplus
extern "C" {
#endif

OPAL_DECL_FUNC_ND OpalResult opalInit();
// OPAL_DECL_FUNC void opalErrorHandle(OpalResult result);
#define opalErrorHandle(result) if (result != OPAL_SUCCESS) { fprintf(stderr, "Error at %s:%d: %d\n", __FILE__, __LINE__, result); }
OPAL_DECL_FUNC_ND OpalResult opalTerminate();

#ifdef __cplusplus
}
#endif

#endif