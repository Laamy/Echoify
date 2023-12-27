#pragma region Includes

#include <windows.h>
#include <vector>
#include <string>
#include <Psapi.h>
#include <sstream>
#include <thread>
#include <queue>
#include <map>
#include <iostream>
#include <mutex>

bool g_isRunning = true;
HMODULE procModule;

// some imgui stuff
#include "Libs/imgui/imgui_impl_opengl3.h"
#include "Libs/imgui/imgui_impl_win32.h"

#include "Libs/minhook/minhook.h"

#include "Utils/MemoryUtils.h"

#include "GameCore/Structs/geom.h"
#include "GameCore/Guns.h"
#include "GameCore/Ent/fpsent.h" // main player class

#include "FileIO.cpp"

#include "Game.h"

#include "Module/Module.h"

std::vector<Module*> modules;

#include "Hook/FuncHook.h"

#include "Console.cpp"

#include "Module/ModuleManager.h"

#pragma endregion

/*

Known issues:
    - dll leaves 320kb (Ish) left over from ejecting, probably from not cleaning up opengl completely

*/

DWORD APIENTRY ejectThread(HMODULE lpParam)
{
    while (g_isRunning)
        Sleep(0);

    std::cout << "Ejecting client..." << std::endl;

    Sleep(50);

	std::cout << "Uninstalling imgui" << std::endl;

    // not a full shutdown as we leave some opengl resources behind but its fine
	//ImGui_ImplOpenGL3_Shutdown(); // shutdown opengl in imgui
	ImGui::DestroyContext();

	std::cout << "removing hooks & other resources.." << std::endl;

	MH_DisableHook(MH_ALL_HOOKS); // minhook stuff
	MH_Uninitialize();
    Game::Uninitialize();

	std::cout << "complete." << std::endl;

    Console::CloseConsole();
    FreeLibraryAndExitThread(lpParam, 1);
}

void Init(HANDLE module) {
    Console::CreateConsole("Echoify Debug");
    InitHooks();
    InitMods();
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH) {
        procModule = module;
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Init, module, 0, 0);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ejectThread, module, 0, 0);
    }
    return TRUE;
}