#include "App.hpp"

#include <stdexcept>
#include <vector>
#include <cmath>
#include <algorithm>

#include <GLFW/glfw3.h>
#include "render/GL.hpp"
#include "render/RasterLayer.hpp"
#include "render/Viewport.hpp"
#include "ui/Ui.hpp"

static void glfw_error_cb(int err, const char* desc) {
    (void)err;
    fprintf(stderr, "GLFW error: %s\n", desc);
}

bool App::init() {
    glfwSetErrorCallback(glfw_error_cb);
    if (!glfwInit()) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window_ = glfwCreateWindow(winW_, winH_, "meteo", nullptr, nullptr);
    if (!window_) return false;

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);

    if (!gl_init()) return false;

    return true;
}

void App::run() {
    const int gridW = 512, gridH = 256;
    RasterLayer raster(gridW, gridH);
    raster.buildDefaultColormap();

    ViewportLayout layout;
    layout.mode = ViewportMode::Four;

    float t = 0.0f;
    bool playing = true;
    float alpha = 0.85f;
    float vmin = 0.0f, vmax = 1.0f;

    while (!glfwWindowShouldClose(window_) && running_) {
        glfwPollEvents();
        glfwGetFramebufferSize(window_, &winW_, &winH_);

        if (playing) t += 0.016f;

        std::vector<float> field(gridW * gridH);
        for (int y = 0; y < gridH; ++y) {
            for (int x = 0; x < gridW; ++x) {
                float fx = float(x) / float(gridW);
                float fy = float(y) / float(gridH);
                float v =
                    0.55f
                    + 0.25f * std::sin(6.0f * fx + t)
                    + 0.20f * std::cos(5.0f * fy - 0.8f * t)
                    + 0.10f * std::sin(10.0f * (fx + fy) + 0.4f *t);
                field[y * gridW + x] = v;
            }
        }
        raster.uploadScalar(field.data());

        glClearColor(0.07f, 0.07f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        auto rects = layout.computeRects(winW_, winH_);

        for (auto& r : rects) {
            raster.setParams(vim, vmax, alpha);
            raster.render(r.x, r,y, r.w, r.h);
        }

        ui_begin();
        UiState s{};
        s.viewportMode = layout.mode;
        s.playing = playing;
        s.alpha = alpha;
        s.vmin = vmin;
        s.max = vmax;

        ui_draw(s);

        layout.mode = s.viewportMode;
        playing = s.playing;
        alpha = s.alpha;
        vmin = s.vmin;
        vmax = std::max(s.vmax, s.vmin + 1e-6f);

        ui_end();

        glfwSwapBuffers(window_);
    }
}

void App::shutdown() {
    ui_shutdown();
    if (window_) glfwDestroyWindow(window_);
    glfwTerminate();
}
