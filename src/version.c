#include "opal/version.h"

const char* opalGetVersionString() {
    return "OPAL " HEDLEY_STRINGIFY(OPAL_VERSION_MAJOR) "." HEDLEY_STRINGIFY(OPAL_VERSION_MINOR) "." HEDLEY_STRINGIFY(OPAL_VERSION_PATCH);
}