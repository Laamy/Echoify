#pragma once

void* __o__drawhudicons;

void drawhudiconsDetour(fpsent* d) {

	//std::cout << "drawing hud icons.." << std::endl;

	// print the current ammo count for the held gun with damage
	Game::fpsEntPtr = d;

	for (Module* mod : modules)
		if (mod->enabled)
			mod->OnTick(d);

	//std::cout << std::hex << Game::GetLocalPlayer() << " " << game::player1 << std::endl;

	return CallFunc<void, fpsent*>(__o__drawhudicons, d);
}

class DrawHubIconsHook : public FuncHook {
public:
	bool Initialize() override {
		//uintptr_t drawhubIconsAddr = GetFunctionAddress("game::drawhudicons");
		uintptr_t drawhubIconsAddr = findOffset("48 8B C4 53 48 81 EC ? ? ? ? 48 8B D9 ? ? 70", "DrawHubIcons");

		if (not HookFunction((void*)drawhubIconsAddr, &drawhudiconsDetour, &__o__drawhudicons))
			return false;

		return true;
	}

	static DrawHubIconsHook& Get() {
		static DrawHubIconsHook single;
		return single;
	}
};