#include "actions/action.h"
#include "game/game.h"

namespace Actions {

inline Action::~Action() = default;

void ChangeDir::Act(Snake::Snake &snake) {
    snake.ChangeDirection(dir);
}

void SpeedUp::Act(Snake::Snake &snake) {
    snake.SpeedUp(speedUp);
}

void QuitGame::Act(Game &game) {
    game.Stop();
}

}