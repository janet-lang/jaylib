/* Wrappers for raylib types.
 * We provide facilities for creating instances of types,
 * as well as coercing standard Janet datastructures to types. This
 * lets us make an API that interacts well with Janet code. */


// Some Basic Colors
// NOTE: Custom raylib color palette for amazing visuals on WHITE background
#define _LIGHTGRAY_  { 200, 200, 200, 255 }   // Light Gray
#define _GRAY_       { 130, 130, 130, 255 }   // Gray
#define _DARKGRAY_   { 80, 80, 80, 255 }      // Dark Gray
#define _YELLOW_     { 253, 249, 0, 255 }     // Yellow
#define _GOLD_       { 255, 203, 0, 255 }     // Gold
#define _ORANGE_     { 255, 161, 0, 255 }     // Orange
#define _PINK_       { 255, 109, 194, 255 }   // Pink
#define _RED_        { 230, 41, 55, 255 }     // Red
#define _MAROON_     { 190, 33, 55, 255 }     // Maroon
#define _GREEN_      { 0, 228, 48, 255 }      // Green
#define _LIME_       { 0, 158, 47, 255 }      // Lime
#define _DARKGREEN_  { 0, 117, 44, 255 }      // Dark Green
#define _SKYBLUE_    { 102, 191, 255, 255 }   // Sky Blue
#define _BLUE_       { 0, 121, 241, 255 }     // Blue
#define _DARKBLUE_   { 0, 82, 172, 255 }      // Dark Blue
#define _PURPLE_     { 200, 122, 255, 255 }   // Purple
#define _VIOLET_     { 135, 60, 190, 255 }    // Violet
#define _DARKPURPLE_ { 112, 31, 126, 255 }    // Dark Purple
#define _BEIGE_      { 211, 176, 131, 255 }   // Beige
#define _BROWN_      { 127, 106, 79, 255 }    // Brown
#define _DARKBROWN_  { 76, 63, 47, 255 }      // Dark Brown

#define _WHITE_      { 255, 255, 255, 255 }   // White
#define _BLACK_      { 0, 0, 0, 255 }         // Black
#define _BLANK_      { 0, 0, 0, 0 }           // Blank (Transparent)
#define _MAGENTA_    { 255, 0, 255, 255 }     // Magenta
#define _RAYWHITE_   { 245, 245, 245, 255 }   // My own White (raylib logo)


/* Key map */
typedef struct {
    const char *name;
    int key;
} KeyDef;

/* Keep KeyDef arrays sorted */

