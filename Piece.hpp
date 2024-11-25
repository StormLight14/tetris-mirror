#pragma once
#include <vector>
#include <utility>

using std::vector, std::pair;

// ALL COORDINATES ARE DONE BY {ROW, COL} AKA {Y, X}
//
class Piece {
  public:
    enum class PieceType {
      I, O, T, S, Z, J, L
    };

    Piece(PieceType pieceType);
    void rotate(); // will be clockwise
    vector<pair<int, int>> getShape() const; // gets coordinates of each block that makes up the shape
    vector<pair<int, int>> getGlobalShape(); // gives shape relative to global coordinates
    PieceType getPieceType() const;
    void setPosition(int y, int x);
    void move(int dirY, int dirX);
    void setPosition(pair<int, int> position);
    pair<int, int> getPosition();
  private:
    PieceType pieceType;
    vector<pair<int, int>> shape; // ints are offsets to position (0, 0 in shape == position)
    pair<int, int> position;

    void setShape(); // based on pieceType
};
