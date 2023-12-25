#pragma once

#include "GameCore/Structs/keym.h"

class EntityList {
public:
	fpsent* entities[64];
};

float calculateDifferenceBetweenAngles(float firstAngle, float secondAngle)
{
	float difference = secondAngle - firstAngle;
	while (difference < -180) difference += 360;
	while (difference > 180) difference -= 360;
	return difference;
}

namespace Game {

	bool debugScreen = false;

	class Keymap {
	public:
		static std::map<int, keym*> map; // copied from the source

		static bool GetKeyHeld(const char* name) {
			for (std::pair<int, keym*> instance : map)
			{
				if (strcmp(instance.second->name, name) == 0)
				{
					return instance.second->pressed;
				}
			}

			return false;
		}

		static bool GetKeyHeld(int code) {
			for (std::pair<int, keym*> instance : map)
			{
				if (instance.second->code == code)
				{
					return instance.second->pressed;
				}
			}

			return false;
		}

		static void ClickLeft() {
			INPUT    Input = { 0 };
			// left down 
			Input.type = INPUT_MOUSE;
			Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			SendInput(1, &Input, sizeof(INPUT));
			Sleep(25);
			// left up
			ZeroMemory(&Input, sizeof(INPUT));
			Input.type = INPUT_MOUSE;
			Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			SendInput(1, &Input, sizeof(INPUT));
		}
	};

	static fpsent* fpsEntPtr = nullptr;

	fpsent* GetLocalPlayer() {
		return fpsEntPtr;
	}

	void Uninitialize() {
		fpsEntPtr = nullptr; // not needed
		Keymap::map = {};
	}

	class ViewMatrix {
	private:
		static uintptr_t viewmatrix;

	public:
		static float* Get() {
			return (float*)(range_start + viewmatrix);
		}

		// https://github.com/SkidBit/Sauerbraten-ESP-Aimbot/blob/master/DllProjectBase/esp.cpp#L6C9-L6C9
		static bool WorldToScreen(vec pos, ImVec2& screen, ImVec2 window)
		{
			float* matrix = Get();

			//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
			ImVec4 clipCoords;
			clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
			clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
			clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
			clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

			if (clipCoords.w < 0.1f)
				return false;

			//perspective division, dividing by clip.W = Normalized Device Coordinates
			vec NDC;
			NDC.x = clipCoords.x / clipCoords.w;
			NDC.y = clipCoords.y / clipCoords.w;
			NDC.z = clipCoords.z / clipCoords.w;

			screen.x = (window.x / 2 * NDC.x) + (NDC.x + window.x / 2);
			screen.y = -(window.y / 2 * NDC.y) + (NDC.y + window.y / 2);

			return true;
		}
	};

	class Players {
	private:
		static uintptr_t entitylist;

	public:
		static int Size() {
			return *(int*)(range_start + entitylist + 0xC);
		}

		static EntityList* Get() {
			return *(EntityList**)(range_start + entitylist);
		}

		static std::vector<fpsent*> GetFiltered() {
			std::vector<fpsent*> output;

			EntityList* list = Get();

			for (int i = 0; i < Size(); i++) {
				fpsent* ent = list->entities[i];

				if (!IsBadReadPointer(ent))
					output.push_back(ent);
			}

			return output;
		}

		// Does not include localplayer! (get seperately)
		static std::vector<fpsent*> GetPlaying() {
			std::vector<fpsent*> output;

			for (fpsent* ent : GetFiltered()) {
				if (ent->state == CS_ALIVE && ent != Game::GetLocalPlayer())
					output.push_back(ent);
			}

			return output;
		}

		static std::vector<fpsent*> GetSpectating() {
			std::vector<fpsent*> output;

			for (fpsent* ent : GetFiltered()) {
				if ((ent->state == CS_SPECTATOR || ent->state == CS_EDITING) && ent != Game::GetLocalPlayer())
					output.push_back(ent);
			}

			return output;
		}

		static fpsent* ClosestEnemy() {
			fpsent* closestEntity = nullptr;

			float closestEntityDif = 0x2710; // not an important number its just funny & high

			if (Game::GetLocalPlayer() == nullptr)
				return closestEntity;

			for (fpsent* plyr : GetPlaying()) {
				vec src = Game::GetLocalPlayer()->newpos;
				vec dst = plyr->newpos;

				if (plyr->GetTeam() == Game::GetLocalPlayer()->GetTeam())
					continue; // skip cuz same team

				int dist = src.distance(dst);

				if (dist < closestEntityDif) {
					closestEntityDif = dist;
					closestEntity = plyr;
				}
			}

			return closestEntity;
		}
	};

	//class SDL {
	//public:
	//	static ImVec2 GetCursorPos() { // wtf am i doing
	//		// 0x162AE0,x
	//		// 0x162AF0,y
	//		int* cursorX = reinterpret_cast<int*>(sdl_range_start + 0x162AE0);
	//		int* cursorY = reinterpret_cast<int*>(sdl_range_start + 0x162AF0);

	//		std::cout << *cursorX << "," << *cursorY << std::endl;

	//		return ImVec2(*cursorX, *cursorY);
	//	}
	//};
};

// init map for keymap class
std::map<int, keym*> Game::Keymap::map;

// static addresses (I'll make a sig to this later)
uintptr_t Game::Players::entitylist = 0x346C90;
uintptr_t Game::ViewMatrix::viewmatrix = 0x32D040;