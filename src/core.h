static Janet cfun_InitWindow(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    int32_t width = janet_getinteger(argv, 0);
    int32_t height = janet_getinteger(argv, 1);
    const char *name = janet_getcstring(argv, 2);
    InitWindow(width, height, name);
    return janet_wrap_nil();
}

static Janet cfun_WindowShouldClose(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_boolean(WindowShouldClose());
}

static Janet cfun_CloseWindow(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    CloseWindow();
    return janet_wrap_nil();
}

static Janet cfun_IsWindowReady(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_boolean(IsWindowReady());
}

static Janet cfun_IsWindowMinimized(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_boolean(IsWindowMinimized());
}

static Janet cfun_IsWindowResized(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_boolean(IsWindowResized());
}

static const KeyDef after_init_flag_defs[] = {
    {"vsync-hint", FLAG_VSYNC_HINT},
    {"fullscreen-mode", FLAG_FULLSCREEN_MODE},
    {"window-resizable", FLAG_WINDOW_RESIZABLE},
    {"window-undecorated", FLAG_WINDOW_UNDECORATED},
    {"window-hidden", FLAG_WINDOW_HIDDEN},
    {"window-minimized", FLAG_WINDOW_MINIMIZED},
    {"window-maximized", FLAG_WINDOW_MAXIMIZED},
    {"window-unfocused", FLAG_WINDOW_UNFOCUSED},
    {"window-topmost", FLAG_WINDOW_TOPMOST},
    {"window-always-run", FLAG_WINDOW_ALWAYS_RUN}
};

static Janet cfun_IsWindowState(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const uint8_t *arg_flag = janet_getkeyword(argv, 0);
    int flag = 0;
    for (unsigned j = 0; j < (sizeof(after_init_flag_defs) / sizeof(KeyDef)); j++) {
      if (!janet_cstrcmp(arg_flag, after_init_flag_defs[j].name)) {
	flag = after_init_flag_defs[j].key;
	break;
      }
    }
    if (0 == flag) {
      JanetArray *available = janet_array(0);
      for (unsigned j = 0; j < (sizeof(after_init_flag_defs) / sizeof(KeyDef)); j++) {
	janet_array_push(available, janet_ckeywordv(after_init_flag_defs[j].name));
      }
      janet_panicf("unknown flag %v - available flags are %p", argv[0],
		   janet_wrap_array(available));
    }

    return janet_wrap_boolean(IsWindowState(flag));
}

static Janet cfun_SetWindowState(int32_t argc, Janet *argv) {
    janet_arity(argc, 0, -1);
    unsigned int flags = 0;
    for (int32_t i = 0; i < argc; i++) {
        const uint8_t *arg_flag = janet_getkeyword(argv, i);
        /* Linear scan through after_init_flag_defs to find entry for arg_flag */
        unsigned int flag = 0;
        for (unsigned j = 0; j < (sizeof(after_init_flag_defs) / sizeof(KeyDef)); j++) {
	  if (!janet_cstrcmp(arg_flag, after_init_flag_defs[j].name)) {
	    flag = (unsigned int) after_init_flag_defs[j].key;
                break;
            }
        }
        if (0 == flag) {
            JanetArray *available = janet_array(0);
            for (unsigned j = 0; j < (sizeof(after_init_flag_defs) / sizeof(KeyDef)); j++) {
                janet_array_push(available, janet_ckeywordv(after_init_flag_defs[j].name));
            }
            janet_panicf("unknown flag %v - available flags are %p", argv[i],
                    janet_wrap_array(available));
        }
        flags |= flag;
    }
    SetWindowState(flags);
    return janet_wrap_nil();
}

static Janet cfun_ClearWindowState(int32_t argc, Janet *argv) {
    janet_arity(argc, 0, -1);
    unsigned int flags = 0;
    for (int32_t i = 0; i < argc; i++) {
        const uint8_t *arg_flag = janet_getkeyword(argv, i);
        /* Linear scan through after_init_flag_defs to find entry for arg_flag */
        unsigned int flag = 0;
        for (unsigned j = 0; j < (sizeof(after_init_flag_defs) / sizeof(KeyDef)); j++) {
            if (!janet_cstrcmp(arg_flag, after_init_flag_defs[j].name)) {
                flag = (unsigned int) after_init_flag_defs[j].key;
                break;
            }
        }
        if (0 == flag) {
            JanetArray *available = janet_array(0);
            for (unsigned j = 0; j < (sizeof(after_init_flag_defs) / sizeof(KeyDef)); j++) {
                janet_array_push(available, janet_ckeywordv(after_init_flag_defs[j].name));
            }
            janet_panicf("unknown flag %v - available flags are %p", argv[i],
                    janet_wrap_array(available));
        }
        flags |= flag;
    }
    ClearWindowState(flags);
    return janet_wrap_nil();
}

static Janet cfun_ToggleFullscreen(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    ToggleFullscreen();
    return janet_wrap_nil();
}

static Janet cfun_SetWindowTitle(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *title = janet_getcstring(argv, 0);
    SetWindowTitle(title);
    return janet_wrap_nil();
}

static Janet cfun_SetWindowPosition(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int x = janet_getinteger(argv, 0);
    int y = janet_getinteger(argv, 1);
    SetWindowPosition(x, y);
    return janet_wrap_nil();
}

