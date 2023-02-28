#include "FigureFactory.h"
#include "Arrowhead.h"
#include "Circle.h"
#include "Cross.h"
#include "Dot.h"
#include "Square.h"

std::shared_ptr<Figure> FigureFactory::yield() {
    counter++;
    switch (counter) {
        case 1: {
            return std::make_shared<Circle>();
        } break;
        case 2: {
            return std::make_shared<Square>();
        } break;
        case 3: {
            return std::make_shared<Cross>();
        } break;
        case 4: {
            return std::make_shared<Dot>();
        } break;
        default: {
            return nullptr;
        } break;
    }
}

bool FigureFactory::yieldable() {
    const auto& result = yield();
    counter--;
    return static_cast<bool>(result);
}
