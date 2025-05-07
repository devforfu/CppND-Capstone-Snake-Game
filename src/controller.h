#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "actions/action.h"
#include "snake.h"
#include <map>

class Game;

using KeyBindings = std::map<SDL_KeyCode, Actions::Action&>;

class ControllerInterface {
public:
    ControllerInterface() = default;
    virtual ~ControllerInterface() = 0;
    virtual void HandleInput(Snake::Snake &snake, Game &game) = 0;
};

class BaseInput : public ControllerInterface {
public:
    BaseInput(): ControllerInterface() {}

    virtual void AddBindings() {
        bindings.insert({SDLK_SPACE, speedUp});
        bindings.insert({SDLK_q, quitGame});
    }

    void HandleInput(Snake::Snake &snake, Game &game) override;

protected:
    KeyBindings bindings{};

    // Default actions
    Actions::SpeedUp speedUp{0.01};
    Actions::QuitGame quitGame;
};


class UserInput final : public BaseInput {

public:
    UserInput() {
        BaseInput::AddBindings();
        AddBindings();
    }

    void AddBindings() override {
        bindings.insert({SDLK_UP, up});
        bindings.insert({SDLK_DOWN, down});
        bindings.insert({SDLK_LEFT, left});
        bindings.insert({SDLK_RIGHT, right});
    }

private:
    Actions::ChangeDir up{Snake::Direction::kUp};
    Actions::ChangeDir down{Snake::Direction::kDown};
    Actions::ChangeDir left{Snake::Direction::kLeft};
    Actions::ChangeDir right{Snake::Direction::kRight};
};

class LizardBrain final : public BaseInput {
public:
    LizardBrain() {
        BaseInput::AddBindings();
    }

    void HandleInput(Snake::Snake &snake, Game &game) override;
};

class FoodAverse final : public BaseInput {
public:
    FoodAverse() {
        BaseInput::AddBindings();
    }

    void HandleInput(Snake::Snake &snake, Game &game) override;
};

#endif