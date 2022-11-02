#pragma once

#include "Animation.h"
#include <memory>

class AnimationFactory {
public:
    static std::shared_ptr<Animation> Create(const Field& fieldCurrent, const Field& fieldTarget, const Point& point, Animation::Type type);
};