#pragma once

#include "dynent.h"
#include "fpsstate.h"
#include "../Structs/editinfo.h"

#define MAXSTRLEN 260
typedef char string[MAXSTRLEN];

enum
{
    N_CONNECT = 0, N_SERVINFO, N_WELCOME, N_INITCLIENT, N_POS, N_TEXT, N_SOUND, N_CDIS,
    N_SHOOT, N_EXPLODE, N_SUICIDE,
    N_DIED, N_DAMAGE, N_HITPUSH, N_SHOTFX, N_EXPLODEFX,
    N_TRYSPAWN, N_SPAWNSTATE, N_SPAWN, N_FORCEDEATH,
    N_GUNSELECT, N_TAUNT,
    N_MAPCHANGE, N_MAPVOTE, N_TEAMINFO, N_ITEMSPAWN, N_ITEMPICKUP, N_ITEMACC, N_TELEPORT, N_JUMPPAD,
    N_PING, N_PONG, N_CLIENTPING,
    N_TIMEUP, N_FORCEINTERMISSION,
    N_SERVMSG, N_ITEMLIST, N_RESUME,
    N_EDITMODE, N_EDITENT, N_EDITF, N_EDITT, N_EDITM, N_FLIP, N_COPY, N_PASTE, N_ROTATE, N_REPLACE, N_DELCUBE, N_REMIP, N_EDITVSLOT, N_UNDO, N_REDO, N_NEWMAP, N_GETMAP, N_SENDMAP, N_CLIPBOARD, N_EDITVAR,
    N_MASTERMODE, N_KICK, N_CLEARBANS, N_CURRENTMASTER, N_SPECTATOR, N_SETMASTER, N_SETTEAM,
    N_BASES, N_BASEINFO, N_BASESCORE, N_REPAMMO, N_BASEREGEN, N_ANNOUNCE,
    N_LISTDEMOS, N_SENDDEMOLIST, N_GETDEMO, N_SENDDEMO,
    N_DEMOPLAYBACK, N_RECORDDEMO, N_STOPDEMO, N_CLEARDEMOS,
    N_TAKEFLAG, N_RETURNFLAG, N_RESETFLAG, N_INVISFLAG, N_TRYDROPFLAG, N_DROPFLAG, N_SCOREFLAG, N_INITFLAGS,
    N_SAYTEAM,
    N_CLIENT,
    N_AUTHTRY, N_AUTHKICK, N_AUTHCHAL, N_AUTHANS, N_REQAUTH,
    N_PAUSEGAME, N_GAMESPEED,
    N_ADDBOT, N_DELBOT, N_INITAI, N_FROMAI, N_BOTLIMIT, N_BOTBALANCE,
    N_MAPCRC, N_CHECKMAPS,
    N_SWITCHNAME, N_SWITCHMODEL, N_SWITCHTEAM,
    N_INITTOKENS, N_TAKETOKEN, N_EXPIRETOKENS, N_DROPTOKENS, N_DEPOSITTOKENS, N_STEALTOKENS,
    N_SERVCMD,
    N_DEMOPACKET,
    NUMMSG
};

// pasted from ROBLOX source print stuff
bool addmsg(int type, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[256];  // Adjust the buffer size as needed
    vsnprintf(buffer, sizeof(buffer), fmt, args);

    va_end(args);

    return CallFunc<bool, int, const char*>(range_start + 0x1E6E50, type, buffer);
}

//template<class T>
//static inline T max(T a, T b)
//{
//    return a > b ? a : b;
//}

//template<class T>
//static inline T min(T a, T b)
//{
//    return a < b ? a : b;
//}

template<class T, class U>
static inline T clamp(T a, U b, U c)
{
    return max(T(b), min(a, T(c)));
}

const int fog = 1000; // idk what this is mneant to be ngl

const int MAXWAYPOINTS = USHRT_MAX - 2;
const int MAXWAYPOINTLINKS = 6;
const int WAYPOINTRADIUS = 16;

const float MINWPDIST = 4.f;     // is on top of
const float CLOSEDIST = 32.f;    // is close
const float FARDIST = 128.f;   // too far to remap close
const float JUMPMIN = 4.f;     // decides to jump
const float JUMPMAX = 32.f;    // max jump
const float SIGHTMIN = 64.f;    // minimum line of sight
const float SIGHTMAX = 1024.f;  // maximum line of sight
const float VIEWMIN = 90.f;    // minimum field of view
const float VIEWMAX = 180.f;   // maximum field of view

float viewdist(int x)
{
    return x <= 100 ? clamp((SIGHTMIN + (SIGHTMAX - SIGHTMIN)) / 100.f * float(x), float(SIGHTMIN), float(fog)) : float(fog);
}

