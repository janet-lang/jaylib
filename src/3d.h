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

static Janet cfun_DrawGizmo(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Vector3 position = jaylib_getvec3(argv, 0);
    DrawGizmo(position);
    return janet_wrap_nil();
}

static Janet cfun_DrawGrid(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int slices = janet_getinteger(argv, 0);
    float spacing = (float) janet_getnumber(argv, 1);
    DrawGrid(slices, spacing);
    return janet_wrap_nil();
}

/*
[ ] void DrawCubeV(Vector3 position, Vector3 size, Color color)
[ ] void DrawCubeWires(Vector3 position, float width, float height, float length, Color color)
[ ] void DrawCubeWiresV(Vector3 position, Vector3 size, Color color)
[ ] void DrawSphere(Vector3 centerPos, float radius, Color color)
[ ] void DrawSphereEx(Vector3 centerPos, float radius, int rings, int slices, Color color)
[ ] void DrawSphereWires(Vector3 centerPos, float radius, int rings, int slices, Color color)
[ ] void DrawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color)
[ ] void DrawCylinderWires(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color)
[ ] void DrawPlane(Vector3 centerPos, Vector2 size, Color color)
[ ] void DrawRay(Ray ray, Color color)
*/

static JanetReg threed_cfuns[] = {
    {"draw-line-3d", cfun_DrawLine3D, NULL},
    {"draw-circle-3d", cfun_DrawCircle3D, NULL},
    {"draw-cube", cfun_DrawCube, NULL},
    {"draw-cube-texture", cfun_DrawCubeTexture, NULL},
    {"draw-gizmo", cfun_DrawGizmo, NULL},
    {"draw-grid", cfun_DrawGizmo, NULL},
    {NULL, NULL, NULL}
};
