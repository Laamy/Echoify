#pragma once

class InfAmmo : public Module {
public:
	InfAmmo() : Module::Module("InfAmmo", "Player", "Infinite Ammo", "yeemi#0", "P") {};

	void OnTick(fpsent* player) override {
		// setup current gun ammo to 999
		player->ammo[player->gunselect] = 999;
	};
};