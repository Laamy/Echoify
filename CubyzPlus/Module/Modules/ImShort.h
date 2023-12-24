#pragma once

class ImShort : public Module {
public:
	ImShort() : Module::Module("ImShort", "Makes you short", "yeemi#0", "K") {};

	void OnTick(fpsent* player) override {
		// set eyeheight to 1 (default is 4.6-ish)
		player->eyeheight = 1;
	};

	void OnDisable() override {
		fpsent* plyr = Game::GetLocalPlayer();

		if (plyr != nullptr) {
			plyr->eyeheight = 14; // normal eyeheight
		}
	}
};