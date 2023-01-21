static Janet cfun_rlViewport(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    int posX = janet_getinteger(argv, 0);
    int posY = janet_getinteger(argv, 1);
    int width = janet_getinteger(argv, 2);
    int height = janet_getinteger(argv, 3);
    rlViewport(posX, posY, width, height);
    return janet_wrap_nil();
}

static const KeyDef rl_flag_defs[] = {
    {"rl-modelview", RL_MODELVIEW},
    {"rl-projection", RL_PROJECTION},
};


static Janet cfun_rlMatrixMode(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const uint8_t *arg_flag = janet_getkeyword(argv, 0);
    int flag = 0;
    for (unsigned j = 0; j < (sizeof(rl_flag_defs) / sizeof(KeyDef)); j++) {
        if (!janet_cstrcmp(arg_flag, rl_flag_defs[j].name))
            {
	flag = rl_flag_defs[j].key;
	break;
            }
    }

    if (0 == flag) {
        JanetArray *available = janet_array(0);
        for (unsigned j = 0; j < (sizeof(flag_defs) / sizeof(KeyDef)); j++) {
            janet_array_push(available, janet_ckeywordv(flag_defs[j].name));
        }
        janet_panicf("unknown flag %v - available flags are %p", arg_flag,
		 janet_wrap_array(available));
    }
    
    rlMatrixMode(flag);
    return janet_wrap_nil();
}

static Janet cfun_rlLoadIdentity(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    rlLoadIdentity();
    return janet_wrap_nil();
}

static Janet cfun_rlOrtho(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    float left = (float) janet_getnumber(argv, 0);
    float right = (float) janet_getnumber(argv, 1);
    float bottom = (float) janet_getnumber(argv, 2);
    float top = (float) janet_getnumber(argv, 3);
    float znear = (float) janet_getnumber(argv, 4);
    float zfar = (float) janet_getnumber(argv, 5);
    rlOrtho(left, right, bottom, top, znear, zfar);
    return janet_wrap_nil();
}

static Janet cfun_rlTranslatef(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    float x = (float) janet_getnumber(argv, 0);
    float y = (float) janet_getnumber(argv, 1);
    float z = (float) janet_getnumber(argv, 2);
    rlTranslatef(x, y, z);
    return janet_wrap_nil();
}

static Janet cfun_rlRotatef(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    float angle = (float) janet_getnumber(argv, 0);
    float x = (float) janet_getnumber(argv, 1);
    float y = (float) janet_getnumber(argv, 2);
    float z = (float) janet_getnumber(argv, 3);
    rlRotatef(angle, x, y, z);
    return janet_wrap_nil();
}

static Janet cfun_rlScalef(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    float x = (float) janet_getnumber(argv, 0);
    float y = (float) janet_getnumber(argv, 1);
    float z = (float) janet_getnumber(argv, 2);
    rlScalef(x, y, z);
    return janet_wrap_nil();
}

static Janet cfun_rlEnableScissorTest(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    rlEnableScissorTest();
    return janet_wrap_nil();
}

static Janet cfun_rlScissor(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    int posX = janet_getinteger(argv, 0);
    int posY = janet_getinteger(argv, 1);
    int width = janet_getinteger(argv, 2);
    int height = janet_getinteger(argv, 3);
    rlScissor(posX, posY, width, height);
    return janet_wrap_nil();
}

static Janet cfun_rlPushMatrix(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    rlPushMatrix();
    return janet_wrap_nil();
}

static Janet cfun_rlPopMatrix(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    rlPopMatrix();
    return janet_wrap_nil();
}

static Janet cfun_rlMultMatrixfScreenScale(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    Vector2 v = GetWindowScaleDPI();
    float s = v.x * v.y;
    rlMultMatrixf(&s); // Apply screen scaling
    return janet_wrap_nil();
}

static Janet cfun_rlDrawRenderBatchActive(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    rlDrawRenderBatchActive();
    return janet_wrap_nil();
}

static JanetReg rlgl_cfuns[] = {
    {"rl-viewport", cfun_rlViewport, NULL},
    {"rl-matrix-mode", cfun_rlMatrixMode, NULL},
    {"rl-ortho", cfun_rlOrtho, NULL},
    {"rl-push-matrix", cfun_rlPushMatrix, NULL},
    {"rl-pop-matrix", cfun_rlPopMatrix, NULL},
    {"rl-load-identity", cfun_rlLoadIdentity, NULL},
    {"rl-translatef", cfun_rlTranslatef, NULL},
    {"rl-rotatef", cfun_rlRotatef, NULL},
    {"rl-scalef", cfun_rlScalef, NULL},
    {"rl-enable-scissor-test", cfun_rlEnableScissorTest, NULL},
    {"rl-scissor", cfun_rlScissor, NULL},
    {"rl-mult-matrixf-screen-scale", cfun_rlMultMatrixfScreenScale, NULL},
    {"rl-draw-render-batch-active", cfun_rlDrawRenderBatchActive, NULL},
    {NULL, NULL, NULL}
};