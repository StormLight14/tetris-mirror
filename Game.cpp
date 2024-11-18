#include "Game.hpp"

Game::Game() {
  score = 0;
  level = 0;
  pieces = {};
}

void Game::initCurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true); // for arrow keys
}

void Game::handleGravity() {
  
}

void Game::handleInput() {
  
}

void Game::displayGame() {
  
}
