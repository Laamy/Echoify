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

    void Draw(ImVec2 nextPos)
    {
        /// @style Dark
        /// @unit px
        /// @begin TopWindow
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 2, 2 });
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 2, 2 });
        ImGui::SetNextWindowPos(nextPos);
        ImGui::SetNextWindowSize({ 104, 158 }, ImGuiCond_FirstUseEver);
        if (isOpen && ImGui::Begin("title###Tabui_category", &isOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
        {
            /// @separator

            // fix font default scale
            ImGui::SetWindowFontScale(0.41f);

            // TODO: Add Draw calls of dependant popup windows here

            /// @begin Child
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyle().Colors[ImGuiCol_ChildBg]);
            ImGui::BeginChild("child1", { 100, 24 }, false, ImGuiWindowFlags_AlwaysUseWindowPadding);
            {
                /// @separator

                /// @begin Text
                ImGui::TextUnformatted("ClickTP");
                /// @end Text

                /// @separator
                ImGui::EndChild();
            }
            ImGui::PopStyleColor();
            /// @end Child

            /// @begin Child
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyle().Colors[ImGuiCol_ChildBg]);
            ImGui::BeginChild("child2", { 100, 24 }, false, ImGuiWindowFlags_AlwaysUseWindowPadding);
            {
                /// @separator

                /// @begin Text
                ImGui::TextUnformatted("Disabler");
                /// @end Text

                /// @separator
                ImGui::EndChild();
            }
            ImGui::PopStyleColor();
            /// @end Child

            /// @begin Child
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyle().Colors[ImGuiCol_ChildBg]);
            ImGui::BeginChild("child3", { 100, 24 }, false, ImGuiWindowFlags_AlwaysUseWindowPadding);
            {
                /// @separator

                /// @begin Text
                ImGui::TextUnformatted("Franky");
                /// @end Text

                /// @separator
                ImGui::EndChild();
            }
            ImGui::PopStyleColor();
            /// @end Child

            /// @begin Child
            ImGui::PushStyleColor(ImGuiCol_ChildBg, 0xff323432);
            ImGui::BeginChild("child4", { 100, 24 }, false, ImGuiWindowFlags_AlwaysUseWindowPadding);
            {
                /// @separator

                /// @begin Text
                ImGui::TextUnformatted(" NetSkip");
                /// @end Text

                /// @separator
                ImGui::EndChild();
            }
            ImGui::PopStyleColor();
            /// @end Child

            /// @begin Child
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyle().Colors[ImGuiCol_ChildBg]);
            ImGui::BeginChild("child5", { 100, 24 }, false, ImGuiWindowFlags_AlwaysUseWindowPadding);
            {
                /// @separator

                /// @begin Text
                ImGui::TextUnformatted("NoFall");
                /// @end Text

                /// @separator
                ImGui::EndChild();
            }
            ImGui::PopStyleColor();
            /// @end Child

            /// @begin Child
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyle().Colors[ImGuiCol_ChildBg]);
            ImGui::BeginChild("child6", { 100, 24 }, false, ImGuiWindowFlags_AlwaysUseWindowPadding);
            {
                /// @separator

                /// @begin Text
                ImGui::TextUnformatted("TestModule");
                /// @end Text

                /// @separator
                ImGui::EndChild();
            }
            ImGui::PopStyleColor();
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