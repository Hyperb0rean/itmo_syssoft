#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

struct sockaddr_in local;

int main(int argc, char** argv) {
  int s = socket(AF_INET, SOCK_DGRAM, 0);

  inet_aton("127.0.0.1", &local.sin_addr);
  local.sin_port = htons(atoi(argv[1]));
  local.sin_family = AF_INET;

  int result = bind(s, (struct sockaddr*)&local, sizeof(local));

  char buff[BUFSIZ];
  for (;;) {
    size_t len = read(s, buff, BUFSIZ);
    buff[len] = '\0';
    if (strcmp(buff, "OFF\n") == 0) {
      break;
    }
    printf("%s\n", buff);
  }
  return 0;
}