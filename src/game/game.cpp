#include "game.h"
#include "SDL.h"

Game::Game(const std::size_t gridWidth, const std::size_t gridHeight) :
    engine(dev()),
    width(static_cast<int>(gridWidth)),
    height(static_cast<int>(gridHeight)),
    random_w(0, width - 1),
    random_h(0, height - 1),
    snake(static_cast<int>(gridWidth), static_cast<int>(gridHeight)) {
    PlaceFood();
}

void Game::Run(ControllerInterface &controller, const Renderer &renderer, const std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    int frame_count = 0;
    bool running = true;

    while (running) {
        const Uint32 frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        controller.HandleInput(running, snake, *this);
        Update();
        renderer.Render(snake, food);

        const Uint32 frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        const Uint32 frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            renderer.UpdateWindowTitle(score, frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}

void Game::PlaceFood() {
    while (true) {
        const int x = random_w(engine);
        // Check that the location is not occupied by a snake item before placing food.
        if (const int y = random_h(engine); !snake.SnakeCell(x, y)) {
            food.x = x;
            food.y = y;
            return;
        }
    }
}

void Game::Update() {
    if (snake.IsDead()) return;

    snake.Update();

    if (food.x == snake.GetHeadX() && food.y == snake.GetHeadY()) {
        score++;
        PlaceFood();
        snake.GrowBody();
        snake.SpeedUp();
    }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.GetSize(); }