#ifndef Z_BG_ICEFLOE_H
#define Z_BG_ICEFLOE_H

#include "ultra64.h"
#include "global.h"

struct BgIcefloe;

typedef void (*BgIcefloeActionFunc)(struct BgIcefloe*, PlayState*);

typedef struct BgIcefloe {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x0164 */ BgIcefloeActionFunc actionFunc;
    /* 0x018C */ s16 bobPhaseSlow;
    /* 0x018E */ s16 bobPhaseFast;
    /* 0x0190 */ s16 bobIncrSlow;
    /* 0x0192 */ s16 bobIncrFast;
    /* 0x0194 */ f32 sinkOffset;
    /* 0x0198 */ f32 bobOffset;
                 u16 timer;
} BgIcefloe; // size = 0x019C

#endif
