#include <raylib.h>
#include <janet.h>

#include "types.h"

#include "core.h"
#include "shapes.h"
#include "audio.h"

JANET_MODULE_ENTRY(JanetTable *env) {
    janet_cfuns(env, "jaylib", core_cfuns);
    janet_cfuns(env, "jaylib", shapes_cfuns);
    janet_cfuns(env, "jaylib", audio_cfuns);
}
