#include "wifitransmitter.hh"

#include <cstring>

#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

bool WifiTransmitter::doOpen() {
  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    fprintf(stderr, "Error: unable to initialize a new socket\n");
    return false;
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(ip.c_str());
  addr.sin_port = htons(port);

  if (connect(sock, (const struct sockaddr*)&addr, sizeof(addr)) < 0) {
    fprintf(stderr, "Error: cannot connect to server %s:%u\n", ip.c_str(), port);
    return false;
  }

  return true;
}

bool WifiTransmitter::doClose() {
  if (::close(sock) < 0) { // Resolve conflict between close (unistd.h) and WifiTransmitter::close
    fprintf(stderr, "Error: cannot close connection with server\n");
    return false;
  }
  return true;
}

bool WifiTransmitter::sendBytes(const uint8_t *bytes, uint32_t size) {
  int32_t code = send(sock, bytes, size, 0);
  
  if (code < 0) {
    fprintf(stderr, "Error: connection with server interrupted");
    return false;
  } else if (code == 0) {
    fprintf(stderr, "Error: cannot send any bytes to server\n");
    return false;
  } else if (code < size) {
    fprintf(stderr, "Error: could not send all %u bytes to server\n", size);
    return false;
  }

  return true;
}

bool WifiTransmitter::recvBytes(uint8_t *bytes, uint32_t size, uint32_t& recvSize) {
  ssize_t code = recv(sock, bytes, size, 0);
  
  if (code < 0) {
    fprintf(stderr, "Error: connection with server interrupted\n");
    recvSize = 0;
    return false;
  } else if (code == 0) {
    fprintf(stderr, "Error: cannot recv any bytes from server\n");
    recvSize = 0;
    return false;
  }

  recvSize = (uint32_t) code;
  return true;
}
