#include "Game.hpp"
#include "Piece.hpp"
#include <ncurses.h>

Game::Game() : playing(true), score(0), level(0), pieces({Piece(Piece::PieceType::I)}) {
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

int Game::getGridWidth() {
  return 10;
}

int Game::getGridHeight() {
  return 20;
}

void Game::setDefaultGrid() {
  grid = {};

  for (int i=0; i<getGridHeight(); i++) {
    vector<char> row = {};

    for (int j=0; j<getGridWidth(); j++) {
      row.push_back('#');
    }

    grid.push_back(row);
  }
}

void Game::handleGravity() {
  for (auto& piece : pieces) {
    for (auto& block : piece.getGlobalShape()) {
      if (!(block.first < getGridHeight() - 1)) {
        piece.move(1, 0);
      }
    }

  }
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
  clear(); // clear window
  
  for (auto& piece : pieces) {
    for (auto& block : piece.getGlobalShape())
    grid[block.first][block.second] = 'P';
  }

  for (auto& row : grid) {
    printw("|");
    for (auto &character : row) {
      printw("%c", character);
    }
    printw("|\n");
  }

  refresh(); // show updated display
}
