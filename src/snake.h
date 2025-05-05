#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

namespace Snake {

enum class Direction {
    kUp, kDown, kLeft, kRight
};

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
    bool IsAlive() const { return alive; }
    bool IsDead() const { return !IsAlive(); }
    int GetSize() const { return size; }

    float head_x;
    float head_y;
    std::vector<SDL_Point> body;
    Direction direction = Direction::kUp;

private:
    void UpdateHead();
    void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

    bool growing{false};
    int grid_width;
    int grid_height;

    float speed{0.1f};
    int size{1};
    bool alive{true};
};

}
#endif