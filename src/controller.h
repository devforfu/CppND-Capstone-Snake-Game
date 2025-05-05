#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake::Snake &snake) const;

 private:
  void ChangeDirection(Snake::Snake &snake, Snake::Direction input, Snake::Direction opposite) const;
};

#endif