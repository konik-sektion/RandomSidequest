#pragma once
#include <glad/glad.h>

class Quad {
    public:
        Quad();
        ~Quad();
        void draw() const;

    private:
        GLuint vao_ = 0;
        GLuint vbo_ = 0;
};
