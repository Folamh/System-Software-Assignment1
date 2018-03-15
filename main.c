#include "daemonize.h"
#include "is_time.h"
#include "backup.h"

int main() {

    openlog("Assignment1-Log", LOG_PID|LOG_CONS, LOG_DAEMON);
//    daemonize();

    // setup of authd

    backup("/home/rmurphy/Projects/playhouse/c/test_folder", "/home/rmurphy/Projects/playhouse/c/test_folder_bak");

    while (true) {
        if (is_time(23, 59, 59)) {

        }
        break;
    }
    closelog();
    return 0;
}
