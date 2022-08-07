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

static Janet cfun_GetCamera2DTarget(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Camera2D *camera = jaylib_getcamera2d(argv, 0);
  Vector2 target = camera->target;
  return jaylib_wrap_vec2(target);
}

static Janet cfun_GetCamera2DOffset(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Camera2D *camera = jaylib_getcamera2d(argv, 0);
  Vector2 offset = camera->offset;
  return jaylib_wrap_vec2(offset);
}

static Janet cfun_GetCamera2DRotation(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Camera2D *camera = jaylib_getcamera2d(argv, 0);
  float rotation = camera->rotation;
  return janet_wrap_number(rotation);
}

static Janet cfun_GetCamera2DZoom(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Camera2D *camera = jaylib_getcamera2d(argv, 0);
  float zoom = camera->zoom;
  return janet_wrap_number(zoom);
}

static Janet cfun_SetCamera2DTarget(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Camera2D *camera = jaylib_getcamera2d(argv, 0);
  Vector2 target = jaylib_getvec2(argv, 1);
  camera->target = target;
  return janet_wrap_nil();
}

static Janet cfun_SetCamera2DOffset(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Camera2D *camera = jaylib_getcamera2d(argv, 0);
  Vector2 offset = jaylib_getvec2(argv, 1);
  camera->offset = offset;
  return janet_wrap_nil();
}

static Janet cfun_SetCamera2DRotation(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Camera2D *camera = jaylib_getcamera2d(argv, 0);
  float rotation = janet_getnumber(argv, 1);
  camera->rotation = rotation;
  return janet_wrap_nil();
}

