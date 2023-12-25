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
	// TODO: ItemESP - esp items idk what else u thought
	// TODO: Animations - custom animations & other tweaks to interpolated game mechs
	// TODO: NoHurtcam - disable all hurt effects (or increase them)
	// TODO: FreeLook - allow looking around freely from a third person perspective whole holding ALT (possibly?)
	// TODO: NoSway - disable hand swaying

	// misc
	// TODO: ClickTP - teleport to where you right click when holding CTRL
	// TODO: NetSkip - similar to pingspoof
	// TODO: Crasher - I realized theres quite a few ways to crash sauerbraten servers with game defined packets
	// TODO: AntiBot - allow control over what ESP, aimbot, tracers, ect can hook onto
	// TODO: NoLagBack - prevents the server from changing your server side position freely
	// TODO: AntiImmobile - prevents the server from locking your position (so you can move after games end, ect)
	// TODO: StreamerMode - Change your username/ms

	// movement
	modules.push_back(new Flight());
	modules.push_back(new Speed());
	// TODO: AntiVoid - falling into death pits while hacking hard sucks
	// TODO: FastStop - instantly stop moving when letting go of any keys (velocity, ect)
	// TODO: HighJump - allow controlling of the jump height

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
	// TODO: InPvPTower - named after a CTF exploit where you could get millions of CTF points to get onto the server leaderboard in minutes (it works here)

	// other (not modules)
	// scripting api to allow direct access via javascript or luau(most likely a roblox luau implemenetation as thats what i do most)
	// custom chat commands
	// more speed options (for bunny hop)
	// slash friends to filter out friends from aimbot & aura cheats

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