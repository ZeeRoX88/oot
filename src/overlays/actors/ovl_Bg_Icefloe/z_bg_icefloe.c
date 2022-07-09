/*
 * File: z_bg_icefloe.c
 * Overlay: ovl_Bg_Icefloe
 * Description: Ice Arrow floating ice platform
 */

#include "z_bg_icefloe.h"
#include "overlays/effects/ovl_Effect_Ss_Kakera/z_eff_ss_kakera.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS 0

void BgIcefloe_Init(Actor* thisx, PlayState* play);
void BgIcefloe_Destroy(Actor* thisx, PlayState* play);
void BgIcefloe_Update(Actor* thisx, PlayState* play);
void BgIcefloe_Draw(Actor* thisx, PlayState* play);

void BgIcefloe_SetupFloatNonrotating(BgIcefloe* this);
void BgIcefloe_FloatNonrotating(BgIcefloe* this, PlayState* play);
void BgIcefloe_Melt(BgIcefloe* this, PlayState* play);

const ActorInit Bg_Icefloe_InitVars = {
    ACTOR_BG_ICEFLOE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(BgIcefloe),
    (ActorFunc)BgIcefloe_Init,
    (ActorFunc)BgIcefloe_Destroy,
    (ActorFunc)BgIcefloe_Update,
    (ActorFunc)BgIcefloe_Draw,
};

static s16 sSpawnCount = 0; // count to limit the number of active spawns
static Color_RGBA8 sColorWhite = { 250, 250, 250, 100 };
static Color_RGBA8 sColorGray = { 180, 180, 180, 100 };
static Vec3f sUnitDirections[] = {
    { 0.0f, 0.7071f, 0.7071f },
    { 0.7071f, 0.7071f, 0.0f },
    { 0.0f, 0.7071f, -0.7071f },
    { -0.7071f, 0.7071f, 0.0f },
};

void BgIcefloe_SetupAction(BgIcefloe* this, BgIcefloeActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void BgIcefloe_Bobbing(BgIcefloe* this) {
    this->bobOffset = (Math_SinS(this->bobPhaseSlow) * 4.0f) + (Math_SinS(this->bobPhaseFast) * 3.0f);
}

/* void BgIcefloe_SinkUnderPlayer(BgIcefloe* this) {
    f32 target;
    f32 step;

    step = 0.2f;

    // Sink under Player's weight if standing on it
    target = (func_80043548(&this->dyna) ? -4.0f : 0.0f);

    Math_StepToF(&this->sinkOffset, target, step);
} */

void BgIcefloe_SetWaterline(BgIcefloe* this) {
    this->dyna.actor.world.pos.y = this->sinkOffset + this->bobOffset + this->dyna.actor.home.pos.y;
}

void BgIcefloe_SpawnFragments(BgIcefloe* this, PlayState* play) {
    Vec3f velocity;
    Vec3f pos;
    s32 i;
    Vec3f* dir;
    s32 life;
    Vec3f accel;
    f32 scale;

    accel.x = accel.z = 0.0f;
    accel.y = -1.0f;

    for (i = 0; i < ARRAY_COUNT(sUnitDirections); i++) {
        dir = &sUnitDirections[i];

        life = (s32)Rand_CenteredFloat(5.0f) + 12;
        scale = Rand_CenteredFloat(0.3f) + 0.6f;

        pos.x = this->dyna.actor.world.pos.x + (dir->x * this->dyna.actor.scale.x * 20.0f);
        pos.y = this->dyna.actor.world.pos.y + (dir->y * this->dyna.actor.scale.y * 20.0f) + 20.0f;
        pos.z = this->dyna.actor.world.pos.z + (dir->z * this->dyna.actor.scale.z * 20.0f);

        velocity.x = (Rand_ZeroOne() - 0.5f) * 10.0f;
        velocity.y = Rand_ZeroOne() * 20.0f;
        velocity.z = (Rand_ZeroOne() - 0.5f) * 10.0f;

        EffectSsEnIce_Spawn(play, &pos, scale, &velocity, &accel, &sColorWhite, &sColorGray, life);

        pos.x = this->dyna.actor.world.pos.x + (dir->x * this->dyna.actor.scale.x * 40.0f);
        pos.y = this->dyna.actor.world.pos.y + (dir->y * this->dyna.actor.scale.y * 40.0f) + 20.0f;
        pos.z = this->dyna.actor.world.pos.z + (dir->z * this->dyna.actor.scale.z * 40.0f);

        velocity.x = (Rand_ZeroOne() - 0.5f) * 8.0f;
        velocity.y = Rand_ZeroOne() * 10.0f;
        velocity.z = (Rand_ZeroOne() - 0.5f) * 8.0f;

        EffectSsEnIce_Spawn(play, &pos, scale, &velocity, &accel, &sColorWhite, &sColorGray, life);
    }
}

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 3000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 2200, ICHAIN_STOP),
};

