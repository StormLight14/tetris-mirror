#include "Game.hpp"
#include <curses.h>

int main() {
  Game game;
  game.initCurses();

  // main game loop
  while (game.playing) {
    game.handleGravity();
    game.handleInput();
    game.displayGame();
  }

  endwin(); // reset terminal settings to default
  return 0;
}
