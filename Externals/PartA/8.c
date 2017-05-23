#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void ChildProcess ( )
{
	printf("Child ID: %d Parent ID: %d\n", getpid(), getppid());
	printf("Child Process Completed------------\n");
}

void ParentProcess()
{
	printf("Parent ID: %d\n", getpid());
	printf("Parent Process Completed------------\n");
}

int main ()
{
	pid_t pid;
	printf("Parent Process ID: %d\n", getpid());

	pid = fork();
	if ( pid < 0 ){
		printf("Error ! Couldnt Fork ");
		exit(0);
	}
	else if ( pid == 0 ){
		ChildProcess();
	}
	else {
		pid = wait(NULL);
		printf("From Parent : Child Process ID: %d\n" , pid );
		ParentProcess();
	}
}
