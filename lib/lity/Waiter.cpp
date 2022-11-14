#include "Waiter.h"

Waiter::Waiter(int interval)
: interval(interval) {
}

bool Waiter::isReady(unsigned long currentTime) {
    bool result = false;

    if (currentTime >= previousTime + interval) {
        previousTime = currentTime;

        result = true;
    }

    return result;
}
