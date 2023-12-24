// Generated with ImRAD 0.6
// visit https://github.com/tpecholt/imrad

// some imgui stuff
#include "../../../Libs/imgui/imgui_impl_opengl3.h"
#include "../../../Libs/imgui/imgui_impl_win32.h"

#pragma once

class TabuiCategory
{
public:
    /// @begin interface
    void Open()
    {
        isOpen = true;
    };

    void Close()
    {
        isOpen = false;
    };

    void Draw(std::string category, int selectedModule, ImVec2 nextPos)
    {
        std::vector<Module*> catModules;

        for (Module* mod : modules) {
            if (mod->category == category)
                catModules.push_back(mod);
        }

        /// @style Dark
        /// @unit px
        /// @begin TopWindow
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 2, 2 });
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 2, 2 });
        ImGui::SetNextWindowPos(nextPos);
        ImGui::SetNextWindowSize({ 104, (28.f * (float)catModules.size()) - 4.f }, ImGuiCond_Always);
        if (isOpen && ImGui::Begin("title###Tabui_category", &isOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
        {
            /// @separator

            // fix font default scale
            ImGui::SetWindowFontScale(0.41f);

            // TODO: Add Draw calls of dependant popup windows here

            /// @begin Child
            int sel = 0;
            for (Module* mod : catModules) {
                if (sel == selectedModule)
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, 0xff323432);
                else
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyle().Colors[ImGuiCol_ChildBg]);

                ImGui::BeginChild((std::string("child") + mod->name).c_str(), {100, 24}, false, ImGuiWindowFlags_AlwaysUseWindowPadding);
                {
                    /// @separator

                    /// @begin Text
                    if (sel == selectedModule)
                        ImGui::TextUnformatted((std::string(" ") + mod->name).c_str());
                    else
                        ImGui::TextUnformatted(mod->name.c_str());
                    /// @end Text

                    /// @separator
                    ImGui::EndChild();
                }
                ImGui::PopStyleColor();
                sel++;
            }
            /// @end Child

            /// @separator
            ImGui::End();
        }
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();
        /// @end TopWindow
    };

    /// @end interface

private:
    /// @begin impl

    bool isOpen = true;
    /// @end impl
};