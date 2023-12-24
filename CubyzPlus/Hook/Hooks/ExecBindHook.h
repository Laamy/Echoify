#pragma once

void* __o__execbind;

void execbindDetour(keym* k, bool isdown) { // isdown arguemnt is useless btw cuz pressed also shows the isdown state

	// first priority is the exit keybind
	if (k->name != nullptr && Game::Keymap::GetKeyHeld("LCTRL") && strcmp(k->name, "L") == 0)
		g_isRunning = false;

	// store
	Game::Keymap::map[k->code] = k;

	// tick modules keyevents
	for (Module* mod : modules) {
		if (mod->keybind == k->name && k->pressed)
			mod->Toggle();
	}

	// debug
	if (Game::debugScreen) {
		std::cout << "'" << k->name << "'" << std::endl;
	}

	// debug toggle
	if (strcmp(k->name, "F3") == 0 && isdown)
	{
		Game::debugScreen = !Game::debugScreen;
	}

	return CallFunc<void, keym*, bool>(__o__execbind, k, isdown);
}

class ExecBindHook : public FuncHook {
public:
	bool Initialize() override {
		//uintptr_t drawhubIconsAddr = GetFunctionAddress("execbind");
		uintptr_t execbindAddr = findOffset("40 53 41 56 41 57 48 83 EC 20", "execbind");

		if (not HookFunction((void*)execbindAddr, &execbindDetour, &__o__execbind))
			return false;

		return true;
	}

	static ExecBindHook& Get() {
		static ExecBindHook single;
		return single;
	}
};