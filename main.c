#include <stdio.h>
#include "daemonize.h"
#include <syslog.h>
#include "is_time.h"

int main() {
	openlog("Assignment1-Log", LOG_PID|LOG_CONS, LOG_DAEMON);
	printf("Before");
	daemonize();
	
	if (is_time(23, 59, 59)) {
		printf("Hello");
	}
	printf("After");
	closelog();
	return 0;
}