static const KeyDef key_defs[] = {
    {"'", KEY_APOSTROPHE},
    {",", KEY_COMMA},
    {"-", KEY_MINUS},
    {".", KEY_PERIOD},
    {"/", KEY_SLASH},
    {"0", KEY_ZERO},
    {"1", KEY_ONE},
    {"2", KEY_TWO},
    {"3", KEY_THREE},
    {"4", KEY_FOUR},
    {"5", KEY_FIVE},
    {"6", KEY_SIX},
    {"7", KEY_SEVEN},
    {"8", KEY_EIGHT},
    {"9", KEY_NINE},
    {";", KEY_SEMICOLON},
    {"=", KEY_EQUAL},
    {"a", KEY_A},
    {"b", KEY_B},
    {"backslash", KEY_BACKSLASH},
    {"backspace", KEY_BACKSPACE},
    {"c", KEY_C},
    {"caps-lock", KEY_CAPS_LOCK},
    {"d", KEY_D},
    {"delete", KEY_DELETE},
    {"down", KEY_DOWN},
    {"e", KEY_E},
    {"end", KEY_END},
    {"enter", KEY_ENTER},
    {"escape", KEY_ESCAPE},
    {"f", KEY_F},
    {"f1", KEY_F1},
    {"f10", KEY_F10},
    {"f11", KEY_F11},
    {"f12", KEY_F12},
    {"f2", KEY_F2},
    {"f3", KEY_F3},
    {"f4", KEY_F4},
    {"f5", KEY_F5},
    {"f6", KEY_F6},
    {"f7", KEY_F7},
    {"f8", KEY_F8},
    {"f9", KEY_F9},
    {"g", KEY_G},
    {"grave", KEY_GRAVE},
    {"h", KEY_H},
    {"home", KEY_HOME},
    {"i", KEY_I},
    {"insert", KEY_INSERT},
    {"j", KEY_J},
    {"k", KEY_K},
    {"kb-menu", KEY_KB_MENU},
    {"kp-*", KEY_KP_MULTIPLY},
    {"kp-+", KEY_KP_ADD},
    {"kp--", KEY_KP_SUBTRACT},
    {"kp-.", KEY_KP_DECIMAL},
    {"kp-/", KEY_KP_DIVIDE},
    {"kp-0", KEY_KP_0},
    {"kp-1", KEY_KP_1},
    {"kp-2", KEY_KP_2},
    {"kp-3", KEY_KP_3},
    {"kp-4", KEY_KP_4},
    {"kp-5", KEY_KP_5},
    {"kp-6", KEY_KP_6},
    {"kp-7", KEY_KP_7},
    {"kp-8", KEY_KP_8},
    {"kp-9", KEY_KP_9},
    {"kp-=", KEY_KP_EQUAL},
    {"kp-enter", KEY_KP_ENTER},
    {"l", KEY_L},
    {"left", KEY_LEFT},
    {"left-alt", KEY_LEFT_ALT},
    {"left-bracket", KEY_LEFT_BRACKET},
    {"left-control", KEY_LEFT_CONTROL},
    {"left-shift", KEY_LEFT_SHIFT},
    {"left-super", KEY_LEFT_SUPER},
    {"m", KEY_M},
    {"n", KEY_N},
    {"num-lock", KEY_NUM_LOCK},
    {"o", KEY_O},
    {"p", KEY_P},
    {"page-down", KEY_PAGE_DOWN},
    {"page-up", KEY_PAGE_UP},
    {"pause", KEY_PAUSE},
    {"print-screen", KEY_PRINT_SCREEN},
    {"q", KEY_Q},
    {"r", KEY_R},
    {"right", KEY_RIGHT},
    {"right-alt", KEY_RIGHT_ALT},
    {"right-bracket", KEY_RIGHT_BRACKET},
    {"right-control", KEY_RIGHT_CONTROL},
    {"right-shift", KEY_RIGHT_SHIFT},
    {"right-super", KEY_RIGHT_SUPER},
    {"s", KEY_S},
    {"scroll-lock", KEY_SCROLL_LOCK},
    {"space", KEY_SPACE},
    {"t", KEY_T},
    {"tab", KEY_TAB},
    {"u", KEY_U},
    {"up", KEY_UP},
    {"v", KEY_V},
    {"w", KEY_W},
    {"x", KEY_X},
    {"y", KEY_Y},
    {"z", KEY_Z}
};

static const KeyDef button_defs[] = {
    {"left-face-down", GAMEPAD_BUTTON_LEFT_FACE_DOWN},
    {"left-face-left", GAMEPAD_BUTTON_LEFT_FACE_LEFT},
    {"left-face-right", GAMEPAD_BUTTON_LEFT_FACE_RIGHT},
    {"left-face-up", GAMEPAD_BUTTON_LEFT_FACE_UP},
    {"left-thumb", GAMEPAD_BUTTON_LEFT_THUMB},
    {"left-trigger-1", GAMEPAD_BUTTON_LEFT_TRIGGER_1},
    {"left-trigger-2", GAMEPAD_BUTTON_LEFT_TRIGGER_2},
    {"middle", GAMEPAD_BUTTON_MIDDLE},
    {"middle-left", GAMEPAD_BUTTON_MIDDLE_LEFT},
    {"middle-right", GAMEPAD_BUTTON_MIDDLE_RIGHT},
    {"right-face-down", GAMEPAD_BUTTON_RIGHT_FACE_DOWN},
    {"right-face-left", GAMEPAD_BUTTON_RIGHT_FACE_LEFT},
    {"right-face-right", GAMEPAD_BUTTON_RIGHT_FACE_RIGHT},
    {"right-face-up", GAMEPAD_BUTTON_RIGHT_FACE_UP},
    {"right-thumb", GAMEPAD_BUTTON_RIGHT_THUMB},
    {"right-trigger-1", GAMEPAD_BUTTON_RIGHT_TRIGGER_1},
    {"right-trigger-2", GAMEPAD_BUTTON_RIGHT_TRIGGER_2},
    {"unknown", GAMEPAD_BUTTON_UNKNOWN},
};

