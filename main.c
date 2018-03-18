#include "daemonize.h"
#include "is_time.h"
#include "backup.h"

int main() {

    openlog("Assignment1-Log", LOG_PID|LOG_CONS, LOG_DAEMON);
//    daemonize();

    // setup of authd

    backup("/var/www/html/intranet", "/home/rmurphy");

    while (true) {
        if (is_time(23, 59, 59)) {

        }
        break;
    }
    closelog();
    return 0;
}
