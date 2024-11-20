#include "Game.hpp"
#include <iostream>

Game::Game() : playing(true), score(0), level(0), pieces({}) {}

void Game::initCurses() {
  initscr();
  start_color();

  cbreak();
  noecho();
  keypad(stdscr, true); // for arrow keys
  
  nodelay(stdscr, true); // getch() gives ERR if no input
  
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(4, COLOR_GREEN, COLOR_BLACK);
  init_pair(5, COLOR_RED, COLOR_BLACK);
  init_pair(6, COLOR_BLUE, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

void Game::handleGravity() {
  
}

void Game::handleInput() {
  int key = getch();

  if (key == 'a' || key == KEY_LEFT) {

  } else if (key == 's' || key == KEY_DOWN) {

  } else if (key == 'd' || key == KEY_RIGHT) {

  } else if (key == 'w' || key == KEY_UP) {

  } else if (key == 'q') {
    playing = false;
  }
  
  refresh();
}

void Game::displayGame() {
  
}