static const KeyDef axis_defs[] = {
    {"left-trigger", GAMEPAD_AXIS_LEFT_TRIGGER},
    {"left-x", GAMEPAD_AXIS_LEFT_X},
    {"left-y", GAMEPAD_AXIS_LEFT_Y},
    {"right-trigger", GAMEPAD_AXIS_RIGHT_TRIGGER},
    {"right-x", GAMEPAD_AXIS_RIGHT_X},
    {"right-y", GAMEPAD_AXIS_RIGHT_Y},
    {"unknown", GAMEPAD_BUTTON_UNKNOWN},
};

static const KeyDef mouse_defs[] = {
    {"left", MOUSE_LEFT_BUTTON},
    {"middle", MOUSE_MIDDLE_BUTTON},
    {"right", MOUSE_RIGHT_BUTTON}
};

static const KeyDef uniform_type_defs[] = {
    {"float", SHADER_UNIFORM_FLOAT},
    {"int", SHADER_UNIFORM_INT},
    {"vec2", SHADER_UNIFORM_VEC2},
    {"vec3", SHADER_UNIFORM_VEC3},
    {"vec4", SHADER_UNIFORM_VEC4}
};

static int jaylib_castdef(const Janet *argv, int32_t n, const KeyDef *defs, int count) {
    if (janet_checkint(argv[n])) {
        return janet_unwrap_integer(argv[n]);
    }
    const uint8_t *nameu = janet_getkeyword(argv, n);
    const char *name = (const char *)nameu;
    int hi = count - 1;
    int lo = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int cmp = strcmp(defs[mid].name, name);
        if (cmp < 0) {
            lo = mid + 1;
        } else if (cmp > 0) {
            hi = mid - 1;
        } else {
            return defs[mid].key;
        }
    }
    janet_panicf("unknown key :%s", name);
}

static int jaylib_getkey(const Janet *argv, int32_t n) {
    return jaylib_castdef(argv, n, key_defs, sizeof(key_defs) / sizeof(KeyDef));
}

static int jaylib_getbutton(const Janet *argv, int32_t n) {
    return jaylib_castdef(argv, n, button_defs, sizeof(button_defs) / sizeof(KeyDef));
}

static int jaylib_getaxis(const Janet *argv, int32_t n) {
    return jaylib_castdef(argv, n, axis_defs, sizeof(axis_defs) / sizeof(KeyDef));
}

static int jaylib_getmouse(const Janet *argv, int32_t n) {
    return jaylib_castdef(argv, n, mouse_defs, sizeof(mouse_defs) / sizeof(KeyDef));
}

static int jaylib_getuniformtype(const Janet *argv, int32_t n) {
    return jaylib_castdef(argv, n, uniform_type_defs, sizeof(uniform_type_defs) / sizeof(KeyDef));
}

struct named_color {
    const char *name;
    Color color;
};

const struct named_color named_colors[] = {
    {"beige", _BEIGE_},
    {"black", _BLACK_},
    {"blank", _BLANK_},
    {"blue", _BLUE_},
    {"brown", _BROWN_},
    {"dark-blue", _DARKBLUE_},
    {"dark-brown", _DARKBROWN_},
    {"dark-gray", _DARKGRAY_},
    {"dark-green", _DARKGREEN_},
    {"dark-purple", _DARKPURPLE_},
    {"gold", _GOLD_},
    {"gray", _GRAY_},
    {"green", _GREEN_},
    {"light-gray", _LIGHTGRAY_},
    {"lime", _LIME_},
    {"magenta", _MAGENTA_},
    {"maroon", _MAROON_},
    {"orange", _ORANGE_},
    {"pink", _PINK_},
    {"purple", _PURPLE_},
    {"ray-white", _RAYWHITE_},
    {"ray-white", _RAYWHITE_},
    {"red", _RED_},
    {"sky-blue", _SKYBLUE_},
    {"violet", _VIOLET_},
    {"white", _WHITE_},
    {"yellow",_YELLOW_},
};

