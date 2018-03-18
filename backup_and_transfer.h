#ifndef BACKUP_TRANSFER_H
#define BACKUP_TRANSFER_H

#include <sys/stat.h>
#include <stdlib.h>
#include <syslog.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

void change_perm(char folder[], char mode[]) {
    if (chmod(folder, (__mode_t) strtol(mode, 0, 8)) < 0) {
        syslog(LOG_ERR, "Error while changing file permissions.");
    }
}

void backup_and_transfer(char *folder, char *bak_loc, char *trans_loc) {
    char filename[40];
    struct tm *timenow;
    time_t now = time(NULL);
    timenow = gmtime(&now);
    strftime(filename, sizeof(filename), "backup_%Y-%m-%d_%H-%M-%S.tar", timenow);

    syslog(LOG_INFO, "Locking down folder for backup and transfer.");
    change_perm(folder, "0555");

    char command[300];
    snprintf(command, sizeof(command), "tar Pczf %s/%s %s", bak_loc, filename, folder);
    syslog(LOG_DEBUG, "Backup command: %s", command);

    syslog(LOG_INFO, "Creating backup: %s", filename);
    system(command);

    syslog(LOG_INFO, "Beginning transfer to : %s", trans_loc);
    snprintf(command, sizeof(command), "rsync -ac %s %s", folder, trans_loc);
    syslog(LOG_DEBUG, "Transfer command: %s", command);
    system(command);

    syslog(LOG_INFO, "Unlocking folder.");
    change_perm(folder, "0777");
}

#endif //BACKUP_TRANSFER_H