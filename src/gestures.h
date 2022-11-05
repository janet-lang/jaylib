static int jaylib_getgesture(const Janet *argv, int32_t n) {
    const uint8_t *kw = janet_getkeyword(argv, n);
    if (!janet_cstrcmp(kw, "tap")) {
        return GESTURE_TAP;
    } else if (!janet_cstrcmp(kw, "double-tap")) {
        return GESTURE_DOUBLETAP;
    } else if (!janet_cstrcmp(kw, "hold")) {
        return GESTURE_HOLD;
    } else if (!janet_cstrcmp(kw, "drag")) {
        return GESTURE_DRAG;
    } else if (!janet_cstrcmp(kw, "swipe-right")) {
        return GESTURE_SWIPE_RIGHT;
    } else if (!janet_cstrcmp(kw, "swipe-left")) {
        return GESTURE_SWIPE_LEFT;
    } else if (!janet_cstrcmp(kw, "swipe-up")) {
        return GESTURE_SWIPE_UP;
    } else if (!janet_cstrcmp(kw, "swipe-down")) {
        return GESTURE_SWIPE_DOWN;
    } else if (!janet_cstrcmp(kw, "pinch-in")) {
        return GESTURE_PINCH_IN;
    } else if (!janet_cstrcmp(kw, "pinch-out")) {
        return GESTURE_PINCH_OUT;
    } else {
        janet_panicf("unknown gesture %v", argv[n]);
    }
}

static Janet cfun_SetGesturesEnabled(int32_t argc, Janet *argv) {
    unsigned int flags = 0;
    for (int32_t i = 0; i < argc; i++)
        flags |= jaylib_getgesture(argv, i);
    SetGesturesEnabled(flags);
    return janet_wrap_nil();
}

static Janet cfun_IsGestureDetected(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int gesture = jaylib_getgesture(argv, 0);
    return janet_wrap_boolean(IsGestureDetected(gesture));
}

static Janet cfun_GetGestureDetected(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    switch (GetGestureDetected()) {
        default:
        case GESTURE_NONE:
            return janet_wrap_nil();
        case GESTURE_TAP:
            return janet_ckeywordv("tap");
        case GESTURE_DOUBLETAP:
            return janet_ckeywordv("double-tap");
        case GESTURE_HOLD:
            return janet_ckeywordv("hold");
        case GESTURE_DRAG:
            return janet_ckeywordv("drag");
        case GESTURE_SWIPE_RIGHT:
            return janet_ckeywordv("swipe-right");
        case GESTURE_SWIPE_LEFT:
            return janet_ckeywordv("swipe-left");
        case GESTURE_SWIPE_UP:
            return janet_ckeywordv("swipe-up");
        case GESTURE_SWIPE_DOWN:
            return janet_ckeywordv("swipe-down");
        case GESTURE_PINCH_IN:
            return janet_ckeywordv("pinch-in");
        case GESTURE_PINCH_OUT:
            return janet_ckeywordv("pinch-out");
    }
}

static Janet cfun_GetTouchPointCount(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_integer(GetTouchPointCount());
}

static Janet cfun_GetGestureHoldDuration(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_number((double) GetGestureHoldDuration());
}

static Janet cfun_GetGestureDragVector(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return jaylib_wrap_vec2(GetGestureDragVector());
}

static Janet cfun_GetGestureDragAngle(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_number((double) GetGestureDragAngle());
}

static Janet cfun_GetGesturePinchVector(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return jaylib_wrap_vec2(GetGesturePinchVector());
}

static Janet cfun_GetGesturePinchAngle(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_number((double) GetGesturePinchAngle());
}

static JanetReg gesture_cfuns[] = {
    {"set-gestures-enabled", cfun_SetGesturesEnabled, 
        "(set-gestures-enabled flags)\n\n"
        "Enable a set of gestures using flags"
    },
    {"gesture-detected?", cfun_IsGestureDetected, 
        "(gesture-detected? gesture)\n\n"
        "Check if a gesture have been detected"
    },
    {"get-gesture-detected", cfun_GetGestureDetected, 
        "(get-gesture-detected)\n\n"
        "Get latest detected gesture"
    },
    {"get-touch-point-count", cfun_GetTouchPointCount, 
        "(get-touch-point-count)\n\n"
        "Get number of touch points"
    },
    {"get-gesture-hold-duration", cfun_GetGestureHoldDuration, 
        "(get-gesture-hold-duration)\n\n"
        "Get gesture hold time in milliseconds"
    },
    {"get-gesture-drag-vector", cfun_GetGestureDragVector, 
        "(get-gesture-drag-vector)\n\n"
        "Get gesture drag vector"
    },
    {"get-gesture-drag-angle", cfun_GetGestureDragAngle, 
        "(get-gesture-drag-angle)\n\n"
        "Get gesture drag angle"
    },
    {"get-gesture-pinch-vector", cfun_GetGesturePinchVector, 
        "(get-gesture-pinch-vector)\n\n"
        "Get gesture pinch delta"
    },
    {"get-gesture-pinch-angle", cfun_GetGesturePinchAngle, 
        "(get-gesture-pinch-angle)\n\n"
        "Get gesture pinch angle"
    },
    {NULL, NULL, NULL}
};