static Janet cfun_SetWindowMonitor(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int monitor = janet_getinteger(argv, 0);
    SetWindowMonitor(monitor);
    return janet_wrap_nil();
}

static Janet cfun_SetWindowMinSize(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int width = janet_getinteger(argv, 0);
    int height = janet_getinteger(argv, 1);
    SetWindowMinSize(width, height);
    return janet_wrap_nil();
}

static Janet cfun_SetWindowSize(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int width = janet_getinteger(argv, 0);
    int height = janet_getinteger(argv, 1);
    SetWindowSize(width, height);
    return janet_wrap_nil();
}

static Janet cfun_GetWindowHandle(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_pointer(GetWindowHandle());
}

static Janet cfun_GetScreenWidth(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_integer(GetScreenWidth());
}

static Janet cfun_GetScreenHeight(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_integer(GetScreenHeight());
}

static Janet cfun_GetMonitorCount(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_integer(GetMonitorCount());
}

static Janet cfun_GetMonitorWidth(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int monitor = janet_getinteger(argv, 0);
    return janet_wrap_integer(GetMonitorWidth(monitor));
}

static Janet cfun_GetMonitorHeight(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int monitor = janet_getinteger(argv, 0);
    return janet_wrap_integer(GetMonitorHeight(monitor));
}

static Janet cfun_GetMonitorPhysicalWidth(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int monitor = janet_getinteger(argv, 0);
    return janet_wrap_integer(GetMonitorPhysicalWidth(monitor));
}

static Janet cfun_GetMonitorPhysicalHeight(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int monitor = janet_getinteger(argv, 0);
    return janet_wrap_integer(GetMonitorPhysicalHeight(monitor));
}

static Janet cfun_GetMonitorName(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int monitor = janet_getinteger(argv, 0);
    return janet_cstringv(GetMonitorName(monitor));
}

static Janet cfun_GetClipboardText(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_cstringv(GetClipboardText());
}

static Janet cfun_SetClipboardText(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *text = janet_getcstring(argv, 0);
    SetClipboardText(text);
    return janet_wrap_nil();
}

static Janet cfun_ShowCursor(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    ShowCursor();
    return janet_wrap_nil();
}

static Janet cfun_HideCursor(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    HideCursor();
    return janet_wrap_nil();
}

static Janet cfun_IsCursorHidden(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_boolean(IsCursorHidden());
}

static Janet cfun_EnableCursor(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    EnableCursor();
    return janet_wrap_nil();
}

static Janet cfun_DisableCursor(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    DisableCursor();
    return janet_wrap_nil();
}

static Janet cfun_IsCursorOnScreen(int32_t argc, Janet *argv) {
	(void) argv;
	janet_fixarity(argc, 0);
	return janet_wrap_boolean(IsCursorOnScreen());
}

static Janet cfun_ClearBackground(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Color color = jaylib_getcolor(argv, 0);
    ClearBackground(color);
    return janet_wrap_nil();
}

static Janet cfun_BeginDrawing(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    BeginDrawing();
    return janet_wrap_nil();
}

static Janet cfun_EndDrawing(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    EndDrawing();
    return janet_wrap_nil();
}

static Janet cfun_BeginMode2D(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    BeginMode2D(*jaylib_getcamera2d(argv, 0));
    return  janet_wrap_nil();
}

static Janet cfun_EndMode2D(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    EndMode2D();
    return janet_wrap_nil();
}

static Janet cfun_SetTargetFPS(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int fps = janet_getinteger(argv, 0);
    SetTargetFPS(fps);
    return janet_wrap_nil();
}

static Janet cfun_GetFPS(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_integer(GetFPS());
}

static Janet cfun_GetFrameTime(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_number(GetFrameTime());
}

/* Some raylib versions don't have all of these flags */
static const KeyDef flag_defs[] = {
    {"vsync-hint", FLAG_VSYNC_HINT},
    {"fullscreen-mode", FLAG_FULLSCREEN_MODE},
    {"window-resizable", FLAG_WINDOW_RESIZABLE},
    {"window-undecorated", FLAG_WINDOW_UNDECORATED},
    {"window-hidden", FLAG_WINDOW_HIDDEN},
    {"window-minimized", FLAG_WINDOW_MINIMIZED},
    {"window-maximized", FLAG_WINDOW_MAXIMIZED},
    {"window-unfocused", FLAG_WINDOW_UNFOCUSED},
    {"window-topmost", FLAG_WINDOW_TOPMOST},
    {"window-always-run", FLAG_WINDOW_ALWAYS_RUN},
    {"window-transparent", FLAG_WINDOW_TRANSPARENT},
    {"window-highdpi", FLAG_WINDOW_HIGHDPI},
    {"interlaced-hint", FLAG_INTERLACED_HINT},
    {"msaa-4x-hint", FLAG_MSAA_4X_HINT}
};

