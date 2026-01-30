#define GLFW_INCLUDE_NONE

#include "GL.hpp"

#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void GLAPIENTRY gl_debug_cb(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei,
        const GLchar* message,
        const void*
) {
    (void)source; (void)type; (void)id; (void)severity;
    std::fprintf(stderr, "GL: %s\n", message);
}

bool gl_init() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::fprintf(stderr, "Failed to init GLAD\n");
        return false;
    }

    std::fprintf(stderr, "OpenGL: %s\n", glGetString(GL_VERSION));
    std::fprintf(stderr, "Vendor: %s\n", glGetString(GL_VENDOR));
    std::fprintf(stderr, "Renderer: %s\n", glGetString(GL_RENDERER));

    if (GLAD_GL_KHR_debug) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(gl_debug_cb, nullptr);
    }

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}           
