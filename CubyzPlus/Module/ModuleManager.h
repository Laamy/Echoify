#pragma once

//#include "Modules/InfAmmo.h"
//#include "Modules/ImShort.h"
#include "Modules/Speed.h"
#include "Modules/Flight.h"
#include "Modules/Tracers.h"
#include "Modules/ESP.h"
#include "Modules/Aimbot.h"
#include "Modules/TabUI.h"

void InitMods() { // the commented TODO modules are most likely confirmed modules im gonna be working on
	// combat
	modules.push_back(new Aimbot());
	// TODO: Hitbox - increase a fake hitbox around each player for ghost cheaters
	// TODO: Tpaura - teleort around the players (or smoothly interpolate) while shooting

	// visual
	modules.push_back(new TabUI());
	modules.push_back(new Tracers());
	modules.push_back(new ESP());
	// TODO: Animations - custom animations & other tweaks to interpolated game mechs
	// TODO: NoHurtcam - disable all hurt effects (or increase them)

	// misc
	// TODO: ClickTP - teleport to where you right click when holding CTRL
	// TODO: NetSkip - similar to pingspoof
	// TODO: Crasher - I realized theres quite a few ways to crash sauerbraten servers with game defined packets

	// movement
	modules.push_back(new Flight());
	modules.push_back(new Speed());
	// TODO: AntiVoid - falling into death pits while hacking hard sucks
	// TODO: FastSpot - instantly stop moving when letting go of any keys (velocity, ect)

	// player
	// TODO: AirJump - jump on air
	// TODO: Spider - climb walls
	// TODO: Velocity - nothing modifies ur velocity values other then ur movement keys
	// TODO: Phase - phase through walls
	// TODO: NoClip - floors too
	// TODO: FreeCam - allow the camera to fly freely

	// world
	// TODO: AirStuck - forcefully stick yourself to a single place
	// TODO: SoundPlayer - allow spam of some sounds

	for (Module* mod : modules) {
		bool has = false;
		for (std::string cat : tabui.categories) {
			if (mod->category == cat)
				has = true;
		}

		if (!has)
			tabui.categories.push_back(mod->category);
	}
}