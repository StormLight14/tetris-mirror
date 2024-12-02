#include "Game.hpp"
#include "Piece.hpp"
#include <ncurses.h>
#include <algorithm>
#include <sstream>
#include <random>
#include <iostream>

Game::Game() : messages(), playing(true), score(0), level(0), velocityX(0), pieces({Piece(this, Piece::PieceType::J)}) {
  activePiece = &pieces[0];
}

Game::~Game() {
  //delete(activePiece);
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
      //messages.push_back("game thinks wall is in the way (left).");
      return; // wall collision on the left
    }

    if (velocityX == 1 && maxX >= getGridWidth() - 1) {
      //messages.push_back("game thinks wall is in the way (right).");
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
      newActivePiece();
      return; // block collides with floor
    }
    for (auto& piece : pieces) {
      for (auto& pieceBlock : piece.getGlobalShape()) {
        if (piece.getId() != activePiece->getId() && block.first + 1 == pieceBlock.first && block.second == pieceBlock.second) { // slot not empty
          newActivePiece();
          return; // block collides with block under
        }
      }
    }
  }

  activePiece->move(1, 0);

  refresh();
}

void Game::newActivePiece() {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<> distrib(1, 7);
  
  Piece newPiece(this, static_cast<Piece::PieceType>(distrib(gen)));
  pieces.push_back(newPiece);
  activePiece = &pieces[pieces.size() - 1];
  activePiece->setId(pieces.size() - 1);
}

void Game::handleLineClear() {
  // Loop through each row of the grid
  for (int row = 0; row < getGridHeight(); ++row) {
    bool fullLine = true;

    // Check if the row is completely filled
    for (int col = 0; col < getGridWidth(); ++col) {
      if (grid[row][col] != "\u25A0") {
        fullLine = false;
        break;
      }
    }
    if (fullLine) {
      messages.push_back("CLEARED LINE");
      score += 100;
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
  clear(); // Clear the screen/window

  // Reset the grid to empty spaces first
  for (auto& row : grid) {
    for (auto& cell : row) {
      cell = "\u2022"; // Use the empty circle character for empty spaces
    }
  }

  // Place each piece on the grid
  for (auto& piece : pieces) {
    int colorPair = static_cast<int>(piece.getPieceType());

    for (auto& block : piece.getGlobalShape()) {
      // Assign the square symbol to the grid
      grid[block.first][block.second] = "\u25A0";
    }
  }

  bool shownScore = false;
  for (int row = 0; row < getGridHeight(); ++row) {
    printw("|"); // Left boundary of the grid
    for (int col = 0; col < getGridWidth(); ++col) {
      if (grid[row][col] == "\u25A0") {
        for (auto& piece : pieces) {
          if (std::find(piece.getGlobalShape().begin(), piece.getGlobalShape().end(),
                        std::make_pair(row, col)) != piece.getGlobalShape().end()) {
            int colorPair = 0;
            switch (piece.getPieceType()) {
              case Piece::PieceType::I:
                colorPair = 1;
                break;
              case Piece::PieceType::J:
                colorPair = 2;
                break;
              case Piece::PieceType::L:
                colorPair = 3;
                break;
              case Piece::PieceType::O:
                colorPair = 4;
                break;
              case Piece::PieceType::S:
                colorPair = 5;
                break;
              case Piece::PieceType::T:
                colorPair = 6;
                break;
              case Piece::PieceType::Z:
                colorPair = 7;
                break;
            }
            attron(COLOR_PAIR(colorPair));
            printw("%s ", grid[row][col].c_str());
            attroff(COLOR_PAIR(colorPair));
            break;
          }
        }
      } else {
        printw("%s ", grid[row][col].c_str());
      }
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

vector<Piece> Game::getPieces() {
  return pieces;
}
