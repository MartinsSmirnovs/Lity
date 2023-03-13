#include "AnimationFactory.h"
#include "Blink.h"
#include "Fade.h"

std::shared_ptr<Animation> AnimationFactory::Create(const Field& fieldCurrent, const Field& fieldTarget, const Point& point, Animation::Type type) {
    switch (type) {
        case Animation::appearance: {
            return std::make_shared<Fade>(fieldCurrent.getColor(),
                                          fieldTarget.getColor(),
                                          point);
        } break;
        case Animation::payment: {
            return std::make_shared<Blink>(fieldCurrent.getColor(),
                                           fieldTarget.getColor(),
                                           point);
        } break;
    }
}
