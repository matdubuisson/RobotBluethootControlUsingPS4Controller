#include <csignal>
#include <iostream>

#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define IP "127.0.0.1"
#define PORT 33333
#define LISTEN 1

using namespace std;

static int32_t sock = -1;

static
void closeServer() {
  // if (sock > 0 && shutdown(sock, SHUT_RDWR) < 0) {
  //   fprintf(stderr, "Error: cannot shutdown connection\n");
  // }

  if (sock > 0 && close(sock) < 0) {
    fprintf(stderr, "Error: cannot close socket\n");
  }

  std::cout << "Server closed" << std::endl;
}

static
void handleExit() {
  closeServer();
}

static
void handleInterrupt(int sig) {
  exit(sig);
}

int main() {
  if (atexit(handleExit) < 0) {
    fprintf(stderr, "Error: cannot set exit handler\n");
    return EXIT_FAILURE;
  }

  if (signal(SIGINT, handleInterrupt) == SIG_ERR) {
    fprintf(stderr, "Error: cannot set interrupt handler\n");
    return EXIT_FAILURE;
  }

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    fprintf(stderr, "Error: cannot create socket\n");
    return EXIT_FAILURE;
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(IP);
  addr.sin_port = htons(PORT);

  if (bind(sock, (const struct sockaddr*)&addr, sizeof(addr)) < 0) {
    fprintf(stderr, "Error: cannot bind socket to address %s:%u\n", IP, PORT);
    return EXIT_FAILURE;
  }

  // if (listen(sock, LISTEN) < 0) {
  //   fprintf(stderr, "Error: cannot define max listening to %u clients\n", LISTEN);
  //   return EXIT_FAILURE;
  // }

  while (1) {}

  return EXIT_SUCCESS;
}