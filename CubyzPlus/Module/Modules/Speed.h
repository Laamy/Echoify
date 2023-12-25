#pragma once

class Speed : public Module {
public:
	Speed() : Module::Module("Speed", "Movement", "Speed utility", "yeemi#0", "O") {};

	float speed = 1.1f; // WTF THEY DETECT 10% SPEED?

	void OnTick(fpsent* player) override {
		player->maxspeed = speed * 100;
		player->animinterp->reset();
	};

	void OnDisable() override {
		fpsent* plyr = Game::GetLocalPlayer();

		if (plyr != nullptr) {
			plyr->maxspeed = 100;
		}
	}
};