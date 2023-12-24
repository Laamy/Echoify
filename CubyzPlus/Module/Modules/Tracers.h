#pragma once

class Tracers : public Module {
public:
	Tracers() : Module::Module("Tracers", "Visual", "Draw lines from bottom of the screen to players nearby", "yeemi#0", "M") {};

	void OnUpdate(ImDrawData* context) override {

		ImVec2 displaySize = ImGui::GetIO().DisplaySize;
		
		for (fpsent* plyr : Game::Players::GetPlaying()) {
			ImVec2 screenOut;
			if (Game::ViewMatrix::WorldToScreen(plyr->newpos, screenOut, displaySize)) {
				ImDrawList* list = ImGui::GetBackgroundDrawList();

				ImU32 colour = ImU32(0xFF0000FF);

				if (plyr->GetTeam() == Game::GetLocalPlayer()->GetTeam())
					colour = ImColor(0, 255, 0);

				list->AddLine(screenOut, ImVec2(displaySize.x / 2, displaySize.y), colour, 1);
			}
		}

		//ImGui::SetNextWindowSize(ImVec2(1920, 1080), ImGuiCond_FirstUseEver);
		//ImGui::SetNextWindowPos(ImVec2(0, 0));
		//ImGui::Begin("Echoify Menu by yeemi#0", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
		//if (Game::GetLocalPlayer() == nullptr)
		//{
		//	ImGui::Text("Not ingame..");
		//}
		//else
		//{
		//	fpsent* plyr = Game::GetLocalPlayer();
		//	// physent variables first
		//	{
		//		// starting vecs
		//	}
		//	ImGui::Text("entities count: %d", Game::Players::Size());
		//	IMGUI_TEXT_NEWLINE();
		//	for (fpsent* plyr : Game::Players::GetFiltered()) {
		//		std::stringstream ss;
		//		ss << plyr->xradius << "," << plyr->yradius << "," << plyr->zmargin;
		//		ImGui::Text(ss.str().c_str());
		//	}
		//}
		//ImGui::End();
	}
};