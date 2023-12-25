#pragma once

class AutoRespawn : public Module {
public:
	AutoRespawn() : Module::Module("AutoRespawn", "Player", "Automatically respawn", "yeemi#0", "NONE") {};

	void OnTick(fpsent* player) override {

		std::stringstream ss;

		char c;
		int r;
		for (int i = 0; i < 10; i++)
		{
			r = rand() % 26;   // generate a random number
			c = 'a' + r;            // Convert to a character from a-z
			ss << c;
		}

		player->SetName(ss.str().c_str());

		//addmsg(N_SWITCHNAME, "rs", player->name);
		CallFunc<bool, int, const char*, const char*>(range_start + 0x1E6E50, N_SWITCHNAME, "rs", player->name);

	}
};