/*
Font LoadFontFromImage(Image image, Color key, int firstChar);                                    // Load font from Image (XNA style)
CharInfo *LoadFontData(const char *fileName, int fontSize, int *fontChars, int charsCount, int type); // Load font data for further use
Image GenImageFontAtlas(CharInfo *chars, int charsCount, int fontSize, int padding, int packMethod);  // Generate image font atlas using chars info
*/

/* Get a c like string, but also works with buffers. */
static const char *jaylib_getcstring(const Janet *argv, int32_t n) {
    if (janet_checktype(argv[n], JANET_BUFFER)) {
        JanetBuffer *buf = janet_unwrap_buffer(argv[n]);
        janet_buffer_push_u8(buf, 0);
        buf->count--;
        return (const char *)buf->data;
    }
    return janet_getcstring(argv, n);
}

static Janet cfun_GetFontDefault(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    Font *font = janet_abstract(&AT_Font, sizeof(Font));
    *font = GetFontDefault();
    return janet_wrap_abstract(font);
}

static Janet cfun_LoadFont(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *fileName = janet_getcstring(argv, 0);
    Font *font = janet_abstract(&AT_Font, sizeof(Font));
    *font = LoadFont(fileName);
    return janet_wrap_abstract(font);
}

static Janet cfun_LoadFontEx(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    const char *fileName = janet_getcstring(argv, 0);
    int fontSize = janet_getinteger(argv, 1);
    JanetView ints = janet_getindexed(argv, 2);
    int *raw_ints = janet_smalloc(sizeof(int) * ints.len);
    for (int32_t i = 0; i < ints.len; i++) {
        raw_ints[i] = janet_getinteger(ints.items, i);
    }
    Font *font = janet_abstract(&AT_Font, sizeof(Font));
    *font = LoadFontEx(fileName, fontSize, raw_ints, ints.len);
    janet_sfree(raw_ints);
    return janet_wrap_abstract(font);
}

static Janet cfun_UnloadFont(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Font font = *jaylib_getfont(argv, 0);
    UnloadFont(font);
    return janet_wrap_nil();
}

static Janet cfun_DrawFPS(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int x = janet_getinteger(argv, 0);
    int y = janet_getinteger(argv, 1);
    DrawFPS(x, y);
    return janet_wrap_nil();
}

static Janet cfun_DrawText(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    const char *text = jaylib_getcstring(argv, 0);
    int x = janet_getinteger(argv, 1);
    int y = janet_getinteger(argv, 2);
    int fontSize = janet_getinteger(argv, 3);
    Color color = jaylib_getcolor(argv, 4);
    DrawText(text, x, y, fontSize, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawTextEx(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    Font font = *jaylib_getfont(argv, 0);
    const char *text = jaylib_getcstring(argv, 1);
    Vector2 position = jaylib_getvec2(argv, 2);
    float fontSize = (float) janet_getnumber(argv, 3);
    float spacing = (float) janet_getnumber(argv, 4);
    Color color = jaylib_getcolor(argv, 5);
    DrawTextEx(font, text, position, fontSize, spacing, color);
    return janet_wrap_nil();
}

static Janet cfun_MeasureText(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    const char *text = jaylib_getcstring(argv, 0);
    int fontSize = janet_getinteger(argv, 1);
    return janet_wrap_integer(MeasureText(text, fontSize));
}

static Janet cfun_MeasureTextEx(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Font font = *jaylib_getfont(argv, 0);
    const char *text = jaylib_getcstring(argv, 1);
    float fontSize = (float) janet_getnumber(argv, 2);
    float spacing = (float) janet_getnumber(argv, 3);
    return jaylib_wrap_vec2(MeasureTextEx(font, text, fontSize, spacing));
}

static Janet cfun_GetGlyphIndex(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Font font = *jaylib_getfont(argv, 0);
    int character = janet_getinteger(argv, 1);
    return janet_wrap_integer(GetGlyphIndex(font, character));
}

static Janet cfun_GetFontTexture(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Font font = *jaylib_getfont(argv, 0);
    Texture2D *texture = janet_abstract(&AT_Texture2D, sizeof(Texture2D));
    *texture = font.texture;
    return janet_wrap_abstract(texture);
}

static JanetReg text_cfuns[] = {
    {"get-font-default", cfun_GetFontDefault, NULL},
    {"load-font", cfun_LoadFont, NULL},
    {"load-font-ex", cfun_LoadFontEx, NULL},
    {"unload-font", cfun_UnloadFont, NULL},
    {"draw-fps", cfun_DrawFPS, NULL},
    {"draw-text", cfun_DrawText, NULL},
    {"draw-text-ex", cfun_DrawTextEx, NULL},
    {"measure-text", cfun_MeasureText, NULL},
    {"measure-text-ex", cfun_MeasureTextEx, NULL},
    {"get-glyph-index", cfun_GetGlyphIndex, NULL},
    {"get-font-texture", cfun_GetFontTexture, NULL},
    {NULL, NULL, NULL}
};
