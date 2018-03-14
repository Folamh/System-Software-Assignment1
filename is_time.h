#include <stdbool.h>
#include <time.h>

bool is_time (int hr, int min, int sec) {
	time_t current_time;
	time(&current_time);
	struct tm desired_time = *localtime(&current_time);
	desired_time.tm_hour = hr;
	desired_time.tm_min = min;
	desired_time.tm_sec = sec;

	if (difftime(current_time, mktime(&desired_time))) {
		return true;
	} else {
		return false;
	}
}
