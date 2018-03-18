#ifndef IS_TIME_H
#define IS_TIME_H

#include <stdbool.h>
#include <time.h>
#include <unistd.h>

bool is_time (int hr, int min, int sec) {
    time_t current_time;
    time(&current_time);
    struct tm desired_time = *localtime(&current_time);
    desired_time.tm_hour = hr;
    desired_time.tm_min = min;
    desired_time.tm_sec = sec;

    if (difftime(current_time, mktime(&desired_time))) {
        sleep(3);
        return true;
    } else {
        return false;
    }
}

#endif //IS_TIME_H