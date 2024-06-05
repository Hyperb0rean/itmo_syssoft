#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_number(const char* str) {
  int i;
  for (i = 0; str[i] != 0; ++i) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

int main(void) {
  struct dirent** namelist;
  int n;
  n = scandir("/proc/", &namelist, NULL, alphasort);
  if (n == -1) {
    perror("scandir");
    exit(EXIT_FAILURE);
  }

  int counter = 0;
  while (n--) {
    if (is_number(namelist[n]->d_name)) {
      char path[256];
      snprintf(path, sizeof(path), "/proc/%s/status", namelist[n]->d_name);
      FILE* fp = fopen(path, "r");
      char buff[256];
      fscanf(fp, "Name: %s", buff);
      if (!strcmp("genenv", buff)) {
        ++counter;
      }
    }
    free(namelist[n]);
  }
  printf("%d\n", counter);
  free(namelist);
  exit(EXIT_SUCCESS);
}