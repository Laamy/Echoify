#pragma once

struct hitmsg
{
	int target, lifesequence, info1, info2;
	ivec dir;
};

#include <chrono>

class StreamMode : public Module {
public:
	StreamMode() : Module::Module("StreamMode", "Misc", "Randomize your username every second or so", "yeemi#0", "NONE") {};

	std::chrono::steady_clock::time_point lastTime;

	int counter = 0;

	void OnTick(fpsent* context) override {

		std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<int> elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastTime);

		static int counter = 0;

		if (elapsedTime.count() >= 2) {

			std::stringstream ss;

			char c;
			int r;
			for (int i = 0; i < 15; i++)
			{
				r = rand() % 26;   // generate a random number
				c = 'a' + r;            // Convert to a character from a-z
				ss << c;
			}

			fpsent* closest = Game::Players::ClosestEnemy();

			if (closest && closest->GetName().length() > 3) {
				Game::Player::SetName((closest->GetName()).c_str()); //  + ss.str()
			}

			lastTime = currentTime;
		}

	}
};