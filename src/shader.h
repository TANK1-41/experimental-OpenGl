//
// Created by TANK1_41 on 3/29/2022.
//

#pragma once

#include "GL/glew.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <xstring>

class shader {
public:
    //the program ID assigned by open gl
    unsigned int ID;

    //constructor reads and builds the shader
    shader(const char *vertexPath, const char *fragmentPath);
    ~shader();
    //activiate / bind the shader
    void use();

    //utility uniform functions
    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void setVec4(const std::string &name, float v1,float v2,float v3,float v4) const;
};
