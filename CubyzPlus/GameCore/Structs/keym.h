#pragma once

#define DELETEA(p) if(p) { delete[] p; p = 0; }

struct keym
{
    enum
    {
        ACTION_DEFAULT = 0,
        ACTION_SPECTATOR,
        ACTION_EDITING,
        NUMACTIONS
    };

    int code;
    char* name;
    char* actions[NUMACTIONS];
    bool pressed;

    keym() : code(-1),
        name(NULL),
        pressed(false)
    {
        loopi(NUMACTIONS)
            actions[i] = newstring("");
    }

    ~keym() {
        DELETEA(name);

        loopi(NUMACTIONS)
            DELETEA(actions[i]);
    }
};