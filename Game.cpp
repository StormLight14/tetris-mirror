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
  // printw("\n%d", key);

  // w, left
  if (key == 97 || key == KEY_LEFT) {
    printw("Pressed left.\n");
    // s, down
  } else if (key == 115 || key == KEY_DOWN) {
    printw("Pressed down.\n");
    // d, right
  } else if (key == 100 || key == KEY_RIGHT) {
    printw("Pressed right.\n");
  }
  
  refresh();
}

void Game::displayGame() {
  
}
