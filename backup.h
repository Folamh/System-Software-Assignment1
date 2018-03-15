#ifndef BACKUP_H
#define BACKUP_H

#include <sys/stat.h>
#include <stdlib.h>
#include <syslog.h>
#include <time.h>
#include <string.h>

void backup(char folder[100], char bak_loc[100]) {
    syslog(LOG_INFO, "Locking down backup folder.");
    char mode[] = "0444";
    int i = strtol(mode, 0, 8);
    if (chmod(folder, i) < 0) {
        syslog(LOG_ERR, "Error while changing file permissions.");
    }

    char filename[40];
    struct tm *timenow;

    time_t now = time(NULL);
    timenow = gmtime(&now);

    strftime(filename, sizeof(filename), strcat(bak_loc, "/Backup_%Y-%m-%d_%H:%M:%S"), timenow);
    syslog(LOG_INFO, "Creating backup: %s", filename);
}

#endif //BACKUP_H
