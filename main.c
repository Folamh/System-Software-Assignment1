#include "daemonize.h"
#include "is_time.h"
#include "backup_and_transfer.h"
#include "auditd.h"

int main() {
    char intranet[] = "/var/www/html/intranet";
    char live[] = "/var/www/html/live";
    char bak_loc[] = "/var/backups";
    char report_loc[] = "/var/reports";
    char key[] = "SystemSoftware-Assignment1";

    openlog(key, LOG_PID|LOG_CONS, LOG_DAEMON);

    int msqid = msgget((key_t)56565, 0666 | IPC_CREAT);
    if (msqid < 0) {
        syslog(LOG_ERR, "Unable to build queue.");
        closelog();
        exit(EXIT_FAILURE);
    }
    struct message {
        long type;
        char text[120];
    } msg;
    long msgtyp = 0;

    daemonize();

    setup_auditd(intranet, key);

    while (true) {
        if (is_time(23, 59, 59)) {
            syslog(LOG_INFO, "Beginning end of day routine.");
            int pid = fork();
            if (pid == 0) {
                syslog(LOG_DEBUG, "Forking off backup and transfer.");
                backup_and_transfer(intranet, bak_loc, live);
            }

            pid = fork();
            if (pid == 0) {
                syslog(LOG_DEBUG, "Forking off report file creation.");
                file_report(report_loc, key);
            }
            sleep(1);
        }
        if (msgrcv(msqid, (void *) &msg, sizeof(msg.text), msgtyp, MSG_NOERROR | IPC_NOWAIT) > 0)  {
            if (strcmp(msg.text, "BACKUP") == 0) {
                syslog(LOG_INFO, "Forcing backup and transfer.");
                int pid = fork();
                if (pid == 0) {
                    syslog(LOG_DEBUG, "Forking off backup and transfer.");
                    backup_and_transfer(intranet, bak_loc, live);
                }
            } else {
                syslog(LOG_INFO, msg.text);
            }
        }
    }
}
