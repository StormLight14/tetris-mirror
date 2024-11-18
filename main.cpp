#include "Game.hpp"

int main() {
  Game game;
  game.initCurses();

  // main game loop
  while (true) {
    game.handleGravity();
    game.handleInput();
    game.displayGame();
  }
}
