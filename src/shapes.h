static Janet cfun_DrawPixel(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    int posX = janet_getinteger(argv, 0);
    int posY = janet_getinteger(argv, 1);
    Color c = jaylib_getcolor(argv, 2);
    DrawPixel(posX, posY, c);
    return janet_wrap_nil();
}

static Janet cfun_DrawPixelV(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Vector2 pos = jaylib_getvec2(argv, 0);
    Color c = jaylib_getcolor(argv, 1);
    DrawPixelV(pos, c);
    return janet_wrap_nil();
}

static Janet cfun_DrawLine(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    int x1 = janet_getinteger(argv, 0);
    int y1 = janet_getinteger(argv, 1);
    int x2 = janet_getinteger(argv, 2);
    int y2 = janet_getinteger(argv, 3);
    Color c = jaylib_getcolor(argv, 4);
    DrawLine(x1, y1, x2, y2, c);
    return janet_wrap_nil();
}

static Janet cfun_DrawLineV(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Vector2 p1 = jaylib_getvec2(argv, 0);
    Vector2 p2 = jaylib_getvec2(argv, 1);
    Color c = jaylib_getcolor(argv, 2);
    DrawLineV(p1, p2, c);
    return janet_wrap_nil();
}

static Janet cfun_DrawLineEx(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Vector2 p1 = jaylib_getvec2(argv, 0);
    Vector2 p2 = jaylib_getvec2(argv, 1);
    float thick = (float) janet_getnumber(argv, 2);
    Color c = jaylib_getcolor(argv, 3);
    DrawLineEx(p1, p2, thick, c);
    return janet_wrap_nil();
}

static Janet cfun_DrawLineBezier(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Vector2 p1 = jaylib_getvec2(argv, 0);
    Vector2 p2 = jaylib_getvec2(argv, 1);
    float thick = (float) janet_getnumber(argv, 2);
    Color c = jaylib_getcolor(argv, 3);
    DrawLineBezier(p1, p2, thick, c);
    return janet_wrap_nil();
}

static Vector2 *jaylib_getvec2s(const Janet *argv, int32_t n, int32_t *len) {
    JanetView view = janet_getindexed(argv, n);
    Vector2 *mem = janet_smalloc(sizeof(Vector2) * view.len);
    for (int32_t i = 0; i < view.len; i++) {
        mem[i] = jaylib_getvec2(view.items, i);
    }
    *len = view.len;
    return mem;
}

static Janet cfun_DrawLineStrip(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int32_t len;
    Vector2 *points = jaylib_getvec2s(argv, 0, &len);
    Color c = jaylib_getcolor(argv, 1);
    DrawLineStrip(points, len, c);
    janet_sfree(points);
    return janet_wrap_nil();
}

static Janet cfun_DrawCircle(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    int centerX = janet_getinteger(argv, 0);
    int centerY = janet_getinteger(argv, 1);
    float radius = (float) janet_getnumber(argv, 2);
    Color c = jaylib_getcolor(argv, 3);
    DrawCircle(centerX, centerY, radius, c);
    return janet_wrap_nil();
}

static Janet cfun_DrawCircleV(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Vector2 center = jaylib_getvec2(argv, 0);
    float radius = (float) janet_getnumber(argv, 1);
    Color c = jaylib_getcolor(argv, 2);
    DrawCircleV(center, radius, c);
    return janet_wrap_nil();
}

static Janet cfun_DrawCircleSector(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    Vector2 center = jaylib_getvec2(argv, 0);
    float radius = (float) janet_getnumber(argv, 1);
    int startAngle = janet_getinteger(argv, 2);
    int endAngle = janet_getinteger(argv, 3);
    int segments = janet_getinteger(argv, 4);
    Color c = jaylib_getcolor(argv, 5);
    DrawCircleSector(center, radius, startAngle, endAngle, segments, c);
    return janet_wrap_nil();
}

static Janet cfun_DrawCircleSectorLines(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    Vector2 center = jaylib_getvec2(argv, 0);
    float radius = (float) janet_getnumber(argv, 1);
    int startAngle = janet_getinteger(argv, 2);
    int endAngle = janet_getinteger(argv, 3);
    int segments = janet_getinteger(argv, 4);
    Color c = jaylib_getcolor(argv, 5);
    DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, c);
    return janet_wrap_nil();
}

