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
      I=1, O, T, S, Z, J, L
    };

    Piece(Game* game, PieceType pieceType);
    void rotate(); // will be clockwise
    void updatePosition();
    void rotateI();
    void rotateO();
    void rotateT();
    void rotateS();
    void rotateZ();
    void rotateJ();
    void rotateL();
    vector<pair<int, int>> getShape() const; // gets coordinates of each block that makes up the shape
    vector<pair<int, int>> getGlobalShape(); // gives shape relative to global coordinates
    PieceType getPieceType() const;
    void setPosition();
    void setPosition(int y, int x);
    void move(int dirY, int dirX);
    void setPosition(pair<int, int> position);
    int getId();
    void setId(int i);
    pair<int, int> getPosition();
  private:
    PieceType pieceType;
    vector<pair<int, int>> shape; // ints are offsets to position (0, 0 in shape == position)
    pair<int, int> position;
    int orientation;
    int id;
    Game* game;
    void setShape(); // based on pieceType
};
