#pragma once

#include <IGL/Config.h>

#include <chrono>


namespace igl {


    class Clock {

        timespec mTime;

    public:

        Clock();

        void start();
        void restart();

        void pause();
        void resume();

        long elapsedSeconds(bool refresh = true);
        long elapsedMillis(bool refresh = true);
        long elapsedMicros(bool refresh = true);
        long elapsedNanos(bool refresh = true);

        float elapsedSecondsF(bool refresh = true);
        double elapsedSecondsD(bool refresh = true);
    };
}