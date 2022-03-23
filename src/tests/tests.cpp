//
// Created by TANK1_41 on 3/23/2022.
//
#include "tests.h"
#include "imgui/imgui.h"
namespace test{


    TestMenu::TestMenu(Test *&currentTestPointer)
    :m_CurrentTest(currentTestPointer)
    {

    }
    TestMenu::~TestMenu()
    {

    }
    void TestMenu::OnImGuiRender() {
        for (const auto &test: m_Tests)
        {
            if(ImGui::Button(test.first.c_str()))
                m_CurrentTest = test.second();
        }

    }

}