#pragma once
#include <cstdint>

struct GLFWwindow;

class App {
    public:
        bool init();
        bool run();
        void shutdown();

    private:
        GLFWwindow* window_ = nullptr;
        int winW_ = 1280, winH_ = 720;
        bool running_ = true;
};
