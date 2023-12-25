#pragma once

#include <DbgHelp.h>
#include <strsafe.h>

#define PI 3.14159265359

// util used to call functions by their void* address
template <typename R, typename... Args>
R CallFunc(void* func, Args... args) {
    return ((R(*)(Args...))func)(args...);
}

// util used to call functions by their uintptr_t address
template <typename R, typename... Args>
R CallFunc(uintptr_t func, Args... args) {
    return ((R(*)(Args...))func)(args...);
}

struct stringslice
{
    const char* str;
    int len;
    stringslice() {}
    stringslice(const char* str, int len) : str(str), len(len) {}
    stringslice(const char* str, const char* end) : str(str), len(int(end - str)) {}

    const char* end() const { return &str[len]; }
};

inline char* copystring(char* d, const char* s, size_t len)
{
    size_t slen = min(strlen(s), len - 1);
    memcpy(d, s, slen);
    d[slen] = 0;
    return d;
}
template<size_t N> inline char* copystring(char(&d)[N], const char* s) { return copystring(d, s, N); }

inline char* copystring(char* d, const stringslice& s, size_t len)
{
    size_t slen = min(size_t(s.len), len - 1);
    memcpy(d, s.str, slen);
    d[slen] = 0;
    return d;
}
template<size_t N> inline char* copystring(char(&d)[N], const stringslice& s) { return copystring(d, s, N); }

inline char* newstring(size_t l) { return new char[l + 1]; }
inline char* newstring(const char* s, size_t l) { return copystring(newstring(l), s, l + 1); }
inline char* newstring(const char* s) { size_t l = strlen(s); char* d = newstring(l); memcpy(d, s, l + 1); return d; }

const char* name = "sauerbraten.exe";
const char* sdlNname = "SDL2.dll";

// game base address
uintptr_t range_start = (uintptr_t)GetModuleHandleA(name);
uintptr_t sdl_range_start = (uintptr_t)GetModuleHandleA(sdlNname);
HMODULE module = GetModuleHandleA(name);
HMODULE sdlModule = GetModuleHandleA(sdlNname);
#pragma comment(lib, "dbghelp.lib")

class AddressSymbol {
public:
    bool Failure = true;
    DWORD64 Address;
    DWORD64 SymbolDisplacement;
    WCHAR FunctionName[255];
    WCHAR FileName[255];
    WCHAR ModuleName[255];
    int LineNumber;

    static const int MAX_NAME_LENGH = 255;
};

// https://github.com/Ant2i/FRE4/blob/master/Dev/Source/Platform/Private/Win/WinPlatformStack.cpp#L176
void ProgramAddressToSymbolInfo(uint64_t address, AddressSymbol& oSymbolInfo) {
    SymInitialize(GetCurrentProcess(), nullptr, true);

    oSymbolInfo.Address = address;

    uint32_t lastError = 0;
    HANDLE processHandle = GetCurrentProcess();

    char symbolBuffer[sizeof(IMAGEHLP_SYMBOL64) + AddressSymbol::MAX_NAME_LENGH] = { 0 };
    IMAGEHLP_SYMBOL64* symbol = (IMAGEHLP_SYMBOL64*)symbolBuffer;
    symbol->SizeOfStruct = sizeof(symbolBuffer);
    symbol->MaxNameLength = AddressSymbol::MAX_NAME_LENGH;

    if (SymGetSymFromAddr64(processHandle, address, nullptr, symbol)) {
        int32_t offset = 0;
        while (symbol->Name[offset] < 32 || symbol->Name[offset] > 127) {
            offset++;
        }

        // Convert ANSI to wide string
        MultiByteToWideChar(CP_ACP, 0, symbol->Name + offset, -1, oSymbolInfo.FunctionName, AddressSymbol::MAX_NAME_LENGH);

        // Concatenate "()"
        wcscat(oSymbolInfo.FunctionName, L"()");
    }
    else {
        lastError = GetLastError();
    }

    IMAGEHLP_LINE64 imageHelpLine = { 0 };
    imageHelpLine.SizeOfStruct = sizeof(imageHelpLine);
    if (SymGetLineFromAddr64(processHandle, address, (::DWORD*)&oSymbolInfo.SymbolDisplacement, &imageHelpLine)) {
        MultiByteToWideChar(CP_ACP, 0, imageHelpLine.FileName, -1, oSymbolInfo.FileName, AddressSymbol::MAX_NAME_LENGH);
        oSymbolInfo.LineNumber = imageHelpLine.LineNumber;
    }
    else {
        lastError = GetLastError();
    }

    IMAGEHLP_MODULE64 imageHelpModule = { 0 };
    imageHelpModule.SizeOfStruct = sizeof(imageHelpModule);
    if (SymGetModuleInfo64(processHandle, address, &imageHelpModule)) {
        MultiByteToWideChar(CP_ACP, 0, imageHelpModule.ImageName, -1, oSymbolInfo.ModuleName, AddressSymbol::MAX_NAME_LENGH);
    }
    else {
        lastError = GetLastError();
    }

    SymCleanup(processHandle);
}

