static Janet cfun_LoadImage(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *fileName = janet_getcstring(argv, 0);
    Image *image = janet_abstract(&AT_Image, sizeof(Image));
    *image = LoadImage(fileName);
    return janet_wrap_abstract(image);
}

static Janet cfun_ImageDimensions(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Image image = *jaylib_getimage(argv, 0);
    Janet dim[2] = { janet_wrap_integer(image.width), janet_wrap_integer(image.height) };
    return janet_wrap_tuple(janet_tuple_n(dim, 2));
}

static Janet cfun_ExportImage(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Image image = *jaylib_getimage(argv, 0);
    const char *fileName = janet_getcstring(argv, 1);
    ExportImage(image, fileName);
    return janet_wrap_nil();
}

static Janet cfun_ExportImageAsCode(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Image image = *jaylib_getimage(argv, 0);
    const char *fileName = janet_getcstring(argv, 1);
    ExportImageAsCode(image, fileName);
    return janet_wrap_nil();
}

static Janet cfun_LoadTexture(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    const char *fileName = janet_getcstring(argv, 0);
    Texture2D *texture = janet_abstract(&AT_Texture2D, sizeof(Texture2D));
    *texture = LoadTexture(fileName);
    return janet_wrap_abstract(texture);
}

static Janet cfun_LoadTextureFromImage(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Image image = *jaylib_getimage(argv, 0);
    Texture2D *texture = janet_abstract(&AT_Texture2D, sizeof(Texture2D));
    *texture = LoadTextureFromImage(image);
    return janet_wrap_abstract(texture);
}

static Janet cfun_LoadTextureCubemap(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Image image = *jaylib_getimage(argv, 0);
    const uint8_t *kw = janet_getkeyword(argv, 1);
    int layoutType = 0;
    if (!janet_cstrcmp(kw, "auto-detect")) {
        layoutType = CUBEMAP_LAYOUT_AUTO_DETECT;
    } else if (!janet_cstrcmp(kw, "line-vertical")) {
        layoutType = CUBEMAP_LAYOUT_LINE_VERTICAL;
    } else if (!janet_cstrcmp(kw, "line-horizontal")) {
        layoutType = CUBEMAP_LAYOUT_LINE_HORIZONTAL;
    } else if (!janet_cstrcmp(kw, "3x4")) {
        layoutType = CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR;
    } else if (!janet_cstrcmp(kw,  "4x3")) {
        layoutType = CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE;
    } else if (!janet_cstrcmp(kw, "panorama")) {
        layoutType = CUBEMAP_LAYOUT_PANORAMA;
    } else {
        janet_panicf("unknown layout type %v", argv[1]);
    }
    TextureCubemap *cubemap = janet_abstract(&AT_TextureCubemap, sizeof(TextureCubemap));
    *cubemap = LoadTextureCubemap(image, layoutType);
    return janet_wrap_abstract(cubemap);
}

static Janet cfun_LoadRenderTexture(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    int width = janet_getinteger(argv, 0);
    int height = janet_getinteger(argv, 1);
    RenderTexture *texture = janet_abstract(&AT_RenderTexture, sizeof(RenderTexture));
    *texture = LoadRenderTexture(width, height);
    return janet_wrap_abstract(texture);
}

static Janet cfun_UnloadImage(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Image image = *jaylib_getimage(argv, 0);
    UnloadImage(image);
    return janet_wrap_nil();
}

static Janet cfun_UnloadTexture(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Texture2D texture = *jaylib_gettexture2d(argv, 0);
    UnloadTexture(texture);
    return janet_wrap_nil();
}

static Janet cfun_UnloadRenderTexture(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    RenderTexture texture = *jaylib_getrendertexture(argv, 0);
    UnloadRenderTexture(texture);
    return janet_wrap_nil();
}

static Janet cfun_GetTextureData(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Texture2D texture = *jaylib_gettexture2d(argv, 0);
    Image *image = janet_abstract(&AT_Image, sizeof(Image));
    *image = GetTextureData(texture);
    return janet_wrap_abstract(image);
}

