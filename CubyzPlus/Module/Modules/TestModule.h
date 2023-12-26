#pragma once

class TestModule : public Module {
public:
	TestModule() : Module::Module("TestModule", "Debug", "Test Utilities for yeemi!!!", "yeemi#0", "0") {};

	void OnTick(fpsent* player) override {

		//addmsg(N_CLIENTPING, "i", player->ping = -MAXINT32); // bro?
	};

	void OnDisable() override {
		fpsent* plyr = Game::GetLocalPlayer();

		if (plyr != nullptr) {

		}
	}
};