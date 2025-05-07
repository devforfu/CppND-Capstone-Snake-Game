#pragma once

#include "snake.h"

class Game;

namespace Actions {

enum class ActionTarget {
    Game, Snake
};

struct Action {
    Action() = default;
    virtual ~Action() = 0;
    virtual void Act(Snake::Snake &snake) {}
    virtual void Act(Game &game) {}
    virtual ActionTarget Target() = 0;
};

struct SnakeAction : Action {
    void Act(Game &game) override {}
    ActionTarget Target() override { return ActionTarget::Snake; }
};

struct ChangeDir final : SnakeAction {
    explicit ChangeDir(const Snake::Direction newDir): dir{newDir} {}
    void Act(Snake::Snake &snake) override;
private:
    Snake::Direction dir{};
};

struct SpeedUp final : SnakeAction {
    explicit SpeedUp(const float speedUpValue): speedUp{speedUpValue} {}
    void Act(Snake::Snake &snake) override;
private:
    float speedUp{};
};

struct GameAction : Action {
    void Act(Snake::Snake &snake) override {}
    ActionTarget Target() override { return ActionTarget::Game; }
};

struct QuitGame final : GameAction {
    void Act(Game &game) override;
};

}