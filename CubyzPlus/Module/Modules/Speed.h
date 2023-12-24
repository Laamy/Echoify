#pragma once

class Speed : public Module {
public:
	Speed() : Module::Module("Speed", "Movement", "Speed utility", "yeemi#0", "O") {};

	float speed = 3;

	void OnTick(fpsent* player) override {
		player->maxspeed = speed * 100;
	};

	void OnDisable() override {
		fpsent* plyr = Game::GetLocalPlayer();

		if (plyr != nullptr) {
			plyr->maxspeed = 100;
		}
	}
};