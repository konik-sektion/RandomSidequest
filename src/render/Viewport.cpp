#include "Viewport.hpp"

std::vector<Rect> ViewportLayout::computeRects(int W, int H) const {
    std::vector<Rect> out;
    if (mode == ViewportMode::One) {
        out.push_back({0, 0, W, H});
    } else if (mode == ViewportMode::Two) {
        out.push_back({0, H/2, W, H/2});
        out.push_back({0, 0,   W, H/2});
    } else {
        out.push_back({0,   H/2, W/2, H/2});
        out.push_back({W/2, H/2, W/2, H/2});
        out.push_back({0,   0,   W/2, H/2});
        out.push_back({W/2, 0,   W/2, H/2});
    }
    return out;
}
