#pragma once

#include "Animation.h"
#include "Field.h"
#include <memory>

namespace AnimationFactory
{
std::shared_ptr< Animation > Create( const Field& fieldCurrent, const Field& fieldTarget, const Point& point, Animation::Type type );
};