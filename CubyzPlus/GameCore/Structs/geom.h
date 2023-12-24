#pragma once

struct vec;

struct vec
{
    union
    {
        struct { float x, y, z; };
        struct { float r, g, b; };
        float v[3];
    };

    vec() {}
    explicit vec(int a) : x(a), y(a), z(a) {}
    explicit vec(float a) : x(a), y(a), z(a) {}
    vec(float a, float b, float c) : x(a), y(b), z(c) {}
    explicit vec(int v[3]) : x(v[0]), y(v[1]), z(v[2]) {}
    explicit vec(const float* v) : x(v[0]), y(v[1]), z(v[2]) {}

    vec(float yaw, float pitch) : x(-sinf(yaw) * cosf(pitch)), y(cosf(yaw)* cosf(pitch)), z(sinf(pitch)) {}

    float& operator[](int i) { return v[i]; }
    float  operator[](int i) const { return v[i]; }

    vec& set(int i, float f) { v[i] = f; return *this; }

    bool operator==(const vec& o) const { return x == o.x && y == o.y && z == o.z; }
    bool operator!=(const vec& o) const { return x != o.x || y != o.y || z != o.z; }

    bool iszero() const { return x == 0 && y == 0 && z == 0; }
    float squaredlen() const { return x * x + y * y + z * z; }
    template<class T> float dot2(const T& o) const { return x * o.x + y * o.y; }
    float dot(const vec& o) const { return x * o.x + y * o.y + z * o.z; }
    float absdot(const vec& o) const { return fabs(x * o.x) + fabs(y * o.y) + fabs(z * o.z); }
    vec& pow(float f) { x = ::pow(x, f); y = ::pow(y, f); z = ::pow(z, f); return *this; }
    vec& exp() { x = ::exp(x); y = ::exp(y); z = ::exp(z); return *this; }
    vec& exp2() { x = ::exp2(x); y = ::exp2(y); z = ::exp2(z); return *this; }
    vec& sqrt() { x = sqrtf(x); y = sqrtf(y); z = sqrtf(z); return *this; }
    vec& mul(const vec& o) { x *= o.x; y *= o.y; z *= o.z; return *this; }
    vec& mul(float f) { x *= f; y *= f; z *= f; return *this; }
    vec& square() { mul(*this); return *this; }
    vec& div(const vec& o) { x /= o.x; y /= o.y; z /= o.z; return *this; }
    vec& div(float f) { x /= f; y /= f; z /= f; return *this; }
    vec& recip() { x = 1 / x; y = 1 / y; z = 1 / z; return *this; }
    vec& add(const vec& o) { x += o.x; y += o.y; z += o.z; return *this; }
    vec& add(float f) { x += f; y += f; z += f; return *this; }
    vec& add2(float f) { x += f; y += f; return *this; }
    vec& addz(float f) { z += f; return *this; }
    vec& sub(const vec& o) { x -= o.x; y -= o.y; z -= o.z; return *this; }
    vec& sub(float f) { x -= f; y -= f; z -= f; return *this; }
    vec& sub2(float f) { x -= f; y -= f; return *this; }
    vec& subz(float f) { z -= f; return *this; }
    vec& neg2() { x = -x; y = -y; return *this; }
    vec& neg() { x = -x; y = -y; z = -z; return *this; }

    float distance(const vec& other) const
    {
        float dx = x - other.x;
        float dy = y - other.y;
        float dz = z - other.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }
};

struct ivec
{
    union
    {
        struct { int x, y, z; };
        struct { int r, g, b; };
        int v[3];
    };

    ivec() {}
    explicit ivec(const vec& v) : x(int(v.x)), y(int(v.y)), z(int(v.z)) {}
    ivec(int a, int b, int c) : x(a), y(b), z(c) {}
    /*ivec(int d, int row, int col, int depth)
    {
        v[R[d]] = row;
        v[C[d]] = col;
        v[D[d]] = depth;
    }*/
    ivec(int i, const ivec& co, int size) : x(co.x + ((i & 1) >> 0) * size), y(co.y + ((i & 2) >> 1) * size), z(co.z + ((i & 4) >> 2) * size) {}

    int& operator[](int i) { return v[i]; }
    int  operator[](int i) const { return v[i]; }

    //int idx(int i) { return v[i]; }
    bool operator==(const ivec& v) const { return x == v.x && y == v.y && z == v.z; }
    bool operator!=(const ivec& v) const { return x != v.x || y != v.y || z != v.z; }
    bool iszero() const { return x == 0 && y == 0 && z == 0; }
    ivec& shl(int n) { x <<= n; y <<= n; z <<= n; return *this; }
    ivec& shr(int n) { x >>= n; y >>= n; z >>= n; return *this; }
    ivec& mul(int n) { x *= n; y *= n; z *= n; return *this; }
    ivec& div(int n) { x /= n; y /= n; z /= n; return *this; }
    ivec& add(int n) { x += n; y += n; z += n; return *this; }
    ivec& sub(int n) { x -= n; y -= n; z -= n; return *this; }
    ivec& mul(const ivec& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
    ivec& div(const ivec& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }
    ivec& add(const ivec& v) { x += v.x; y += v.y; z += v.z; return *this; }
    ivec& sub(const ivec& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    ivec& mask(int n) { x &= n; y &= n; z &= n; return *this; }
    ivec& neg() { return mul(-1); }
    ivec& abs() { x = ::abs(x); y = ::abs(y); z = ::abs(z); return *this; }
    ivec& cross(const ivec& a, const ivec& b) { x = a.y * b.z - a.z * b.y; y = a.z * b.x - a.x * b.z; z = a.x * b.y - a.y * b.x; return *this; }
    int dot(const ivec& o) const { return x * o.x + y * o.y + z * o.z; }

    static inline ivec floor(const vec& o) { return ivec(int(::floor(o.x)), int(::floor(o.y)), int(::floor(o.z))); }
    static inline ivec ceil(const vec& o) { return ivec(int(::ceil(o.x)), int(::ceil(o.y)), int(::ceil(o.z))); }
};