#pragma once

#include <IGL/igl_compile_includes.h>


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

        float elapsedSecondsFloat(bool refresh = true);
        double elapsedSecondsDouble(bool refresh = true);
    };
}