static Janet cfun_GetScreenData(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    Image *image = janet_abstract(&AT_Image, sizeof(Image));
    *image = GetScreenData();
    return janet_wrap_abstract(image);
}

static Janet cfun_GetRenderTextureTexture2d(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  RenderTexture renderTexture = *jaylib_getrendertexture(argv, 0);
  Texture2D *texture = janet_abstract(&AT_Texture2D, sizeof(Texture2D));
  *texture = renderTexture.texture;
  return janet_wrap_abstract(texture);
}

static Janet cfun_ImageCopy(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Image image = *jaylib_getimage(argv, 0);
    Image *newImage = janet_abstract(&AT_Image, sizeof(Image));
    *newImage = ImageCopy(image);
    return janet_wrap_abstract(newImage);
}

static Janet cfun_ImageFromImage(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Image image = *jaylib_getimage(argv, 0);
    Rectangle rect = jaylib_getrect(argv, 1);
    Image *newImage = janet_abstract(&AT_Image, sizeof(Image));
    *newImage = ImageFromImage(image, rect);
    return janet_wrap_abstract(newImage);
}

static Janet cfun_ImageToPOT(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Image *image = jaylib_getimage(argv, 0);
    Color color = jaylib_getcolor(argv, 1);
    ImageToPOT(image, color);
    return argv[0];
}

static Janet cfun_ImageFormat(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Image *image = jaylib_getimage(argv, 0);
    int format = jaylib_getpixelformat(argv, 1);
    ImageFormat(image, format);
    return argv[0];
}

static Janet cfun_ImageAlphaMask(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Image *image = jaylib_getimage(argv, 0);
    Image *mask = jaylib_getimage(argv, 1);
    ImageAlphaMask(image, *mask);
    return argv[0];
}

static Janet cfun_ImageAlphaClear(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Image *image = jaylib_getimage(argv, 0);
    Color color = jaylib_getcolor(argv, 1);
    float threshold = (float) janet_getnumber(argv, 2);
    ImageAlphaClear(image, color, threshold);
    return argv[0];
}

static Janet cfun_ImageAlphaCrop(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Image *image = jaylib_getimage(argv, 0);
    float threshold = (float) janet_getnumber(argv, 1);
    ImageAlphaCrop(image, threshold);
    return argv[0];
}

static Janet cfun_ImageAlphaPremultiply(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Image *image = jaylib_getimage(argv, 0);
    ImageAlphaPremultiply(image);
    return argv[0];
}

static Janet cfun_ImageCrop(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Image *image = jaylib_getimage(argv, 0);
    Rectangle rect = jaylib_getrect(argv, 1);
    ImageCrop(image, rect);
    return argv[0];
}

static Janet cfun_ImageResize(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Image *image = jaylib_getimage(argv, 0);
    int newWidth = janet_getinteger(argv, 1);
    int newHeight = janet_getinteger(argv, 2);
    ImageResize(image, newWidth, newHeight);
    return argv[0];
}

static Janet cfun_ImageResizeNN(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Image *image = jaylib_getimage(argv, 0);
    int newWidth = janet_getinteger(argv, 1);
    int newHeight = janet_getinteger(argv, 2);
    ImageResizeNN(image, newWidth, newHeight);
    return argv[0];
}

static Janet cfun_ImageResizeCanvas(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    Image *image = jaylib_getimage(argv, 0);
    int newWidth = janet_getinteger(argv, 1);
    int newHeight = janet_getinteger(argv, 2);
    int offsetX = janet_getinteger(argv, 3);
    int offsetY = janet_getinteger(argv, 4);
    Color color = jaylib_getcolor(argv, 5);
    ImageResizeCanvas(image, newWidth, newHeight, offsetX, offsetY, color);
    return argv[0];
}

static Janet cfun_ImageMipmaps(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Image *image = jaylib_getimage(argv, 0);
    ImageMipmaps(image);
    return argv[0];
}

static Janet cfun_ImageDither(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    Image *image = jaylib_getimage(argv, 0);
    int rBpp = janet_getinteger(argv, 1);
    int gBpp = janet_getinteger(argv, 2);
    int bBpp = janet_getinteger(argv, 3);
    int aBpp = janet_getinteger(argv, 4);
    ImageDither(image, rBpp, gBpp, bBpp, aBpp);
    return argv[0];
}