float viewfieldx(int x)
{
    return x <= 100 ? clamp((VIEWMIN + (VIEWMAX - VIEWMIN)) / 100.f * float(x), float(VIEWMIN), float(VIEWMAX)) : float(VIEWMAX);
}

float viewfieldy(int x)
{
    return viewfieldx(x) * 3.f / 4.f;
}

namespace ai
{
    const int NUMPREVNODES = 6;
    int curtime = 0, lastmillis = 1, elapsedtime = 0, totalmillis = 1; // not ai stuff im just using it regardless

    struct aistate
    {
        int type, millis, targtype, target, idle;
        bool override;

        aistate(int m, int t, int r = -1, int v = -1) : type(t), millis(m), targtype(r), target(v)
        {
            reset();
        }
        ~aistate() {}
        aistate() {}

        void reset()
        {
            idle = 0;
            override = false;
        }
    };

    enum
    {
        AI_S_WAIT = 0,      // waiting for next command
        AI_S_DEFEND,        // defend goal target
        AI_S_PURSUE,        // pursue goal target
        AI_S_INTEREST,      // interest in goal entity
        AI_S_MAX
    };
    
    enum
    {
        AI_T_NODE,
        AI_T_PLAYER,
        AI_T_AFFINITY,
        AI_T_ENTITY,
        AI_T_MAX
    };

    struct aiinfo
    {
        std::vector<aistate> state;
        std::vector<int> route;
        vec target, spot;
        int enemy, enemyseen, enemymillis, weappref, prevnodes[NUMPREVNODES], targnode, targlast, targtime, targseq,
            lastrun, lasthunt, lastaction, lastcheck, jumpseed, jumprand, blocktime, huntseq, blockseq, lastaimrnd;
        float targyaw, targpitch, views[3], aimrnd[3];
        bool dontmove, becareful, tryreset, trywipe;

        aiinfo()
        {
            clearsetup();
            reset();
            loopk(3) views[k] = 0.f;
        }
        ~aiinfo() {}

        void clearsetup()
        {
            weappref = GUN_PISTOL;
            spot = target = vec(0, 0, 0);
            lastaction = lasthunt = lastcheck = enemyseen = enemymillis = blocktime = huntseq = blockseq = targtime = targseq = lastaimrnd = 0;
            lastrun = jumpseed = lastmillis;
            jumprand = lastmillis + 5000;
            targnode = targlast = enemy = -1;
        }

        void clear(bool prev = false)
        {
            if (prev) memset(prevnodes, -1, sizeof(prevnodes));
            route.resize(0);
        }

        void wipe(bool prev = false)
        {
            clear(prev);
            state.resize(0);
            addstate(AI_S_WAIT);
            trywipe = false;
        }

        void clean(bool tryit = false)
        {
            if (!tryit) becareful = dontmove = false;
            targyaw = rnd(360);
            targpitch = 0.f;
            tryreset = tryit;
        }

        void reset(bool tryit = false) { wipe(); clean(tryit); }

        bool hasprevnode(int n) const
        {
            loopi(NUMPREVNODES) if (prevnodes[i] == n) return true;
            return false;
        }

        void addprevnode(int n)
        {
            if (prevnodes[0] != n)
            {
                memmove(&prevnodes[1], prevnodes, sizeof(prevnodes) - sizeof(prevnodes[0]));
                prevnodes[0] = n;
            }
        }

        aistate& addstate(int t, int r = -1, int v = -1)
        {
            aistate stateC = aistate(lastmillis, t, r, v);
            state.push_back(stateC);
            return stateC;
        }

        void removestate(int index = -1)
        {
            //if (index < 0) state.pop_back();
            /*else if (state.range(index)) state.remove(index);
            if (!state.size()) addstate(AI_S_WAIT);*/
        }

        aistate& getstate(int idx = -1)
        {
            /*if (state.inrange(idx)) return state[idx];
            return state.end();*/
        }

        aistate& switchstate(aistate& b, int t, int r = -1, int v = -1)
        {
            if ((b.type == t && b.targtype == r) || (b.type == AI_S_INTEREST && b.targtype == AI_T_NODE))
            {
                b.millis = lastmillis;
                b.target = v;
                b.reset();
                return b;
            }
            return addstate(t, r, v);
        }
    };
}

enum { PRIV_NONE = 0, PRIV_MASTER, PRIV_AUTH, PRIV_ADMIN };

#define MAXRAYS 20
#define EXP_SELFDAMDIV 2
#define EXP_SELFPUSH 2.5f
#define EXP_DISTSCALE 1.5f

