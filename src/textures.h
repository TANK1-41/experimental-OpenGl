//
// Created by TANK1_41 on 4/1/2022.
//

#ifndef OPENGL_TEXTURES_H
#define OPENGL_TEXTURES_H


class texture {
private:
    static unsigned int s_slot;
    unsigned int m_renderID;
    unsigned int m_position;
public:
    texture(const char *fileLocation, unsigned int colorFormat);

    texture(const texture &rhs) = delete;

    texture &operator=(texture &rhs) = delete;

    void bind() const;

    void unBind();

    [[nodiscard]] unsigned int getRenderID() const;
};


#endif //OPENGL_TEXTURES_H