static Janet cfun_LoadImagePalette(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Image *image = jaylib_getimage(argv, 0);
    int maxPaletteSize = janet_getinteger(argv, 1);
    int extractCount = 0;
    Color *colors = LoadImagePalette(*image, maxPaletteSize, &extractCount);
    JanetArray *acolors = janet_array(extractCount);
    for (int i = 0; i < extractCount; i++) {
        Color c = colors[i];
        Janet *t = janet_tuple_begin(4);
        t[0] = janet_wrap_integer(c.r);
        t[1] = janet_wrap_integer(c.g);
        t[2] = janet_wrap_integer(c.b);
        t[3] = janet_wrap_integer(c.a);
        janet_array_push(acolors, janet_wrap_tuple(janet_tuple_end(t)));
    }
    return janet_wrap_array(acolors);
}

static Janet cfun_ImageText(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    const char *text = janet_getcstring(argv, 0);
    int fontSize = janet_getinteger(argv, 1);
    Color color = jaylib_getcolor(argv, 2);
    Image *image = janet_abstract(&AT_Image, sizeof(Image));
    *image = ImageText(text, fontSize, color);
    return janet_wrap_abstract(image);
}

static Janet cfun_ImageTextEx(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    Font *font  = jaylib_getfont(argv, 0);
    const char *text = janet_getcstring(argv, 1);
    float fontSize = (float) janet_getnumber(argv, 2);
    float spacing = (float) janet_getnumber(argv, 3);
    Color color = jaylib_getcolor(argv, 4);
    Image *image = janet_abstract(&AT_Image, sizeof(Image));
    *image = ImageTextEx(*font, text, fontSize, spacing, color);
    return janet_wrap_abstract(image);
}

static Janet cfun_ImageDraw(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    Image *dst = jaylib_getimage(argv, 0);
    Image *src = jaylib_getimage(argv, 1);
    Rectangle srcRect = jaylib_getrect(argv, 2);
    Rectangle destRect = jaylib_getrect(argv, 3);
    Color tint = jaylib_getcolor(argv, 4);
    ImageDraw(dst, *src, srcRect, destRect, tint);
    return argv[0];
}

static Janet cfun_ImageDrawRectangleRec(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Image *dst = jaylib_getimage(argv, 0);
    Rectangle rec = jaylib_getrect(argv, 1);
    Color color = jaylib_getcolor(argv, 2);
    ImageDrawRectangleRec(dst, rec, color);
    return argv[0];
}

static Janet cfun_ImageDrawRectangleLines(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Image *dst = jaylib_getimage(argv, 0);
    Rectangle rec = jaylib_getrect(argv, 1);
    int thick = janet_getinteger(argv, 2);
    Color color = jaylib_getcolor(argv, 3);
    ImageDrawRectangleLines(dst, rec, thick, color);
    return argv[0];
}

static Janet cfun_ImageDrawText(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    Image *dst = jaylib_getimage(argv, 0);
    const char *text = janet_getcstring(argv, 1);
    int posX = janet_getinteger(argv, 2);
    int posY = janet_getinteger(argv, 3);
    int fontSize = janet_getinteger(argv, 4);
    Color color = jaylib_getcolor(argv, 5);
    ImageDrawText(dst, text, posX, posY, fontSize, color);
    return argv[0];
}

static Janet cfun_ImageDrawTextEx(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 7);
    Image *dst = jaylib_getimage(argv, 0);
    Font *font = jaylib_getfont(argv, 1);
    const char *text = janet_getcstring(argv, 2);
    Vector2 position = jaylib_getvec2(argv, 3);
    float fontSize = (float) janet_getnumber(argv, 4);
    float spacing = (float) janet_getnumber(argv, 5);
    Color color = jaylib_getcolor(argv, 6);
    ImageDrawTextEx(dst, *font, text, position, fontSize, spacing, color);
    return argv[0];
}

