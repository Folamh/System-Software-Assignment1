all: System-Software-Assignment1 Force-Backup

System_Software_Assignment1: main.c
	gcc -o System_Software_Assignment1 main.c auditd.h backup_and_transfer.h daemonize.h is_time.h

Force_Backup: force_backup.c
	gcc -o Force_Backup force_backup.c
