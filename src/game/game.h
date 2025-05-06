#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
public:
    Game(std::size_t gridWidth, std::size_t gridHeight);

    void Run(ControllerInterface &controller, const Renderer &renderer, std::size_t target_frame_duration);

    [[nodiscard]] int GetScore() const;
    [[nodiscard]] int GetSize() const;
    [[nodiscard]] int GetFoodX() const { return food.x; }
    [[nodiscard]] int GetFoodY() const { return food.y; }
    [[nodiscard]] int GetWorldLimitX() const { return width - 1; }
    [[nodiscard]] int GetWorldLimitY() const { return height - 1; }

private:
    int width{};
    int height{};
    int score{0};

    Snake::Snake snake;
    SDL_Point food{};

    void PlaceFood();
    void Update();

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<> random_w;
    std::uniform_int_distribution<> random_h;
};

#endif