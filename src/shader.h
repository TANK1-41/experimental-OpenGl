//
// Created by TANK1_41 on 3/29/2022.
//

#pragma once

#include "GL/glew.h"
#include <xstring>
#include <fstream>
#include <sstream>
#include <iostream>

class shader {
public:
    //the program ID assigned by open gl
        unsigned int ID;

    //constructor reads and builds the shader
    shader(const char* vertexPath, const char* fragmentPath);
    //activiate / bind the shader
    void use();
    //utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

};



