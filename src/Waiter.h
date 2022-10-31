#pragma once

class Waiter {
public:
    Waiter(int interval);

    bool isReady(int currentTime);

private:
    unsigned long previousTime = 0;
    const int interval         = 0;
};
