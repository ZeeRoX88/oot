// ice arrow platform
u64 gMagicIcefloe1TLUT[] = {
#include "assets/objects/object_spot08_obj/iceberg_tlut_1.rgba16.inc.c"
};

u64 gMagicIcefloe2TLUT[] = {
#include "assets/objects/object_spot08_obj/iceberg_tlut_2.rgba16.inc.c"
};

u64 gMagicIcefloeUndersideTex[] = {
#include "assets/objects/object_spot08_obj/iceberg_underside.rgba16.inc.c"
};

u64 gMagicIcefloeSideTex[] = {
#include "assets/objects/object_spot08_obj/iceberg_side.ci4.inc.c"
};

u64 gMagicIcefloeTopTex[] = {
#include "assets/objects/object_spot08_obj/iceberg_top.ci4.inc.c"
};

Vtx magicicefloe_objVtx[] = {
#include "assets/objects/object_spot08_obj/object_spot08_objVtx_002970.vtx.inc"
};

Gfx gMagicIcefloeDL[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(gMagicIcefloeUndersideTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 8, 0, G_TX_NOMIRROR |
                         G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 6, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPClearGeometryMode(G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_CULL_BACK | G_FOG | G_LIGHTING),
    gsDPSetPrimColor(0, 0, 250, 220, 200, 255),
    gsSPVertex(magicicefloe_objVtx, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTextureBlock_4b(gMagicIcefloeSideTex, G_IM_FMT_CI, 64, 64, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal16(0, gMagicIcefloe1TLUT),
    gsSPVertex(&magicicefloe_objVtx[3], 14, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP2Triangles(2, 4, 3, 0, 4, 5, 3, 0),
    gsSP2Triangles(4, 6, 5, 0, 7, 5, 6, 0),
    gsSP2Triangles(6, 8, 7, 0, 9, 10, 11, 0),
    gsSP2Triangles(10, 9, 12, 0, 12, 13, 10, 0),
    gsSP2Triangles(13, 12, 1, 0, 1, 0, 13, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(gMagicIcefloeUndersideTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 8, 0, G_TX_NOMIRROR |
                         G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 6, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&magicicefloe_objVtx[17], 15, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
    gsSP1Triangle(12, 13, 14, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTextureBlock_4b(gMagicIcefloeTopTex, G_IM_FMT_CI, 64, 64, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadTLUT_pal16(0, gMagicIcefloe2TLUT),
    gsSPVertex(&magicicefloe_objVtx[32], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(0, 3, 4, 0, 0, 4, 5, 0),
    gsSPEndDisplayList(),
};

CamData gMagicIcefloeCol_camDataList_00002E10[] = {
    { 0x0000, 0, NULL },
};

SurfaceType gMagicIcefloeCol_surfaceType_00002E18[] = {
    { 0x00000000, 0x000007CC },
    { 0x0000A000, 0x000007CC }, // use { 0x00000000, 0x000007CC }, to make surface not slippery
};

CollisionPoly gMagicIcefloeCol_polygons_00002E28[] = {
    { 0x0000, 0x0000, 0x0001, 0x0002, 0x7FFF, 0x0000, 0x009A, 0xFA43 },
    { 0x0000, 0x0002, 0x0003, 0x0000, 0x69E7, 0xDB36, 0x3DC2, 0xF9D2 },
    { 0x0000, 0x0002, 0x0004, 0x0003, 0x3F77, 0x0010, 0x6F28, 0xFA43 },
    { 0x0000, 0x0004, 0x0005, 0x0003, 0xFF6A, 0xDB3A, 0x7A99, 0xF9D3 },
    { 0x0000, 0x0004, 0x0006, 0x0005, 0xBF8A, 0xFFFA, 0x6E94, 0xFA43 },
    { 0x0000, 0x0007, 0x0005, 0x0006, 0x9592, 0xDB23, 0x3CCE, 0xF9D2 },
    { 0x0000, 0x0006, 0x0008, 0x0007, 0x8001, 0x0000, 0xFF66, 0xFA43 },
    { 0x0000, 0x0008, 0x0009, 0x0007, 0x9619, 0xDB36, 0xC23E, 0xF9D2 },
    { 0x0000, 0x0009, 0x0008, 0x000A, 0xC089, 0x0010, 0x90D8, 0xFA43 },
    { 0x0000, 0x000A, 0x000B, 0x0009, 0x0096, 0xDB3A, 0x8567, 0xF9D3 },
    { 0x0000, 0x000B, 0x000A, 0x0001, 0x4076, 0xFFFA, 0x916C, 0xFA43 },
    { 0x0000, 0x0001, 0x0000, 0x000B, 0x6A6E, 0xDB23, 0xC332, 0xF9D2 },
    { 0x0000, 0x0005, 0x000C, 0x0003, 0xFFB3, 0x90B6, 0x3F3B, 0xF942 },
    { 0x0000, 0x0007, 0x000C, 0x0005, 0xC915, 0x90B9, 0x1F60, 0xF942 },
    { 0x0000, 0x0009, 0x000C, 0x0007, 0xC961, 0x90B6, 0xE026, 0xF942 },
    { 0x0000, 0x000B, 0x000C, 0x0009, 0x004D, 0x90B6, 0xC0C5, 0xF942 },
    { 0x0000, 0x0000, 0x000C, 0x000B, 0x36EB, 0x90B9, 0xE0A0, 0xF942 },
    { 0x0000, 0x0003, 0x000C, 0x0000, 0x369F, 0x90B6, 0x1FDA, 0xF942 },
    { 0x0001, 0x0001, 0x000A, 0x0008, 0x0000, 0x7FFF, 0x0000, 0xFF6A },
    { 0x0001, 0x0001, 0x0008, 0x0006, 0x0000, 0x7FFF, 0x0000, 0xFF6A },
    { 0x0001, 0x0001, 0x0006, 0x0004, 0x0000, 0x7FFF, 0x0000, 0xFF6A },
    { 0x0001, 0x0001, 0x0004, 0x0002, 0x0000, 0x7FFF, 0x0000, 0xFF6A },
};

Vec3s gMagicIcefloeCol_vtx_00002F88[] = {
    {   1469,  -1262,      7 },
    {   1473,    150,   -842 },
    {   1465,    150,    855 },
    {    729,  -1262,   1276 },
    {     -8,    150,   1696 },
    {   -740,  -1262,   1269 },
    {  -1473,    150,    842 },
    {  -1469,  -1262,     -7 },
    {  -1465,    150,   -855 },
    {   -729,  -1262,  -1276 },
    {      8,    150,  -1696 },
    {    740,  -1262,  -1269 },
    {      0,  -1985,      0 },
};

CollisionHeader gMagicIcefloeCol = { 
    { -1473, -1985, -1696 },
    { 1473, 150, 1696 },
    13,
    gMagicIcefloeCol_vtx_00002F88,
    22,
    gMagicIcefloeCol_polygons_00002E28,
    gMagicIcefloeCol_surfaceType_00002E18,
    gMagicIcefloeCol_camDataList_00002E10,
    0,
    NULL
};

