#pragma once

class AutoRespawn : public Module {
public:
	AutoRespawn() : Module::Module("AutoRespawn", "Player", "Automatically respawn", "yeemi#0", "NONE") {};

	void OnTick(fpsent* player) override {

		if (player->state == CS_DEAD) {
			player->TryRespawn();
		}

	}
};