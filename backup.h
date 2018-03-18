#ifndef BACKUP_H
#define BACKUP_H

#include <sys/stat.h>
#include <stdlib.h>
#include <syslog.h>
#include <time.h>
#include <string.h>

void change_perm(char folder[], char mode[]) {
    if (chmod(folder, strtol(mode, 0, 8)) < 0) {
        syslog(LOG_ERR, "Error while changing file permissions.");
    }
}

void backup(char folder[100], char bak_loc[100]) {
    syslog(LOG_INFO, "Locking down folder for backup.");
    change_perm(folder, "0444");

    char filename[40];
    struct tm *timenow;

    time_t now = time(NULL);
    timenow = gmtime(&now);

    strftime(filename, sizeof(filename), "backup_%Y-%m-%d_%H:%M:%S.tar", timenow);
    syslog(LOG_INFO, "Creating backup: %s", filename);

    strcat(bak_loc, filename);
    char command[180] = "tar czf ";
    strcat(command, bak_loc);
    strcat(command, " ");
    strcat(command, folder);
    syslog(LOG_INFO, "%s", command);
    
    syslog(LOG_INFO, "Unlocking folder.");
    change_perm(folder, "0777");
}

#endif //BACKUP_H