static Janet cfun_SetConfigFlags(int32_t argc, Janet *argv) {
    janet_arity(argc, 0, -1);
    unsigned int flags = 0;
    for (int32_t i = 0; i < argc; i++) {
        const uint8_t *arg_flag = janet_getkeyword(argv, i);
        /* Linear scan through flag_defs to find entry for arg_flag */
        unsigned int flag = 0;
        for (unsigned j = 0; j < (sizeof(flag_defs) / sizeof(KeyDef)); j++) {
            if (!janet_cstrcmp(arg_flag, flag_defs[j].name)) {
                flag = (unsigned int) flag_defs[j].key;
                break;
            }
        }
        if (0 == flag) {
            JanetArray *available = janet_array(0);
            for (unsigned j = 0; j < (sizeof(flag_defs) / sizeof(KeyDef)); j++) {
                janet_array_push(available, janet_ckeywordv(flag_defs[j].name));
            }
            janet_panicf("unknown flag %v - available flags are %p", argv[i],
                    janet_wrap_array(available));
        }
        flags |= flag;
    }
    SetConfigFlags(flags);
    return janet_wrap_nil();
}

static const KeyDef log_defs[] = {
    {"all", LOG_ALL},
    {"trace", LOG_TRACE},
    {"debug", LOG_DEBUG},
    {"info", LOG_INFO},
    {"warning", LOG_WARNING},
    {"error", LOG_ERROR},
    {"fatal", LOG_FATAL},
    {"none", LOG_NONE}
};

static int jaylib_getlogtype(const Janet *argv, int32_t n) {
    const uint8_t *kw = janet_getkeyword(argv, n);
    for (int i = 0; i <= LOG_NONE; i++) {
        if (!janet_cstrcmp(kw, log_defs[i].name))
            return log_defs[i].key;
    }
    janet_panicf("unknown log type %v", argv[n]);
}

static Janet cfun_SetTraceLogLevel(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int logType = jaylib_getlogtype(argv, 0);
    SetTraceLogLevel(logType);
    return janet_wrap_nil();
}

/* Global C callback */
static JanetFunction *jaylib_tracelog_closure = NULL;

static void jaylib_tracelog_callback(int logType, const char *text, va_list args) {
    Janet argv[2];
    argv[0] = janet_ckeywordv(log_defs[logType].name);
    char buf[256];
    va_list args2;
    va_copy(args2, args);
    int len = vsnprintf(buf, sizeof(buf), text, args);
    if (len < 0) return;
    if (len >= 256) {
        uint8_t *long_buf = janet_string_begin(len);
        vsnprintf((char *) long_buf, len, text, args2);
        argv[1] = janet_wrap_string(janet_string_end(long_buf));
    } else {
        argv[1] = janet_cstringv(buf);
    }
    Janet out = janet_wrap_nil();
    JanetFiber *fiber = NULL;
    int sign = janet_pcall(jaylib_tracelog_closure, 2, argv, &out, &fiber);
    if (sign != JANET_SIGNAL_OK) {
        janet_stacktrace(fiber, out);
    }
}

static Janet cfun_SetTraceLogCallback(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    JanetFunction *f;
    if (janet_checktype(argv[0], JANET_NIL)) {
        f = NULL;
    } else {
        f = janet_getfunction(argv, 0);
    }
    if (NULL != jaylib_tracelog_closure) {
        janet_gcunroot(janet_wrap_function(jaylib_tracelog_closure));
    }
    jaylib_tracelog_closure = f;
    if (f) {
        janet_gcroot(janet_wrap_function(jaylib_tracelog_closure));
        SetTraceLogCallback(jaylib_tracelog_callback);
    } else {
        SetTraceLogCallback(NULL);
    }
    return janet_wrap_nil();
}

static Janet cfun_TraceLog(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int logType = jaylib_getlogtype(argv, 0);
    const char *s = janet_getcstring(argv, 1);
    TraceLog(logType, "%s", s);
    return janet_wrap_nil();
}

static Janet cfun_TakeScreenshot(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *fileName = janet_getcstring(argv, 0);
    TakeScreenshot(fileName);
    return janet_wrap_nil();
}

static Janet cfun_GetTime(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_number(GetTime());
}

static Janet cfun_IsKeyPressed(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int key = jaylib_getkey(argv, 0);
    return janet_wrap_boolean(IsKeyPressed(key));
}

static Janet cfun_IsKeyDown(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int key = jaylib_getkey(argv, 0);
    return janet_wrap_boolean(IsKeyDown(key));
}

static Janet cfun_IsKeyUp(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int key = jaylib_getkey(argv, 0);
    return janet_wrap_boolean(IsKeyUp(key));
}

static Janet cfun_IsKeyReleased(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int key = jaylib_getkey(argv, 0);
    return janet_wrap_boolean(IsKeyReleased(key));
}

static Janet cfun_GetKeyPressed(int32_t argc, Janet *argv) {
    (void) argv;
    janet_arity(argc, 0, 1);
    int key = GetKeyPressed();
    if (argc == 0 || !janet_truthy(argv[1])) {
        for (unsigned i = 0; i < (sizeof(key_defs) / sizeof(KeyDef)); i++) {
            if (key_defs[i].key == key)
                return janet_ckeywordv(key_defs[i].name);
        }
    }
    return janet_wrap_integer(key);
}

static Janet cfun_SetExitKey(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int key = jaylib_getkey(argv, 0);
    SetExitKey(key);
    return janet_wrap_nil();
}

static Janet cfun_IsGamepadAvailable(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int gamepad = janet_getinteger(argv, 0);
    return janet_wrap_boolean(IsGamepadAvailable(gamepad));
}

static Janet cfun_GetGamepadName(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int gamepad = janet_getinteger(argv, 0);
    return janet_cstringv(GetGamepadName(gamepad));
}

