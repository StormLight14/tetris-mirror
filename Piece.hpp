#pragma once
#include <vector>
#include <utility>

using std::vector, std::pair;

class Piece {
  public:
    enum class PieceType {
      I, O, T, S, Z, J, L
    };

    Piece(PieceType pieceType);
    void rotate(); // will be clockwise
    vector<pair<int, int>> getShape() const; // gets coordinates of each block that makes up the shape
    PieceType getPieceType() const;
    void setPosition(int x, int y);
    void move(int dirX, int dirY);
    void setPosition(pair<int, int> position);
  private:
    PieceType pieceType;
    vector<pair<int, int>> shape; // ints are relative to position (0, 0 of shape == position)
    pair<int, int> position;

    void setShape(); // based on pieceType
};
