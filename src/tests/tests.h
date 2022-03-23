//
// Created by William Aey on 3/21/2022.
//

#pragma once
#include <vector>
#include <iostream>
#include "string"
#include "functional"
#define OPENGL_TESTS_H

namespace test {
    class Test {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime){};
        virtual void OnRender(){};
        virtual void OnImGuiRender(){};
    };

class TestMenu : public Test{
public:
    TestMenu(Test*& currentTestPointer);
    virtual ~TestMenu();


    void OnImGuiRender() override;
    template<typename t>
    void RegisterTest(const std::string& name)
    {
        std::cout<< "Registering tests" <<name <<std::endl;
        m_Tests.push_back(std::make_pair(name,[](){return new t();} ));
    }
    private:
    Test*& m_CurrentTest;
    std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
};
}// namespace test