#include "Console.h"

#include <wtypes.h>

void Console::CreateConsole(const char* title)
{
    HWND consoleWnd = GetConsoleWindow();
    if (!consoleWnd)
    {
        AllocConsole();

        freopen_s(&f, "CONOUT$", "w", stdout);
        freopen_s(&f, "CONIN$", "r", stdin);
        SetConsoleTitleA(title);
    }
    else
    {
        ShowWindow(GetConsoleWindow(), SW_SHOW);
    }
}

void Console::CloseConsole()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    ClearConsole();
}

void Console::ClearConsole()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    COORD homeCoords = { 0, 0 };

    if (hConsole == INVALID_HANDLE_VALUE || !GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return;
    }

    int cells = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, ' ', cells, homeCoords, &count);
    SetConsoleCursorPosition(hConsole, homeCoords);
}