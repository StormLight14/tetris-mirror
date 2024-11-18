#include "Game.hpp"
#include <curses.h>

int main() {
  Game game;
  game.initCurses();

  // main game loop
  while (true) {
    game.handleGravity();
    game.handleInput();
    game.displayGame();
  }

  endwin(); // reset terminal settings to default
  return 0;
}
