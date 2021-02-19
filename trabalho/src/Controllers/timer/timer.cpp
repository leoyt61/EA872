#include "../../../Include/Controllers/timer/timer.hpp"
#include <iostream>


Timer::Timer() {

};

Timer::~Timer(){
};

void Timer::start() {
    m_StartTime = std::chrono::system_clock::now();
    m_bRunning = true;
}

void Timer::stop() {
    m_EndTime = std::chrono::system_clock::now();
    m_bRunning = false;
}

double Timer::elapsedMilliseconds() {
    std::chrono::time_point<std::chrono::system_clock> endTime;

    if(m_bRunning)
    {
        endTime = std::chrono::system_clock::now();
    }
    else
    {
        return 0;
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
}

double Timer::elapsedSeconds() {
    return elapsedMilliseconds() / 1000.0;
}
