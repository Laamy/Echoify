#pragma once

#include "physent.h"

#include "../Structs/entitylight.h"
#include "../Structs/animinterpinfo.h"

#define MAXANIMPARTS 3

#define loop(v,m) for(int v = 0; v < int(m); ++v)
#define loopi(m) loop(i,m)

struct occludequery;
struct ragdolldata;

struct dynent : physent                         // animated characters, or characters that can receive input
{
    bool k_left, k_right, k_up, k_down;         // see input code

    entitylight light;
    animinterpinfo animinterp[MAXANIMPARTS];
    ragdolldata* ragdoll;
    occludequery* query;
    int lastrendered;
    unsigned char occluded;

    dynent() : ragdoll(NULL), query(NULL), lastrendered(0), occluded(0)
    {
        reset();
    }

    ~dynent()
    {
#ifndef STANDALONE
        extern void cleanragdoll(dynent * d);
        if (ragdoll) cleanragdoll(this);
#endif
    }

    void stopmoving()
    {
        k_left = k_right = k_up = k_down = jumping = false;
        move = strafe = 0;
    }

    void reset()
    {
        physent::reset();
        stopmoving();
        loopi(MAXANIMPARTS) animinterp[i].reset();
    }

    vec abovehead() { return vec(o).add(vec(0, 0, aboveeye + 4)); }
};