#include <cstdint>
#include <cstring>
#include <iostream>

using namespace std;

#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#define SDL_HINT_MAIN_CALLBACK_RATE 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "operation.hh"
#include "wifitransmitter.hh"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

static uint64_t lastTicks;

static SDL_Gamepad* gamepad = nullptr;
static WifiTransmitter* transmitter = nullptr;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  // std::cout << "App started" << std::endl;

  lastTicks = SDL_GetTicks();

  SDL_SetAppMetadata("PS4CONTROLLER", "0.0", "com.ps4controller");

  if (!SDL_Init(SDL_INIT_GAMEPAD)) {
    SDL_Log("Error: cannot initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_HasGamepad()) {
    SDL_Log("Error: no gamepad found");
    return SDL_APP_FAILURE;
  }

  int32_t count = 0;
  SDL_JoystickID* ids = SDL_GetGamepads(&count);

  for (uint32_t i = 0; i < count; i++) {
    SDL_Gamepad* gamepadi = SDL_OpenGamepad(ids[i]);
    SDL_Log("Gamepad connected: %s", SDL_GetGamepadName(gamepadi));
    gamepad = gamepadi;
    break;
  }

  transmitter = new WifiTransmitter("127.0.0.1", 33333);
  transmitter->open();

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  #define BUFFER_SIZE 1000
  static uint8_t buffer[BUFFER_SIZE];

  switch (event->type) {
    case SDL_EVENT_QUIT:
      return SDL_APP_SUCCESS;
    case SDL_EVENT_GAMEPAD_BUTTON_DOWN: {
      // std::cout << "Press: ";

      switch (event->gbutton.button) {
        case SDL_GAMEPAD_BUTTON_START:
          // std::cout << "START" << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::START));
          break;
        case SDL_GAMEPAD_BUTTON_BACK:
          // std::cout << "BACK" << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::BACK));
          break;
        
        case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER:
          // std::cout << "LEFT SHOULDER" << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::LEFT_SHOULDER));
          break;
        case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER:
          // std::cout << "RIGHT SHOULDER" << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::RIGHT_SHOULDER));
          break;
        
        case SDL_GAMEPAD_BUTTON_LEFT_STICK:
          // std::cout << "LEFT STICK" << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::LEFT_STICK));
          break;
        case SDL_GAMEPAD_BUTTON_RIGHT_STICK:
          // std::cout << "RIGHT STICK" << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::RIGHT_STICK));
          break;
        
        case SDL_GAMEPAD_BUTTON_NORTH:
          // std::cout << "NORTH" << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::NORTH));
          break;
        case SDL_GAMEPAD_BUTTON_SOUTH:
          // std::cout << "SOUTH" << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::SOUTH));
          break;
        case SDL_GAMEPAD_BUTTON_WEST:
          // std::cout << "WEST" << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::WEST));
          break;
        case SDL_GAMEPAD_BUTTON_EAST:
          // std::cout << "EAST" << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::EAST));
          break;

        case SDL_GAMEPAD_BUTTON_DPAD_UP:
          // std::cout << "UP" << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::UP));
          break;
        case SDL_GAMEPAD_BUTTON_DPAD_DOWN:
          // std::cout << "DOWN" << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::DOWN));
          break;
        case SDL_GAMEPAD_BUTTON_DPAD_LEFT:
          // std::cout << "LEFT" << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::LEFT));
          break;
        case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:
          // std::cout << "RIGHT" << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::RIGHT));
          break;

        case SDL_GAMEPAD_BUTTON_TOUCHPAD:
          // std::cout << "TOUCHPAD" << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::TOUCHPAD));
          return SDL_APP_SUCCESS;
      }
      
      break;
    } case SDL_EVENT_GAMEPAD_BUTTON_UP: {
      // std::cout << "Release: ";
      
      switch (event->gbutton.button) {
        case SDL_GAMEPAD_BUTTON_START:
          // std::cout << "START" << std::endl;
          break;
        case SDL_GAMEPAD_BUTTON_BACK:
          // std::cout << "BACK" << std::endl;
          break;
        
        case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER:
          // std::cout << "LEFT SHOULDER" << std::endl;
          break;
        case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER:
          // std::cout << "RIGHT SHOULDER" << std::endl;
          break;
        
        case SDL_GAMEPAD_BUTTON_LEFT_STICK:
          // std::cout << "LEFT STICK" << std::endl;
          break;
        case SDL_GAMEPAD_BUTTON_RIGHT_STICK:
          // std::cout << "RIGHT STICK" << std::endl;
          break;
        
        case SDL_GAMEPAD_BUTTON_NORTH:
          // std::cout << "NORTH" << std::endl;
          break;
        case SDL_GAMEPAD_BUTTON_SOUTH:
          // std::cout << "SOUTH" << std::endl;
          break;
        case SDL_GAMEPAD_BUTTON_WEST:
          // std::cout << "WEST" << std::endl;
          break;
        case SDL_GAMEPAD_BUTTON_EAST:
          // std::cout << "EAST" << std::endl;
          break;

        case SDL_GAMEPAD_BUTTON_DPAD_UP:
          // std::cout << "UP" << std::endl;
          break;
        case SDL_GAMEPAD_BUTTON_DPAD_DOWN:
          // std::cout << "DOWN" << std::endl;
          break;
        case SDL_GAMEPAD_BUTTON_DPAD_LEFT:
          // std::cout << "LEFT" << std::endl;
          break;
        case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:
          // std::cout << "RIGHT" << std::endl;
          break;

        case SDL_GAMEPAD_BUTTON_TOUCHPAD:
          // std::cout << "TOUCHPAD" << std::endl;
          return SDL_APP_SUCCESS;
      }

      break;
    } case SDL_EVENT_GAMEPAD_AXIS_MOTION: {
      int32_t value = event->gaxis.value;

      switch (event->gaxis.axis) {
        case SDL_GAMEPAD_AXIS_LEFTX:
          // std::cout << "LEFT JOYSTICK X: " << value << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::LEFTX));
          break;
        case SDL_GAMEPAD_AXIS_LEFTY:
          // std::cout << "LEFT JOYSTICK Y: " << value << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::LEFTY));
          break;

        case SDL_GAMEPAD_AXIS_RIGHTX:
          // std::cout << "RIGHT JOYSTICK X: " << value << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::RIGHTX));
          break;
        case SDL_GAMEPAD_AXIS_RIGHTY:
          // std::cout << "RIGHT JOYSTICK Y: " << value << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::RIGHTY));
          break;

        case SDL_GAMEPAD_AXIS_LEFT_TRIGGER:
          // std::cout << "LEFT TRIGGER: " << value << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::LEFT_TRIGGER));
          break;
        case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER:
          // std::cout << "RIGHT TRIGGER: " << value << std::endl;
          transmitter->sendByte(static_cast<const uint8_t>(Operation::RIGHT_TRIGGER));
          break;
      }

      transmitter->sendBytes((const uint8_t*) &value, 4);

      break;
    }
  }
  
  return SDL_APP_CONTINUE;
  #undef BUFFER_SIZE
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  uint64_t currentTicks = SDL_GetTicks();
  if (currentTicks - lastTicks < 1000)
    return SDL_APP_CONTINUE;
  lastTicks = currentTicks;

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  if (gamepad != nullptr) SDL_CloseGamepad(gamepad);
  if (transmitter != nullptr) {
    transmitter->close();
    delete transmitter;
    transmitter = nullptr;
  }
}