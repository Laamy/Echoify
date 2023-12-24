#pragma once

void RenderModuleList() {
    /// @begin TopWindow
    ImGui::SetNextWindowSize({ 640, 480 }, ImGuiCond_FirstUseEver);
    if (ImGui::Begin("title###Dsadsa", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
    {
        /// @separator

            // TODO: Add Draw calls of dependant popup windows here

        /// @begin TabBar
        if (ImGui::BeginTabBar("tabBar1", ImGuiTabBarFlags_None))
        {
            /// @separator

            /// @begin TabItem
            if (ImGui::BeginTabItem("Modules", nullptr, ImGuiTabItemFlags_None))
            {
                /// @separator

                /// @separator
                ImGui::EndTabItem();
            }
            /// @end TabItem

            /// @begin TabItem
            ImGui::BeginDisabled(true);
            if (ImGui::BeginTabItem("Extra", nullptr, ImGuiTabItemFlags_None))
            {
                /// @separator

                /// @separator
                ImGui::EndTabItem();
            }
            ImGui::EndDisabled();
            /// @end TabItem

            /// @begin TabItem
            ImGui::BeginDisabled(true);
            if (ImGui::BeginTabItem("Debug", nullptr, ImGuiTabItemFlags_None))
            {
                /// @separator

                /// @separator
                ImGui::EndTabItem();
            }
            ImGui::EndDisabled();
            /// @end TabItem

            /// @separator
            ImGui::EndTabBar();
        }
        /// @end TabBar

        /// @begin TreeNode
        ImGui::SetNextItemOpen(true, ImGuiCond_Appearing);
        if (ImGui::TreeNodeEx("SampleCategory", ImGuiTreeNodeFlags_None))
        {
            /// @separator

            /// @begin TreeNode
            for (Module* mod : modules) {
                ImGui::SetNextItemOpen(true, ImGuiCond_Appearing);
                if (ImGui::TreeNodeEx("SampleModule", ImGuiTreeNodeFlags_None))
                {
                    /// @separator

                    /// @begin CheckBox
                    ImGui::Checkbox("Enable", &mod->enabled);
                    /// @end CheckBox

                    /// @begin Slider
                    /*ImGui::SetNextItemWidth(200);
                    ImGui::SliderFloat("SampleModuleSlider", &value16, 0, 1, nullptr);
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
                        ImGui::SetTooltip("Tooltip");*/
                    /// @end Slider

                    /// @begin ColorEdit
                    /*ImGui::SetNextItemWidth(200);
                    ImGui::ColorEdit3("SampleModuleColorPicker", (float*)&value17, ImGuiColorEditFlags_None);
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
                        ImGui::SetTooltip("Tooltip");*/
                    /// @end ColorEdit

                    /// @begin CheckBox
                    /*ImGui::Checkbox("SampleModuleCheckBox", &value18);
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
                        ImGui::SetTooltip("Tooltip");*/
                    /// @end CheckBox

                    /// @begin Combo
                    /*ImGui::SetNextItemWidth(200);
                    ImGui::Combo("SampleModuleCombo", &value19, "combo1\0combo2\0combo3\0");
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal))
                        ImGui::SetTooltip("Tooltip");*/
                    /// @end Combo

                    /// @separator
                    ImGui::TreePop();
                }
            }
            /// @end TreeNode

            /// @separator
            ImGui::TreePop();
        }
        /// @end TreeNode

        /// @separator
        ImGui::End();
    }
    /// @end TopWindow

}