static Janet cfun_SetCamera2DZoom(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  Camera2D *camera = jaylib_getcamera2d(argv, 0);
  float zoom = janet_getnumber(argv, 1);
  camera->zoom = zoom;
  return janet_wrap_nil();
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
    {"init-window", cfun_InitWindow, NULL},
    {"window-should-close", cfun_WindowShouldClose, NULL},
    {"close-window", cfun_CloseWindow, NULL},
    {"window-ready?", cfun_IsWindowReady, NULL},
    {"window-minimized?", cfun_IsWindowMinimized, NULL},
    {"window-resized?", cfun_IsWindowResized, NULL},
    {"window-state?", cfun_IsWindowState, NULL},
    {"set-window-state", cfun_SetWindowState, NULL},
    {"clear-window-state", cfun_ClearWindowState, NULL},
    {"toggle-fullscreen", cfun_ToggleFullscreen, NULL},
    {"set-window-title", cfun_SetWindowTitle, NULL},
    {"set-window-position", cfun_SetWindowPosition, NULL},
    {"set-window-monitor", cfun_SetWindowMonitor, NULL},
    {"set-window-min-size", cfun_SetWindowMinSize, NULL},
    {"set-window-size", cfun_SetWindowSize, NULL},
    {"get-window-handle", cfun_GetWindowHandle, NULL},
    {"get-screen-width", cfun_GetScreenWidth, NULL},
    {"get-screen-height", cfun_GetScreenHeight, NULL},
    {"get-monitor-count", cfun_GetMonitorCount, NULL},
    {"get-monitor-width", cfun_GetMonitorWidth, NULL},
    {"get-monitor-height", cfun_GetMonitorHeight, NULL},
    {"get-monitor-physical-width", cfun_GetMonitorPhysicalWidth, NULL},
    {"get-monitor-physical-height", cfun_GetMonitorPhysicalHeight, NULL},
    {"get-monitor-name", cfun_GetMonitorName, NULL},
    {"get-clipboard-text", cfun_GetClipboardText, NULL},
    {"set-clipboard-text", cfun_SetClipboardText, NULL},
    {"show-cursor", cfun_ShowCursor, NULL},
    {"hide-cursor", cfun_HideCursor, NULL},
    {"cursor-hidden?", cfun_IsCursorHidden, NULL},
    {"enable-cursor", cfun_EnableCursor, NULL},
    {"disable-cursor", cfun_DisableCursor, NULL},
    {"cursor-on-screen?", cfun_IsCursorOnScreen, NULL},
    {"clear-background", cfun_ClearBackground, NULL},
    {"begin-drawing", cfun_BeginDrawing, NULL},
    {"end-drawing", cfun_EndDrawing, NULL},
    {"begin-mode-2d", cfun_BeginMode2D, NULL},
    {"end-mode-2d", cfun_EndMode2D, NULL},
    {"set-target-fps", cfun_SetTargetFPS, NULL},
    {"get-fps", cfun_GetFPS, NULL},
    {"get-frame-time", cfun_GetFrameTime, NULL},
    {"get-time", cfun_GetTime, NULL},
    {"set-config-flags", cfun_SetConfigFlags, NULL},
    {"set-trace-log-level", cfun_SetTraceLogLevel, NULL},
    {"set-trace-log-callback", cfun_SetTraceLogCallback, NULL},
    {"trace-log", cfun_TraceLog, NULL},
    {"take-screenshot", cfun_TakeScreenshot, NULL},
    {"key-pressed?", cfun_IsKeyPressed, NULL},
    {"key-released?", cfun_IsKeyReleased, NULL},
    {"key-up?", cfun_IsKeyUp, NULL},
    {"key-down?", cfun_IsKeyDown, NULL},
    {"get-key-pressed", cfun_GetKeyPressed, NULL},
    {"set-exit-key", cfun_SetExitKey, NULL},
    {"gamepad-available?", cfun_IsGamepadAvailable, NULL},
    {"gamepad-button-down?", cfun_IsGamepadButtonDown, NULL},
    {"gamepad-button-up?", cfun_IsGamepadButtonUp, NULL},
    {"gamepad-button-pressed?", cfun_IsGamepadButtonPressed, NULL},
    {"gamepad-button-released?", cfun_IsGamepadButtonReleased, NULL},
    {"get-gamepad-button-pressed", cfun_GetGamepadButtonPressed, NULL},
    {"get-gamepad-name", cfun_GetGamepadName, NULL},
    {"get-gamepad-axis-count", cfun_GetGamepadAxisCount, NULL},
    {"get-gamepad-axis-movement", cfun_GetGamepadAxisMovement, NULL},
    {"mouse-button-pressed?", cfun_IsMouseButtonPressed, NULL},
    {"mouse-button-up?", cfun_IsMouseButtonUp, NULL},
    {"mouse-button-released?", cfun_IsMouseButtonReleased, NULL},
    {"mouse-button-down?", cfun_IsMouseButtonDown, NULL},
    {"get-mouse-x", cfun_GetMouseX, NULL},
    {"get-mouse-y", cfun_GetMouseY, NULL},
    {"get-mouse-position", cfun_GetMousePosition, NULL},
    {"set-mouse-position", cfun_SetMousePosition, NULL},
    {"set-mouse-offset", cfun_SetMouseOffset, NULL},
    {"set-mouse-scale", cfun_SetMouseScale, NULL},
    {"get-mouse-wheel-move", cfun_GetMouseWheelMove, NULL},
    {"get-touch-x", cfun_GetTouchX, NULL},
    {"get-touch-y", cfun_GetTouchY, NULL},
    {"get-touch-position", cfun_GetTouchPosition, NULL},
    {"get-dropped-files", cfun_GetDroppedFiles, NULL},
    {"clear-dropped-files", cfun_ClearDroppedFiles, NULL},
    {"save-storage-value", cfun_SaveStorageValue, NULL},
    {"load-storage-value", cfun_LoadStorageValue, NULL},
    {"open-url", cfun_OpenUrl, NULL},
    {"set-window-icon", cfun_SetWindowIcon, NULL},
    {"begin-mode-3d", cfun_BeginMode3D, NULL},
    {"end-mode-3d", cfun_EndMode3D, NULL},
    {"begin-texture-mode", cfun_BeginTextureMode, NULL},
    {"end-texture-mode", cfun_EndTextureMode, NULL},
    {"camera-2d", cfun_Camera2D, NULL},
    {"get-camera-2d-target", cfun_GetCamera2DTarget, NULL},
    {"get-camera-2d-offset", cfun_GetCamera2DOffset, NULL},
    {"get-camera-2d-rotation", cfun_GetCamera2DRotation, NULL},
    {"get-camera-2d-zoom", cfun_GetCamera2DZoom, NULL},
    {"set-camera-2d-target", cfun_SetCamera2DTarget, NULL},
    {"set-camera-2d-offset", cfun_SetCamera2DOffset, NULL},
    {"set-camera-2d-rotation", cfun_SetCamera2DRotation, NULL},
    {"set-camera-2d-zoom", cfun_SetCamera2DZoom, NULL},
    {"camera-3d", cfun_Camera3D, NULL},
    {"set-camera-mode", cfun_SetCameraMode, NULL},
    {"update-camera", cfun_UpdateCamera, NULL},
    {"set-camera-pan-control", cfun_SetCameraPanControl, NULL},
    {"set-camera-alt-control", cfun_SetCameraAltControl, NULL},
    {"set-camera-smooth-zoom-control", cfun_SetCameraSmoothZoomControl, NULL},
    {"set-camera-move-controls", cfun_SetCameraMoveControls, NULL},
    {NULL, NULL, NULL}
};
