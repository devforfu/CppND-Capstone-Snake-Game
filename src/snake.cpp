#include "snake.h"
#include <cmath>
#include <iostream>

namespace Snake {

void Snake::Update() {
    SDL_Point prevCell{GetHeadX(), GetHeadY()};  // We first capture the head's cell before updating.
    UpdateHead();
    SDL_Point currCell{GetHeadX(), GetHeadY()};  // Capture the head's cell after updating.

    // Update all the body vector items if the snake head has moved to a new cell.
    if (currCell.x != prevCell.x || currCell.y != prevCell.y) {
        UpdateBody(currCell, prevCell);
    }
}

void Snake::UpdateHead() {
    switch (direction) {
        case Direction::kUp:    { head_y -= speed; } break;
        case Direction::kDown:  { head_y += speed; } break;
        case Direction::kLeft:  { head_x -= speed; } break;
        case Direction::kRight: { head_x += speed; } break;
    }

    // Wrap the Snake around to the beginning if going off of the screen.
    const auto gridWidth = static_cast<float>(grid_width);
    const auto gridHeight = static_cast<float>(grid_height);
    head_x = fmodf(head_x + gridWidth, gridWidth);
    head_y = fmodf(head_y + gridHeight, gridHeight);
}

void Snake::UpdateBody(const SDL_Point &current_cell, const SDL_Point &prev_cell) {
    // Add previous head location to vector
    body.push_back(prev_cell);

    if (!growing) {
        // Remove the tail from the vector.
        body.erase(body.begin());
    } else {
        growing = false;
        size++;
    }

    // Check if the snake has died.
    for (const auto &[x, y] : body) {
        if (current_cell.x == x && current_cell.y == y) {
            alive = false;
            break;
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