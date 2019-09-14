#include <raylib.h>
#include <janet.h>

#include "types.h"

#include "core.h"
#include "shapes.h"

JANET_MODULE_ENTRY(JanetTable *env) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    janet_cfuns(env, "jaylib", core_cfuns);
    janet_cfuns(env, "jaylib", shapes_cfuns);
}
