#include <raylib.h>
#include <rlgl.h>
#include <janet.h>

#include "types.h"

#include "core.h"
#include "shapes.h"
#include "audio.h"
#include "gestures.h"
#include "text.h"
#include "image.h"
#include "3d.h"
#include "rlgl.h"
#include "shader.h"
#include "math.h"

JANET_MODULE_ENTRY(JanetTable *env) {
    janet_cfuns(env, "jaylib", core_cfuns);
    janet_cfuns(env, "jaylib", shapes_cfuns);
    janet_cfuns(env, "jaylib", audio_cfuns);
    janet_cfuns(env, "jaylib", gesture_cfuns);
    janet_cfuns(env, "jaylib", text_cfuns);
    janet_cfuns(env, "jaylib", image_cfuns);
    janet_cfuns(env, "jaylib", threed_cfuns);
    janet_cfuns(env, "jaylib", rlgl_cfuns);
    janet_cfuns(env, "jaylib", shader_cfuns);
    janet_cfuns(env, "jaylib", math_cfuns);
}
