#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

//My best effort until now because of the time
//but you just does not work with more than 
//one parameter if you do not give them
//when you run the code
//With argv[] works fine


int main( int argc, char *argv[] )  {
int t = 1;
while(t==1){
	pid_t pid;
	pid = fork();
	if (pid < 0) {
		printf("entre");
		fprintf(stderr, "Error, fork failed: %d\n",errno);
		exit (-1) ;
	}
	else if (pid == 0) {
		if(argc<2){
			char *cmds[20];
			char str[40];
			char *ptrToken;
			printf("carlota> ");
			scanf("%s",str);
			//fgets(str, strlen(str), stdin);
			ptrToken = strtok(str, " ");
			int i=0;
			while ( ptrToken != NULL) {
				cmds[i]=ptrToken;
				ptrToken = strtok( NULL, " " );
				i++;
	  		}
			cmds[i]=NULL;

			int ex = execvp(cmds[0], cmds);
			if(ex<0){
				fprintf(stderr, "Execution error: %d\n",errno);
				return -ex;

}
		}
		else{
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
	}
	else {
		wait(NULL);
	}
}
}


