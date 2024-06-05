#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int dfs(int pid) {
  char path[256];
  sprintf(path, "/proc/%d/task/%d/children", pid, pid);
  FILE* f = fopen(path, "rb");
  int id;
  int res = 1;
  while (fscanf(f, "%d", &id) >= 0) {
    res += dfs(id);
  }
  fclose(f);
  return res;
}

int main(int argc, char** argv) {
  int pid = atoi(argv[1]);
  printf("%d\n", dfs(pid));
  return 0;
}