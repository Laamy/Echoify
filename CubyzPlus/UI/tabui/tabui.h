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

    std::vector<std::string> categories = { "Combat", "Movement", "Visual" };
    int selectedCategory = 0;

    void Next() {
        selectedCategory = (selectedCategory + 1) % categories.size();
    }

    void Prev() {
        selectedCategory = (selectedCategory - 1 + categories.size()) % categories.size();
    }

    void Draw()
    {
        /// @style Dark
        /// @unit px
        /// @begin TopWindow
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 2, 2 });
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 2, 2 });
        ImGui::SetNextWindowSize({ 104, ((this->categories.size() + 1) * 28.f) - 4 }, ImGuiCond_FirstUseEver);
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

                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyle().Colors[ImGuiCol_ChildBg]);
                ImGui::BeginChild((std::string("child") + i).c_str(), { 100, 24 }, false, ImGuiWindowFlags_AlwaysUseWindowPadding);
                {
                    /// @separator

                    /// @begin Text
                    if (selectedCategory == sel)
                        ImGui::TextUnformatted((std::string(">") + i).c_str());
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
    }

    /// @end interface

private:
    /// @begin impl

    bool isOpen = true;
    /// @end impl
};