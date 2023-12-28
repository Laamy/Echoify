#pragma once

class ESP : public Module {
public:
	ESP() : Module::Module("ESP", "Visual", "Draw boxes with info around players", "yeemi#0", "N") {};

	void OnUpdate(ImDrawData* context) override {
        if (Game::GetLocalPlayer() == nullptr)
            return;

		ImVec2 displaySize = ImGui::GetIO().DisplaySize;

		for (fpsent* plyr : Game::Players::GetPlaying()) {
            ImVec2 screenOutCenter;
            if (Game::ViewMatrix::WorldToScreen(
                vec(plyr->newpos), screenOutCenter, displaySize)) {

                ImDrawList* list = ImGui::GetBackgroundDrawList();

                ImU32 colour = ImU32(0xFF0000FF);

                if (plyr->GetTeam() == Game::GetLocalPlayer()->GetTeam())
                    colour = ImColor(0, 255, 0);

                float distance = Game::GetLocalPlayer()->o.distance(plyr->o) / (plyr->eyeheight * 6); // scale distance properly

                const float baseSizeX = 50.0f;
                const float baseSizeY = baseSizeX * 2.0f;
                float boxSizeX = max(baseSizeX / distance, 5.0f);
                float boxSizeY = max(baseSizeY / distance, 10.0f);

                ImVec2 boxMin = ImVec2(screenOutCenter.x - boxSizeX / 2, screenOutCenter.y - boxSizeY / 2);
                ImVec2 boxMax = ImVec2(screenOutCenter.x + boxSizeX / 2, screenOutCenter.y + boxSizeY / 2);

                // adjust
                boxMin.y += boxSizeY / 2;
                boxMax.y += boxSizeY / 2;

                // Draw the box and text
                list->AddText(NULL, 18, ImVec2(screenOutCenter.x, screenOutCenter.y), colour, plyr->GetName().c_str());
                list->AddRect(boxMin, boxMax, colour, 1);
            }
		}
	}
};