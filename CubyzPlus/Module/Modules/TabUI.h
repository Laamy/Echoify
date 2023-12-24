#pragma once

#include "../../UI/tabui/tabui.h"

Tabui tabui;

class TabUI : public Module {
public:
	TabUI() : Module::Module("TabUI", "Allow ease of access to modules", "yeemi#0", "V") {};

	void OnUpdate(ImDrawData* context) {
		tabui.Draw(); 
	}

	// these two are not needed yet but might be useful in the future so I've left them
	void onDisable() {
		tabui.Close();
	}

	void onEnable() {
		tabui.Open();
	}
};