#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "snake.h"

template<typename T>
struct WorldSize {
    T screenWidth;
    T screenHeight;
    T gridWidth;
    T gridHeight;

    [[nodiscard]] T GetBlockWidth() const { return screenWidth / gridWidth; }
    [[nodiscard]] T GetBlockHeight() const { return screenHeight / gridHeight; }

    template<typename U>
    WorldSize<U> Cast() const {
        return (WorldSize<U>) {
            .screenWidth = static_cast<U>(screenWidth),
            .screenHeight = static_cast<U>(screenHeight),
            .gridWidth = static_cast<U>(gridWidth),
            .gridHeight = static_cast<U>(gridHeight),
        };
    }
};

class Renderer {
public:
    explicit Renderer(WorldSize<int> size);
    ~Renderer();

    void Render(const Snake::Snake &snake, SDL_Point const &food) const;
    void UpdateWindowTitle(int score, int fps) const;

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    const WorldSize<int> m_worldSize;
};

#endif