struct fpsent : dynent, fpsstate
{
    int weight;                         // affects the effectiveness of hitpush
    int clientnum, privilege, lastupdate, plag, ping;
    int lifesequence;                   // sequence id for each respawn, used in damage test
    int respawned, suicided;
    int lastpain;
    int lastaction, lastattackgun;
    bool attacking;
    int attacksound, attackchan, idlesound, idlechan;
    int lasttaunt;
    int lastpickup, lastpickupmillis, lastbase, lastrepammo, flagpickup, tokens;
    vec lastcollect;
    int frags, flags, deaths, totaldamage, totalshots;
    editinfo* edit;
    float deltayaw, deltapitch, deltaroll, newyaw, newpitch, newroll;
    int smoothmillis;

    string name, team, info;
    int playermodel;
    ai::aiinfo* ai;
    int ownernum, lastnode;

    vec muzzle;

    fpsent() : weight(100), clientnum(-1), privilege(PRIV_NONE), lastupdate(0), plag(0), ping(0), lifesequence(0), respawned(-1), suicided(-1), lastpain(0), attacksound(-1), attackchan(-1), idlesound(-1), idlechan(-1), frags(0), flags(0), deaths(0), totaldamage(0), totalshots(0), edit(NULL), smoothmillis(-1), playermodel(-1), ai(NULL), ownernum(-1), muzzle(-1, -1, -1)
    {
        name[0] = team[0] = info[0] = 0;
        respawn();
    }

    void ToggleAttack() {
        attacking = !attacking;
    }

    void TryRespawn() {
        CallFunc<bool, int, const char*, fpsent*>(range_start + 0x1E6E50, N_TRYSPAWN, "rc", this);
    }

    void Suicide() {
        CallFunc<bool, int, const char*, fpsent*>(range_start + 0x1E6E50, N_SUICIDE, "rc", this);
    }

    void teleport(vec newpos) {
        resetinterp(); // reset pos n stuff

        physstate = PHYS_FALL;
        vel = falling = vec(0, 0, 0);
        floor = vec(0, 0, 1); // reset physics stuff

        this->newpos = newpos;
    }

    //void ServerSideTeamExploit(const char* newTeam) {
    //    std::stringstream ss;

    //    for (int i = 0; i < 260; i++)
    //    {
    //        ss << "a";
    //    }

    //    std::string oldName = this->GetName();
    //    this->SetName((ss.str() + newTeam).c_str());
    //    Sleep(250);
    //    this->SetName(oldName.c_str());
    //}

    void SetName(const char* str) {
        if (IsBadReadPointer(this))
            return;

        strcpy(name, newstring(str));

        CallFunc<bool, int, const char*, const char*>(range_start + 0x1E6E50, N_SWITCHNAME, "rs", GetName().c_str());
    }

    void SendMsg(const char* name) {
        CallFunc<bool, int, const char*, fpsent*, const char*>(range_start + 0x1E6E50, N_TEXT, "rcs", this, name);
    }

    std::string GetName() {
        if (IsBadReadPointer(this)) // im gonna say so many bad words
            return std::string("");

        return std::string(name);
    }

    std::string GetTeam() {
        if (IsBadReadPointer(this))
            return std::string("");

        return std::string(team);
    }

    /*~fpsent()
    {
        freeeditinfo(edit);
        if (attackchan >= 0) stopsound(attacksound, attackchan);
        if (idlechan >= 0) stopsound(idlesound, idlechan);
        if (ai) delete ai;
    }*/

    void hitpush(int damage, const vec& dir, fpsent* actor, int gun)
    {
        vec push(dir);
        push.mul((actor == this && guns[gun].exprad ? EXP_SELFPUSH : 1.0f) * guns[gun].hitpush * damage / weight);
        vel.add(push);
    }

    /*void stopattacksound()
    {
        if (attackchan >= 0) stopsound(attacksound, attackchan, 250);
        attacksound = attackchan = -1;
    }

    void stopidlesound()
    {
        if (idlechan >= 0) stopsound(idlesound, idlechan, 100);
        idlesound = idlechan = -1;
    }*/

    // incomplete respawn, still usable..
    void respawn()
    {
        dynent::reset();
        fpsstate::respawn();
        respawned = suicided = -1;
        lastaction = 0;
        lastattackgun = gunselect;
        attacking = false;
        lasttaunt = 0;
        lastpickup = -1;
        lastpickupmillis = 0;
        lastbase = lastrepammo = -1;
        flagpickup = 0;
        tokens = 0;
        lastcollect = vec(-1e10f, -1e10f, -1e10f);
        //stopattacksound();
        lastnode = -1;
    }

    /*int respawnwait(int secs, int delay = 0)
    {
        return max(0, secs - (::lastmillis - lastpain - delay) / 1000);
    }*/
};