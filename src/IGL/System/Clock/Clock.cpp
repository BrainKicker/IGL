#include <IGL/System/Clock/Clock.h>


namespace igl {

    
    timespec operator-(const timespec& start, const timespec& stop) {
        timespec result { stop.tv_sec - start.tv_sec, stop.tv_nsec - start.tv_nsec };
        if (stop.tv_nsec - start.tv_nsec < 0) {
            result.tv_sec -= 1;
            result.tv_nsec += 1000000000L;
        }
        return result;
    }



    Clock::Clock() : mTime{ 0, 0 } {
        start();
    }



    void Clock::start() {
        mTime.tv_sec = mTime.tv_nsec = 0;
        clock_gettime(CLOCK_MONOTONIC, &mTime);
    }

    void Clock::restart() {
        start();
    }



    void Clock::pause() {
        // do nothing
    }

    void Clock::resume() {
        start();
    }



    long Clock::elapsedSeconds(bool refresh) {
        return elapsedNanos(refresh) / 1000000000L;
    }

    long Clock::elapsedMillis(bool refresh) {
        return elapsedNanos(refresh) / 1000000L;
    }

    long Clock::elapsedMicros(bool refresh) {
        return elapsedNanos(refresh) / 1000L;
    }

    long Clock::elapsedNanos(bool refresh) {
        timespec curTime { 0, 0 };
        clock_gettime(CLOCK_MONOTONIC, &curTime);
        timespec elapsedTime = curTime - mTime;
        if (refresh)
            mTime = curTime;
        return elapsedTime.tv_sec * 1000000000L + elapsedTime.tv_nsec;
    }



    float Clock::elapsedSecondsFloat(bool refresh) {
        return ((float) elapsedNanos(refresh)) / 1000000000.0f;
    }

    double Clock::elapsedSecondsDouble(bool refresh) {
        return ((double) elapsedNanos(refresh)) / 1000000000.0;
    }
}