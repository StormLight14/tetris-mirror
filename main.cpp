#include "Game.hpp"
#include <curses.h>
#include <chrono>
#include <thread>
#include <iostream>

int main() {
  Game game;
  game.initCurses();

  const int FPS = 20;
  std::chrono::milliseconds frameDuration(1000 / FPS);

  auto previousTime = std::chrono::steady_clock::now();

  while (game.playing) {
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - previousTime;

    game.handleInput();
    game.setDefaultGrid();
    game.handleMovement();
    
    if (game.getElapsedFrames() % 15 == 0) {
      game.handleGravity();
      game.handleLineClear();
    }

    if (game.getElapsedFrames() % 1000 == 0 && frameDuration > std::chrono::milliseconds(2)) {
      frameDuration -= std::chrono::milliseconds(1);
    }

    game.incrementElapsedFrames();
    if (!game.instantDrop) {
      game.displayGame();
    }

    // sleep to maintain consistent frame rate
    if (game.instantDrop) {
      std::this_thread::sleep_for(frameDuration / 100.0 - elapsedTime);
    } else if (game.speedUp) {
      std::this_thread::sleep_for(frameDuration / 2.5 - elapsedTime);
    } else {
      std::this_thread::sleep_for(frameDuration - elapsedTime);
    }

    previousTime = currentTime;
  }
  
  endwin();  // reset terminal settings to default
  std::cout << "Final score: " << game.getScore() << "\n";
  return 0;
}
