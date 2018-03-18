all: System-Software-Assignment1 Force-Backup

System-Software-Assignment1: main.c
	gcc -o System-Software-Assignment1 main.c auditd.h backup_and_transfer.h daemonize.h is_time.h

Force-Backup: force_backup.c
	gcc -o Force-Backup force_backup.c
