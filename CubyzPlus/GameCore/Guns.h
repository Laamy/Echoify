#pragma once

enum { AI_NONE = 0, AI_BOT, AI_MAX };

enum { GUN_FIST = 0, GUN_SG, GUN_CG, GUN_RL, GUN_RIFLE, GUN_GL, GUN_PISTOL, GUN_FIREBALL, GUN_ICEBALL, GUN_SLIMEBALL, GUN_BITE, GUN_BARREL, NUMGUNS };
enum { A_BLUE, A_GREEN, A_YELLOW };     // armour types... take 20/40/60 % off
enum { M_NONE = 0, M_SEARCH, M_HOME, M_ATTACKING, M_PAIN, M_SLEEP, M_AIMING };  // monster states

enum
{
    S_JUMP = 0, S_LAND, S_RIFLE, S_PUNCH1, S_SG, S_CG,
    S_RLFIRE, S_RLHIT, S_WEAPLOAD, S_ITEMAMMO, S_ITEMHEALTH,
    S_ITEMARMOUR, S_ITEMPUP, S_ITEMSPAWN, S_TELEPORT, S_NOAMMO, S_PUPOUT,
    S_PAIN1, S_PAIN2, S_PAIN3, S_PAIN4, S_PAIN5, S_PAIN6,
    S_DIE1, S_DIE2,
    S_FLAUNCH, S_FEXPLODE,
    S_SPLASH1, S_SPLASH2,
    S_GRUNT1, S_GRUNT2, S_RUMBLE,
    S_PAINO,
    S_PAINR, S_DEATHR,
    S_PAINE, S_DEATHE,
    S_PAINS, S_DEATHS,
    S_PAINB, S_DEATHB,
    S_PAINP, S_PIGGR2,
    S_PAINH, S_DEATHH,
    S_PAIND, S_DEATHD,
    S_PIGR1, S_ICEBALL, S_SLIMEBALL,
    S_JUMPPAD, S_PISTOL,

    S_V_BASECAP, S_V_BASELOST,
    S_V_FIGHT,
    S_V_BOOST, S_V_BOOST10,
    S_V_QUAD, S_V_QUAD10,
    S_V_RESPAWNPOINT,

    S_FLAGPICKUP,
    S_FLAGDROP,
    S_FLAGRETURN,
    S_FLAGSCORE,
    S_FLAGRESET,

    S_BURN,
    S_CHAINSAW_ATTACK,
    S_CHAINSAW_IDLE,

    S_HIT,

    S_FLAGFAIL
};

// renderparticles
enum
{
    PART_BLOOD = 0,
    PART_WATER,
    PART_SMOKE,
    PART_STEAM,
    PART_FLAME,
    PART_FIREBALL1, PART_FIREBALL2, PART_FIREBALL3,
    PART_STREAK, PART_LIGHTNING,
    PART_EXPLOSION, PART_EXPLOSION_BLUE,
    PART_SPARK, PART_EDIT,
    PART_SNOW,
    PART_MUZZLE_FLASH1, PART_MUZZLE_FLASH2, PART_MUZZLE_FLASH3,
    PART_HUD_ICON,
    PART_HUD_ICON_GREY,
    PART_TEXT,
    PART_TEXT_ICON,
    PART_METER, PART_METER_VS,
    PART_LENS_FLARE
};

static const struct guninfo { int sound, attackdelay, damage, spread, projspeed, kickamount, range, rays, hitpush, exprad, ttl; const char* name, * file; short part; } guns[NUMGUNS] =
{
    { S_PUNCH1,    250,  50,   0,   0,  0,   14,  1,  80,  0,    0, "fist",            "fist",   0 },
    { S_SG,       1400,  10, 400,   0, 20, 1024, 20,  80,  0,    0, "shotgun",         "shotg",  0 },
    { S_CG,        100,  30, 100,   0,  7, 1024,  1,  80,  0,    0, "chaingun",        "chaing", 0 },
    { S_RLFIRE,    800, 120,   0, 320, 10, 1024,  1, 160, 40,    0, "rocketlauncher",  "rocket", 0 },
    { S_RIFLE,    1500, 100,   0,   0, 30, 2048,  1,  80,  0,    0, "rifle",           "rifle",  0 },
    { S_FLAUNCH,   600,  90,   0, 200, 10, 1024,  1, 250, 45, 1500, "grenadelauncher", "gl",     0 },
    { S_PISTOL,    500,  35,  50,   0,  7, 1024,  1,  80,  0,    0, "pistol",          "pistol", 0 },
    { S_FLAUNCH,   200,  20,   0, 200,  1, 1024,  1,  80, 40,    0, "fireball",        nullptr,     PART_FIREBALL1 },
    { S_ICEBALL,   200,  40,   0, 120,  1, 1024,  1,  80, 40,    0, "iceball",         nullptr,     PART_FIREBALL2 },
    { S_SLIMEBALL, 200,  30,   0, 640,  1, 1024,  1,  80, 40,    0, "slimeball",       nullptr,     PART_FIREBALL3 },
    { S_PIGR1,     250,  50,   0,   0,  1,   12,  1,  80,  0,    0, "bite",            nullptr,     0 },
    { -1,            0, 120,   0,   0,  0,    0,  1,  80, 40,    0, "barrel",          nullptr,     0 }
};