static Color jaylib_getcolor(const Janet *argv, int32_t n) {
    Janet x = argv[n];
    const Janet *els = NULL;
    int32_t len = 0;
    if (janet_indexed_view(x, &els, &len)) {
        if (len == 3 || len == 4) {
            uint8_t r = (uint8_t) (janet_getnumber(els, 0) * 255);
            uint8_t g = (uint8_t) (janet_getnumber(els, 1) * 255);
            uint8_t b = (uint8_t) (janet_getnumber(els, 2) * 255);
            uint8_t a = (len == 4)
                ? (uint8_t)(janet_getnumber(els, 3) * 255)
                : 255;
            return (Color) { r, g, b, a };
        } else {
            janet_panicf("expected 3 or 4 color components, got %d", len);
        }
    } else if (janet_checktype(x, JANET_NUMBER)) {
        int64_t value = janet_getinteger64(argv, n);
        return (Color) {
            ((value >> 24)  & 0xFF),
            ((value >> 16)  & 0xFF),
            ((value >> 8)  & 0xFF),
            ((value >> 0)  & 0xFF)
        };
    } else {
        const uint8_t *nameu = janet_getkeyword(argv, n);
        const char *name = (const char *)nameu;
        int hi = (sizeof(named_colors) / sizeof(struct named_color)) - 1;
        int lo = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int cmp = strcmp(named_colors[mid].name, name);
            if (cmp < 0) {
                lo = mid + 1;
            } else if (cmp > 0) {
                hi = mid - 1;
            } else {
                return named_colors[mid].color;
            }
        }
        janet_panicf("unknown color :%s", name);
    }
}

static float idx_getfloat(JanetView idx, int index) {
    if (index >= idx.len) {
        janet_panicf("index %d outside of range [0, %d)", idx.len);
    }
    if (!janet_checktype(idx.items[index], JANET_NUMBER)) {
        janet_panicf("expected number, got %v", idx.items[index]);
    }
    return (float) janet_unwrap_number(idx.items[index]);
}

static Vector2 jaylib_getvec2(const Janet *argv, int32_t n) {
    JanetView idx = janet_getindexed(argv, n);
    return (Vector2) {
        idx_getfloat(idx, 0),
        idx_getfloat(idx, 1)
    };
}

static Vector3 jaylib_getvec3(const Janet *argv, int32_t n) {
    JanetView idx = janet_getindexed(argv, n);
    return (Vector3) {
        idx_getfloat(idx, 0),
        idx_getfloat(idx, 1),
        idx_getfloat(idx, 2)
    };
}

static Vector4 jaylib_getvec4(const Janet *argv, int32_t n) {
    JanetView idx = janet_getindexed(argv, n);
    return (Vector4) {
        idx_getfloat(idx, 0),
        idx_getfloat(idx, 1),
        idx_getfloat(idx, 2),
        idx_getfloat(idx, 3)
    };
}

static Rectangle jaylib_getrect(const Janet *argv, int32_t n) {
    JanetView idx = janet_getindexed(argv, n);
    return (Rectangle) {
        idx_getfloat(idx, 0),
        idx_getfloat(idx, 1),
        idx_getfloat(idx, 2),
        idx_getfloat(idx, 3)
    };
}

static Ray jaylib_getray(const Janet *argv, int32_t n) {
    JanetView idx = janet_getindexed(argv, n);
    if (idx.len < 2) {
        janet_panicf("ray needs a position and direction, got %v", argv[n]);
    }
    Vector3 p = jaylib_getvec3(idx.items, 0);
    Vector3 d = jaylib_getvec3(idx.items, 1);
    return (Ray){ p, d };
}

