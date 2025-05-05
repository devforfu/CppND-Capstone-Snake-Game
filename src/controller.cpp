#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::HandleInput(bool &running, Snake::Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      if (auto key = static_cast<KeyBindings::key_type>(e.key.keysym.sym); bindings.find(key) != bindings.end()) {
        Snake::Action &action = bindings.at(key);
        action.Act(snake);
      }
    }
  }
}