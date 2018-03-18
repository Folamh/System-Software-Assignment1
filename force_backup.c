#include <string.h>
#include <sys/msg.h>

int main() {
    int msqid = 56565;
    struct message {
        long type;
        char text[120];
    } msg;

    msg.type = 1;
    strcpy(msg.text, "BACKUP");
    msgsnd(msqid, (void *) &msg, sizeof(msg.text), IPC_NOWAIT);
    return 0;
}