/* Wrappers for raylib types.
 * We provide facilities for creating instances of types,
 * as well as coercing standard Janet datastructures to types. This
 * lets us make an API that interacts well with Janet code. */

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
    {"l", KEY_K},
    {"left", KEY_LEFT},
    {"left-alt", KEY_LEFT_ALT},
    {"left-bracket", KEY_LEFT_BRACKET},
    {"left-control", KEY_LEFT_CONTROL},
    {"left-shift", KEY_LEFT_SHIFT},
    {"left-super", KEY_LEFT_SUPER},
    {"m", KEY_K},
    {"n", KEY_K},
    {"num-lock", KEY_NUM_LOCK},
    {"o", KEY_K},
    {"p", KEY_K},
    {"page-down", KEY_PAGE_DOWN},
    {"page-up", KEY_PAGE_UP},
    {"pause", KEY_PAUSE},
    {"print-screen", KEY_PRINT_SCREEN},
    {"q", KEY_K},
    {"r", KEY_K},
    {"right", KEY_RIGHT},
    {"right-alt", KEY_RIGHT_ALT},
    {"right-bracket", KEY_RIGHT_BRACKET},
    {"right-control", KEY_RIGHT_CONTROL},
    {"right-shift", KEY_RIGHT_SHIFT},
    {"right-super", KEY_RIGHT_SUPER},
    {"s", KEY_K},
    {"scroll-lock", KEY_SCROLL_LOCK},
    {"space", KEY_SPACE},
    {"t", KEY_K},
    {"tab", KEY_TAB},
    {"u", KEY_K},
    {"up", KEY_UP},
    {"v", KEY_K},
    {"w", KEY_K},
    {"x", KEY_K},
    {"y", KEY_K},
    {"z", KEY_K}
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
    {"unknown", GAMEPAD_AXIS_UNKNOWN},
};

