#include "Game.hpp"
#include <iostream>

Game::Game() {
  score = 0;
  level = 0;
  pieces = {};
}

void Game::initCurses() {
  initscr();
  start_color();

  cbreak();
  noecho();
  keypad(stdscr, true); // for arrow keys
  
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
  // printw("\n%d", key);

  if (key == 97 || key == 260) {
    printw("\nPressed left.");
  } else if (key == 115 || key == 258) {
    printw("\nPressed down.");
  } else if (key == 100 || key == 261) {
    printw("\nPressed right.");
  }
  
  refresh();
}

void Game::displayGame() {
  
}
