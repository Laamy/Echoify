#pragma once

class selinfo;
class cube;

struct block3
{
    ivec o, s;
    int grid, orient;
    block3() {}
    //block3(const selinfo& sel) : o(sel.o), s(sel.s), grid(sel.grid), orient(sel.orient) {}
    cube* c() { return (cube*)(this + 1); }
    int size()    const { return s.x * s.y * s.z; }
};