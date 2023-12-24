#pragma once

#include "../../UI/tabui/tabui.h"

Tabui tabui;

class TabUI : public Module {
public:
	TabUI() : Module::Module("TabUI", "Allow ease of access to modules", "yeemi#0", "V") {};

	// might make this always draw regardless of module enable state
	void OnUpdate(ImDrawData* context) override {
		tabui.Draw(); 
	}

	void OnKey(keym* key) override {
		if (key->pressed && strcmp(key->name, "UP") == 0)
			tabui.Prev();

		if (key->pressed && strcmp(key->name, "DOWN") == 0)
			tabui.Next();

		std::cout << key->name << std::endl;
	}

	// these two are not needed yet but might be useful in the future so I've left them
	void onDisable() {
		tabui.Close();
	}

	void onEnable() {
		tabui.Open();
	}
};