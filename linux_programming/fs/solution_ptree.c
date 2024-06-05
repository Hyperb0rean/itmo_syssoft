#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "stdlib.h"

int get_ppid(int pid) {
  char path[1024];
  snprintf(path, sizeof(path), "/proc/%d/stat", pid);
  int fd = open(path, O_RDONLY);
  if (fd != -1) {
    int ppid;
    FILE* stat_file = fdopen(fd, "r");
    fscanf(stat_file, "%*d %*s %*c %d", &ppid);
    fclose(stat_file);
    close(fd);
    return ppid;
  }
  close(fd);
  exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
  int pid;
  for (pid = atoi(argv[1]); pid != 0; pid = get_ppid(pid)) {
    printf("%d\n", pid);
  }
  return 0;
}