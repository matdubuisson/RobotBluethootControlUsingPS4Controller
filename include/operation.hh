#ifndef __OPERATION__HH__
#define __OPERATION__HH__

enum Operation {
  START = 0,
  BACK,
  LEFT_SHOULDER,
  RIGHT_SHOULDER,
  LEFT_STICK,
  RIGHT_STICK,
  NORTH,
  SOUTH,
  WEST,
  EAST,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  TOUCHPAD,
  TAKE_ARGUMENT = 0x80, // Simple mask to distinguish operations faster
  LEFTX,
  LEFTY,
  RIGHTX,
  RIGHTY,
  LEFT_TRIGGER,
  RIGHT_TRIGGER
};

#endif