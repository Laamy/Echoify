#pragma once

#include <chrono>

class StreamMode : public Module {
public:
	StreamMode() : Module::Module("StreamMode", "Misc", "Randomize your username every second or so", "yeemi#0", "NONE") {};

	std::chrono::steady_clock::time_point lastTime;

	void OnTick(fpsent* context) override {

		std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<int> elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastTime);

		if (elapsedTime.count() >= 2) {
			//std::cout << "second passed" << std::endl;

			//std::stringstream ss;

			//char c;
			//int r;
			//for (int i = 0; i < 10; i++)
			//{
			//	r = rand() % 26;   // generate a random number
			//	c = 'a' + r;            // Convert to a character from a-z
			//	ss << c;
			//}

			//Game::GetLocalPlayer()->SetName(ss.str().c_str());

			Game::GetLocalPlayer()->SetName(Game::Players::ClosestEnemy()->GetName().c_str());

			lastTime = currentTime;
		}

	}
};