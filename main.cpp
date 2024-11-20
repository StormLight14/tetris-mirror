#include "Game.hpp"
#include <curses.h>
#include <thread>
#include <mutex> // for some thread safety stuff i kinda get

int main() {
  Game game;
  game.initCurses();

  std::mutex gameMutex;

  std::thread inputThread([&]() { // uses a lambda thingy to run input code on a separate thread
    while (true) {
      std::lock_guard<std::mutex> lock(gameMutex); // locks mutex for thread safety
      game.handleInput();

      if (!game.playing) {
        break;
      }
    }
  });

  while (true) {
    std::lock_guard<std::mutex> lock(gameMutex);
    game.handleGravity();
    game.displayGame();

    if (!game.playing) {
      break;
    }
  }

  inputThread.join(); // make sure input thread will end
  endwin(); // reset terminal settings to default
  
  return 0;
}
