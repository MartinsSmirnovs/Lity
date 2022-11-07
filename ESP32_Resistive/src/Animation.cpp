#include "Animation.h"

Animation::Animation(const RGB& colorCurrent, const RGB& colorTarget, const Point& point)
: point(point),
  colorTarget(colorTarget),
  colorCurrent(colorCurrent) {
}

auto Animation::getPoint() const -> const Point& {
    return point;
}

auto Animation::getColor() const -> const RGB& {
    return colorCurrent;
}
