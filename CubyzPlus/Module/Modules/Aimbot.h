#pragma once

class Aimbot : public Module {
public:
	Aimbot() : Module::Module("Aimbot", "Combat", "Automatically aim towards the closest player", "yeemi#0", "B") {};

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

		if (closestEntity != nullptr) {
			vec src = Game::GetLocalPlayer()->newpos;
			vec dst = closestEntity->newpos;

			dst.z -= 2;

			ImVec2 currentAngle = GetAngles(src, dst);

			if (GetAsyncKeyState(VK_RBUTTON)) {
				Game::GetLocalPlayer()->yaw = currentAngle.x;
				Game::GetLocalPlayer()->pitch = currentAngle.y;
			}
		}
	}
};