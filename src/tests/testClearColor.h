//
// Created by William Aey on 3/21/2022.
//

#pragma once
#include "tests.h"

namespace test{
    class TestClearColor : public Test{
    public:
        TestClearColor();
        ~TestClearColor() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        float m_ClearColor[4];
    };
}