#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "stdlib.h"

const char* get_proc_filename() {
  int pid = getpid();
  int length = snprintf(NULL, 0, "%d", pid);
  char* buf = malloc(length + 1);
  char* str = malloc(length + 12);
  snprintf(buf, length + 1, "%d", pid);
  strcpy(str, "/proc/");
  strcat(str, buf);
  strcat(str, "/stat");
  free(buf);
  return str;
}

int main() {
  const char* filename = get_proc_filename();
  int fd = open(filename, O_RDONLY);
  if (fd != -1) {
    int ppid;
    FILE* stat_file = fdopen(fd, "r");
    fscanf(stat_file, "%*d %*s %*c %d", &ppid);
    printf("%d\n", ppid);
  }
  free((void*)filename);
  return 0;
}