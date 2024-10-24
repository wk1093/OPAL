#pragma once
#ifndef _OPAL_PCH_H_
#define _OPAL_PCH_H_

#include <hedley.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint16_t OpalResult; // just in case the counter goes above 255 (likely since we have a lot of different errors)

#define OPAL_SUCCESS 0

#define OPAL_FAILURE (__COUNTER__+1)

#define OPAL_NO_DISCARD HEDLEY_WARN_UNUSED_RESULT

#define OPAL_VERSION_NUMBER (OPAL_VERSION_MAJOR * 10000 + OPAL_VERSION_MINOR * 100 + OPAL_VERSION_PATCH)

#ifndef OPAL_DECL_FUNC

#define OPAL_DECL_FUNC HEDLEY_PUBLIC
#endif
#ifndef OPAL_DECL_STRUCT

#define OPAL_DECL_STRUCT
#endif
#ifndef OPAL_DECL_FUNC_ND

#define OPAL_DECL_FUNC_ND OPAL_DECL_FUNC OPAL_NO_DISCARD
#endif
#ifndef OPAL_DECL_VAR

#define OPAL_DECL_VAR HEDLEY_PUBLIC
#endif
#ifndef OPAL_DECL_ENUM

#define OPAL_DECL_ENUM
#endif

#ifdef __cplusplus
}
#endif

#endif