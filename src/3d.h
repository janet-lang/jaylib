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

static Janet cfun_DrawTriangle3D(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Vector3 v1 = jaylib_getvec3(argv, 0);
    Vector3 v2 = jaylib_getvec3(argv, 1);
    Vector3 v3 = jaylib_getvec3(argv, 2);
    Color color = jaylib_getcolor(argv, 3);
    DrawTriangle3D(v1, v2, v3, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawTriangleStrip3D(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    JanetView points = janet_getindexed(argv, 0);
    Vector3 *raw_points = janet_smalloc(sizeof(Vector3) * points.len);
    for (int32_t i = 0; i < points.len; i++) {
        raw_points[i] = jaylib_getvec3(points.items, i);
    }
    Color color = jaylib_getcolor(argv, 1);
    DrawTriangleStrip3D(raw_points, points.len, color);
    janet_sfree(raw_points);
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

static Janet cfun_DrawCylinderEx(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    Vector3 startPos = jaylib_getvec3(argv, 0);
    Vector3 endPos = jaylib_getvec3(argv, 1);
    float startRadius = (float) janet_getnumber(argv, 2);
    float endRadius = (float) janet_getnumber(argv, 3);
    int sides = janet_getinteger(argv, 4);
    Color color = jaylib_getcolor(argv, 5);
    DrawCylinderEx(startPos, endPos, startRadius, endRadius, sides, color);
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

static Janet cfun_DrawCylinderWiresEx(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    Vector3 startPos = jaylib_getvec3(argv, 0);
    Vector3 endPos = jaylib_getvec3(argv, 1);
    float startRadius = (float) janet_getnumber(argv, 2);
    float endRadius = (float) janet_getnumber(argv, 3);
    int sides = janet_getinteger(argv, 4);
    Color color = jaylib_getcolor(argv, 5);
    DrawCylinderWiresEx(startPos, endPos, startRadius, endRadius, sides, color);
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

static Janet cfun_DrawMesh(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Mesh mesh = *jaylib_getmesh(argv, 0);
    Material material = *jaylib_getmaterial(argv, 1);
    Matrix transform = jaylib_getmatrix(argv, 2);
    DrawMesh(mesh, material, transform);
    return janet_wrap_nil();
}

static Janet cfun_DrawMeshInstanced(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Mesh mesh = *jaylib_getmesh(argv, 0);
    Material material = *jaylib_getmaterial(argv, 1);
    JanetView transforms = janet_getindexed(argv, 2);
    Matrix *raw_transforms = janet_smalloc(sizeof(Matrix) * transforms.len);
    for (int32_t i = 0; i < transforms.len; i++) {
        raw_transforms[i] = jaylib_getmatrix(transforms.items, i);
    }
    DrawMeshInstanced(mesh, material, raw_transforms, transforms.len);
    janet_sfree(raw_transforms);
    return janet_wrap_nil();
}

static Janet cfun_GenMeshPoly(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int sides = janet_getinteger(argv, 0);
    float radius = (float) janet_getnumber(argv, 1);
    Mesh *polyMesh = janet_abstract(&AT_Mesh, sizeof(Mesh));
    *polyMesh = GenMeshPoly(sides, radius);
    return janet_wrap_abstract(polyMesh);
}

static Janet cfun_GenMeshPlane(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    float width = (float) janet_getnumber(argv, 0);
    float length = (float) janet_getnumber(argv, 1);
    int resX = janet_getinteger(argv, 2);
    int resY = janet_getinteger(argv, 3);
    Mesh *planeMesh = janet_abstract(&AT_Mesh, sizeof(Mesh));
    *planeMesh = GenMeshPlane(width, length, resX, resY);
    return janet_wrap_abstract(planeMesh);
}

static Janet cfun_GenMeshCube(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    float width = (float) janet_getnumber(argv, 0);
    float height = (float) janet_getnumber(argv, 1);
    float length = (float) janet_getnumber(argv, 2);
    Mesh *cubeMesh = janet_abstract(&AT_Mesh, sizeof(Mesh));
    *cubeMesh = GenMeshCube(width, height, length);
    return janet_wrap_abstract(cubeMesh);
}

static Janet cfun_GenMeshSphere(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    float radius = (float) janet_getnumber(argv, 0);
    int rings = janet_getinteger(argv, 1);
    int slices = janet_getinteger(argv, 2);
    Mesh *sphereMesh = janet_abstract(&AT_Mesh, sizeof(Mesh));
    *sphereMesh = GenMeshSphere(radius, rings, slices);
    return janet_wrap_abstract(sphereMesh);
}

static Janet cfun_GenMeshHemiSphere(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    float radius = (float) janet_getnumber(argv, 0);
    int rings = janet_getinteger(argv, 1);
    int slices = janet_getinteger(argv, 2);
    Mesh *sphereMesh = janet_abstract(&AT_Mesh, sizeof(Mesh));
    *sphereMesh = GenMeshHemiSphere(radius, rings, slices);
    return janet_wrap_abstract(sphereMesh);
}

static Janet cfun_GenMeshCylinder(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    float radius = (float) janet_getnumber(argv, 0);
    float height = (float) janet_getnumber(argv, 1);
    int slices = janet_getinteger(argv, 2);
    Mesh *cylinderMesh = janet_abstract(&AT_Mesh, sizeof(Mesh));
    *cylinderMesh = GenMeshCylinder(radius, height, slices);
    return janet_wrap_abstract(cylinderMesh);
}

static Janet cfun_GenMeshCone(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    float radius = (float) janet_getnumber(argv, 0);
    float height = (float) janet_getnumber(argv, 1);
    int slices = janet_getinteger(argv, 2);
    Mesh *coneMesh = janet_abstract(&AT_Mesh, sizeof(Mesh));
    *coneMesh = GenMeshCone(radius, height, slices);
    return janet_wrap_abstract(coneMesh);
}

static Janet cfun_GenMeshTorus(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    float radius = (float) janet_getnumber(argv, 0);
    float size = (float) janet_getnumber(argv, 1);
    int radSeg = janet_getinteger(argv, 2);
    int sides = janet_getinteger(argv, 3);
    Mesh *torusMesh = janet_abstract(&AT_Mesh, sizeof(Mesh));
    *torusMesh = GenMeshTorus(radius, size, radSeg, sides);
    return janet_wrap_abstract(torusMesh);
}

static Janet cfun_GenMeshKnot(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    float radius = (float) janet_getnumber(argv, 0);
    float size = (float) janet_getnumber(argv, 1);
    int radSeg = janet_getinteger(argv, 2);
    int sides = janet_getinteger(argv, 3);
    Mesh *knotMesh = janet_abstract(&AT_Mesh, sizeof(Mesh));
    *knotMesh = GenMeshKnot(radius, size, radSeg, sides);
    return janet_wrap_abstract(knotMesh);
}

static Janet cfun_GenMeshHeightmap(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Image image = *jaylib_getimage(argv, 0);
    Vector3 size = jaylib_getvec3(argv, 1);
    Mesh *mapMesh = janet_abstract(&AT_Mesh, sizeof(Mesh));
    *mapMesh = GenMeshHeightmap(image, size);
    return janet_wrap_abstract(mapMesh);
}

static Janet cfun_GenMeshCubicmap(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Image image = *jaylib_getimage(argv, 0);
    Vector3 size = jaylib_getvec3(argv, 1);
    Mesh *mapMesh = janet_abstract(&AT_Mesh, sizeof(Mesh));
    *mapMesh = GenMeshCubicmap(image, size);
    return janet_wrap_abstract(mapMesh);
}

static Janet cfun_LoadMaterials(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *fileName = janet_getcstring(argv, 0);
    int materialCount;
    Material *materials = LoadMaterials(fileName, &materialCount);
    JanetArray *array = janet_array(materialCount);
    array->count = materialCount;
    // materials might be null, but only when materialCount is 0
    // in which case we never dereference it
    for (int i = 0; i < materialCount; i++) {
        Material *material = janet_abstract(&AT_Material, sizeof(Material));
        *material = materials[i];
        array->data[i] = janet_wrap_abstract(material);
    }
    if (materials) {
        MemFree(materials);
    }
    return janet_wrap_array(array);
}

static Janet cfun_LoadMaterialDefault(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 0);
    Material *defaultMaterial = janet_abstract(&AT_Material, sizeof(Material));
    *defaultMaterial = LoadMaterialDefault();
    return janet_wrap_abstract(defaultMaterial);
}

static Janet cfun_UnloadMaterial(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Material *material = jaylib_getmaterial(argv, 0);
    UnloadMaterial(*material);
    return janet_wrap_nil();
}

static Janet cfun_SetMaterialTexture(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Material *material = jaylib_getmaterial(argv, 0);
    int mapType = jaylib_getmaterialmaptype(argv, 1);
    Texture2D *texture = jaylib_gettexture2d(argv, 2);
    SetMaterialTexture(material, mapType, *texture);
    return janet_wrap_nil();
}

static Janet cfun_SetModelMeshMaterial(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Model *model = jaylib_getmodel(argv, 0);
    int meshID = janet_getinteger(argv, 1);
    int materialID = janet_getinteger(argv, 2);
    SetModelMeshMaterial(model, meshID, materialID);
    return janet_wrap_nil();
}

static Janet cfun_LoadModel(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *fileName = janet_getcstring(argv, 0);
    Model *model = janet_abstract(&AT_Model, sizeof(Model));
    *model = LoadModel(fileName);
    return janet_wrap_abstract(model);
}

static Janet cfun_LoadModelFromMesh(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Mesh *mesh = jaylib_getmesh(argv, 0);
    Model *model = janet_abstract(&AT_Model, sizeof(Model));
    *model = LoadModelFromMesh(*mesh);
    return janet_wrap_abstract(model);
}

static Janet cfun_UnloadModel(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Model *model = jaylib_getmodel(argv, 0);
    UnloadModel(*model);
    return janet_wrap_nil();
}

static Janet cfun_GetModelBoundingBox(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Model *model = jaylib_getmodel(argv, 0);
    BoundingBox bbox = GetModelBoundingBox(*model);
    Janet *tup = janet_tuple_begin(2);
    tup[0] = jaylib_wrap_vec3(bbox.min);
    tup[1] = jaylib_wrap_vec3(bbox.max);
    return janet_wrap_tuple(janet_tuple_end(tup));
}

static Janet cfun_ExportMesh(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Mesh *mesh = jaylib_getmesh(argv, 0);
    const char *fileName = janet_getcstring(argv, 1);
    bool success = ExportMesh(*mesh, fileName);
    return janet_wrap_boolean(success);
}

static Janet cfun_UploadMesh(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Mesh *mesh = jaylib_getmesh(argv, 0);
    bool dynamic = janet_getboolean(argv, 1);
    UploadMesh(mesh, dynamic);
    return janet_wrap_nil();
}

static Janet cfun_UnloadMesh(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Mesh *mesh = jaylib_getmesh(argv, 0);
    UnloadMesh(*mesh);
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
    {"draw-triangle-3d", cfun_DrawTriangle3D, 
        "(draw-triangle-3d v1 v2 v3 color)\n\n"
        "Draw a triangle in 3D world space"
    },
    {"draw-triangle-strip-3d", cfun_DrawTriangleStrip3D, 
        "(draw-triangle-strip-3d points color)\n\n"
        "Draw a triangle strip in 3D world space"
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
    {"draw-cylinder-ex", cfun_DrawCylinderEx, 
        "(draw-cylinder-ex start-pos end-pos start-radius end-radius sides color)\n\n"
        "Draw a cylinder with base at startPos and top at endPos"
    },
    {"draw-cylinder-wires", cfun_DrawCylinderWires, 
        "(draw-cylinder-wires [center-x center-y center-z] radius-top radius-bottom height slices color)\n\n"
        "Draw a cylinder/cone wires"
    },
    {"draw-cylinder-wires-ex", cfun_DrawCylinderWiresEx, 
        "(draw-cylinder-wires-ex start-pos end-pos start-radius end-radius sides color)\n\n"
        "Draw a cylinder wires with base at startPos and top at endPos"
    },
    {"draw-plane", cfun_DrawPlane, 
        "(draw-plane [center-x center-y center-z] [height width] color)\n\n"
        "Draw a plane XZ"
    },
    {"draw-ray", cfun_DrawRay, 
        "(draw-ray ray color)\n\n"
        "Draw a ray line"
    },
    {"draw-mesh", cfun_DrawMesh,
        "(draw-mesh mesh material transform)\n\n"
        "Draw a mesh with material and transform"    
    },
    {"draw-mesh-instanced", cfun_DrawMeshInstanced,
        "(draw-mesh-instanced mesh material transforms)\n\n"
        "Draw multiple mesh instances with material and different transforms"    
    },
    {"load-materials", cfun_LoadMaterials,
        "(load-materials filename)\n\n"
        "Load materials from model file"
    },
    {"load-material-default", cfun_LoadMaterialDefault,
        "(load-material-default)\n\n"
        "Load and return the default material"    
    },
    {"unload-material", cfun_UnloadMaterial,
        "(unload-material material)\n\n"
        "Unload material from GPU memory (VRAM)"    
    },
    {"set-material-texture", cfun_SetMaterialTexture,
        "(set-material-texture material map-type texture)\n\n"
        "Set texture for a material map type (:diffuse, :specular...)"    
    },
    {"set-model-mesh-material", cfun_SetModelMeshMaterial,
        "(set-model-mesh-material model mesh-id material-id)\n\n"
        "Set material for a mesh"    
    },
    {"gen-mesh-poly", cfun_GenMeshPoly,
        "(gen-mesh-poly sides radius)\n\n"
        "Generate a polygonal mesh with given number of sides and radius"    
    },
    {"gen-mesh-plane", cfun_GenMeshPlane,
        "(gen-mesh-plane width length res-x res-y)\n\n"
        "Generate a plane mesh with given dimensions and subdivisions"    
    },
    {"gen-mesh-cube", cfun_GenMeshCube,
        "(gen-mesh-cube width height length)\n\n"
        "Generate a cube mesh with given dimensions"    
    },
    {"gen-mesh-sphere", cfun_GenMeshSphere,
        "(gen-mesh-sphere radius rings slices)\n\n"
        "Generate a sphere mesh with given dimensions"    
    },
    {"gen-mesh-hemisphere", cfun_GenMeshHemiSphere,
        "(gen-mesh-hemisphere radius rings slices)\n\n"
        "Generate a hemisphere mesh with given dimensions (no bottom cap)"    
    },
    {"gen-mesh-cylinder", cfun_GenMeshCylinder,
        "(gen-mesh-cylinder radius height slices)\n\n"
        "Generate a cylinder mesh with given dimensions"    
    },
    {"gen-mesh-cone", cfun_GenMeshCone,
        "(gen-mesh-cone radius height slices)\n\n"
        "Generate a cone mesh with given dimensions"    
    },
    {"gen-mesh-torus", cfun_GenMeshTorus,
        "(gen-mesh-torus radius size rad-seg sides)\n\n"
        "Generate a torus mesh with given dimensions"    
    },
    {"gen-mesh-knot", cfun_GenMeshKnot,
        "(gen-mesh-knot radius size rad-seg sides)\n\n"
        "Generate a trefoil knot mesh with given dimensions"    
    },
    {"gen-mesh-heightmap", cfun_GenMeshHeightmap,
        "(gen-mesh-heightmap image size)\n\n"
        "Generate a heightmap mesh from image data and size (vec3)"    
    },
    {"gen-mesh-cubicmap", cfun_GenMeshCubicmap,
        "(gen-mesh-cubicmap image size)\n\n"
        "Generate a cubicmap mesh from image data and size (vec3)"    
    },
    {"load-model", cfun_LoadModel,
        "(load-model filename)\n\n"
        "Load model from files (meshes and materials)"    
    },
    {"load-model-from-mesh", cfun_LoadModelFromMesh,
        "(load-model-from-mesh mesh)\n\n"
        "Load model from generated mesh (default material)"    
    },
    {"unload-model", cfun_UnloadModel,
        "(unload-model model)\n\n"
        "Unload model (including meshes) from memory (RAM and/or VRAM)"    
    },
    {"get-model-bounding-box", cfun_GetModelBoundingBox,
        "(get-model-bounding-box model)\n\n"
        "Compute model bounding box limits (considers all meshes). Returns [[min-x min-y min-z] [max-x max-y max-z]]"    
    },
    {"export-mesh", cfun_ExportMesh,
        "(export-mesh mesh filename)\n\n"
        "Export mesh data to file, returns true on success"    
    },
    {"upload-mesh", cfun_UploadMesh,
        "(upload-mesh mesh dynamic)\n\n"
        "Upload mesh vertex data in GPU and provide VAO/VBO ids"    
    },
    {"unload-mesh", cfun_UnloadMesh,
        "(unload-mesh mesh)\n\n"
        "Unload mesh data from CPU and GPU"    
    },
    {NULL, NULL, NULL}
};