static Janet cfun_ImageFlipVertical(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Image *image = jaylib_getimage(argv, 0);
    ImageFlipVertical(image);
    return argv[0];
}

static Janet cfun_ImageFlipHorizontal(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Image *image = jaylib_getimage(argv, 0);
    ImageFlipHorizontal(image);
    return argv[0];
}

static Janet cfun_ImageRotateCW(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Image *image = jaylib_getimage(argv, 0);
    ImageRotateCCW(image);
    return argv[0];
}

static Janet cfun_ImageRotateCCW(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Image *image = jaylib_getimage(argv, 0);
    ImageRotateCCW(image);
    return argv[0];
}

static Janet cfun_ImageColorTint(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Image *image = jaylib_getimage(argv, 0);
    Color tint = jaylib_getcolor(argv, 1);
    ImageColorTint(image, tint);
    return argv[0];
}

static Janet cfun_ImageColorInvert(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Image *image = jaylib_getimage(argv, 0);
    ImageColorInvert(image);
    return argv[0];
}

static Janet cfun_ImageColorGrayscale(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Image *image = jaylib_getimage(argv, 0);
    ImageColorGrayscale(image);
    return argv[0];
}

static Janet cfun_ImageColorContrast(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Image *image = jaylib_getimage(argv, 0);
    float contrast = (float) janet_getnumber(argv, 1);
    ImageColorContrast(image, contrast);
    return argv[0];
}

static Janet cfun_ImageColorBrightness(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Image *image = jaylib_getimage(argv, 0);
    int brightness = janet_getinteger(argv, 1);
    ImageColorBrightness(image, brightness);
    return argv[0];
}

static Janet cfun_ImageColorReplace(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Image *image = jaylib_getimage(argv, 0);
    Color color = jaylib_getcolor(argv, 1);
    Color replace = jaylib_getcolor(argv, 2);
    ImageColorReplace(image, color, replace);
    return argv[0];
}

