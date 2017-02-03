#include <unistd.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <errno.h>
#include <fcntl.h> 
#include <string.h>

//May be passed two strings, one with the name of the file to edit and
//the other with the string you want to write on it, or just pass the 
//first one and then pass the string to insert in through fgets()

int main( int argc, char *argv[] )  {
	if(argc<2){
		printf("At least file path argument expected.\n");
		return(-1);
	}
	if(argc>3){
		printf("Too many arguments supplied.\n");
		return(-1);
	}
	int file = open(argv[1],O_WRONLY | O_APPEND |  O_CREAT, 0666);
	if (file!=-1){
		int sys=0;
		if(argc==2){
			char str[256];
			printf("Insert the string you want to write:\n"); 
			fgets(str, 256, stdin);
			sys=syscall(SYS_write, file, str, strlen(str));
		}
		else{
			sys=syscall(SYS_write, file, argv[2], strlen(argv[2]));
		}
		close(file);
		if(sys<0){
			fprintf(stderr, "Failure writing in the \"%s\" file, errno = %d\n",argv[1], errno);
		}
		return 0;
	}
	else{
        	fprintf(stderr, "Failure opening the file \"%s\", errno = %d\n",argv[1], errno);
	}
	
}

