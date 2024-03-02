#pragma once

#include "Figure.h"
#include <memory>

class FigureFactory
{
public:
    std::shared_ptr< Figure > yield();
    bool yieldable();

private:
    int counter = 0;
};
