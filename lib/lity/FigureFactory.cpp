#include "FigureFactory.h"
#include "Arrowhead.h"
#include "Cross.h"
#include "Dot.h"

std::shared_ptr<Figure> FigureFactory::yield() {
    counter++;
    switch (counter) {
        case 1: {
            return std::make_shared<Cross>();
        } break;
        case 2: {
            return std::make_shared<Arrowhead>();
        } break;
        case 3: {
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
