#include "controller.h"
#include "game/game.h"
#include "snake.h"

#include "SDL.h"

void UserInput::HandleInput(bool &running, Snake::Snake &snake, const Game &game) {
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

void LizardBrain::HandleInput(bool &running, Snake::Snake &snake, const Game &game) {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) running = false;
    }

    const auto xFood = game.GetFoodX();
    const auto yFood = game.GetFoodY();
    const auto xHead = snake.GetHeadX();
    const auto yHead = snake.GetHeadY();

    Snake::Direction new_direction = snake.GetDirection();

    if (xHead < xFood) {          // Try to move horizontally toward food first
        new_direction = Snake::Direction::kRight;
    } else if (xHead > xFood) {
        new_direction = Snake::Direction::kLeft;
    } else if (yHead < yFood) {   // If horizontal is aligned, try vertical
        new_direction = Snake::Direction::kDown;
    } else if (yHead > yFood) {
        new_direction = Snake::Direction::kUp;
    }

    snake.ChangeDirection(new_direction);
}
