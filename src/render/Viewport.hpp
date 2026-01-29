#pragma once
#include <vector>

struct Rect {
    int x, y, w, h;
};

enum class ViewportMode {
    One, Two, Four
};

struct ViewportLayout {
    ViewportMode mode = ViewportMode::Four;
    std::vector<Rect> computeRects(int fbW, int fbH) const;
};
