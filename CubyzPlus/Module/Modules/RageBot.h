#pragma once

class RageBot : public Module {
public:
	RageBot() : Module::Module("RageBot", "Debug", "Rage bot to kill then disconnect asap", "yeemi#0", "NONE") {};

	std::chrono::steady_clock::time_point lastTime;

	void OnTick(fpsent* player) override {
		if (player->state == CS_DEAD) {
			player->TryRespawn();
		}

		if (player->state == CS_SPECTATOR) {
			player->SendMsg("spectator is cringe");
			Game::Disconnect();
		}

		std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<int> elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastTime);

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
				Game::GetLocalPlayer()->SetName((closest->GetName()).c_str()); //  + ss.str()
			}

			lastTime = currentTime;
		}
	};

	float lerp(float a, float b, float t) {
		return a + t * (b - a);
	}

	//int lerpSpeed = 6; // takes 6 frames to lerp

	ImVec2 GetAngles(vec src, vec dst) {
		static ImVec2 currentAngle = { 0, 0 };

		ImVec2 angle;
		angle.x = (atan2f(dst.x - src.x, dst.y - src.y) * -1.0) / PI * 180.0;
		angle.y = asinf((dst.z - src.z) / src.distance(dst)) * (180.0 / PI);

		// Smoothly interpolate angles over lerpSpeed(6) updates
		currentAngle.x = lerp(currentAngle.x, angle.x, 0.2f);
		currentAngle.y = lerp(currentAngle.y, angle.y, 0.2f);

		return currentAngle;
	}

	// pretty bad
	void OnUpdate(ImDrawData* context) override { // Game::GetLocalPlayer()->yaw, Game::GetLocalPlayer()->pitch

		fpsent* closestEntity = Game::Players::ClosestEnemy();

		if (!IsBadReadPointer(closestEntity->name))
		{
			vec ne = closestEntity->newpos;
			vec ce = closestEntity->vel;

			Game::GetLocalPlayer()->teleport(vec(ne.x + (ce.x / 12), ne.y + (ce.y / 12), ne.z - 15));

			if (closestEntity != nullptr) {
				vec src = Game::GetLocalPlayer()->newpos;
				vec dst = closestEntity->newpos;

				dst.z -= 2;

				ImVec2 currentAngle = GetAngles(src, dst);

				Game::GetLocalPlayer()->yaw = currentAngle.x;
				Game::GetLocalPlayer()->pitch = currentAngle.y;
			}

			if (Game::GetLocalPlayer()->ammo[GUN_FIST] > 0) // chainsaw active so lets use it as its OP as fuck
				Game::GetLocalPlayer()->gunselect = GUN_FIST;

			Game::GetLocalPlayer()->attacking = true;
		}
		else {
			if (Game::Players::GetFiltered().size() > 1) // when loading in theres a split second where this all ticks but it has no players
				Game::Disconnect(); // disconnect cuz everyones DEAD
		}

		//Game::Keymap::ClickLeft();
	}

	void OnDisable() override {

	}
};