static const KeyDef pixel_format_defs[] = {
    {"astc-4x4-rgba", PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA},
    {"astc-8x8-rgba", PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA},
    {"dxt1-rgb", PIXELFORMAT_COMPRESSED_DXT1_RGB},
    {"dxt1-rgba", PIXELFORMAT_COMPRESSED_DXT1_RGBA},
    {"dxt3-rgba", PIXELFORMAT_COMPRESSED_DXT3_RGBA},
    {"dxt5-rgba", PIXELFORMAT_COMPRESSED_DXT5_RGBA},
    {"etc1-rgb", PIXELFORMAT_COMPRESSED_ETC1_RGB},
    {"etc2-eac_rgba", PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA},
    {"etc2-rgb", PIXELFORMAT_COMPRESSED_ETC2_RGB},
    {"gray-alpha", PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA},
    {"grayscale", PIXELFORMAT_UNCOMPRESSED_GRAYSCALE},
    {"pvrt-rgb", PIXELFORMAT_COMPRESSED_PVRT_RGB},
    {"pvrt-rgba", PIXELFORMAT_COMPRESSED_PVRT_RGBA},
    {"r32", PIXELFORMAT_UNCOMPRESSED_R32},
    {"r32g32b32", PIXELFORMAT_UNCOMPRESSED_R32G32B32},
    {"r32g32b32a32", PIXELFORMAT_UNCOMPRESSED_R32G32B32A32},
    {"r4g4b4a4", PIXELFORMAT_UNCOMPRESSED_R4G4B4A4},
    {"r5g5b5a1", PIXELFORMAT_UNCOMPRESSED_R5G5B5A1},
    {"r5g6b5", PIXELFORMAT_UNCOMPRESSED_R5G6B5},
    {"r8g8b8", PIXELFORMAT_UNCOMPRESSED_R8G8B8},
    {"r8g8b8a8", PIXELFORMAT_UNCOMPRESSED_R8G8B8A8}
};

static int jaylib_getpixelformat(const Janet *argv, int32_t n) {
    return jaylib_castdef(argv, n, pixel_format_defs, sizeof(pixel_format_defs) / sizeof(KeyDef));
}

static Janet jaylib_wrap_vec2(Vector2 x) {
    Janet *tup = janet_tuple_begin(2);
    tup[0] = janet_wrap_number(x.x);
    tup[1] = janet_wrap_number(x.y);
    return janet_wrap_tuple(janet_tuple_end(tup));
}

static Vector2 jaylib_unwrap_vec2(const Janet val) {
  JanetView view;
  if (!janet_indexed_view(val, &view.items, &view.len)) {
    janet_panic("expected vec to be an indexed type");
  }

  if (view.len != 2) {
    janet_panic("vec must have exactly 2 elements");
  }

  float x = idx_getfloat(view, 0);
  float y = idx_getfloat(view, 1);
  return (Vector2) { x, y };
}

static const JanetAbstractType AT_TextureCubemap = {
    "jaylib/texture-cubemap",
    JANET_ATEND_NAME
};

/*
static TextureCubemap *jaylib_gettexturecubemap(const Janet *argv, int32_t n) {
    return ((TextureCubemap *)janet_getabstract(argv, n, &AT_TextureCubemap));
}
*/
static const JanetAbstractType AT_Shader = {
    "jaylib/shader",
    JANET_ATEND_NAME
};

static Shader *jaylib_getshader(const Janet *argv, int32_t n) {
    return ((Shader *)janet_getabstract(argv, n, &AT_Shader));
};

static const JanetAbstractType AT_Texture2D = {
    "jaylib/texture2d",
    JANET_ATEND_NAME
};

static Texture2D *jaylib_gettexture2d(const Janet *argv, int32_t n) {
    return ((Texture2D *)janet_getabstract(argv, n, &AT_Texture2D));
}

static const JanetAbstractType AT_Image = {
    "jaylib/image",
    JANET_ATEND_NAME
};

static Image *jaylib_getimage(const Janet *argv, int32_t n) {
    return ((Image *)janet_getabstract(argv, n, &AT_Image));
}

static const JanetAbstractType AT_Wave = {
    "jaylib/wave",
    JANET_ATEND_NAME
};

static Wave *jaylib_getwave(const Janet *argv, int32_t n) {
    return ((Wave *)janet_getabstract(argv, n, &AT_Wave));
}

