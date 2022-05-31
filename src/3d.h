static Janet cfun_DrawLine3D(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Vector3 start = jaylib_getvec3(argv, 0);
    Vector3 end = jaylib_getvec3(argv, 1);
    Color color = jaylib_getcolor(argv, 2);
    DrawLine3D(start, end, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawCircle3D(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    Vector3 center = jaylib_getvec3(argv, 0);
    float radius = (float) janet_getnumber(argv, 1);
    Vector3 axis = jaylib_getvec3(argv, 2);
    float angle = (float) janet_getnumber(argv, 3);
    Color color = jaylib_getcolor(argv, 4);
    DrawCircle3D(center, radius, axis, angle, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawCube(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    Vector3 pos = jaylib_getvec3(argv, 0);
    float width = (float) janet_getnumber(argv, 1);
    float height = (float) janet_getnumber(argv, 2);
    float length = (float) janet_getnumber(argv, 3);
    Color color = jaylib_getcolor(argv, 4);
    DrawCube(pos, width, height, length, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawCubeTexture(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    Texture2D *texture = jaylib_gettexture2d(argv, 0);
    Vector3 position = jaylib_getvec3(argv, 1);
    float width = (float) janet_getnumber(argv, 2);
    float height = (float) janet_getnumber(argv, 3);
    float length = (float) janet_getnumber(argv, 4);
    Color color = jaylib_getcolor(argv, 5);
    DrawCubeTexture(*texture, position, width, height, length, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawGrid(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int slices = janet_getinteger(argv, 0);
    float spacing = (float) janet_getnumber(argv, 1);
    DrawGrid(slices, spacing);
    return janet_wrap_nil();
}

static Janet cfun_DrawCubeV(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Vector3 position = jaylib_getvec3(argv, 0);
    Vector3 size = jaylib_getvec3(argv, 1);
    Color color = jaylib_getcolor(argv, 2);
    DrawCubeV(position, size, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawCubeWires(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    Vector3 position = jaylib_getvec3(argv, 0);
    float width = (float) janet_getnumber(argv, 1);
    float height = (float) janet_getnumber(argv, 2);
    float length = (float) janet_getnumber(argv, 3);
    Color color = jaylib_getcolor(argv, 4);
    DrawCubeWires(position, width, height, length, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawCubeWiresV(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Vector3 position = jaylib_getvec3(argv, 0);
    Vector3 size = jaylib_getvec3(argv, 1);
    Color color = jaylib_getcolor(argv, 2);
    DrawCubeWiresV(position, size, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawSphere(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Vector3 centerPos = jaylib_getvec3(argv, 0);
    float radius = (float) janet_getnumber(argv, 1);
    Color color = jaylib_getcolor(argv, 2);
    DrawSphere(centerPos, radius, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawSphereEx(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    Vector3 position = jaylib_getvec3(argv, 0);
    float radius = (float) janet_getnumber(argv, 1);
    int rings = janet_getinteger(argv, 2);
    int slices = janet_getinteger(argv, 3);
    Color color = jaylib_getcolor(argv, 4);
    DrawSphereEx(position, radius, rings, slices, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawSphereWires(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    Vector3 centerPos = jaylib_getvec3(argv, 0);
    float radius = (float) janet_getnumber(argv, 1);
    int rings = janet_getinteger(argv, 2);
    int slices = janet_getinteger(argv, 3);
    Color color = jaylib_getcolor(argv, 4);
    DrawSphereWires(centerPos, radius, rings, slices, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawCylinder(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    Vector3 position = jaylib_getvec3(argv, 0);
    float radiusTop = (float) janet_getnumber(argv, 1);
    float radiusBottom = (float) janet_getnumber(argv, 2);
    float height = (float) janet_getnumber(argv, 3);
    int slices = janet_getinteger(argv, 4);
    Color color = jaylib_getcolor(argv, 5);
    DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawCylinderWires(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    Vector3 position = jaylib_getvec3(argv, 0);
    float radiusTop = (float) janet_getnumber(argv, 1);
    float radiusBottom = (float) janet_getnumber(argv, 2);
    float height = (float) janet_getnumber(argv, 3);
    int slices = janet_getinteger(argv, 4);
    Color color = jaylib_getcolor(argv, 5);
    DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawPlane(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Vector3 centerPos = jaylib_getvec3(argv, 0);
    Vector2 size = jaylib_getvec2(argv, 1);
    Color color = jaylib_getcolor(argv, 2);
    DrawPlane(centerPos, size, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawRay(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Ray ray = jaylib_getray(argv, 0);
    Color color = jaylib_getcolor(argv, 1);
    DrawRay(ray, color);
    return janet_wrap_nil();
}

static JanetReg threed_cfuns[] = {
    {"draw-line-3d", cfun_DrawLine3D, NULL},
    {"draw-circle-3d", cfun_DrawCircle3D, NULL},
    {"draw-cube", cfun_DrawCube, NULL},
    {"draw-cube-v", cfun_DrawCubeV, NULL},
    {"draw-cube-wires", cfun_DrawCubeWires, NULL},
    {"draw-cube-wires-v", cfun_DrawCubeWiresV, NULL},
    {"draw-cube-texture", cfun_DrawCubeTexture, NULL},
    {"draw-grid", cfun_DrawGrid, NULL},
    {"draw-sphere", cfun_DrawSphere, NULL},
    {"draw-sphere-ex", cfun_DrawSphereEx, NULL},
    {"draw-sphere-wires", cfun_DrawSphereWires, NULL},
    {"draw-cylinder", cfun_DrawCylinder, NULL},
    {"draw-cylinder-wires", cfun_DrawCylinderWires, NULL},
    {"draw-plane", cfun_DrawPlane, NULL},
    {"draw-ray", cfun_DrawRay, NULL},
    {NULL, NULL, NULL}
};