uintptr_t GetFunctionAddress(const char* functionName) {
    if (!SymInitialize(GetCurrentProcess(), nullptr, TRUE)) {
        std::cout << "Failed to initialize symbol handling. Error: " << GetLastError() << std::endl;
    }

    DWORD64 base = SymLoadModuleEx(GetCurrentProcess(), nullptr, name, nullptr, 0, 0, nullptr, 0);
    if (!base) {
        std::cout << "Failed to load symbols for module. Error: " << GetLastError() << std::endl;
    }

    IMAGEHLP_SYMBOL64 symbolInfo = { sizeof(IMAGEHLP_SYMBOL64) };
    symbolInfo.SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
    uintptr_t addr = 0;

    if (SymGetSymFromName64(GetCurrentProcess(), functionName, &symbolInfo)) {
        addr = symbolInfo.Address;

        /*WCHAR Name[255];
        StringCchCopy(Name, sizeof(Name) / sizeof(Name[0]), STRSAFE_LPCWSTR(symbolInfo.Name));*/

        std::cout << "Using SymGetSymFromName64, Address: " << std::hex << addr << std::endl;
        std::cout << "Using SymGetSymFromName64, Name: " << std::hex << symbolInfo.Name << std::endl;
        std::cout << "Using SymGetSymFromName64, MaxNameLength: " << std::hex << symbolInfo.MaxNameLength << std::endl;
    }
    else {
        std::cout << "Failed to get symbol information. Error: " << GetLastError() << std::endl;
    }

    return addr;
}

// function used to hook game functions
bool HookFunction(void* pTarget, void* pDetour, void* pOriginal) {

    static bool initialized = false;

    if (!initialized) {
        initialized = true;

        if (MH_Initialize() != MH_OK) {
            return false;
        }
    }

    if (MH_CreateHook(pTarget, pDetour, (LPVOID*)pOriginal) != MH_OK) {
        return false;
    }

    if (MH_EnableHook(pTarget) != MH_OK) {
        return false;
    }

    return true;

}

static void* findMultiLvlPtr(uintptr_t baseAddr, std::vector<unsigned int> offsets) {

    uintptr_t addr = baseAddr;

    for (int I = 0; I < offsets.size(); I++)
    {
        addr = *(uintptr_t*)(addr);

        if ((uintptr_t*)(addr) == nullptr)
        {
            return reinterpret_cast<void*>(addr);
        }

        addr += offsets[I];
    };

    return reinterpret_cast<void*>(addr);

};

#define INRANGE(x, a, b) (x >= a && x <= b)
#define GET_BYTE(x) ((GET_BITS(x[0]) << 4) | GET_BITS(x[1]))
#define GET_BITS(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa) : (INRANGE(x, '0', '9') ? (x - '0') : 0))

static uintptr_t findSig(const char* sig) {

    const char* pattern = sig;
    uintptr_t first_match = 0;
    static MODULEINFO mi_mod_info;
    static bool init = false;
    if (!init)
    {
        init = true;
        GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(range_start), &mi_mod_info, sizeof(MODULEINFO));
    }
    static const uintptr_t range_end = range_start + mi_mod_info.SizeOfImage;

    BYTE pat_byte = GET_BYTE(pattern);
    const char* old_pat = pattern;

    for (uintptr_t p_cur = range_start; p_cur < range_end; p_cur++) // eevrything we use is over 0x100000 so we can just skip that part of memory
    {
        if (!*pattern)
        {
            return first_match;
        }

        while (*(PBYTE)pattern == ' ')
        {
            pattern++;
        }

        if (!*pattern)
        {
            return first_match;
        }

        if (old_pat != pattern)
        {
            old_pat = pattern;
            if (*(PBYTE)pattern != '\?') {
                pat_byte = GET_BYTE(pattern);
            }
        }

        if (*(PBYTE)pattern == '\?' || *(BYTE*)p_cur == pat_byte)
        {
            if (!first_match)
            {
                first_match = p_cur;
            }

            if (!pattern[2])
            {
                return first_match;
            }

            pattern += 2;
        }
        else
        {
            pattern = sig;
            first_match = 0;
        }
    }

    return 0;

}

// https://stackoverflow.com/questions/496034/most-efficient-replacement-for-isbadreadptr
bool IsBadReadPointer(void* p) {
    MEMORY_BASIC_INFORMATION mbi = { 0 };
    if (::VirtualQuery(p, &mbi, sizeof(mbi)))
    {
        DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
        bool b = !(mbi.Protect & mask);
        // check the page is not a guard page
        if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) b = true;

        return b;
    }
    return true;
}

static uintptr_t findOffset(const char* sig, const char* sidId) {

    uintptr_t sigResult = findSig(sig);

    if (sigResult == 0) {

        std::stringstream ss;
        ss << "[" << sidId << "] Failed to find signiture";
        std::cout << ss.str().c_str() << std::endl;

        return 0;
    }

    return sigResult;

}

#define N (624)             
#define M (397)                
#define K (0x9908B0DFU)       

static unsigned int state[N];
static int next = N;

void seedMT(unsigned int seed)
{
    state[0] = seed;
    for (unsigned int i = 1; i < N; i++)
        state[i] = seed = 1812433253U * (seed ^ (seed >> 30)) + i;
    next = 0;
}

unsigned int randomMT()
{
    int cur = next;
    if (++next >= N)
    {
        if (next > N) { seedMT(5489U + time(NULL)); cur = next++; }
        else next = 0;
    }
    unsigned int y = (state[cur] & 0x80000000U) | (state[next] & 0x7FFFFFFFU);
    state[cur] = y = state[cur < N - M ? cur + M : cur + M - N] ^ (y >> 1) ^ (-int(y & 1U) & K);
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9D2C5680U;
    y ^= (y << 15) & 0xEFC60000U;
    y ^= (y >> 18);
    return y;
}

#define loopk(m) loop(k,m)
#define rnd(x) ((int)(randomMT()&0x7FFFFFFF)%(x))