static Janet cfun_IsGamepadButtonDown(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int gamepad = janet_getinteger(argv, 0);
    int button = jaylib_getbutton(argv, 1);
    return janet_wrap_boolean(IsGamepadButtonDown(gamepad, button));
}

static Janet cfun_IsGamepadButtonReleased(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int gamepad = janet_getinteger(argv, 0);
    int button = jaylib_getbutton(argv, 1);
    return janet_wrap_boolean(IsGamepadButtonReleased(gamepad, button));
}

static Janet cfun_IsGamepadButtonUp(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int gamepad = janet_getinteger(argv, 0);
    int button = jaylib_getbutton(argv, 1);
    return janet_wrap_boolean(IsGamepadButtonUp(gamepad, button));
}

static Janet cfun_IsGamepadButtonPressed(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int gamepad = janet_getinteger(argv, 0);
    int button = jaylib_getbutton(argv, 1);
    return janet_wrap_boolean(IsGamepadButtonPressed(gamepad, button));
}

static Janet cfun_GetGamepadButtonPressed(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_integer(GetGamepadButtonPressed());
}

static Janet cfun_GetGamepadAxisCount(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int gamepad = janet_getinteger(argv, 0);
    return janet_wrap_integer(GetGamepadAxisCount(gamepad));
}

static Janet cfun_GetGamepadAxisMovement(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int gamepad = janet_getinteger(argv, 0);
    int axis = jaylib_getaxis(argv, 1);
    return janet_wrap_number((double) GetGamepadAxisMovement(gamepad, axis));
}

static Janet cfun_IsMouseButtonPressed(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int button = jaylib_getmouse(argv, 0);
    return janet_wrap_boolean(IsMouseButtonPressed(button));
}

static Janet cfun_IsMouseButtonDown(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int button = jaylib_getmouse(argv, 0);
    return janet_wrap_boolean(IsMouseButtonDown(button));
}

static Janet cfun_IsMouseButtonReleased(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int button = jaylib_getmouse(argv, 0);
    return janet_wrap_boolean(IsMouseButtonReleased(button));
}

static Janet cfun_IsMouseButtonUp(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int button = jaylib_getmouse(argv, 0);
    return janet_wrap_boolean(IsMouseButtonUp(button));
}

static Janet cfun_GetMouseX(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_integer(GetMouseX());
}

static Janet cfun_GetMouseY(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_integer(GetMouseY());
}

static Janet cfun_GetMousePosition(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    Vector2 pos = GetMousePosition();
    return jaylib_wrap_vec2(pos);
}

static Janet cfun_SetMousePosition(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int x = janet_getinteger(argv, 0);
    int y = janet_getinteger(argv, 1);
    SetMousePosition(x, y);
    return janet_wrap_nil();
}

static Janet cfun_SetMouseOffset(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int x = janet_getinteger(argv, 0);
    int y = janet_getinteger(argv, 1);
    SetMouseOffset(x, y);
    return janet_wrap_nil();
}

static Janet cfun_SetMouseScale(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    float x = (float) janet_getnumber(argv, 0);
    float y = (float) janet_getnumber(argv, 1);
    SetMouseScale(x, y);
    return janet_wrap_nil();
}

static Janet cfun_GetMouseWheelMove(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_number(GetMouseWheelMove());
}

static Janet cfun_GetTouchX(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_integer(GetTouchX());
}

static Janet cfun_GetTouchY(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_integer(GetTouchY());
}

static Janet cfun_GetTouchPosition(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int index = janet_getinteger(argv, 0);
    Vector2 pos = GetTouchPosition(index);
    return jaylib_wrap_vec2(pos);
}

static Janet cfun_GetDroppedFiles(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    int count;
    /* Do we need to free this/these? */
    char **results = GetDroppedFiles(&count);
    JanetArray *array = janet_array(0);
    for (int i = 0; i < count; i++) {
        janet_array_push(array, janet_cstringv(results[i]));
    }
    return janet_wrap_array(results);
}

static Janet cfun_ClearDroppedFiles(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    ClearDroppedFiles();
    return janet_wrap_nil();
}

static Janet cfun_SaveStorageValue(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int32_t position = janet_getinteger(argv, 0);
    int32_t value = janet_getinteger(argv, 1);
    SaveStorageValue(position, value);
    return janet_wrap_nil();
}

static Janet cfun_LoadStorageValue(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int32_t position = janet_getinteger(argv, 0);
    return janet_wrap_integer(LoadStorageValue(position));
}

static Janet cfun_OpenUrl(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *url = janet_getcstring(argv, 0);
    OpenURL(url);
    return janet_wrap_nil();
}

static Janet cfun_SetWindowIcon(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Image *image = jaylib_getimage(argv, 0);
    SetWindowIcon(*image);
    return janet_wrap_nil();
}

