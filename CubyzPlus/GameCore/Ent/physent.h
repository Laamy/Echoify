#pragma once

enum { CS_ALIVE = 0, CS_DEAD, CS_SPAWNING, CS_LAGGED, CS_EDITING, CS_SPECTATOR };
enum { PHYS_FLOAT = 0, PHYS_FALL, PHYS_SLIDE, PHYS_SLOPE, PHYS_FLOOR, PHYS_STEP_UP, PHYS_STEP_DOWN, PHYS_BOUNCE };
enum { ENT_PLAYER = 0, ENT_AI, ENT_INANIMATE, ENT_CAMERA, ENT_BOUNCE };
enum { COLLIDE_NONE = 0, COLLIDE_ELLIPSE, COLLIDE_OBB, COLLIDE_ELLIPSE_PRECISE };

struct physent                                  // base entity type, can be affected by physics
{
    vec o, vel, falling;                        // origin, velocity
    vec deltapos, newpos;                       // movement interpolation
    float yaw, pitch, roll;
    float maxspeed;                             // cubes per second, 100 for player
    float radius, eyeheight, aboveeye;          // bounding box size
    float xradius, yradius, zmargin;
    vec floor;                                  // the normal of floor the dynent is on
    // chunk here is 256 bytes in size ^

    unsigned short timeinair;
    unsigned char inwater;
    bool jumping;
    char move, strafe;

    unsigned char physstate;                            // one of PHYS_* above
    unsigned char state, editstate;                     // one of CS_* above
    unsigned char type;                                 // one of ENT_* above
    unsigned char collidetype;                          // one of COLLIDE_* above           

    bool blocked;                               // used by physics to signal ai

    void resetinterp()
    {
        newpos = o;
        deltapos = vec(0, 0, 0);
    }

    void reset()
    {
        inwater = 0;
        timeinair = 0;
        jumping = false;
        strafe = move = 0;
        physstate = PHYS_FALL;
        vel = falling = vec(0, 0, 0);
        floor = vec(0, 0, 1);
    }

    vec feetpos(float offset = 0) const { return vec(o).add(vec(0, 0, offset - eyeheight)); }
    vec headpos(float offset = 0) const { return vec(o).add(vec(0, 0, offset)); }

    bool maymove() const { return timeinair || physstate < PHYS_FLOOR || vel.squaredlen() > 1e-4f || deltapos.squaredlen() > 1e-4f; }
};