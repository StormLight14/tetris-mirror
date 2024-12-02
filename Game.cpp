#include "Game.hpp"
#include "Piece.hpp"
#include <ncurses.h>
#include <sstream>

Game::Game() : messages(), playing(true), score(0), level(0), velocityX(0), pieces({Piece(this, Piece::PieceType::I)}) {
  activePiece = &pieces[0];
}

Game::~Game() {
  delete(activePiece);
}

void Game::initCurses() {
  setlocale(LC_ALL, "");
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
    vector<string> row = {};

    for (int j=0; j<getGridWidth(); j++) {
      row.push_back("\u2022");
    }

    grid.push_back(row);
  }
}

bool Game::blockInPos(pair<int, int> pos) {
  for (auto& piece : pieces) {
    for (auto& block : piece.getGlobalShape()) {
      if (block.first == pos.first && block.second == pos.second) {
        return true;
      }
    }
  }

  return false;
}

void Game::handleMovement() {
  if (velocityX != 0 && activePiece != nullptr) {
    int minX = 100;
    int maxX = -100;

    for (auto& block : activePiece->getGlobalShape()) {
      if (block.second < minX) {
        minX = block.second;
      }
      if (block.second > maxX) {
        maxX = block.second;
      }
    }
    
    //std::ostringstream oss;
    //oss << "MinX, MaxX: " << minX << ", " << maxX << " " << getGridWidth();
    //messages.push_back(oss.str());


    if (velocityX == -1 && minX <= 0) {
      messages.push_back("game thinks wall is in the way (left).");
      return; // wall collision on the left
    }

    if (velocityX == 1 && maxX >= getGridWidth() - 1) {
      messages.push_back("game thinks wall is in the way (right).");
      return; // wall collision on the right
    }

    for (auto& block : activePiece->getGlobalShape()) {
      if (velocityX == -1 && block.second == minX && blockInPos({block.first, block.second - 1})) {
        return;
      }
      if (velocityX == 1 && block.second == maxX && blockInPos({block.first, block.second + 1})) {
        return;
      }
    }

    activePiece->move(0, velocityX);
    velocityX = 0; // reset velocity after moving
    refresh();
  }
}

void Game::handleGravity() {
  if (activePiece == nullptr) {
    return;
  }

  for (auto& block : activePiece->getGlobalShape()) {
    if (!(block.first < getGridHeight() - 1)) {
      return; // avoid block going past floor
    }
    if (grid[block.first + 1][block.second] != "\u2022") { // empty slot, bullet character
      return; // block collides with block under
    }
  }

  activePiece->move(1, 0);

  refresh();
}


void Game::handleInput() {
  int key = getch();

  if (key == 'a' || key == KEY_LEFT) {
    velocityX = -1;
  } else if (key == 'd' || key == KEY_RIGHT) {
    velocityX = 1;
  }

  if (key == 's' || key == KEY_DOWN) {
    // speed up movement speed
  } else if (key == 'w' || key == KEY_UP) {
    if (activePiece != nullptr) {
      activePiece->rotate();
    }
  } else if (key == 'q') {
    playing = false;
  }

  flushinp();
  
  refresh();
}

void Game::displayGame() {
  clear(); // clear window
  
  for (auto& piece : pieces) {
    for (auto& block : piece.getGlobalShape())
    grid[block.first][block.second] = "\u25A0"; // square character
  }

  for (auto& row : grid) {
    printw("|");
    for (auto& charstr : row) {
      printw("%s ", charstr.c_str());
    }
    printw("|\n");
  }

  for (auto& message : messages) {
    printw("%s\n", message.c_str());
  }

  refresh(); // show updated display
}

void Game::incrementElapsedFrames() {
  elapsedFrames += 1;
}

int Game::getElapsedFrames() {
  return elapsedFrames;
}
