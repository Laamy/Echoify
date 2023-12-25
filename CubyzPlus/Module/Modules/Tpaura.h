#pragma once

class Tpaura : public Module {
public:
	Tpaura() : Module::Module("Tpaura", "Combat", "Rage module to instantly kill EVERYONE cuz they r FAGGOTS", "yeemi#0", "9") {};

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

		//Game::Keymap::ClickLeft();
	}
};