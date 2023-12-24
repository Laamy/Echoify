#pragma once

class Flight : public Module {
public:
    Flight() : Module::Module("Flight", "Fancy PI flight", "yeemi#0", "J") {};

    float speed = 2.5f;

    float degreesToRadians(float degrees) {
        return degrees * (PI / 180.0f);
    }

    float radiansToDegrees(float radians) {
        return radians * (180.0f / PI);
    }

    void OnTick(fpsent* player) override {
        vec cameraVector = player->headpos();

        float yaw = cameraVector.x;

        yaw = degreesToRadians(yaw);

        vec cameraDirection;
        cameraDirection.x = cos(yaw);
        cameraDirection.z = sin(yaw);

        float length = sqrt(cameraDirection.x * cameraDirection.x + cameraDirection.z * cameraDirection.z);
        if (length != 0.0f) {
            cameraDirection.x /= length;
            cameraDirection.z /= length;
        }

        vec velocity(0.0f, 0.0f, 0.0f);

        if (player->strafe == -1) {
            velocity.x += speed * cameraDirection.x;
            velocity.z += speed * cameraDirection.z;
        }
        else if (player->strafe == 1) {
            velocity.x -= speed * cameraDirection.x;
            velocity.z -= speed * cameraDirection.z;
        }

        if (player->move == -1) {
            velocity.x -= speed * cameraDirection.z;
            velocity.z += speed * cameraDirection.x;
        }
        else if (player->move == 1) {
            velocity.x += speed * cameraDirection.z;
            velocity.z -= speed * cameraDirection.x;
        }

        player->vel.x = velocity.x;

        if (Game::Keymap::GetKeyHeld(VK_SPACE))
            player->vel.z = player->vel.z * (speed / 2);
        /*else if (player->crouching)
            player->vel.z = -(speed / 2);*/

        player->vel.y = velocity.z;
    };
};