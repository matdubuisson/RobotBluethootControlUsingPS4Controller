// transmitter.cc  Copyright (C) 2026 Dubuisson Mattéo

#include <cstdint>

#ifndef __TRANSMITTER__HH__
#define __TRANSMITTER__HH__

class Transmitter {
public:
  inline
  Transmitter(): active(false) {}

  inline
  Transmitter(bool active): active(active) {
    if (active)
      open();
  }

public:
  inline
  bool open() {
    active = true;
    return doOpen();
  }

  inline
  bool close() {
    active = false;
    return doClose();
  }

  inline
  bool isActive() {
    return active;
  }

protected:
  virtual
  bool doOpen() = 0;

  virtual
  bool doClose() = 0;

public:
  virtual
  bool sendBytes(const uint8_t *bytes, uint32_t size) = 0;

  inline
  bool sendByte(const uint8_t byte) {
    return sendBytes(&byte, 1);
  }

  inline
  bool recvByte(uint8_t& byte) {
    uint32_t recvSize;
    return recvBytes(&byte, 1, recvSize) && recvSize == 1;
  }

  virtual
  bool recvBytes(uint8_t *bytes, uint32_t size, uint32_t& recvSize) = 0;

private:
  bool active;
};

#endif