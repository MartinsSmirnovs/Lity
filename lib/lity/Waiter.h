#pragma once

class Waiter {
public:
    Waiter(int interval);

    bool isReady(unsigned long currentTime);

private:
    unsigned long previousTime = 0;
    const int interval         = 0;
};
