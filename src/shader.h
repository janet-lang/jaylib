static Janet cfun_LoadShader(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    const char *vertexShaderFileName;
    const char *fragmentShaderFileName;
    if (janet_checktype(argv[0], JANET_NIL)) {
        vertexShaderFileName = NULL;
    } else {
        vertexShaderFileName = janet_getcstring(argv, 0);
    }
    if (janet_checktype(argv[1], JANET_NIL)) {
        fragmentShaderFileName = NULL;
    } else {
        fragmentShaderFileName = janet_getcstring(argv, 1);
    }
    Shader *shader = janet_abstract(&AT_Shader, sizeof(Shader));
    *shader = LoadShader(vertexShaderFileName, fragmentShaderFileName);
    return janet_wrap_abstract(shader);
}

static Janet cfun_UnloadShader(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Shader *shader = jaylib_getshader(argv, 0);
    UnloadShader(*shader);
    return janet_wrap_nil();
}

static Janet cfun_BeginShaderMode(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Shader *shader = jaylib_getshader(argv, 0);
    BeginShaderMode(*shader);
    return janet_wrap_nil();
}

static Janet cfun_EndShaderMode(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    EndShaderMode();
    return janet_wrap_nil();
}

static Janet cfun_GetShaderLocation(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Shader *shader = jaylib_getshader(argv, 0);
    const char *uniformName = janet_getcstring(argv, 1);
    int locIndex = GetShaderLocation(*shader, uniformName);
    return janet_wrap_integer(locIndex);
}

static Janet cfun_SetShaderValue(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Shader *shader = jaylib_getshader(argv, 0);
    int locIndex = janet_getinteger(argv, 1);
    int uniformType = jaylib_getuniformtype(argv, 3);
    switch (uniformType) {
        case SHADER_UNIFORM_FLOAT:
            float valueFloat = (float) janet_getnumber(argv, 2);
            SetShaderValue(*shader, locIndex, (const void*) &valueFloat, uniformType);
            break;
        case SHADER_UNIFORM_INT:
            int valueInt = janet_getinteger(argv, 2);
            SetShaderValue(*shader, locIndex, (const void*) &valueInt, uniformType);
            break;
        case SHADER_UNIFORM_VEC2:
            Vector2 valueVec2 = jaylib_getvec2(argv, 2);
            SetShaderValue(*shader, locIndex, (const void*) &valueVec2, uniformType);
            break;
        case SHADER_UNIFORM_VEC3:
            Vector3 valueVec3 = jaylib_getvec3(argv, 2);
            SetShaderValue(*shader, locIndex, (const void*) &valueVec3, uniformType);
            break;
        case SHADER_UNIFORM_VEC4:
            Vector4 valueVec4 = jaylib_getvec4(argv, 2);
            SetShaderValue(*shader, locIndex, (const void*) &valueVec4, uniformType);
            break;
        default:
            janet_panicf("unknown uniform type %d", uniformType);
            break;
    }
    return janet_wrap_nil();
}

static JanetReg shader_cfuns[] = {
    {"load-shader", cfun_LoadShader,
        "(loader-shader vertex-shader fragment-shader)\n\n"
        "Load shader from files and bind default locations"
    },
    {"unload-shader", cfun_UnloadShader,
        "(unloader-shader shader)\n\n"
        "Unload shader from GPU memory (VRAM)"
    },
    {"begin-shader-mode", cfun_BeginShaderMode,
        "(begin-shader-mode shader)\n\n"
        "Begin custom shader drawing"
    },
    {"end-shader-mode", cfun_EndShaderMode,
        "(end-shader-mode)\n\n"
        "End custom shader drawing (use default shader)"
    },
    {"get-shader-location", cfun_GetShaderLocation,
        "(set-shader-location shader uniform-name)\n\n"
        "Get shader uniform location"
    },
    {"set-shader-value", cfun_SetShaderValue,
        "(set-shader-value shader loc-index value uniform-type)\n\n"
        "Set shader uniform value"
    },
    {NULL, NULL, NULL}
};
