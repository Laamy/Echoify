#pragma once

#include "Modules/InfAmmo.h"
#include "Modules/ImShort.h"
#include "Modules/Speed.h"
#include "Modules/Flight.h"
#include "Modules/Tracers.h"
#include "Modules/ESP.h"
#include "Modules/Aimbot.h"

void InitMods() {
	modules.push_back(new InfAmmo());
	modules.push_back(new ImShort());
	modules.push_back(new Speed());
	modules.push_back(new Flight());
	modules.push_back(new Tracers());
	modules.push_back(new ESP());
	modules.push_back(new Aimbot());
}