static Janet cfun_DrawCircleGradient(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    int centerX = janet_getinteger(argv, 0);
    int centerY = janet_getinteger(argv, 1);
    float radius = (float) janet_getnumber(argv, 2);
    Color c1 = jaylib_getcolor(argv, 3);
    Color c2 = jaylib_getcolor(argv, 4);
    DrawCircleGradient(centerX, centerY, radius, c1, c2);
    return janet_wrap_nil();
}

static Janet cfun_DrawCircleLines(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    int centerX = janet_getinteger(argv, 0);
    int centerY = janet_getinteger(argv, 1);
    float radius = (float) janet_getnumber(argv, 2);
    Color c = jaylib_getcolor(argv, 3);
    DrawCircleLines(centerX, centerY, radius, c);
    return janet_wrap_nil();
}

static Janet cfun_DrawRing(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 7);
    Vector2 center = jaylib_getvec2(argv, 0);
    float innerRadius = (float) janet_getnumber(argv, 1);
    float outerRadius = (float) janet_getnumber(argv, 2);
    int startAngle = janet_getinteger(argv, 3);
    int endAngle = janet_getinteger(argv, 4);
    int segments = janet_getinteger(argv, 5);
    Color color = jaylib_getcolor(argv, 6);
    DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawRingLines(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 7);
    Vector2 center = jaylib_getvec2(argv, 0);
    float innerRadius = (float) janet_getnumber(argv, 1);
    float outerRadius = (float) janet_getnumber(argv, 2);
    int startAngle = janet_getinteger(argv, 3);
    int endAngle = janet_getinteger(argv, 4);
    int segments = janet_getinteger(argv, 5);
    Color color = jaylib_getcolor(argv, 6);
    DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawRectangle(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    int posX = janet_getinteger(argv, 0);
    int posY = janet_getinteger(argv, 1);
    int width = janet_getinteger(argv, 2);
    int height = janet_getinteger(argv, 3);
    Color color = jaylib_getcolor(argv, 4);
    DrawRectangle(posX, posY, width, height, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawRectangleV(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Vector2 position = jaylib_getvec2(argv, 0);
    Vector2 size = jaylib_getvec2(argv, 1);
    Color color = jaylib_getcolor(argv, 2);
    DrawRectangleV(position, size, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawRectangleRec(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Rectangle rec = jaylib_getrect(argv, 0);
    Color color = jaylib_getcolor(argv, 1);
    DrawRectangleRec(rec, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawRectanglePro(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Rectangle rec = jaylib_getrect(argv, 0);
    Vector2 origin = jaylib_getvec2(argv, 1);
    float rotation = (float) janet_getnumber(argv, 2);
    Color color = jaylib_getcolor(argv, 3);
    DrawRectanglePro(rec, origin, rotation, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawRectangleGradientV(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    int posX = janet_getinteger(argv, 0);
    int posY = janet_getinteger(argv, 1);
    int width = janet_getinteger(argv, 2);
    int height = janet_getinteger(argv, 3);
    Color color1 = jaylib_getcolor(argv, 4);
    Color color2 = jaylib_getcolor(argv, 5);
    DrawRectangleGradientV(posX, posY, width, height, color1, color2);
    return janet_wrap_nil();
}

static Janet cfun_DrawRectangleGradientH(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    int posX = janet_getinteger(argv, 0);
    int posY = janet_getinteger(argv, 1);
    int width = janet_getinteger(argv, 2);
    int height = janet_getinteger(argv, 3);
    Color color1 = jaylib_getcolor(argv, 4);
    Color color2 = jaylib_getcolor(argv, 5);
    DrawRectangleGradientH(posX, posY, width, height, color1, color2);
    return janet_wrap_nil();
}

static Janet cfun_DrawRectangleGradientEx(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    Rectangle rec = jaylib_getrect(argv, 0);
    Color col1 = jaylib_getcolor(argv, 1);
    Color col2 = jaylib_getcolor(argv, 2);
    Color col3 = jaylib_getcolor(argv, 3);
    Color col4 = jaylib_getcolor(argv, 4);
    DrawRectangleGradientEx(rec, col1, col2, col3, col4);
    return janet_wrap_nil();
}

static Janet cfun_DrawRectangleLines(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    int posX = janet_getinteger(argv, 0);
    int posY = janet_getinteger(argv, 1);
    int width = janet_getinteger(argv, 2);
    int height = janet_getinteger(argv, 3);
    Color color = jaylib_getcolor(argv, 4);
    DrawRectangleLines(posX, posY, width, height, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawRectangleLinesEx(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Rectangle rec = jaylib_getrect(argv, 0);
    int lineThick = janet_getinteger(argv, 1);
    Color color = jaylib_getcolor(argv, 2);
    DrawRectangleLinesEx(rec, lineThick, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawRectangleRounded(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Rectangle rec = jaylib_getrect(argv, 0);
    float roundness = (float) janet_getnumber(argv, 1);
    int segments = janet_getinteger(argv, 2);
    Color color = jaylib_getcolor(argv, 3);
    DrawRectangleRounded(rec, roundness, segments, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawRectangleRoundedLines(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    Rectangle rec = jaylib_getrect(argv, 0);
    float roundness = (float) janet_getnumber(argv, 1);
    int segments = janet_getinteger(argv, 2);
    int lineThick = janet_getinteger(argv, 3);
    Color color = jaylib_getcolor(argv, 4);
    DrawRectangleRoundedLines(rec, roundness, segments, lineThick, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawTriangle(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Vector2 v1 = jaylib_getvec2(argv, 0);
    Vector2 v2 = jaylib_getvec2(argv, 1);
    Vector2 v3 = jaylib_getvec2(argv, 2);
    Color color = jaylib_getcolor(argv, 3);
    DrawTriangle(v1, v2, v3, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawTriangleLines(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Vector2 v1 = jaylib_getvec2(argv, 0);
    Vector2 v2 = jaylib_getvec2(argv, 1);
    Vector2 v3 = jaylib_getvec2(argv, 2);
    Color color = jaylib_getcolor(argv, 3);
    DrawTriangleLines(v1, v2, v3, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawTriangleFan(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int32_t len;
    Vector2 *points = jaylib_getvec2s(argv, 0, &len);
    Color color = jaylib_getcolor(argv, 1);
    DrawTriangleFan(points, len, color);
    janet_sfree(points);
    return janet_wrap_nil();
}

static Janet cfun_DrawTriangleStrip(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int32_t len;
    Vector2 *points = jaylib_getvec2s(argv, 0, &len);
    Color color = jaylib_getcolor(argv, 1);
    DrawTriangleStrip(points, len, color);
    janet_sfree(points);
    return janet_wrap_nil();
}

static Janet cfun_DrawPoly(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    Vector2 center = jaylib_getvec2(argv, 0);
    int sides = janet_getinteger(argv, 1);
    float radius = (float) janet_getnumber(argv, 2);
    float rotation = (float) janet_getnumber(argv, 3);
    Color color = jaylib_getcolor(argv, 4);
    DrawPoly(center, sides, radius, rotation, color);
    return janet_wrap_nil();
}

static Janet cfun_CheckCollisionRecs(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Rectangle rec1 = jaylib_getrect(argv, 0);
    Rectangle rec2 = jaylib_getrect(argv, 1);
    if (CheckCollisionRecs(rec1, rec2)) {
        return janet_wrap_true();
    } else {
        return janet_wrap_false();
    }
}

static Janet cfun_CheckCollisionCircles(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Vector2 center1 = jaylib_getvec2(argv, 0);
    float radius1 = (float) janet_getnumber(argv, 1);
    Vector2 center2 = jaylib_getvec2(argv, 2);
    float radius2 =  (float) janet_getnumber(argv, 3);
    if (CheckCollisionCircles(center1, radius1, center2, radius2)) {
        return janet_wrap_true();
    } else {
        return janet_wrap_false();
    }
}

static Janet cfun_CheckCollisionCircleRec(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Vector2 center = jaylib_getvec2(argv, 0);
    float radius = (float) janet_getnumber(argv, 1);
    Rectangle rec = jaylib_getrect(argv, 2);
    if (CheckCollisionCircleRec(center, radius, rec)) {
        return janet_wrap_true();
    } else {
        return janet_wrap_false();
    }
}

static Janet cfun_CheckCollisionPointRec(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Vector2 point = jaylib_getvec2(argv, 0);
    Rectangle rec = jaylib_getrect(argv, 1);
    if (CheckCollisionPointRec(point, rec)) {
        return janet_wrap_true();
    } else {
        return janet_wrap_false();
    }
}

static Janet cfun_CheckCollisionPointCircle(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Vector2 point = jaylib_getvec2(argv, 0);
    Vector2 center = jaylib_getvec2(argv, 1);
    float radius = (float) janet_getnumber(argv, 2);
    if (CheckCollisionPointCircle(point, center, radius)) {
        return janet_wrap_true();
    } else {
        return janet_wrap_false();
    }
}

static Janet cfun_CheckCollisionPointTriangle(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Vector2 point = jaylib_getvec2(argv, 0);
    Vector2 p1 = jaylib_getvec2(argv, 1);
    Vector2 p2 = jaylib_getvec2(argv, 2);
    Vector2 p3 = jaylib_getvec2(argv, 3);
    if (CheckCollisionPointTriangle(point, p1, p2, p3)) {
        return janet_wrap_true();
    } else {
        return janet_wrap_false();
    }
}

static Janet cfun_CheckCollisionPointPoly(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Vector2 point = jaylib_getvec2(argv, 0);
    JanetView polyPoints = janet_getindexed(argv, 1);
    Vector2 *rawPolyPoints = janet_smalloc(sizeof(Vector2) * polyPoints.len);
    for (int32_t i = 0; i < polyPoints.len; i++) {
        rawPolyPoints[i] = jaylib_getvec2(polyPoints.items, i);
    }
    Janet result;
    if (CheckCollisionPointPoly(point, rawPolyPoints, polyPoints.len)) {
        result = janet_wrap_true();
    } else {
        result = janet_wrap_false();
    }
    janet_sfree(rawPolyPoints);
    return result;
}

static Janet cfun_CheckCollisionLines(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Vector2 startPos1 = jaylib_getvec2(argv, 0);
    Vector2 endPos1 = jaylib_getvec2(argv, 1);
    Vector2 startPos2 = jaylib_getvec2(argv, 2);
    Vector2 endPos2 = jaylib_getvec2(argv, 3);
    Vector2 collisionPoint;
    if (CheckCollisionLines(startPos1, endPos1, startPos2, endPos2, &collisionPoint)) {
        return jaylib_wrap_vec2(collisionPoint);
    } else {
        return janet_wrap_nil();
    }
}

static Janet cfun_CheckCollisionPointLine(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Vector2 point = jaylib_getvec2(argv, 0);
    Vector2 p1 = jaylib_getvec2(argv, 1);
    Vector2 p2 = jaylib_getvec2(argv, 2);
    int threshold = janet_getinteger(argv, 3);
    if (CheckCollisionPointLine(point, p1, p2, threshold)) {
        return janet_wrap_true();
    } else {
        return janet_wrap_false();
    }
}

static Janet cfun_GetCollisionRec(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Rectangle rec1 = jaylib_getrect(argv, 0);
    Rectangle rec2 = jaylib_getrect(argv, 1);
    Rectangle res = GetCollisionRec(rec1, rec2);
    Janet *tup = janet_tuple_begin(4);
    tup[0] = janet_wrap_number(res.x);
    tup[1] = janet_wrap_number(res.y);
    tup[2] = janet_wrap_number(res.width);
    tup[3] = janet_wrap_number(res.height);
    return janet_wrap_tuple(janet_tuple_end(tup));
}

static JanetReg shapes_cfuns[] = {
    {"draw-pixel", cfun_DrawPixel, 
        "(draw-pixel pos-x pos-y color)\n\n"
        "Draw a pixel"
    },
    {"draw-pixel-v", cfun_DrawPixelV, 
        "(draw-pixel-v [pos-x pos-y] color)\n\n"
        "Draw a pixel (Vector version)"
    },
    {"draw-line", cfun_DrawLine, 
        "(draw-line start-pos-x start-pos-y end-pos-x end-pos-y color)\n\n"
        "Draw a line"
    },
    {"draw-line-v", cfun_DrawLineV, 
        "(draw-line-v [start-pos-x start-pos-y] [end-pos-x end-pos-y] color)\n\n"
        "Draw a line (Vector version)"
    },
    {"draw-line-ex", cfun_DrawLineEx, 
        "(draw-line-ex [start-pos-x start-pos-y] [end-pos-x end-pos-y] thick color)\n\n"
        "Draw a line defining thickness"
    },
    {"draw-line-bezier", cfun_DrawLineBezier, 
        "(draw-line-bezier [start-pos-x start-pos-y] [end-pos-x end-pos-y] thick color)\n\n"
        "Draw a line using cubic-bezier curves in-out"
    },
    {"draw-line-strip", cfun_DrawLineStrip, 
        "(draw-line-strip [a b] points-count color)\n\n"
        "Draw lines sequence"
    },
    {"draw-circle", cfun_DrawCircle, 
        "(draw-circle center-x center-y radius color)\n\n"
        "Draw a color-filled circle"
    },
    {"draw-circle-sector", cfun_DrawCircleSector, 
        "(draw-circle-sector [pos-x pos-y] radius start-angle end-angle segments color)\n\n"
        "Draw a piece of a circle"
    },
    {"draw-circle-sector-lines", cfun_DrawCircleSectorLines, 
        "(draw-circle-sector-lines [pos-x pos-y] radius start-angle end-angle segments color)\n\n"
        "Draw circle sector outline"
    },
    {"draw-circle-v", cfun_DrawCircleV, 
        "(draw-circle-v [pos-x pos-y] radius color)\n\n"
        "Draw a color-filled circle (Vector version)"
    },
    {"draw-circle-gradient", cfun_DrawCircleGradient, 
        "(draw-circle-gradient center-x center-y radius color-1 color-2)\n\n"
        "Draw a gradient-filled circle"
    },
    {"draw-circle-lines", cfun_DrawCircleLines, 
        "(draw-circle-lines center-x center-y radius color)\n\n"
        "Draw circle outline"
    },
    {"draw-ring", cfun_DrawRing, 
        "(draw-ring [pos-x pos-y] inner-radius outer-radius start-angle end-angle segments color)\n\n"
        "Draw ring"
    },
    {"draw-ring-lines", cfun_DrawRingLines, 
        "(draw-ring-lines [pos-x pos-y] inner-radius outer-radius start-angle end-angle segments color)\n\n"
        "Draw ring outline"
    },
    {"draw-rectangle", cfun_DrawRectangle, 
        "(draw-rectangle pos-x pos-y width height color)\n\n"
        "Draw a color-filled rectangle"
    },
    {"draw-rectangle-v", cfun_DrawRectangleV, 
        "(draw-rectangle-v [pos-x pos-y] [width height] color)\n\n"
        "Draw a color-filled rectangle (Vector version)"
    },
    {"draw-rectangle-rec", cfun_DrawRectangleRec, 
        "(draw-rectangle-rec rec color)\n\n"
        "Draw a color-filled rectangle"
    },
    {"draw-rectangle-pro", cfun_DrawRectanglePro, 
        "(draw-rectangle-pro rec origin rotation color)\n\n"
        "Draw a color-filled rectangle with pro parameters"
    },
    {"draw-rectangle-gradient-v", cfun_DrawRectangleGradientV, 
        "(draw-rectangle-gradient-v pos-x pos-y width height color-1 color-2)\n\n"
        "Draw a vertical-gradient-filled rectangle"
    },
    {"draw-rectangle-gradient-h", cfun_DrawRectangleGradientH, 
        "(draw-rectangle-gradient-h pos-x pos-y width height color-1 color-2)\n\n"
        "Draw a horizontal-gradient-filled rectangle"
    },
    {"draw-rectangle-gradient-ex", cfun_DrawRectangleGradientEx, 
        "(draw-rectangle-gradient-ex rec color-1 color-2 color-3 color-4)\n\n"
        "Draw a gradient-filled rectangle with custom vertex colors"
    },
    {"draw-rectangle-lines", cfun_DrawRectangleLines, 
        "(draw-rectangle-lines pos-x pos-y width height color)\n\n"
        "Draw rectangle outline"
    },
    {"draw-rectangle-lines-ex", cfun_DrawRectangleLinesEx, 
        "(draw-rectangle-lines-ex rec line-thick color)\n\n"
        "Draw rectangle outline with extended parameters"
    },
    {"draw-rectangle-rounded", cfun_DrawRectangleRounded, 
        "(draw-rectangle-rounded rec roundness segments color)\n\n"
        "Draw rectangle with rounded edges"
    },
    {"draw-rectangle-rounded-lines", cfun_DrawRectangleRoundedLines, 
        "(draw-rectangle-rounded-lines rec roundness segments line-thick color)\n\n"
        "Draw rectangle with rounded edges outline"
    },
    {"draw-triangle", cfun_DrawTriangle, 
        "(draw-triangle [x1 y1] [x2 y2] [x3 y3] color)\n\n"
        "Draw a color-filled triangle (vertex in counter-clockwise order!)"
    },
    {"draw-triangle-lines", cfun_DrawTriangleLines, 
        "(draw-triangle-lines [x1 y1] [x2 y2] [x3 y3] color)\n\n"
        "Draw triangle outline (vertex in counter-clockwise order!)"
    },
    {"draw-triangle-fan", cfun_DrawTriangleFan, 
        "(draw-triangle-fan [x y] points-count color)\n\n"
        "Draw a triangle fan defined by points (first vertex is the center)"
    },
    {"draw-triangle-strip", cfun_DrawTriangleStrip, 
        "(draw-triangle-strip [x y] points-count color)\n\n"
        "Draw a triangle strip defined by points"
    },
    {"draw-poly", cfun_DrawPoly, 
        "(draw-poly [pos-x pos-y] sides radius rotation color)\n\n"
        "Draw a regular polygon (Vector version)"
    },
    {"check-collision-recs", cfun_CheckCollisionRecs, 
        "(check-collision-recs rec-1 rec-2)\n\n"
        "Check collision between two rectangles"
    },
    {"check-collision-circles", cfun_CheckCollisionCircles, 
        "(check-collision-circles [x1 y1] r1 [x2 y2] r2)\n\n"
        "Check collision between two circles"
    },
    {"check-collision-circle-rec", cfun_CheckCollisionCircleRec, 
        "(check-collision-circle-rec [x y] radius rec)\n\n"
        "Check collision between circle and rectangle"
    },
    {"check-collision-point-rec", cfun_CheckCollisionPointRec, 
        "(check-collision-point-rec [x y] rec)\n\n"
        "Check if point is inside rectangle"
    },
    {"check-collision-point-circle", cfun_CheckCollisionPointCircle, 
        "(check-collision-point-circle [px py] [cx cy] r)\n\n"
        "Check if point is inside circle"
    },
    {"check-collision-point-triangle", cfun_CheckCollisionPointTriangle, 
        "(check-collision-point-triangle [px py] [x1 y1] [x2 y2] [x3 y3])\n\n"
        "Check if point is inside a triangle"
    },
    {"check-collision-point-poly", cfun_CheckCollisionPointPoly, 
        "(check-collision-point-poly [x y] vertices)\n\n"
        "Check if point is inside a polygon defined by the list of vertices"
    },
    {"check-collision-lines", cfun_CheckCollisionLines, 
        "(check-collision-lines [start-x1 start-y1] [end-x1 end-y1] [start-x2 start-y2] [end-x2 end-y2] [ret-x ret-y])\n\n"
        "Check the collision between two lines defined by two points each, returns collision point"
    },
    {"check-collision-point-line", cfun_CheckCollisionPointLine, 
        "(check-collision-point-line [px py] [start-x start-y] [end-x end-y] threshold)\n\n"
        "Check if point belongs to line created between two points [p1] "
        "and [p2] with defined margin in pixels [threshold]"
    },
    {"get-collision-rec", cfun_GetCollisionRec, 
        "(get-collision-rec rec1 rec2)\n\n"
        "Get collision rectangle for two rectangles collision"
    },
    {NULL, NULL, NULL}
};
