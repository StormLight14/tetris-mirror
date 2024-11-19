#include "Piece.hpp"

Piece::Piece(PieceType t) : pieceType(t), position(0, 0) {
  setShape();
}

void Piece::setShape() {
  switch (pieceType) {
    case PieceType::I:
      shape = {{1, 0}, {1, 1}, {1, 2}, {1, 3}}; // vertical line
      break;
    case PieceType::O:
      shape = {{0, 0}, {0, 1}, {1, 0}, {1, 1}}; // square
      break;
    case PieceType::T:
      shape = {{0, 1}, {1, 0}, {1, 1}, {1, 2}}; // T-shape
      break;
    case PieceType::S:
      shape = {{1, 0}, {2, 0}, {0, 1}, {1, 1}}; // S-shape
      break;
    case PieceType::Z:
      shape = {{0, 0}, {1, 0}, {1, 1}, {2, 1}}; // Z-shape
      break;
    case PieceType::J:
      shape = {{0, 0}, {1, 0}, {2, 0}, {2, 1}}; // J-shape
      break;
    case PieceType::L:
      shape = {{0, 0}, {1, 0}, {2, 0}, {0, 1}}; // L-shape
      break;
  }
}

void Piece::rotate() {
  // goes over each block in the shape
  for (auto& block : shape) {
    // clockwise is (y, -x) i think..
    int x = block.first;
    int y = block.second;
    block.first = y;
    block.second = -x;
  }
}

void Piece::setPosition(int x, int y) {
  position = {x, y};
}

void Piece::setPosition(pair<int, int> pos) {
  position = pos;
}

void Piece::move(int dirX, int dirY) {
  position.first += dirX;
  position.second += dirY;
}
