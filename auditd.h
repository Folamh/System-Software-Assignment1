#ifndef AUDITD_H
#define AUDITD_H

void setup_auditd(char *folder, char *key) {
    syslog(LOG_INFO, "Watching for write changes: %s", folder);
    char command[300];
    snprintf(command, sizeof(command), "auditctl -w %s -p w -k %s", folder, key);
    syslog(LOG_DEBUG, "Audit command: %s", command);
    system(command);
}

void file_report(char *folder, char *key) {
    syslog(LOG_INFO, "Creating audit file report.");
    char filename[40];
    struct tm *timenow;
    time_t now = time(NULL);
    timenow = gmtime(&now);
    strftime(filename, sizeof(filename), "report_%Y-%m-%d.txt", timenow);

    char command[300];
    snprintf(command, sizeof(command), "ausearch -ts today -k %s | aureport -f -i >> %s/%s", key, folder, filename);
    syslog(LOG_DEBUG, "Report creation command: %s", command);
    system(command);

    send_msg("SUCCESS: Report successfully created.");
    exit(EXIT_SUCCESS);
}

#endif //AUDITD_H