static const KeyDef mouse_defs[] = {
    {"left", MOUSE_LEFT_BUTTON},
    {"middle", MOUSE_MIDDLE_BUTTON},
    {"right", MOUSE_RIGHT_BUTTON}
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

static int jaylib_castkey(const Janet *argv, int32_t n) {
    return jaylib_castdef(argv, n, key_defs, sizeof(key_defs) / sizeof(KeyDef));
}

static int jaylib_castbutton(const Janet *argv, int32_t n) {
    return jaylib_castdef(argv, n, button_defs, sizeof(button_defs) / sizeof(KeyDef));
}

static int jaylib_castaxis(const Janet *argv, int32_t n) {
    return jaylib_castdef(argv, n, axis_defs, sizeof(axis_defs) / sizeof(KeyDef));
}

static int jaylib_castmouse(const Janet *argv, int32_t n) {
    return jaylib_castdef(argv, n, mouse_defs, sizeof(mouse_defs) / sizeof(KeyDef));
}

struct named_color {
    const char *name;
    Color color;
};

const struct named_color named_colors[] = {
    {"beige", BEIGE},
    {"black", BLACK},
    {"blank", BLANK},
    {"blue", BLUE},
    {"brown", BROWN},
    {"dark-blue", DARKBLUE},
    {"dark-brown", DARKBROWN},
    {"dark-gray", DARKGRAY},
    {"dark-green", DARKGREEN},
    {"dark-purple", DARKPURPLE},
    {"gold", GOLD},
    {"gray", GRAY},
    {"green", GREEN},
    {"light-gray", LIGHTGRAY},
    {"lime", LIME},
    {"magenta", MAGENTA},
    {"maroon", MAROON},
    {"orange", ORANGE},
    {"pink", PINK},
    {"purple", PURPLE},
    {"ray-white", RAYWHITE},
    {"ray-white", RAYWHITE},
    {"red", RED},
    {"sky-blue", SKYBLUE},
    {"violet", VIOLET},
    {"white", WHITE},
    {"yellow",YELLOW},
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
            ((value >> 0)  & 0xFF),
            ((value >> 8)  & 0xFF),
            ((value >> 16) & 0xFF),
            ((value >> 24) & 0xFF)
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

static float dict_getfloat(Janet dict, const char *key, float dflt) {
    Janet v = janet_get(dict, janet_ckeywordv(key));
    if (janet_checktype(v, JANET_NIL)) {
        return dflt;
    }
    if (!janet_checktype(v, JANET_NUMBER)) {
        janet_panicf("expected number, got %v for key :%s", v, key);
    }
    return (float) janet_unwrap_number(v);
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

static Vector2 jaylib_castvec2(Janet x) {
    JanetView idx;
    if (!janet_indexed_view(x, &idx.items, &idx.len)) {
        if (janet_checktype(x, JANET_NIL)) return (Vector2) {0};
        janet_panicf("expected tuple|array, got %v", x);
    }
    return (Vector2) {
        idx_getfloat(idx, 0),
        idx_getfloat(idx, 1)
    };
}

static Vector2 jaylib_getvec2(const Janet *argv, int32_t n) {
    JanetView idx = janet_getindexed(argv, n);
    return (Vector2) {
        idx_getfloat(idx, 0),
        idx_getfloat(idx, 1)
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

static const KeyDef pixel_format_defs[] = {
    {"astc-4x4-rgba", COMPRESSED_ASTC_4x4_RGBA},
    {"astc-8x8-rgba", COMPRESSED_ASTC_8x8_RGBA},
    {"dxt1-rgb", COMPRESSED_DXT1_RGB},
    {"dxt1-rgba", COMPRESSED_DXT1_RGBA},
    {"dxt3-rgba", COMPRESSED_DXT3_RGBA},
    {"dxt5-rgba", COMPRESSED_DXT5_RGBA},
    {"etc1-rgb", COMPRESSED_ETC1_RGB},
    {"etc2-eac_rgba", COMPRESSED_ETC2_EAC_RGBA},
    {"etc2-rgb", COMPRESSED_ETC2_RGB},
    {"gray-alpha", UNCOMPRESSED_GRAY_ALPHA},
    {"grayscale", UNCOMPRESSED_GRAYSCALE},
    {"pvrt-rgb", COMPRESSED_PVRT_RGB},
    {"pvrt-rgba", COMPRESSED_PVRT_RGBA},
    {"r32", UNCOMPRESSED_R32},
    {"r32g32b32", UNCOMPRESSED_R32G32B32},
    {"r32g32b32a32", UNCOMPRESSED_R32G32B32A32},
    {"r4g4b4a4", UNCOMPRESSED_R4G4B4A4},
    {"r5g5b5a1", UNCOMPRESSED_R5G5B5A1},
    {"r5g6b5", UNCOMPRESSED_R5G6B5},
    {"r8g8b8", UNCOMPRESSED_R8G8B8},
    {"r8g8b8a8", UNCOMPRESSED_R8G8B8A8}
};

static int jaylib_getpixelformat(const Janet *argv, int32_t n) {
    return jaylib_castdef(argv, n, pixel_format_defs, sizeof(pixel_format_defs) / sizeof(KeyDef));
}

/*
static Vector3 jaylib_castvec3(Janet x) {
    JanetView idx;
    if (!janet_indexed_view(x, &idx.items, &idx.len)) {
        if (janet_checktype(x, JANET_NIL)) return (Vector3) {0};
        janet_panicf("expected tuple|array, got %v", x);
    }
    return (Vector3) {
        idx_getfloat(idx, 0),
        idx_getfloat(idx, 1),
        idx_getfloat(idx, 2)
    };
}

static Vector4 jaylib_castvec4(Janet x) {
    JanetView idx;
    if (!janet_indexed_view(x, &idx.items, &idx.len)) {
        if (janet_checktype(x, JANET_NIL)) return (Vector4) {0};
        janet_panicf("expected tuple|array, got %v", x);
    }
    return (Vector4) {
        idx_getfloat(idx, 0),
        idx_getfloat(idx, 1),
        idx_getfloat(idx, 2),
        idx_getfloat(idx, 3)
    };
}
*/

static Janet jget(Janet dict, const char *key) {
    return janet_get(dict, janet_ckeywordv(key));
}

static Camera2D jaylib_getcamera2d(const Janet *argv, int32_t n) {
    Camera2D ret = {0};
    Janet dict = argv[n];
    ret.target = jaylib_castvec2(jget(dict, "target"));
    ret.offset = jaylib_castvec2(jget(dict, "offset"));
    ret.rotation = dict_getfloat(dict, "rotation", 0.0f);
    ret.zoom = dict_getfloat(dict, "zoom", 1.0f);
    return ret;
}

static Janet jaylib_uncastvec2(Vector2 x) {
    Janet *tup = janet_tuple_begin(2);
    tup[0] = janet_wrap_integer(x.x);
    tup[1] = janet_wrap_integer(x.y);
    return janet_wrap_tuple(janet_tuple_end(tup));
}

static const JanetAbstractType AT_TextureCubemap = {
    "jaylib/texture-cubemap",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

/*
static TextureCubemap *jaylib_gettexturecubemap(const Janet *argv, int32_t n) {
    return ((TextureCubemap *)janet_getabstract(argv, n, &AT_TextureCubemap));
}
*/

static const JanetAbstractType AT_Texture2D = {
    "jaylib/texture2d",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static Texture2D *jaylib_gettexture2d(const Janet *argv, int32_t n) {
    return ((Texture2D *)janet_getabstract(argv, n, &AT_Texture2D));
}

static const JanetAbstractType AT_Image = {
    "jaylib/image",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static Image *jaylib_getimage(const Janet *argv, int32_t n) {
    return ((Image *)janet_getabstract(argv, n, &AT_Image));
}

static const JanetAbstractType AT_Wave = {
    "jaylib/wave",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static Wave *jaylib_getwave(const Janet *argv, int32_t n) {
    return ((Wave *)janet_getabstract(argv, n, &AT_Wave));
}

static const JanetAbstractType AT_Sound = {
    "jaylib/sound",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static Sound *jaylib_getsound(const Janet *argv, int32_t n) {
    return ((Sound *)janet_getabstract(argv, n, &AT_Sound));
}

static const JanetAbstractType AT_Music = {
    "jaylib/music",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static Music *jaylib_getmusic(const Janet *argv, int32_t n) {
    return ((Music *)janet_getabstract(argv, n, &AT_Music));
}

static const JanetAbstractType AT_AudioStream = {
    "jaylib/audio-stream",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static AudioStream *jaylib_getaudiostream(const Janet *argv, int32_t n) {
    return ((AudioStream *)janet_getabstract(argv, n, &AT_AudioStream));
}

static const JanetAbstractType AT_Font = {
    "jaylib/font",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static Font *jaylib_getfont(const Janet *argv, int32_t n) {
    return ((Font *)janet_getabstract(argv, n, &AT_Font));
}

static const JanetAbstractType AT_RenderTexture = {
    "jaylib/render-texture",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static RenderTexture *jaylib_getrendertexture(const Janet *argv, int32_t n) {
    return ((RenderTexture *)janet_getabstract(argv, n, &AT_RenderTexture));
}