static const JanetAbstractType AT_Sound = {
    "jaylib/sound",
    JANET_ATEND_NAME
};

static Sound *jaylib_getsound(const Janet *argv, int32_t n) {
    return ((Sound *)janet_getabstract(argv, n, &AT_Sound));
}

static const JanetAbstractType AT_Music = {
    "jaylib/music",
    JANET_ATEND_NAME
};

static Music *jaylib_getmusic(const Janet *argv, int32_t n) {
    return ((Music *)janet_getabstract(argv, n, &AT_Music));
}

static const JanetAbstractType AT_AudioStream = {
    "jaylib/audio-stream",
    JANET_ATEND_NAME
};

static AudioStream *jaylib_getaudiostream(const Janet *argv, int32_t n) {
    return ((AudioStream *)janet_getabstract(argv, n, &AT_AudioStream));
}

static const JanetAbstractType AT_Font = {
    "jaylib/font",
    JANET_ATEND_NAME
};

static Font *jaylib_getfont(const Janet *argv, int32_t n) {
    return ((Font *)janet_getabstract(argv, n, &AT_Font));
}

static const JanetAbstractType AT_RenderTexture = {
    "jaylib/render-texture",
    JANET_ATEND_NAME
};

static RenderTexture *jaylib_getrendertexture(const Janet *argv, int32_t n) {
    return ((RenderTexture *)janet_getabstract(argv, n, &AT_RenderTexture));
}

int camera2d_get(void *p, Janet key, Janet *out);
void camera2d_put(void *p, Janet key, Janet value);

static const JanetAbstractType AT_Camera2D = {
    "jaylib/camera-2d",
    NULL,
    NULL,
    camera2d_get,
    camera2d_put,
    JANET_ATEND_PUT
};

static Camera2D *jaylib_getcamera2d(const Janet *argv, int32_t n) {
    return ((Camera2D *)janet_getabstract(argv, n, &AT_Camera2D));
}

int camera2d_get(void *p, Janet key, Janet *out) {
  Camera2D *camera = (Camera2D *)p;

  if (!janet_checktype(key, JANET_KEYWORD)) {
    janet_panic("expected keyword");
  }

  const uint8_t *kw = janet_unwrap_keyword(key);

  if (janet_cstrcmp(kw, "target")) {
    *out = jaylib_wrap_vec2(camera->target);
    return 1;
  }

  if (janet_cstrcmp(kw, "offset")) {
    *out = jaylib_wrap_vec2(camera->offset);
    return 1;
  }

  if (janet_cstrcmp(kw, "rotation")) {
    *out = janet_wrap_number(camera->rotation);
    return 1;
  }

  if (janet_cstrcmp(kw, "zoom")) {
    *out = janet_wrap_number(camera->zoom);
    return 1;
  }

  return 0;
}


void camera2d_put(void *p, Janet key, Janet value) {
  Camera2D *camera = (Camera2D *)p;

  if (!janet_checktype(key, JANET_KEYWORD)) {
    janet_panic("expected keyword key");
  }

  const uint8_t *kw = janet_unwrap_keyword(key);

  if (!janet_cstrcmp(kw, "target")) {
    camera->target = jaylib_unwrap_vec2(value);
  }

  if (!janet_cstrcmp(kw, "offset")) {
    camera->offset = jaylib_unwrap_vec2(value);
  }

  if (!janet_cstrcmp(kw, "rotation")) {
    if (!janet_checktype(value, JANET_NUMBER)) {
      janet_panic("expected number value");
    }

    camera->rotation = janet_unwrap_number(value);
  }

  if (!janet_cstrcmp(kw, "zoom")) {
    if (!janet_checktype(value, JANET_NUMBER)) {
      janet_panic("expected number value");
    }

    camera->zoom = janet_unwrap_number(value);
  }
}

static const JanetAbstractType AT_Camera3D = {
    "jaylib/camera-3d",
    JANET_ATEND_NAME
};

static Camera3D *jaylib_getcamera3d(const Janet *argv, int32_t n) {
    return ((Camera3D *)janet_getabstract(argv, n, &AT_Camera3D));
}
