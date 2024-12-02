#pragma once

#include <vector>
#include <curses.h>
#include "Piece.hpp"
#include <string>

class Piece;

using std::vector, std::pair, std::string;

class Game {
  public:
    Game();
    ~Game();
    void initCurses();
    void handleInput();
    void handleMovement();
    void handleGravity();
    void newActivePiece();
    void handleLineClear();
    void displayGame();
    int getGridWidth();
    int getGridHeight();
    bool blockInPos(pair<int, int>);
    vector<Piece> getPieces();
    vector<vector<string>> getGrid();
    void setDefaultGrid();
    void incrementElapsedFrames();
    int getElapsedFrames();
    bool playing;
  private:
    int score;
    int level;
    int velocityX; // -1, 0, or 1
    int elapsedFrames;
    Piece* activePiece;
    vector<Piece> pieces;
    vector<vector<string>> grid;
    vector<string> messages;
};

