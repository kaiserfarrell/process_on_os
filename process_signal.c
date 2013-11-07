/***********************************************************************
* Coder Name: Kaiser Farrell
* Copyright (C) 2013                       *
***********************************************************************/

#include <stdlib.h>	/* akan digunakan utk exit() */
#include <unistd.h>	/* akan digunakan utk fork() and getpid() */
#include <signal.h>	/* akan digunakan utk signal */
#include <stdio.h>	/* akan digunakan utk printf() */

#define NUMPROCS 5	/* wakil kepada jumlah process untuk di "fork" */
int nprocs;		/* wakil kepada jumlah child processes */

/* Congfigurasi untuk warna */

#define RED  "\x1B[31m" //merah
#define GRN  "\x1B[32m" //hijau
#define YEL  "\x1B[33m" //kuning
#define BLU  "\x1B[34m" //biru
#define MAG  "\x1B[35m" //magenta
#define CYN  "\x1B[36m" //cyan
#define RESETCOLOR "\033[0m"  //reset color 

int
main(int argc, char **argv) {
	void catch(int);	/* signal handler */
	void child(int n);	/* child calls*/
	void parent(int pid);	/* parent calls */
	int pid;	/* process ID */
	int i;

	printf("\n%s#########################################################", GRN);
	printf("\n%s#               Kaiser Farrell                          #", GRN);
	printf("\n%s#########################################################", GRN);
	signal(SIGCHLD, catch);	/* detect child termination */
	printf("%s\n", RESETCOLOR);

	for (i=0; i < NUMPROCS; i++) {
		switch (pid = fork()) {
		case 0:		/* fork returns 0 to the child */
			child(i);	/* kalau function ada child() never returns;  */
			break;
		case -1:	/* kalo x betul baru jalankan*/
			perror("fork");
			exit(1);
		default:	/* parent start looping utk beranak lagi.. :D */
			nprocs++;	/* count # looping utk process yang telah di fork */
			break;
		}
	}
	
	printf("\n%sReader/Writer: start to sleep\n", RED);
	printf("%s\n", RESETCOLOR);

	/* tiada apa-apa action; signal wakes us out of sleeep */
	while (nprocs != 0) {
		printf("\nReader/Writer:parent going is sleeping\n");
		sleep(60);	/* do nothing for a minute */
	}
	printf("\nReader/Writer:parent goto exiting\n");
	exit(0);
}

void
child(int n) {
	printf("\t%sReader/Writer:child[%d]: child pid=%d, sleeping for %d seconds\n", CYN, n, getpid(), n);
	printf("%s\n", RESETCOLOR);
	sleep(n);	/* sleep for n seconds */
	printf("\t%sReader/Writer:child[%d]: start to quit\n", YEL, n);
	exit(100+n);	/* exit with a return code of 100+n */
	printf("%s\n", RESETCOLOR);
}

void
catch(int snum) {
	int pid;
	int status;

	pid = wait(&status);
	printf("\nReader/Writer: child process pid=%d exited with value %d\n",
		pid, WEXITSTATUS(status));
	printf("%s\n", RESETCOLOR);
	nprocs--;
	signal(SIGCHLD, catch);	/* reset signal*/
}
