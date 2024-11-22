#include "Game.hpp"
#include <curses.h>
#include <thread>
#include <mutex> // for some thread safety stuff i kinda get
#include <chrono>

int main() {
  Game game;
  game.initCurses();

  std::mutex gameMutex;

  std::thread inputThread([&]() { // uses a lambda thingy to run input code on a separate thread
    while (true) {
      std::lock_guard<std::mutex> lock(gameMutex); // locks mutex for thread safety, unlocks when done using
      game.handleInput();

      if (!game.playing) {
        break;
      }
    }
  });

  std::thread gameThread([&]() { // uses a lambda thingy to run input code on a separate thread
    while (true) {
      std::lock_guard<std::mutex> lock(gameMutex); // locks mutex for thread safety, unlocks when done using
      game.handleGravity();
      game.displayGame();

      if (!game.playing) {
        break;
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      }
  });

  inputThread.join(); // make sure input thread will end
  gameThread.join();
  endwin(); // reset terminal settings to default
  
  return 0;
}
