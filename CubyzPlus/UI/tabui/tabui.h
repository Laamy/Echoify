// Generated with ImRAD 0.6
// visit https://github.com/tpecholt/imrad

// some imgui stuff
#include "../../../Libs/imgui/imgui_impl_opengl3.h"
#include "../../../Libs/imgui/imgui_impl_win32.h"

#pragma once

class Tabui
{
public:
    /// @begin interface
    void Open()
    {
        this->isOpen = true;
    };

    void Close()
    {
        this->isOpen = false;
    };

    std::vector<std::string> categories = {};

    int selectedCategory = 0;
    int selectedModule = 0;

    bool inCategory = false;

    TabuiCategory category;

    ImVec2 tabuiPos = ImVec2(50, 50);

    std::vector<Module*> GetCatMods() {
        std::vector<Module*> catModules;

        for (Module* mod : modules) {
            if (mod->category == categories[selectedCategory])
                catModules.push_back(mod);
        }

        return catModules;
    }

    void Next() {
        if (!inCategory)
            selectedCategory = (selectedCategory + 1) % categories.size();
        else {
            std::vector<Module*> catModules = GetCatMods();

            selectedModule = (selectedModule + 1) % catModules.size();
        }
    }

    void Prev() {
        if (!inCategory)
            selectedCategory = (selectedCategory - 1 + categories.size()) % categories.size();
        else {
            std::vector<Module*> catModules = GetCatMods();

            selectedModule = (selectedModule - 1) % catModules.size();
        }
    }

    void Enter() {
        if (inCategory) {
            std::vector<Module*> catModules = GetCatMods();

            catModules[selectedModule]->Toggle();
        }

        if (selectedModule >= GetCatMods().size())
            selectedModule = GetCatMods().size() - 1;
        
        inCategory = true;
        category.Open();
    }

    void Exit() {
        inCategory = false;
        category.Close();
    }

    void Draw()
    {
        /// @style Dark
        /// @unit px
        /// @begin TopWindow
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 2, 2 });
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 2, 2 });
        ImGui::SetNextWindowPos(tabuiPos);
        ImGui::SetNextWindowSize({ 104, ((this->categories.size() + 1) * 26.f) + 2 }, ImGuiCond_FirstUseEver);
        if (this->isOpen && ImGui::Begin("title###Tabui", &this->isOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
        {
            // fix font default scale
            ImGui::SetWindowFontScale(0.41f);

            /// @separator

            // TODO: Add Draw calls of dependant popup windows here

            /// @begin Child
            ImGui::PushStyleColor(ImGuiCol_ChildBg, 0xff993333);
            ImGui::BeginChild("child1", { 100, 24 }, false, ImGuiWindowFlags_AlwaysUseWindowPadding);
            {
                /// @separator

                /// @begin Text
                ImGui::TextUnformatted("   ECHOIFY");
                /// @end Text

                /// @separator
                ImGui::EndChild();
            }
            ImGui::PopStyleColor();
            /// @end Child

            /// @begin Child
            int sel = 0;
            for (std::string i : this->categories) { // each category is 28 pixels down from each others each tops
                /*if (selectedCategory == sel)
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, 0xff323432);*/

                if (selectedCategory == sel)
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, 0xff323432);
                else
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyle().Colors[ImGuiCol_ChildBg]);
                ImGui::BeginChild((std::string("child") + i).c_str(), { 100, 24 }, false, ImGuiWindowFlags_AlwaysUseWindowPadding);
                {
                    /// @separator

                    /// @begin Text
                    if (selectedCategory == sel)
                        ImGui::TextUnformatted((std::string(" ") + i).c_str());
                    else
                        ImGui::TextUnformatted(i.c_str());
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

        //lets check if we're in a category then draw one if we are...
        if (inCategory) {
            category.Draw(categories[selectedCategory], selectedModule, ImVec2(tabuiPos.x + 104, (tabuiPos.y + 24) + (selectedCategory * 28)));// ignore for now
        }
    }

    /// @end interface

private:
    /// @begin impl

    bool isOpen = true;
    /// @end impl
};