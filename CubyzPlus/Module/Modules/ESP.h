#pragma once

class ESP : public Module {
public:
	ESP() : Module::Module("ESP", "Visual", "Draw boxes with info around players", "yeemi#0", "N") {};

	void OnUpdate(ImDrawData* context) override {

		ImVec2 displaySize = ImGui::GetIO().DisplaySize;

		for (fpsent* plyr : Game::Players::GetPlaying()) {
			ImVec2 screenOut;
			if (Game::ViewMatrix::WorldToScreen(plyr->newpos, screenOut, displaySize)) {
				ImDrawList* list = ImGui::GetBackgroundDrawList();

				ImU32 colour = ImU32(0xFF0000FF);

				if (plyr->GetTeam() == Game::GetLocalPlayer()->GetTeam())
					colour = ImColor(0, 255, 0);

				list->AddText(NULL, 18, ImVec2(screenOut.x - 8, screenOut.y - 20), colour, plyr->GetName().c_str());
				list->AddRect(ImVec2(screenOut.x - 8, screenOut.y - 8), ImVec2(screenOut.x + 8, screenOut.y + 15), colour, 1);
			}
		}
	}
};