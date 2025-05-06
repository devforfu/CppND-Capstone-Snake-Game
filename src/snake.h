#ifndef SNAKE_H
#define SNAKE_H

#include <snake.h>
#include <vector>
#include "SDL.h"

namespace Snake {

enum class Direction {
    kUp, kDown, kLeft, kRight
};

inline Direction GetOppositeDirection(const Direction dir) {
    switch (dir) {
        case Direction::kUp: return Direction::kDown;
        case Direction::kDown: return Direction::kUp;
        case Direction::kLeft: return Direction::kRight;
        case Direction::kRight: return Direction::kLeft;
        default: throw std::runtime_error{"invalid enum value"};
    }
}

class Snake {
public:

    Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

    void Update();
    void GrowBody();
    bool SnakeCell(int x, int y);

    void SpeedUp() { speed += 0.02; }
    void SpeedUp(const float value) { speed += value; }

    [[nodiscard]] bool IsAlive() const { return alive; }
    [[nodiscard]] bool IsDead() const { return !IsAlive(); }
    [[nodiscard]] int GetSize() const { return size; }
    [[nodiscard]] int GetHeadX() const { return static_cast<int>(head_x); }
    [[nodiscard]] int GetHeadY() const { return static_cast<int>(head_y); }

    bool ChangeDirection(const Direction newDir) {
        if (size == 1) {
            // can change to any direction if there is nothing but head
            direction = newDir;
            return true;
        }
        // otherwise, can only change direction if the snake does not collide with itself
        if (direction == GetOppositeDirection(newDir)) {
            return false;
        }
        direction = newDir;
        return true;
    }

    std::vector<SDL_Point> body;

private:
    void UpdateHead();
    void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

    int grid_width;
    int grid_height;

    float head_x{};
    float head_y{};
    float speed{0.1f};
    int size{1};
    bool alive{true};
    bool growing{false};

    Direction direction = Direction::kUp;
};

struct Action {
    Action() = default;
    virtual ~Action() = default;
    virtual void Act(Snake &snake) = 0;
};

struct ChangeDir final : Action {
    explicit ChangeDir(const Direction newDir): dir{newDir} {}
    void Act(Snake &snake) override { snake.ChangeDirection(dir); }
private:
    Direction dir;
};

struct SpeedUp final : Action {
    explicit SpeedUp(const float speedUpValue): speedUp{speedUpValue} {}
    void Act(Snake &snake) override { snake.SpeedUp(speedUp); }
private:
    float speedUp;
};

}
#endif