void BgIcefloe_Init(Actor* thisx, PlayState* play) {
    BgIcefloe* this = (BgIcefloe*)thisx;
    CollisionHeader* colHeader = NULL;

    if (sSpawnCount >= 3) {
        Actor_Kill(&this->dyna.actor);
    } else {
        BgIcefloe_SpawnFragments(this, play);
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->dyna.actor.world.pos, 40, NA_SE_EV_ICE_FREEZE);
        sSpawnCount += 1;
    }

    this->timer = 400;

    DynaPolyActor_Init(&this->dyna, DPM_PLAYER);
    CollisionHeader_GetVirtual(&gMagicIcefloeCol, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    Actor_SetScale(&this->dyna.actor, 0.0f);

    this->bobPhaseSlow = (s32)(Rand_ZeroOne() * (0xFFFF + 0.5f));
    this->bobPhaseFast = (s32)(Rand_ZeroOne() * (0xFFFF + 0.5f));

    BgIcefloe_SetupFloatNonrotating(this);
}

void BgIcefloe_Destroy(Actor* thisx, PlayState* play) {
    BgIcefloe* this = (BgIcefloe*)thisx;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void BgIcefloe_SetupFloatNonrotating(BgIcefloe* this) {
    BgIcefloe_SetupAction(this, BgIcefloe_FloatNonrotating);
}

void BgIcefloe_FloatNonrotating(BgIcefloe* this, PlayState* play) {
    BgIcefloe_Bobbing(this);
    // BgIcefloe_SinkUnderPlayer(this);
    BgIcefloe_SetWaterline(this);
    this->dyna.actor.shape.rot.y = this->dyna.actor.home.rot.y;

    // increase size
    Math_SmoothStepToF(&this->dyna.actor.scale.x, 0.05f, 0.1f, 0.1f, 0.0f);
    this->dyna.actor.scale.z = this->dyna.actor.scale.x;
    this->dyna.actor.scale.y = this->dyna.actor.scale.x;

    if (this->timer != 0) {
        this->timer--;
    }
    if (this->timer == 0) {
        Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_ICE_MELT);
        BgIcefloe_SetupAction(this, BgIcefloe_Melt);
    }
}

void BgIcefloe_Melt(BgIcefloe* this, PlayState* play) {
    Vec3f accel;
    Vec3f vel;
    Vec3f pos;
    s32 i;

    accel.x = 0.0f;
    accel.y = this->dyna.actor.scale.y * 100.0f;
    accel.z = 0.0f;
    vel.x = 0.0f;
    vel.y = this->dyna.actor.scale.y * 100.0f;
    vel.z = 0.0f;

    for (i = 0; i < 1; i++) {
        pos.x = this->dyna.actor.world.pos.x;
        pos.y = this->dyna.actor.world.pos.y;
        pos.z = this->dyna.actor.world.pos.z;
        func_8002829C(play, &pos, &vel, &accel, &sColorWhite, &sColorGray, this->dyna.actor.scale.x * 100.0f * 10, this->dyna.actor.scale.x * 100.0f * 20 * 5);
    }

    Math_SmoothStepToF(&this->dyna.actor.scale.x, 0.0f, 0.1f, 0.1f, 0.0f);
    this->dyna.actor.scale.z = this->dyna.actor.scale.x;
    this->dyna.actor.scale.y = this->dyna.actor.scale.x;

    if (this->dyna.actor.scale.x <= 0.001f) {
        sSpawnCount -= 1;
        Actor_Kill(&this->dyna.actor);
    }
}

void BgIcefloe_Update(Actor* thisx, PlayState* play) {
    BgIcefloe* this = (BgIcefloe*)thisx;

    if (Rand_ZeroOne() < 0.05f) {
        this->bobIncrSlow = Rand_S16Offset(300, 100);
        this->bobIncrFast = Rand_S16Offset(800, 400);
    }

    this->bobPhaseSlow += this->bobIncrSlow;
    this->bobPhaseFast += this->bobIncrFast;

    if (this->actionFunc != NULL) {
        this->actionFunc(this, play);
    }
}

void BgIcefloe_Draw(Actor* thisx, PlayState* play) {
    BgIcefloe* this = (BgIcefloe*)thisx;

    Gfx_DrawDListOpa(play, gMagicIcefloeDL);
}