static Janet cfun_Camera2D(int32_t argc, Janet *argv) {
    if ((argc & 1) != 0) {
        janet_panicf("expected even number of arguments, got %d", argc);
    }
    Camera2D *camera = janet_abstract(&AT_Camera2D, sizeof(Camera2D));
    memset(camera, 0, sizeof(Camera2D));
    for (int32_t i = 0; i < argc; i += 2) {
        const uint8_t *kw = janet_getkeyword(argv, i);
        if (!janet_cstrcmp(kw, "target")) {
            camera->target = jaylib_getvec2(argv, i + 1);
        } else if (!janet_cstrcmp(kw, "offset")) {
            camera->offset = jaylib_getvec2(argv, i + 1);
        } else if (!janet_cstrcmp(kw, "rotation")) {
            camera->rotation = (float) janet_getnumber(argv, i + 1);
        } else if (!janet_cstrcmp(kw, "zoom")) {
            camera->zoom = (float) janet_getnumber(argv, i + 1);
        } else {
            janet_panicf("unknown key %v", argv[i]);
        }
    }
    return janet_wrap_abstract(camera);
}

static Janet cfun_Camera3D(int32_t argc, Janet *argv) {
    if ((argc & 1) != 0) {
        janet_panicf("expected even number of arguments, got %d", argc);
    }
    Camera3D *camera = janet_abstract(&AT_Camera3D, sizeof(Camera3D));
    memset(camera, 0, sizeof(Camera3D));
    for (int32_t i = 0; i < argc; i += 2) {
        const uint8_t *kw = janet_getkeyword(argv, i);
        if (!janet_cstrcmp(kw, "target")) {
            camera->target = jaylib_getvec3(argv, i + 1);
        } else if (!janet_cstrcmp(kw, "position")) {
            camera->position = jaylib_getvec3(argv, i + 1);
        } else if (!janet_cstrcmp(kw, "up")) {
            camera->up = jaylib_getvec3(argv, i + 1);
        } else if (!janet_cstrcmp(kw, "fovy")) {
            camera->fovy = (float) janet_getnumber(argv, i + 1);
        } else if (!janet_cstrcmp(kw, "type")) {
            const uint8_t *cameraType = janet_getkeyword(argv, i + 1);
            if (!janet_cstrcmp(cameraType, "perspective")) {
                camera->projection = CAMERA_PERSPECTIVE;
            } else if (!janet_cstrcmp(cameraType, "orthographic")) {
                camera->projection = CAMERA_ORTHOGRAPHIC;
            } else {
                janet_panicf("unknown camera type %v", argv[i + 1]);
            }
        } else {
            janet_panicf("unknown key %v", argv[i]);
        }
    }
    return janet_wrap_abstract(camera);
}

static Janet cfun_BeginMode3D(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Camera3D *camera = jaylib_getcamera3d(argv, 0);
    BeginMode3D(*camera);
    return janet_wrap_nil();
}

static Janet cfun_EndMode3D(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    EndMode3D();
    return janet_wrap_nil();
}

static Janet cfun_BeginTextureMode(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    RenderTexture2D *texture = jaylib_getrendertexture(argv, 0);
    BeginTextureMode(*texture);
    return janet_wrap_nil();
}

static Janet cfun_EndTextureMode(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    EndTextureMode();
    return janet_wrap_nil();
}

static Janet cfun_SetCameraMode(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Camera3D *camera = jaylib_getcamera3d(argv, 0);
    const uint8_t *kw = janet_getkeyword(argv, 1);
    int mode;
    if (!janet_cstrcmp(kw, "first-person")) {
        mode = CAMERA_FIRST_PERSON;
    } else if (!janet_cstrcmp(kw, "third-person")) {
        mode = CAMERA_THIRD_PERSON;
    } else if (!janet_cstrcmp(kw, "free")) {
        mode = CAMERA_FREE;
    } else if (!janet_cstrcmp(kw, "orbital")) {
        mode = CAMERA_ORBITAL;
    } else if (!janet_cstrcmp(kw, "custom")) {
        mode = CAMERA_CUSTOM;
    } else {
        janet_panicf("unknown camera mode %v", kw);
    }
    SetCameraMode(*camera, mode);
    return janet_wrap_nil();
}

static Janet cfun_UpdateCamera(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Camera3D *camera = jaylib_getcamera3d(argv, 0);
    UpdateCamera(camera);
    return janet_wrap_nil();
}

static Janet cfun_SetCameraPanControl(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int key = jaylib_getkey(argv, 0);
    SetCameraPanControl(key);
    return janet_wrap_nil();
}

static Janet cfun_SetCameraAltControl(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int key = jaylib_getkey(argv, 0);
    SetCameraAltControl(key);
    return janet_wrap_nil();
}

static Janet cfun_SetCameraSmoothZoomControl(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int key = jaylib_getkey(argv, 0);
    SetCameraSmoothZoomControl(key);
    return janet_wrap_nil();
}

static Janet cfun_SetCameraMoveControls(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    int k1 = jaylib_getkey(argv, 0);
    int k2 = jaylib_getkey(argv, 1);
    int k3 = jaylib_getkey(argv, 2);
    int k4 = jaylib_getkey(argv, 3);
    int k5 = jaylib_getkey(argv, 4);
    int k6 = jaylib_getkey(argv, 5);
    SetCameraMoveControls(k1, k2, k3, k4, k5, k6);
    return janet_wrap_nil();
}

