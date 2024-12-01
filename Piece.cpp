#include "Piece.hpp"

Piece::Piece(PieceType t) : pieceType(t), position(0, 0) {
  setShape();
}

void Piece::setShape() {
  switch (pieceType) {
    case PieceType::I:
      shape = {{0, 1}, {1, 1}, {2, 1}, {3, 1}}; // vertical line
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

vector<pair<int, int>> Piece::getShape() const {
  return shape;
}

vector<pair<int, int>> Piece::getGlobalShape() {
  vector<pair<int, int>> globalShape = {};

  for (auto& offset : getShape()) {
    pair<int, int> newPair = {getPosition().first + offset.first, getPosition().second + offset.second};
    globalShape.push_back(newPair);
  }

  return globalShape;
}

void Piece::rotate() {
  vector<pair<int, int>> newShape = shape;

  // goes over each block in the shape
  for (auto& block : newShape) {
    // clockwise swaps x, y and makes y negative
    int y = block.first;
    int x = block.second;
    block.first = x;
    block.second = -y;
  }


}

void Piece::setPosition(int row, int col) {
  position = {row, col}; // y, x
}

void Piece::setPosition(pair<int, int> pos) {
  position = pos;
}

void Piece::move(int dirY, int dirX) {
  position.first += dirY;
  position.second += dirX;
}

pair<int, int> Piece::getPosition() {
  return position;
}
