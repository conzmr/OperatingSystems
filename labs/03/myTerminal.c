#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


int main( int argc, char *argv[] )  {
	if(argc<2){
		printf("At least one argument expected.\n");
		return(-1);
	}
	pid_t pid;
	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Error, fork failed: %d\n",errno);
		exit (-1) ;
	}
	else if (pid == 0) {
		int child_pid = getpid();
		char *cmds[argc];
		for(int i=0; i<argc; i++){
			cmds[i]=argv[i+1];
		}
		cmds[argc] = NULL;
		int ex = execvp(cmds[0], cmds);
		if(ex<0){
			fprintf(stderr, "Execution error: %d\n",errno);
			return -ex;
		}
	}
	return 0;
}


