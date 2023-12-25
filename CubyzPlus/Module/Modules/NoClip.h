#pragma once

class NoClip : public Module {
public:
	NoClip() : Module::Module("NoClip", "Player", "Disable all game collisions", "yeemi#0", "NONE") {};

	void OnTick(fpsent* player) override {
		player->collidetype = COLLIDE_NONE;
	}

	void OnDisable() {
		fpsent* plyr = Game::GetLocalPlayer();

		if (!IsBadReadPointer(plyr))
			plyr->collidetype = COLLIDE_ELLIPSE;
	}
};