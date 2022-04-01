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
private:
    unsigned int ID;
public:
    //the program ID assigned by open gl

    //constructor reads and builds the shader
    shader(const char *vertexPath, const char *fragmentPath);

    shader(const shader &rhs) = delete;

    shader &operator=(shader &rhs) = delete;

    ~shader();

    //activiate / bind the shader
    void use() const;

    [[nodiscard]] unsigned int getID() const;

    //utility uniform functions
    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;

    void setVec4(const std::string &name, float v1, float v2, float v3, float v4) const;
};
