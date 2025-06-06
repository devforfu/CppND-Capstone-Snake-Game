#include <iostream>
#include "controller.h"
#include "game/game.h"
#include "renderer.h"

int main() {
    constexpr std::size_t kFramesPerSecond{60};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    constexpr std::size_t kScreenWidth{640};
    constexpr std::size_t kScreenHeight{640};
    constexpr std::size_t kGridWidth{32};
    constexpr std::size_t kGridHeight{32};

    constexpr WorldSize<std::size_t> worldSize{
        .screenWidth = kScreenWidth,
        .screenHeight = kScreenHeight,
        .gridWidth = kGridWidth,
        .gridHeight = kGridHeight,
    };

    const Renderer renderer(worldSize.Cast<int>());

    // LizardBrain brain;
    FoodAverse brain;

    Game game(kGridWidth, kGridHeight);

    game.Run(brain, renderer, kMsPerFrame);

    std::cout << "Game has terminated successfully!\n";
    std::cout << "Score: " << game.GetScore() << "\n";
    std::cout << "Size: " << game.GetSize() << "\n";

    return 0;
}