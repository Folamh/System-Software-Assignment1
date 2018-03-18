#include "daemonize.h"
#include "is_time.h"
#include "backup_and_transfer.h"

void setup_auditd(char *folder, char *key) {
    char command[300];
    snprintf(command, sizeof(command), "auditctl -w %s -p w -k %s", folder, key);
    system(command);
}

void file_report(char *folder, char *key) {
    char filename[40];
    struct tm *timenow;
    time_t now = time(NULL);
    timenow = gmtime(&now);
    strftime(filename, sizeof(filename), "report_%Y-%m-%d.txt", timenow);

    char command[300];
    snprintf(command, sizeof(command), "ausearch -ts today -k %s | aureport -f -i >> %s", key, filename);
    system(command);
}

int main() {
    char intranet[100] = "/var/www/html/intranet";
    char live[100] = "/var/www/html/live";
    char bak_loc[100] = "/var/backups";
    char report_loc[] = "/var/reports";
    char audit_key[] = "SystemSoftware-Assignment";
    openlog("Assignment1-Log", LOG_PID|LOG_CONS, LOG_DAEMON);
    daemonize();

    setup_auditd(intranet, audit_key);

    while (true) {
        if (is_time(23, 59, 59)) {
            backup_and_transfer(intranet, bak_loc, live);
            file_report(report_loc, audit_key);

            sleep(1);
        }
        break;
    }
    closelog();
    return 0;
}
