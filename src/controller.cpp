#include "controller.h"
#include "game/game.h"
#include "snake.h"

#include "SDL.h"

inline ControllerInterface::~ControllerInterface() = default;

void BaseInput::HandleInput(Snake::Snake &snake, Game &game) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            game.Stop();
        } else if (e.type == SDL_KEYDOWN) {
            if (auto key = static_cast<KeyBindings::key_type>(e.key.keysym.sym); bindings.find(key) != bindings.end()) {
                if (Actions::Action &action = bindings.at(key); action.Target() == Actions::ActionTarget::Game) {
                    action.Act(game);
                } else {
                    action.Act(snake);
                }
            }
        }
    }
}

void LizardBrain::HandleInput(Snake::Snake &snake, Game &game) {
    BaseInput::HandleInput(snake, game);

    if (game.IsRunning()) {
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
}

void FoodAverse::HandleInput(Snake::Snake &snake, Game &game) {
    BaseInput::HandleInput(snake, game);

    if (game.IsRunning()) {
        const auto xFood = game.GetFoodX();
        const auto yFood = game.GetFoodY();
        const auto xHead = snake.GetHeadX();
        const auto yHead = snake.GetHeadY();

        Snake::Direction dir = snake.GetDirection();

        switch (dir) {
            case Snake::Direction::kLeft: {
                if (xHead == xFood + 1) {
                    dir = Snake::Direction::kDown;
                }
            }
            break;
            case Snake::Direction::kRight: {
                if (xHead == xFood - 1) {
                    dir = Snake::Direction::kUp;
                }
            }
            break;
            case Snake::Direction::kUp: {
                if (yHead == yFood + 1) {
                    dir = Snake::Direction::kLeft;
                }
            }
            break;
            case Snake::Direction::kDown: {
                if (yHead == yFood - 1) {
                    dir = Snake::Direction::kRight;
                }
            }
            break;
        }

        snake.ChangeDirection(dir);
    }
}
