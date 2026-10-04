#include <csignal>
#include <iostream>

#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "operation.hh"

#define IP "127.0.0.1"
#define PORT 33333
#define LISTEN 1
#define BUFFER_SIZE 1000

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

  struct sockaddr_in clientAddress;
  socklen_t length;
  uint8_t operation;

  while (1) {
    length = sizeof(clientAddress);
    int32_t recvSize = recvfrom(sock, &operation, 1, 0,
      (struct sockaddr*)&clientAddress, &length);
    if (recvSize < 0) {
      fprintf(stderr, "Error: could not recv bytes connection interrupted\n");
      return EXIT_FAILURE;
    }

    switch ((Operation) operation) {
      case START:
        std::cout << "START" << std::endl;
        break;
      case BACK:
        std::cout << "BACK" << std::endl;
        break;
      
      case LEFT_SHOULDER:
        std::cout << "LEFT SHOULDER" << std::endl;
        break;
      case RIGHT_SHOULDER:
        std::cout << "RIGHT SHOULDER" << std::endl;
        break;
      
      case LEFT_STICK:
        std::cout << "LEFT STICK" << std::endl;
        break;
      case RIGHT_STICK:
        std::cout << "RIGHT STICK" << std::endl;
        break;
      
      case NORTH:
        std::cout << "NORTH" << std::endl;
        break;
      case SOUTH:
        std::cout << "SOUTH" << std::endl;
        break;
      case WEST:
        std::cout << "WEST" << std::endl;
        break;
      case EAST:
        std::cout << "EAST" << std::endl;
        break;

      case UP:
        std::cout << "UP" << std::endl;
        break;
      case DOWN:
        std::cout << "DOWN" << std::endl;
        break;
      case LEFT:
        std::cout << "LEFT" << std::endl;
        break;
      case RIGHT:
        std::cout << "RIGHT" << std::endl;
        break;

      case TOUCHPAD:
        std::cout << "TOUCHPAD" << std::endl;
        break;

      case LEFTX:
        std::cout << "LEFTX" << std::endl;
        break;
      case LEFTY:
        std::cout << "LEFTY" << std::endl;
        break;

      case RIGHTX:
        std::cout << "RIGHTX" << std::endl;
        break;
      case RIGHTY:
        std::cout << "RIGHTY" << std::endl;
        break;

      case LEFT_TRIGGER:
        std::cout << "LEFT_TRIGGER" << std::endl;
        break;
      case RIGHT_TRIGGER:
        std::cout << "RIGHT_TRIGGER" << std::endl;
        break;

      default:
        std::printf("Unknown operation: %d\n", (int) operation);
        break;
    }

    if (operation & Operation::TAKE_ARGUMENT) {
      int32_t value;
      recvSize = recvfrom(sock, &value, 4, 0,
        (struct sockaddr*)&clientAddress, &length);
      if (recvSize < 0) {
        fprintf(stderr, "Error: could not recv bytes connection interrupted\n");
        return EXIT_FAILURE;
      }
      std::printf("\t=> %d\n", value);
    }

    // if (sendto(sock, buffer, BUFFER_SIZE, 0,
    //   (const struct sockaddr*)&clientAddress, length) < 0) {
    //   fprintf(stderr, "Error: could not send bytes connection interrupted\n");
    //   return EXIT_FAILURE;
    // }
  }

  return EXIT_SUCCESS;
}