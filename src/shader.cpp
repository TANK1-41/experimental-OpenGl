//
// Created by TANK1_41 on 3/29/2022.
//

#include "shader.h"

shader::shader(const char *vertexPath, const char *fragmentPath) {

}

void shader::use() {
    glUseProgram(ID);
}

void shader::setBool(const std::string &name, bool value) const {

}

void shader::setInt(const std::string &name, int value) const {

}

void shader::setFloat(const std::string &name, float value) const {

}
