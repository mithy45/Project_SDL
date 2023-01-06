#ifndef TIMER_OBJECT_H
#define TIMER_OBJECT_H

#include <stdint.h>

class TimerObject
{
    public:
        TimerObject() = default;
        TimerObject(uint32_t waiting_milisecond);
        ~TimerObject() = default;

        void start();
        bool is_time_reached();
        void reset(uint32_t waiting_milisecond);

        bool paused = true;

    private:
        uint32_t started_ticks = 0U;
        uint32_t wanted_time;
};
#endif