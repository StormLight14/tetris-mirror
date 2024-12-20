#pragma once
#include <vector>
#include <utility>
#include "Game.hpp"

class Game;

using std::vector, std::pair;

// ALL COORDINATES ARE DONE BY {ROW, COL} AKA {Y, X}
//
class Piece {
  public:
    enum class PieceType {
      I=1, O=2, T=3, S=4, Z=5, J=6, L=7
    };

    Piece(Game* game, PieceType pieceType);
    void rotate(); // will be clockwise
    vector<pair<int, int>> getShape() const; // gets coordinates of each block that makes up the shape
    vector<pair<int, int>> getGlobalShape() const; // gives shape relative to global coordinates
    PieceType getPieceType() const;
    int getIntPieceType() const;
    void setPosition();
    void setPosition(int y, int x);
    void move(int dirY, int dirX);
    void setPosition(pair<int, int> position);
    pair<int, int> getPosition() const;
  private:
    PieceType pieceType;
    vector<pair<int, int>> shape; // ints are offsets to position (0, 0 in shape == position)
    pair<int, int> position;
    int orientation;
    Game* game;
    void setShape(); // based on pieceType
};
