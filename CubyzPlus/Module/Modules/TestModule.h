#pragma once

class TestModule : public Module {
public:
	TestModule() : Module::Module("TestModule", "Debug", "Test Utilities for yeemi!!!", "yeemi#0", "0") {};

	void OnTick(fpsent* player) override {
		//player->type = ENT_AI;
		//player->aitype = AI_MAX;
		//player->skill = 101; // max skill bot
		////CallFunc<void, fpsent*>(range_start + 0x1BE8B0, player); // init ai for player
		//player->ai = new ai::aiinfo;

		//if (player->ai)
		//{
		//	player->ai->views[0] = viewfieldx(player->skill);
		//	player->ai->views[1] = viewfieldy(player->skill);
		//	player->ai->views[2] = viewdist(player->skill);
		//}

		player->teleport(Game::Players::ClosestEnemy()->newpos);
		Toggle();
	};

	void OnDisable() override {
		fpsent* plyr = Game::GetLocalPlayer();

		if (plyr != nullptr) {

		}
	}
};