static Janet cfun_DrawTexture(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Texture2D texture = *jaylib_gettexture2d(argv, 0);
    int x = janet_getinteger(argv, 1);
    int y = janet_getinteger(argv, 2);
    Color color = jaylib_getcolor(argv, 3);
    DrawTexture(texture, x, y, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawTextureV(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    Texture2D texture = *jaylib_gettexture2d(argv, 0);
    Vector2 position = jaylib_getvec2(argv, 1);
    Color color = jaylib_getcolor(argv, 2);
    DrawTextureV(texture, position, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawTextureEx(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    Texture2D texture = *jaylib_gettexture2d(argv, 0);
    Vector2 position = jaylib_getvec2(argv, 1);
    float rotation = (float) janet_getnumber(argv, 2);
    float scale = (float) janet_getnumber(argv, 3);
    Color color = jaylib_getcolor(argv, 4);
    DrawTextureEx(texture, position, rotation, scale, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawTextureRec(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    Texture2D texture = *jaylib_gettexture2d(argv, 0);
    Rectangle rect = jaylib_getrect(argv, 1);
    Vector2 position = jaylib_getvec2(argv, 2);
    Color color = jaylib_getcolor(argv, 3);
    DrawTextureRec(texture, rect, position, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawTextureQuad(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    Texture2D texture = *jaylib_gettexture2d(argv, 0);
    Vector2 tiling = jaylib_getvec2(argv, 1);
    Vector2 offset = jaylib_getvec2(argv, 2);
    Rectangle quad = jaylib_getrect(argv, 3);
    Color color = jaylib_getcolor(argv, 3);
    DrawTextureQuad(texture, tiling, offset, quad, color);
    return janet_wrap_nil();
}

static Janet cfun_DrawTexturePro(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    Texture2D texture = *jaylib_gettexture2d(argv, 0);
    Rectangle rect = jaylib_getrect(argv, 1);
    Rectangle dest = jaylib_getrect(argv, 2);
    Vector2 position = jaylib_getvec2(argv, 3);
    float rotation = janet_getnumber(argv, 4);
    Color color = jaylib_getcolor(argv, 5);
    DrawTexturePro(texture, rect, dest, position, rotation, color);
    return janet_wrap_nil();
}

static Janet cfun_GenImageColor(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    int width = janet_getinteger(argv, 0);
    int height = janet_getinteger(argv, 1);
    Color color = jaylib_getcolor(argv, 2);
    Image *image = janet_abstract(&AT_Image, sizeof(Image));
    *image = GenImageColor(width, height, color);
    return janet_wrap_abstract(image);
}

static Janet cfun_GenImageGradientV(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    int width = janet_getinteger(argv, 0);
    int height = janet_getinteger(argv, 1);
    Color c1 = jaylib_getcolor(argv, 2);
    Color c2 = jaylib_getcolor(argv, 3);
    Image *image = janet_abstract(&AT_Image, sizeof(Image));
    *image = GenImageGradientV(width, height, c1, c2);
    return janet_wrap_abstract(image);
}

static Janet cfun_GenImageGradientH(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 4);
    int width = janet_getinteger(argv, 0);
    int height = janet_getinteger(argv, 1);
    Color c1 = jaylib_getcolor(argv, 2);
    Color c2 = jaylib_getcolor(argv, 3);
    Image *image = janet_abstract(&AT_Image, sizeof(Image));
    *image = GenImageGradientH(width, height, c1, c2);
    return janet_wrap_abstract(image);
}

static Janet cfun_GenImageGradientRadial(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    int width = janet_getinteger(argv, 0);
    int height = janet_getinteger(argv, 1);
    float density = (float) janet_getnumber(argv, 2);
    Color inner = jaylib_getcolor(argv, 3);
    Color outer = jaylib_getcolor(argv, 4);
    Image *image = janet_abstract(&AT_Image, sizeof(Image));
    *image = GenImageGradientRadial(width, height, density, inner, outer);
    return janet_wrap_abstract(image);
}

static Janet cfun_GenImageChecked(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 6);
    int width = janet_getinteger(argv, 0);
    int height = janet_getinteger(argv, 1);
    int checksX = janet_getinteger(argv, 2);
    int checksY = janet_getinteger(argv, 3);
    Color col1 = jaylib_getcolor(argv, 4);
    Color col2 = jaylib_getcolor(argv, 5);
    Image *image = janet_abstract(&AT_Image, sizeof(Image));
    *image = GenImageChecked(width, height, checksX, checksY, col1, col2);
    return janet_wrap_abstract(image);
}

static Janet cfun_GenImageWhiteNoise(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    int width = janet_getinteger(argv, 0);
    int height = janet_getinteger(argv, 1);
    float factor = (float) janet_getnumber(argv, 2);
    Image *image = janet_abstract(&AT_Image, sizeof(Image));
    *image = GenImageWhiteNoise(width, height, factor);
    return janet_wrap_abstract(image);
}

static Janet cfun_GenImagePerlinNoise(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 5);
    int width = janet_getinteger(argv, 0);
    int height = janet_getinteger(argv, 1);
    int offsetX = janet_getinteger(argv, 2);
    int offsetY = janet_getinteger(argv, 3);
    float factor = (float) janet_getnumber(argv, 4);
    Image *image = janet_abstract(&AT_Image, sizeof(Image));
    *image = GenImagePerlinNoise(width, height, offsetX, offsetY, factor);
    return janet_wrap_abstract(image);
}

static Janet cfun_GenImageCellular(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 3);
    int width = janet_getinteger(argv, 0);
    int height = janet_getinteger(argv, 1);
    int tileSize = janet_getinteger(argv, 2);
    Image *image = janet_abstract(&AT_Image, sizeof(Image));
    *image = GenImageCellular(width, height, tileSize);
    return janet_wrap_abstract(image);
}

static Janet cfun_GenTextureMipmaps(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Texture2D *texture = jaylib_gettexture2d(argv, 0);
    GenTextureMipmaps(texture);
    return argv[0];
}

static Janet cfun_SetTextureFilter(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Texture2D *texture = jaylib_gettexture2d(argv, 0);
    const uint8_t *kw = janet_getkeyword(argv, 1);
    int filter = 0;
    if (!janet_cstrcmp(kw, "point")) {
        filter = TEXTURE_FILTER_POINT;
    } else if (!janet_cstrcmp(kw, "bilinear")) {
        filter = TEXTURE_FILTER_BILINEAR;
    } else if (!janet_cstrcmp(kw, "trilinear")) {
        filter = TEXTURE_FILTER_TRILINEAR;
    } else if (!janet_cstrcmp(kw, "anisotropic-4x")) {
        filter = TEXTURE_FILTER_ANISOTROPIC_4X;
    } else if (!janet_cstrcmp(kw, "anisotropic-8x")) {
        filter = TEXTURE_FILTER_ANISOTROPIC_8X;
    } else if (!janet_cstrcmp(kw, "anisotropic-16x")) {
        filter = TEXTURE_FILTER_ANISOTROPIC_16X;
    } else {
        janet_panicf("unknown filter %v", argv[1]);
    }
    SetTextureFilter(*texture, filter);
    return janet_wrap_nil();
}

static Janet cfun_SetTextureWrap(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    Texture2D *texture = jaylib_gettexture2d(argv, 0);
    const uint8_t *kw = janet_getkeyword(argv, 1);
    int wrap = 0;
    if (!janet_cstrcmp(kw, "repeat")) {
        wrap = TEXTURE_WRAP_REPEAT;
    } else if (!janet_cstrcmp(kw, "clamp")) {
        wrap = TEXTURE_WRAP_CLAMP;
    } else if (!janet_cstrcmp(kw, "mirror-repeat")) {
        wrap = TEXTURE_WRAP_MIRROR_REPEAT;
    } else if (!janet_cstrcmp(kw, "mirror-clamp")) {
        wrap = TEXTURE_WRAP_MIRROR_CLAMP;
    } else {
        janet_panicf("unknown wrap-mode %v", argv[1]);
    }
    SetTextureWrap(*texture, wrap);
    return janet_wrap_nil();
}

static Janet cfun_GetImageDimensions(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    Image *src = jaylib_getimage(argv, 0);
    Vector2 dim = {
      src->width,
      src->height
    };
    return jaylib_wrap_vec2(dim);
}

/*
// Image/Texture2D data loading/unloading/saving functions
RLAPI Image LoadImagePro(void *data, int width, int height, int format);                                 // Load image from raw data with parameters
RLAPI Image LoadImageRaw(const char *fileName, int width, int height, int format, int headerSize);       // Load image from RAW file data
RLAPI Color *GetImageData(Image image);                                                                  // Get pixel data from image as a Color struct array
RLAPI Vector4 *GetImageDataNormalized(Image image);                                                      // Get pixel data from image as Vector4 array (float normalized)
RLAPI Rectangle GetImageAlphaBorder(Image image, float threshold);                                       // Get image alpha border rectangle
RLAPI int GetPixelDataSize(int width, int height, int format);                                           // Get pixel data size in bytes (image or texture)
RLAPI void UpdateTexture(Texture2D texture, const void *pixels);                                         // Update GPU texture with new data

// Texture2D drawing functions
RLAPI void DrawTextureNPatch(Texture2D texture, NPatchInfo nPatchInfo, Rectangle destRec, Vector2 origin, float rotation, Color tint);  // Draws a texture (or part of it) that stretches or shrinks nicely
*/

static const JanetReg image_cfuns[] = {
    {"load-image-1", cfun_LoadImage, NULL}, // load-image is janet core function, don't want to overwrite if we use (use jaylib)
    {"export-image", cfun_ExportImage, NULL},
    {"export-image-as-code", cfun_ExportImageAsCode, NULL},
    {"load-texture", cfun_LoadTexture, NULL},
    {"load-texture-from-image", cfun_LoadTextureFromImage,  NULL},
    {"load-texture-cubemap", cfun_LoadTextureCubemap, NULL},
    {"load-render-texture", cfun_LoadRenderTexture, NULL},
    {"unload-image", cfun_UnloadImage, NULL},
    {"unload-texture", cfun_UnloadTexture, NULL},
    {"unload-render-texture", cfun_UnloadRenderTexture, NULL},
    {"get-image-dimensions", cfun_GetImageDimensions, NULL},
    {"get-texture-data", cfun_GetTextureData, NULL},
    {"get-screen-data", cfun_GetScreenData, NULL},
    {"get-render-texture-texture2d", cfun_GetRenderTextureTexture2d, NULL},
    {"image-copy", cfun_ImageCopy, NULL},
    {"image-from-image", cfun_ImageFromImage, NULL},
    {"image-to-pot", cfun_ImageToPOT, NULL},
    {"image-format", cfun_ImageFormat, NULL},
    {"image-alpha-mask", cfun_ImageAlphaMask, NULL},
    {"image-alpha-clear", cfun_ImageAlphaClear, NULL},
    {"image-alpha-crop", cfun_ImageAlphaCrop, NULL},
    {"image-alpha-premultiply", cfun_ImageAlphaPremultiply, NULL},
    {"image-crop", cfun_ImageCrop, NULL},
    {"image-resize", cfun_ImageResize, NULL},
    {"image-resize-nn", cfun_ImageResizeNN, NULL},
    {"image-resize-canvas", cfun_ImageResizeCanvas, NULL},
    {"image-mipmaps", cfun_ImageMipmaps, NULL},
    {"image-dimensions", cfun_ImageDimensions, NULL},
    {"image-dither", cfun_ImageDither, NULL},
    {"load-image-pallete", cfun_LoadImagePalette, NULL},
    {"image-text", cfun_ImageText, NULL},
    {"image-text-ex", cfun_ImageTextEx, NULL},
    {"image-draw", cfun_ImageDraw, NULL},
    {"image-draw-rectangle-rec", cfun_ImageDrawRectangleRec, NULL},
    {"image-draw-rectangle-lines", cfun_ImageDrawRectangleLines, NULL},
    {"image-draw-text", cfun_ImageDrawText, NULL},
    {"image-draw-text-ex", cfun_ImageDrawTextEx, NULL},
    {"image-flip-vertical", cfun_ImageFlipVertical, NULL},
    {"image-flip-horizontal", cfun_ImageFlipHorizontal, NULL},
    {"image-rotate-cw", cfun_ImageRotateCW, NULL},
    {"image-rotate-ccw", cfun_ImageRotateCCW, NULL},
    {"image-color-tint", cfun_ImageColorTint, NULL},
    {"image-color-invert", cfun_ImageColorInvert, NULL},
    {"image-color-grayscale", cfun_ImageColorGrayscale, NULL},
    {"image-color-brightness", cfun_ImageColorBrightness, NULL},
    {"image-color-contrast", cfun_ImageColorContrast, NULL},
    {"image-color-replace", cfun_ImageColorReplace, NULL},
    {"draw-texture", cfun_DrawTexture, NULL},
    {"draw-texture-v", cfun_DrawTextureV, NULL},
    {"draw-texture-ex", cfun_DrawTextureEx, NULL},
    {"draw-texture-pro", cfun_DrawTexturePro, NULL},
    {"draw-texture-quad", cfun_DrawTextureQuad, NULL},
    {"draw-texture-rec", cfun_DrawTextureRec, NULL},
    {"gen-image-color", cfun_GenImageColor, NULL},
    {"gen-image-gradient-v", cfun_GenImageGradientV, NULL},
    {"gen-image-gradient-h", cfun_GenImageGradientH, NULL},
    {"gen-image-gradient-radial", cfun_GenImageGradientRadial, NULL},
    {"gen-image-checked", cfun_GenImageChecked, NULL},
    {"gen-image-white-noise", cfun_GenImageWhiteNoise, NULL},
    {"gen-image-perlin-noise", cfun_GenImagePerlinNoise, NULL},
    {"gen-image-cellular", cfun_GenImageCellular, NULL},
    {"gen-texture-mipmaps", cfun_GenTextureMipmaps, NULL},
    {"set-texture-filter", cfun_SetTextureFilter, NULL},
    {"set-texture-wrap", cfun_SetTextureWrap, NULL},
    {NULL, NULL, NULL}
};
