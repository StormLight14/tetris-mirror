#include "Game.hpp"
#include <curses.h>

Game::Game() {

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