static JanetReg core_cfuns[] = {
    {"init-window", cfun_InitWindow, 
        "(init-window width height title)\n\n" 
        "Initialize window and OpenGL context"
    },
    {"window-should-close", cfun_WindowShouldClose, 
        "(window-should-close)\n\n" 
        "Check if KEY_ESCAPE pressed or Close icon pressed"
    },
    {"close-window", cfun_CloseWindow, 
        "(close-window)\n\n" 
        "Close window and unload OpenGL context"
    },
    {"window-ready?", cfun_IsWindowReady, 
        "(window-ready?)\n\n" 
        "Check if window has been initialized successfully"
    },
    {"window-minimized?", cfun_IsWindowMinimized, 
        "(window-minimized?)\n\n" 
        "Check if window is currently minimized"
    },
    {"window-resized?", cfun_IsWindowResized, 
        "(window-resized?)\n\n" 
        "Check if window has been resized last frame"
    },
    {"window-state?", cfun_IsWindowState, 
        "(window-state? flag)\n\n" 
        "Check if one specific window flag is enabled"
    },
    {"set-window-state", cfun_SetWindowState, 
        "(set-window-state flags)\n\n" 
        "Set window configuration state using flags"
    },
    {"clear-window-state", cfun_ClearWindowState, 
        "(clear-window-state flags)\n\n" 
        "Clear window configuration state flags"
    },
    {"toggle-fullscreen", cfun_ToggleFullscreen, 
        "(toggle-fullscreen)\n\n" 
        "Toggle window state: fullscreen/windowed"
    },
    {"set-window-title", cfun_SetWindowTitle, 
        "(set-window-title title)\n\n" 
        "Set title for window"
    },
    {"set-window-position", cfun_SetWindowPosition, 
        "(set-window-position x y)\n\n" 
        "Set window position on screen"
    },
    {"set-window-monitor", cfun_SetWindowMonitor, 
        "(set-window-monitor monitor)\n\n" 
        "Set monitor for the current window"
    },
    {"set-window-min-size", cfun_SetWindowMinSize, 
        "(set-window-min-size width height)\n\n" 
        "Set window minimum dimensions"
    },
    {"set-window-size", cfun_SetWindowSize, 
        "(set-window-size width height)\n\n" 
        "Set window dimensions"
    },
    {"get-window-handle", cfun_GetWindowHandle, 
        "(get-window-handle)\n\n" 
        "Get native window handle"
    },
    {"get-screen-width", cfun_GetScreenWidth, 
        "(get-screen-width)\n\n" 
        "Get current screen width"
    },
    {"get-screen-height", cfun_GetScreenHeight, 
        "(get-screen-height)\n\n" 
        "Get current screen height"
    },
    {"get-monitor-count", cfun_GetMonitorCount, 
        "(get-monitor-count)\n\n" 
        "Get number of connected monitors"
    },
    {"get-monitor-width", cfun_GetMonitorWidth, 
        "(get-monitor-width monitor)\n\n" 
        "Get specified monitor width (max available by monitor)"
    },
    {"get-monitor-height", cfun_GetMonitorHeight, 
        "(get-monitor-height monitor)\n\n" 
        "Get specified monitor height (max available by monitor)"
    },
    {"get-monitor-physical-width", cfun_GetMonitorPhysicalWidth, 
        "(get-monitor-physical-width monitor)\n\n" 
        "Get specified monitor physical width in millimetres"
    },
    {"get-monitor-physical-height", cfun_GetMonitorPhysicalHeight, 
        "(get-monitor-physical-height monitor)\n\n" 
        "Get specified monitor physical height in millimetres"
    },
    {"get-monitor-name", cfun_GetMonitorName, 
        "(get-monitor-name monitor)\n\n" 
        "Get the human-readable, UTF-8 encoded name of the primary monitor"
    },
    {"get-clipboard-text", cfun_GetClipboardText, 
        "(get-clipboard-text)\n\n" 
        "Get clipboard text content"
    },
    {"set-clipboard-text", cfun_SetClipboardText, 
        "(set-clipboard-text text)\n\n" 
        "Set clipboard text content"
    },
    {"show-cursor", cfun_ShowCursor, 
        "(show-cursor)\n\n" 
        "Shows cursor"
    },
    {"hide-cursor", cfun_HideCursor, 
        "(hide-cursor)\n\n" 
        "Hides cursor"
    },
    {"cursor-hidden?", cfun_IsCursorHidden, 
        "(cursor-hidden?)\n\n" 
        "Check if cursor is not visible"
    },
    {"enable-cursor", cfun_EnableCursor, 
        "(enable-cursor)\n\n" 
        "Enables cursor (unlock cursor)"
    },
    {"disable-cursor", cfun_DisableCursor, 
        "(disable-cursor)\n\n" 
        "Disables cursor (lock cursor)"
    },
    {"cursor-on-screen?", cfun_IsCursorOnScreen, 
        "(cursor-on-screen?)\n\n" 
        "Check if cursor is on the screen"
    },
    {"clear-background", cfun_ClearBackground, 
        "(clear-background color)\n\n" 
        "Set background color (framebuffer clear color)"
    },
    {"begin-drawing", cfun_BeginDrawing, 
        "(begin-drawing)\n\n" 
        "Setup canvas (framebuffer) to start drawing"
    },
    {"end-drawing", cfun_EndDrawing, 
        "(end-drawing)\n\n" 
        "End canvas drawing and swap buffers (double buffering)"
    },
    {"begin-mode-2d", cfun_BeginMode2D, 
        "(begin-mode-2d camera)\n\n" 
        "Begin 2D mode with custom camera (2D)"
    },
    {"end-mode-2d", cfun_EndMode2D, 
        "(end-mode-2d)\n\n" 
        "Ends 2D mode with custom camera"
    },
    {"set-target-fps", cfun_SetTargetFPS, 
        "(set-target-fps fps)\n\n" 
        "Set target FPS (maximum)"
    },
    {"get-fps", cfun_GetFPS, 
        "(get-fps)\n\n" 
        "Get current FPS"
    },
    {"get-frame-time", cfun_GetFrameTime, 
        "(get-frame-time)\n\n" 
        "Get time in seconds for last frame drawn (delta time)"
    },
    {"get-time", cfun_GetTime, 
        "(get-time)\n\n" 
        "Get elapsed time in seconds since InitWindow()"
    },
    {"set-config-flags", cfun_SetConfigFlags, 
        "(set-config-flags flags)\n\n" 
        "Setup init configuration flags (view FLAGS)"
    },
    {"set-trace-log-level", cfun_SetTraceLogLevel, 
        "(set-trace-log-level log-level)\n\n" 
        "Set the current threshold (minimum) log level"
    },
    {"set-trace-log-callback", cfun_SetTraceLogCallback, 
        "(set-trace-log-callback callback)\n\n" 
        "Set custom trace log"
    },
    {"trace-log", cfun_TraceLog, 
        "(trace-log log-level text)\n\n" 
        "Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)"
    },
    {"take-screenshot", cfun_TakeScreenshot, 
        "(take-screenshot file-name)\n\n" 
        "Takes a screenshot of current screen (filename extension defines format)"
    },
    {"key-pressed?", cfun_IsKeyPressed, 
        "(key-pressed? key)\n\n" 
        "Check if a key has been pressed once"
    },
    {"key-released?", cfun_IsKeyReleased, 
        "(key-released? key)\n\n" 
        "Check if a key has been released once"
    },
    {"key-up?", cfun_IsKeyUp, 
        "(key-up? key)\n\n" 
        "Check if a key is NOT being pressed"
    },
    {"key-down?", cfun_IsKeyDown, 
        "(key-down? key)\n\n" 
        "Check if a key is being pressed"
    },
    {"get-key-pressed", cfun_GetKeyPressed, 
        "(get-key-pressed)\n\n" 
        "Get key pressed (keycode), call it multiple times for keys "
        "queued, returns 0 when the queue is empty"
    },
    {"set-exit-key", cfun_SetExitKey, 
        "(set-exit-key key)\n\n" 
        "Set a custom key to exit program (default is ESC)"
    },
    {"gamepad-available?", cfun_IsGamepadAvailable, 
        "(gamepad-available? gamepad)\n\n" 
        "Check if a gamepad is available"
    },
    {"gamepad-button-down?", cfun_IsGamepadButtonDown, 
        "(gamepad-button-down? gamepad button)\n\n" 
        "Check if a gamepad button is being pressed"
    },
    {"gamepad-button-up?", cfun_IsGamepadButtonUp, 
        "(gamepad-button-up? gamepad button)\n\n" 
        "Check if a gamepad button is NOT being pressed"
    },
    {"gamepad-button-pressed?", cfun_IsGamepadButtonPressed, 
        "(gamepad-button-pressed? gamepad button)\n\n" 
        "Check if a gamepad button has been pressed once"
    },
    {"gamepad-button-released?", cfun_IsGamepadButtonReleased, 
        "(gamepad-button-released? gamepad button)\n\n" 
        "Check if a gamepad button has been released once"
    },
    {"get-gamepad-button-pressed", cfun_GetGamepadButtonPressed, 
        "(get-gamepad-button-pressed)\n\n" 
        "Get the last gamepad button pressed"
    },
    {"get-gamepad-name", cfun_GetGamepadName, 
        "(get-gamepad-name gamepad)\n\n" 
        "Get gamepad internal name id"
    },
    {"get-gamepad-axis-count", cfun_GetGamepadAxisCount, 
        "(get-gamepad-axis-count gamepad)\n\n" 
        "Get gamepad axis count for a gamepad"
    },
    {"get-gamepad-axis-movement", cfun_GetGamepadAxisMovement, 
        "(get-gamepad-axis-movement gamepad axis)\n\n" 
        "Get axis movement value for a gamepad axis"
    },
    {"mouse-button-pressed?", cfun_IsMouseButtonPressed, 
        "(mouse-button-pressed? button)\n\n" 
        "Check if a mouse button has been pressed once"
    },
    {"mouse-button-up?", cfun_IsMouseButtonUp, 
        "(mouse-button-up? button)\n\n" 
        "Check if a mouse button is NOT being pressed"
    },
    {"mouse-button-released?", cfun_IsMouseButtonReleased, 
        "(mouse-button-released? button)\n\n" 
        "Check if a mouse button has been released once"
    },
    {"mouse-button-down?", cfun_IsMouseButtonDown, 
        "(mouse-button-down? button)\n\n" 
        "Check if a mouse button is being pressed"
    },
    {"get-mouse-x", cfun_GetMouseX, 
        "(get-mouse-x)\n\n" 
        "Get mouse position X"
    },
    {"get-mouse-y", cfun_GetMouseY, 
        "(get-mouse-y)\n\n" 
        "Get mouse position Y"
    },
    {"get-mouse-position", cfun_GetMousePosition, 
        "(get-mouse-position)\n\n" 
        "Get mouse position XY"
    },
    {"set-mouse-position", cfun_SetMousePosition, 
        "(set-mouse-position x y)\n\n" 
        "Set mouse position XY"
    },
    {"set-mouse-offset", cfun_SetMouseOffset, 
        "(set-mouse-offset offset-x offset-y)\n\n" 
        "Set mouse offset"
    },
    {"set-mouse-scale", cfun_SetMouseScale, 
        "(set-mouse-scale scale-x scale-y)\n\n" 
        "Set mouse scaling"
    },
    {"get-mouse-wheel-move", cfun_GetMouseWheelMove, 
        "(get-mouse-wheel-move)\n\n" 
        "Get mouse wheel movement Y"
    },
    {"get-touch-x", cfun_GetTouchX, 
        "(get-touch-x)\n\n" 
        "Get touch position X for touch point 0 (relative to screen size)"
    },
    {"get-touch-y", cfun_GetTouchY, 
        "(get-touch-y)\n\n" 
        "Get touch position Y for touch point 0 (relative to screen size)"
    },
    {"get-touch-position", cfun_GetTouchPosition, 
        "(get-touch-position index)\n\n" 
        "Get touch position XY for a touch point index (relative to screen size)"
    },
    {"get-dropped-files", cfun_GetDroppedFiles, 
        "(get-dropped-files count)\n\n" 
        "Get dropped files names (memory should be freed)"
    },
    {"clear-dropped-files", cfun_ClearDroppedFiles, 
        "(clear-dropped-files)\n\n" 
        "Clear dropped files paths buffer (free memory)"
    },
    {"save-storage-value", cfun_SaveStorageValue, 
        "(save-storage-value position value)\n\n" 
        "Save integer value to storage file (to defined position), "
        "returns true on success"
    },
    {"load-storage-value", cfun_LoadStorageValue, 
        "(load-storage-value position)\n\n" 
        "Load integer value from storage file (from defined position)"
    },
    {"open-url", cfun_OpenUrl, 
        "(open-url url)\n\n" 
        "Open URL with default system browser (if available)"
    },
    {"set-window-icon", cfun_SetWindowIcon, 
        "(set-window-icon image)\n\n" 
        "Set icon for window"
    },
    {"begin-mode-3d", cfun_BeginMode3D, 
        "(begin-mode-3d camera)\n\n" 
        "Begin 3D mode with custom camera (3D)"
    },
    {"end-mode-3d", cfun_EndMode3D, 
        "(end-mode-3d)\n\n" 
        "Ends 3D mode and returns to default 2D orthographic mode"
    },
    {"begin-texture-mode", cfun_BeginTextureMode, 
        "(begin-texture-mode target)\n\n" 
        "Begin drawing to render texture"
    },
    {"end-texture-mode", cfun_EndTextureMode, 
        "(end-texture-mode)\n\n" 
        "Ends drawing to render texture"
    },
    {"camera-2d", cfun_Camera2D, 
        "(camera-2d &opt :offset [x y] :target [x y] :rotation int :zoom float)\n\n" 
        "Instantiate a Camera2D. \n"
        " - :offset   = Camera offset (displacement from target) \n"
        " - :target   = Camera target (rotation and zoom origin) \n"
        " - :rotation = Camera rotation in degrees \n"
        " - :zoom     = Camera zoom (scaling), should be 1.0f by default \n"
    },
    {"camera-3d", cfun_Camera3D, 
        "(camera-3d :position [x y z] :target [x y z] :up [x y z] :fov-y float :projection int)\n\n" 
        "Instantiate a Camera3D. \n"
        " - :position   = Camera position \n"
        " - :target     = Camera target it looks-at \n"
        " - :up         = Camera up vector (rotation over its axis) \n"
        " - :fov-y      = Camera field-of-view apperture in Y (degrees) in perspective, used as near plane width in orthographic \n"
        " - :projection = Camera projection: CAMERA\\_PERSPECTIVE or CAMERA\\_ORTHOGRAPHIC \n"
    },
    {"set-camera-mode", cfun_SetCameraMode, 
        "(set-camera-mode camera mode)\n\n" 
        "Set camera mode (multiple camera modes available)"
    },
    {"update-camera", cfun_UpdateCamera, 
        "(update-camera camera)\n\n" 
        "Update camera position for selected mode"
    },
    {"set-camera-pan-control", cfun_SetCameraPanControl, 
        "(set-camera-pan-control key-pan)\n\n" 
        "Set camera pan key to combine with mouse movement (free camera)"
    },
    {"set-camera-alt-control", cfun_SetCameraAltControl, 
        "(set-camera-alt-control key-alt)\n\n" 
        "Set camera alt key to combine with mouse movement (free camera)"
    },
    {"set-camera-smooth-zoom-control", cfun_SetCameraSmoothZoomControl, 
        "(set-camera-smooth-zoom-control key-smooth-zoom)\n\n" 
        "Set camera smooth zoom key to combine with mouse (free camera)"
    },
    {"set-camera-move-controls", cfun_SetCameraMoveControls, 
        "(set-camera-move-controls key-front key-back key-right key-left key-up key-down)\n\n" 
        "Set camera move controls (1st person and 3rd person cameras)"
    },
    {NULL, NULL, NULL}
};
