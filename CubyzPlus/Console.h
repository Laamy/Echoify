#include <cstdio>

class Console {
public:
    inline static void CreateConsole(const char* title);
    inline static void CloseConsole();
    inline static void ClearConsole();

private:
    static inline FILE* f;
};