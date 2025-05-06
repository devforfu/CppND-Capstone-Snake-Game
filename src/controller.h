#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <map>

using KeyBindings = std::map<SDL_KeyCode, Snake::Action&>;

class Controller {
public:
    Controller() {
        bindings.insert({SDLK_UP, up});
        bindings.insert({SDLK_DOWN, down});
        bindings.insert({SDLK_LEFT, left});
        bindings.insert({SDLK_RIGHT, right});
        bindings.insert({SDLK_SPACE, speedUp});
    }
    void HandleInput(bool &running, Snake::Snake &snake) const;

private:
    KeyBindings bindings{};

    Snake::ChangeDir up{Snake::Direction::kUp};
    Snake::ChangeDir down{Snake::Direction::kDown};
    Snake::ChangeDir left{Snake::Direction::kLeft};
    Snake::ChangeDir right{Snake::Direction::kRight};
    Snake::SpeedUp speedUp{0.01};
};

#endif