#include "Game.hpp"
#include <curses.h>
#include <chrono>
#include <thread>

int main() {
    Game game;
    game.initCurses();

    const int FPS = 30;
    const std::chrono::milliseconds frameDuration(1000 / FPS);

    auto previousTime = std::chrono::steady_clock::now();

    while (game.playing) {
        auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedTime = currentTime - previousTime;

        game.handleInput();

        {
            game.setDefaultGrid();
            game.handleMovement();
            
            if (game.getElapsedFrames() % 30 == 0) {
              game.handleGravity();
            }
            game.handleLineClear();

            game.incrementElapsedFrames();
        }

        game.displayGame();

        // sleep to maintain consistent frame rate
        std::this_thread::sleep_for(frameDuration - elapsedTime);

        previousTime = currentTime;
    }
    
    endwin();  // reset terminal settings to default
    return 0;
}
