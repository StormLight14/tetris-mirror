#include "Game.hpp"
#include "Piece.hpp"
#include <ncurses.h>
#include <algorithm>
#include <sstream>
#include <random>
#include <iostream>

Game::Game() : blocks({}), messages(), playing(true), score(0), level(0), velocityX(0), activePiece(new Piece(this, Piece::PieceType::J)), speedUp(false), instantDrop(false) {

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

int Game::getScore() {
  return score;
}

void Game::setDefaultGrid() {
  grid = {};

  for (int i=0; i<getGridHeight(); i++) {
    vector<pair<string, int>> row = {};

    for (int j=0; j<getGridWidth(); j++) {
      row.push_back({"\u2022", 0});
    }

    grid.push_back(row);
  }
}

bool Game::blockInPos(pair<int, int> pos) {
  bool blockInPos = false;
  for (auto& block : blocks) {
    if (block.y == pos.first && block.x == pos.second) {
      blockInPos = true;
    }
  }

  return blockInPos;
}

void Game::handleMovement() {
  if (activePiece == nullptr) {
    return;
  }

  if (velocityX != 0) {
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


    if (velocityX == -1) {
      if (minX <= 0) {
        return;
      }
    }

    if (velocityX == 1) {
      if (maxX >= getGridWidth() - 1) {
        return;
      }
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
  speedUp = false;
  if (activePiece == nullptr) {
    return;
  }

  for (auto& activeBlock : activePiece->getGlobalShape()) {
    if (!(activeBlock.first < getGridHeight() - 1)) {
      newActivePiece();
      return; // block collides with floor
    }
    for (auto& block : blocks) {
      if (activeBlock.first + 1 == block.y && activeBlock.second == block.x) { // slot not empty
        newActivePiece();
        return; // block collides with block under
      }
    }
  }

  activePiece->move(1, 0);

  refresh();
}

void Game::newActivePiece() {
  instantDrop = false; // piece has dropped
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(1, 7);

  if (activePiece != nullptr) {
    for (auto const block : activePiece->getGlobalShape()) {
      blocks.push_back(Block{block.second, block.first, activePiece->getIntPieceType()});
    }
  }

  activePiece = new Piece(this, static_cast<Piece::PieceType>(distrib(gen)));

  handleLoss();
}

void Game::handleLineClear() {
  // get which rows cleared
  vector<int> clearedRows = {};
  for (int i = 0; i < getGridHeight(); i++) {
    int rowBlocks = 0;
    for (auto& block : blocks) {
      if (block.y == i) {
        rowBlocks += 1;
      }
    }

    if (rowBlocks >= getGridWidth()) {
      clearedRows.push_back(i);
    }
  }
  
  // remove all the cleared blocks
  blocks.erase(
        std::remove_if(blocks.begin(), blocks.end(), [&](const Block& block) {
            return std::find(clearedRows.begin(), clearedRows.end(), block.y) != clearedRows.end();
        }),
        blocks.end()
    );
  
  if (clearedRows.size()) {
    for (auto& block : blocks) {
      // only move blocks that are above the lowest cleared row
      if (block.y < *std::min_element(clearedRows.begin(), clearedRows.end())) {
        // move the block down by the number of rows cleared
        if (block.y < getGridHeight() - 1) {
          block.y += clearedRows.size();
        }
      }
    }
  }

  switch (clearedRows.size()) {
    case 1:
      score += 100;
      break;
    case 2:
      break;
      score += 300;
    case 3:
      score += 500;
      break;
    case 4:
      score += 800;
      break;
    default:
      return;
  }
}

void Game::handleLoss() {
  if (activePiece == nullptr) {
    return;
  }

  for (auto& activeBlock : activePiece->getGlobalShape()) {
    for (auto& block : blocks) {
      if (activeBlock.first == block.y && activeBlock.second == block.x) {
        playing = false;
      }
    }
  }
}

void Game::handleInput() {
  int key = getch();

  if (key == 'a' || key == KEY_LEFT) {
    velocityX = -1;
  } else if (key == 'd' || key == KEY_RIGHT) {
    velocityX = 1;
  }
  
  if (key == 32) { // spacebar
    instantDrop = true;
  }
  else if (key == 's' || key == KEY_DOWN) {
    speedUp = true;
  } else if (key == 'w' || key == KEY_UP) {
    activePiece->rotate();
  } else if (key == 'q') {
    playing = false;
  }

  flushinp();
  
  refresh();
}

void Game::displayGame() {
  clear(); // clear the screen/window
  
  if (activePiece == nullptr) {
    return;
  }

  // reset grid to empty
  for (auto& row : grid) {
    for (auto& cell : row) {
      cell = {"\u2022", 0}; // use empty circle character for empty spaces
    }
  }

  // places each piece
  for (auto& block : blocks) {
    // give each block a square symbol
    grid[block.y][block.x] = {"\u25A0", block.intPieceType};
  }
  
  for (auto& block : activePiece->getGlobalShape()) {
    grid[block.first][block.second] = {"\u25A0", activePiece->getIntPieceType()};
  }

  bool shownScore = false;
  for (int row = 0; row < getGridHeight(); ++row) {
    printw("|"); // left boundary
    for (int col = 0; col < getGridWidth(); ++col) {
      attron(COLOR_PAIR(grid[row][col].second));
      std::ostringstream oss;
      oss << grid[row][col].first << " ";
      printw(oss.str().c_str());
      attroff(COLOR_PAIR(grid[row][col].second));
    }
    if (!shownScore) {
      printw("| Current Score: %d\n", score);
      shownScore = true;
    } else {
      printw("|\n");
    }
  }

  for (auto& message : messages) {
    printw("%s\n", message.c_str());
  }

  refresh();
}

void Game::incrementElapsedFrames() {
  elapsedFrames += 1;
}

int Game::getElapsedFrames() {
  return elapsedFrames;
}
