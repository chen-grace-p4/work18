#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/shm.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>

#include <unistd.h>
#include <fcntl.h>

#define READ 0
#define WRITE 1

int main() {
	//sending input to child
  int fds[2];
  pipe(fds);
  printf("pipe created. fds[0]: %d fds[1]: %d\n", fds[0], fds[1]);
  //recieving response from child
  int fdstwo[2];
  pipe(fdstwo);
  printf("pipe created. fdstwo[0]: %d fdstwo[1]: %d\n", fdstwo[0], fdstwo[1]);

  int f;
  f = fork();

  if (f) {
    //parent
    close(fds[READ]);
    //while (1) {
    	printf("enter an input: ");
   	char input[100];
   	fgets(input, 100, stdin);
    	write(fds[WRITE], input, strlen(input));
    //}
  
    close(fdstwo[WRITE]);
    char line[100];
    while (read(fdstwo[READ], line, sizeof(line)))
      printf("response from child: [%s]\n", line);
  }
  else {
    //child
    close(fds[WRITE]);
    char parentInput[100];
    read(fds[READ], parentInput, sizeof(parentInput));
    strcpy(parentInput, "manipulated");
    
    close(fdstwo[READ]);
    //sleep(2);
    write(fdstwo[WRITE], parentInput, sizeof(parentInput));
  }
  
  return 0;
}
