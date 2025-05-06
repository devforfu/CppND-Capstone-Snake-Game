#include "snake.h"
#include <cmath>
#include <iostream>

namespace Snake {
void Snake::Update() {
  SDL_Point prevCell{GetHeadX(), GetHeadY()};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point currCell{GetHeadX(), GetHeadY()};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new cell.
  if (currCell.x != prevCell.x || currCell.y != prevCell.y) {
    UpdateBody(currCell, prevCell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
    break;

    case Direction::kDown:
      head_y += speed;
    break;

    case Direction::kLeft:
      head_x -= speed;
    break;

    case Direction::kRight:
      head_x += speed;
    break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == GetHeadX() && y == GetHeadY()) return true;
  return std::any_of(body.begin(), body.end(), [x, y](auto const &item) {
    return x == item.x && y == item.y;
  });
}

}