#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

void ChildProcess ( int num ){
		printf("Child %d PID %d\n", num, getpid());
		printf("*** Child process is done ***\n");
}

int main ()
{
	pid_t pid;
	int i;

	printf("Parent ID: %d\n", getpid() );

	for ( i = 0; i < 3; i++){
		pid = fork();

		if ( pid < 0 )
			exit(0);
		else if ( pid == 0 )
			ChildProcess(i);
		else
			wait(NULL);
	}
}
