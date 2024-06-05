#include <fcntl.h>
#include <linux/fs.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  pid_t pid = fork();

  if (pid == -1) {
    return -1;
  }

  if (pid != 0) {
    exit(EXIT_SUCCESS);
  }

  if (setsid() == -1) {
    return -1;
  }

  if (chdir("/") == -1) {
    return -1;
  }

  printf("%d\n", pid);

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  sleep(100);
  return 0;
}