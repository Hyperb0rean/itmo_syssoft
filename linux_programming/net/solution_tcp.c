#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

struct sockaddr_in local;

int comp(const void* elem1, const void* elem2) {
  char lhs = *((char*)elem1);
  char rhs = *((char*)elem2);
  if (lhs < rhs)
    return 1;
  if (rhs > lhs)
    return -1;
  return 0;
}

int main(int argc, char* argv[]) {
  int ss = socket(AF_INET, SOCK_STREAM, 0);
  int cs;

  inet_aton("127.0.0.1", &local.sin_addr);
  local.sin_port = htons(atoi(argv[1]));
  local.sin_family = AF_INET;

  (void)bind(ss, (struct sockaddr*)&local, sizeof(local));
  listen(ss, 5);

  cs = accept(ss, NULL, NULL);

  char buff[BUFSIZ];
  while (1) {
    size_t len = read(cs, buff, BUFSIZ);
    if (strcmp(buff, "OFF") == 0) {
      break;
    }
    qsort(buff, strlen(buff), 1, comp);
    write(cs, buff, len);
  }
  return 0;
}