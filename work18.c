
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

#define READ 0
#define WRITE 1

int main() {

  int fds[2];
  pipe(fds);
  printf("pipe created. fds[0]: %d fds[1]: %d\n", fds[0], fds[1]);

  int f;
  f = fork();

  if (f) {
    //parent
    close(fds[WRITE]);
    char line[10];
    while (read(fds[READ], line, sizeof(line)))
      printf("parent got: [%s]\n", line);
  }
  else {
    //child
    close(fds[READ]);
    sleep(5);
    write(fds[WRITE], "hello!", 7);
    sleep(5);
    write(fds[WRITE], "goodbye", 8);
  }
  return 0;
}
