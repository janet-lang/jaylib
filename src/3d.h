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
    {"draw-line-3d", cfun_DrawLine3D, 
        "(draw-line-3d [start-x start-y start-z] [end-x end-y end-z] color)\n\n"
        "Draw a line in 3D world space"
    },
    {"draw-circle-3d", cfun_DrawCircle3D, 
        "(draw-circle-3d [center-x center-y center-z] radius [rot-x rot-y rot-z] rotation-angle color)\n\n"
        "Draw a circle in 3D world space"
    },
    {"draw-cube", cfun_DrawCube, 
        "(draw-cube [center-x center-y center-z] width height length color)\n\n"
        "Draw cube"
    },
    {"draw-cube-v", cfun_DrawCubeV, 
        "(draw-cube-v [center-x center-y center-z] [width height length] color)\n\n"
        "Draw cube (Vector version)"
    },
    {"draw-cube-wires", cfun_DrawCubeWires, 
        "(draw-cube-wires [center-x center-y center-z] width height length color)\n\n"
        "Draw cube wires"
    },
    {"draw-cube-wires-v", cfun_DrawCubeWiresV, 
        "(draw-cube-wires-v [center-x center-y center-z] [width height length] color)\n\n"
        "Draw cube wires (Vector version)"
    },
    {"draw-cube-texture", cfun_DrawCubeTexture, 
        "(draw-cube-texture texture [center-x center-y center-z] width height length color)\n\n"
        "Draw cube textured"
    },
    {"draw-grid", cfun_DrawGrid, 
        "(draw-grid slices spacing)\n\n"
        "Draw a grid (centered at (0, 0, 0))"
    },
    {"draw-sphere", cfun_DrawSphere, 
        "(draw-sphere [center-x center-y center-z] radius color)\n\n"
        "Draw sphere"
    },
    {"draw-sphere-ex", cfun_DrawSphereEx, 
        "(draw-sphere-ex [center-x center-y center-z] radius rings slices color)\n\n"
        "Draw sphere with extended parameters"
    },
    {"draw-sphere-wires", cfun_DrawSphereWires, 
        "(draw-sphere-wires [center-x center-y center-z] radius rings slices color)\n\n"
        "Draw sphere wires"
    },
    {"draw-cylinder", cfun_DrawCylinder, 
        "(draw-cylinder [center-x center-y center-z] radius-top radius-bottom height slices color)\n\n"
        "Draw a cylinder/cone"
    },
    {"draw-cylinder-wires", cfun_DrawCylinderWires, 
        "(draw-cylinder-wires [center-x center-y center-z] radius-top radius-bottom height slices color)\n\n"
        "Draw a cylinder/cone wires"
    },
    {"draw-plane", cfun_DrawPlane, 
        "(draw-plane [center-x center-y center-z] [height width] color)\n\n"
        "Draw a plane XZ"
    },
    {"draw-ray", cfun_DrawRay, 
        "(draw-ray ray color)\n\n"
        "Draw a ray line"
    },
    {NULL, NULL, NULL}
};
