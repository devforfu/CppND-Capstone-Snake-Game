#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <map>

// #define INTERFACE(CLASS_NAME) ({ \
//     CLASS_NAME() = delete; \
//     CLASS_NAME(CLASS_NAME &copy) = delete; \
//     CLASS_NAME(CLASS_NAME &&moved) = delete; \
//     CLASS_NAME &operator=(CLASS_NAME &other) = delete; \
//     CLASS_NAME &operator=(CLASS_NAME &&moved) = delete; \
// })

class Game;

using KeyBindings = std::map<SDL_KeyCode, Snake::Action&>;

class ControllerInterface {
public:
    ControllerInterface() = default;
    virtual ~ControllerInterface() = default;
    virtual void HandleInput(bool &running, Snake::Snake &snake, const Game &game) = 0;
};

class UserInput final : public ControllerInterface {

public:
    UserInput(): ControllerInterface() {
        bindings.insert({SDLK_UP, up});
        bindings.insert({SDLK_DOWN, down});
        bindings.insert({SDLK_LEFT, left});
        bindings.insert({SDLK_RIGHT, right});
        bindings.insert({SDLK_SPACE, speedUp});
    }

    void HandleInput(bool &running, Snake::Snake &snake, const Game &game) override;

private:
    KeyBindings bindings{};

    Snake::ChangeDir up{Snake::Direction::kUp};
    Snake::ChangeDir down{Snake::Direction::kDown};
    Snake::ChangeDir left{Snake::Direction::kLeft};
    Snake::ChangeDir right{Snake::Direction::kRight};
    Snake::SpeedUp speedUp{0.01};

};

class LizardBrain final : public ControllerInterface {
public:
    LizardBrain(): ControllerInterface() {}
    void HandleInput(bool &running, Snake::Snake &snake, const Game &game) override;
};

#endif