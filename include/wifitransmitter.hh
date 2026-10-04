// transmitter.cc  Copyright (C) 2026 Dubuisson Mattéo

#ifndef __WIFI_TRANSMITTER__HH__
#define __WIFI_TRANSMITTER__HH__

#include <string>

#include "transmitter.hh"

namespace std {

class WifiTransmitter: public Transmitter {
public:
  inline
  WifiTransmitter(string ip, uint16_t port): Transmitter() {}
  
  inline
  WifiTransmitter(string ip, uint16_t port, bool active):
    // Parent construction intentionally put at the end of the initialization
    ip(ip), port(port), Transmitter(active) {}

protected:
  bool doOpen() override;

  bool doClose() override;

public:
  bool sendBytes(const uint8_t *bytes, uint32_t size) override;

  bool recvBytes(uint8_t *bytes, uint32_t size, uint32_t& recvSize) override;

private:
  string ip;
  uint16_t port;
  int32_t sock;
};

}

#endif