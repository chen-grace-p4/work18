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

  //recieving response from child
  int fdstwo[2];
  pipe(fdstwo);

  int f;
  f = fork();

  //parent
  if (f) {
    close(fds[READ]);
    close(fdstwo[WRITE]);

    while (1) {
      printf("enter an input: ");
      char input[100];
      fgets(input, 100, stdin);
      //writes input
    	write(fds[WRITE], input, sizeof(input));

      //reads response from child
      char line[100];
      read(fdstwo[READ], line, sizeof(line));
      printf("response from child: %s\n", line);
   }
  }
  else {
    //child
    close(fds[WRITE]);
    close(fdstwo[READ]);

    while (1) {
      char parentInput[100];
      //reads input and modifies
      read(fds[READ], parentInput, sizeof(parentInput));
      //closes off
      parentInput[strlen(parentInput)-1] = '\0';
      //modifies
      strcat(parentInput, "manipulated");
      //closes off
      parentInput[strlen(parentInput)] = '\0';

      //writes input and sends back to parent
      write(fdstwo[WRITE], parentInput, strlen(parentInput)+1);
   }

  }

  return 0;
}
