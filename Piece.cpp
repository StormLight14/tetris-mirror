#include "Piece.hpp"

Piece::Piece(Game* g, PieceType t) : shape({}), id(0), game(g), pieceType(t), position(2, 2), orientation(0) {
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
  Piece rotatedPiece = *this;

  for (auto& block : rotatedPiece.shape) {
    int oldY = block.first;
    int oldX = block.second;
    block.first = oldX;
    block.second = -oldY;
  }

  for (auto& block : rotatedPiece.getGlobalShape()) {
    if (block.first < 0 || block.first >= game->getGridHeight() || block.second < 0 || block.second >= game->getGridWidth() || game->blockInPos({block.first, block.second})) {
      return; // wall in the way
    }
  }

  shape = rotatedPiece.shape;
}

int Piece::getId() {
  return id;
}

void Piece::setId(int i) {
  id = i;
}

Piece::PieceType Piece::getPieceType() const {
  return pieceType;
}

int Piece::getIntPieceType() const {
  return static_cast<int>(pieceType);
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
