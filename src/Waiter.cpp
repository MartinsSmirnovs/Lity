#include "Waiter.h"

Waiter::Waiter(int interval)
: interval(interval) {
}

bool Waiter::isReady(int currentTime) {
    bool result = false;

    if (currentTime >= previousTime + interval) {
        previousTime = currentTime;

        result = true;
    }

    return result;
}
