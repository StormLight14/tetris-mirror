#include "Piece.hpp"

Piece::Piece(Game* g, PieceType t) : shape({}), id(0), game(g), pieceType(t), position(2, 2), orientation(0) {
  setShape();
}

void Piece::setShape() {
  switch (pieceType) {
    case PieceType::I:
      shape = {{1, 0}, {1, 1}, {1, 2}, {1, 3}}; // horizontal line
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
    switch (pieceType) {
        case PieceType::I:
            Piece::rotateI();
            break;
        case PieceType::O:
            rotateO();
            break;
        case PieceType::T:
            rotateT();
            break;
        case PieceType::S:
            rotateS();
            break;
        case PieceType::Z:
            rotateZ();
            break;
        case PieceType::J:
            rotateJ();
            break;
        case PieceType::L:
            rotateL();
            break;
    }

  updatePosition();
}

int Piece::getId() {
  return id;
}

void Piece::setId(int i) {
  id = i;
}

void Piece::updatePosition() {
    // Calculate the new position based on the current shape and orientation
    int minX = 100, minY = 100;
    for (const auto& block : shape) {
        minY = std::min(minY, block.first);
        minX = std::min(minX, block.second);
    }

    // recalculate position relative to the grid
    position.first = (position.first - minY); // center around smallest y
    position.second = (position.second - minX); // center around smallest x

    // adjust if the piece is near the edge of the grid
    if (position.first < 0) position.first = 0;
    if (position.second < 0) position.second = 0;
}

void Piece::rotateI() {
    if (orientation == 0) {
        shape = {{0, 1}, {1, 1}, {2, 1}, {3, 1}}; // vertical line
        orientation = 1;
    } else {
        shape = {{1, 0}, {1, 1}, {1, 2}, {1, 3}}; // horizontal line
        orientation = 0;
    }
}

void Piece::rotateO() {
  // idk why i made this it does nothing, cause its a square
}

void Piece::rotateT() {
    if (orientation == 0) {
        shape = {{0, 1}, {1, 0}, {1, 1}, {1, 2}}; // T-shape vertical
        orientation = 1;
    } else if (orientation == 1) {
        shape = {{0, 1}, {1, 1}, {1, 0}, {2, 1}}; // T-shape rotated 90 degrees
        orientation = 2;
    } else if (orientation == 2) {
        shape = {{1, 0}, {1, 1}, {1, 2}, {2, 1}}; // T-shape rotated 180 degrees
        orientation = 3;
    } else {
        shape = {{1, 0}, {1, 1}, {2, 1}, {1, 2}}; // T-shape rotated 270 degrees
        orientation = 0;
    }
}

void Piece::rotateS() {
    if (orientation == 0) {
        shape = {{1, 0}, {2, 0}, {0, 1}, {1, 1}}; // S-shape
        orientation = 1;
    } else {
        shape = {{0, 0}, {1, 0}, {1, 1}, {2, 1}}; // Rotated S-shape
        orientation = 0;
    }
}

void Piece::rotateZ() {
    if (orientation == 0) {
        shape = {{0, 0}, {1, 0}, {1, 1}, {2, 1}}; // Z-shape
        orientation = 1;
    } else {
        shape = {{1, 0}, {2, 0}, {0, 1}, {1, 1}}; // Rotated Z-shape
        orientation = 0;
    }
}

void Piece::rotateJ() {
    if (orientation == 0) {
        shape = {{0, 0}, {1, 0}, {2, 0}, {2, 1}}; // J-shape
        orientation = 1;
    } else if (orientation == 1) {
        shape = {{1, 0}, {1, 1}, {1, 2}, {0, 2}}; // Rotated J-shape
        orientation = 2;
    } else if (orientation == 2) {
        shape = {{0, 0}, {1, 0}, {2, 0}, {0, 1}}; // J-shape rotated 180 degrees
        orientation = 3;
    } else {
        shape = {{1, 0}, {1, 1}, {1, 2}, {2, 0}}; // Rotated J-shape
        orientation = 0;
    }
}

void Piece::rotateL() {
    if (orientation == 0) {
        shape = {{0, 0}, {1, 0}, {2, 0}, {0, 1}}; // L-shape
        orientation = 1;
    } else if (orientation == 1) {
        shape = {{1, 0}, {1, 1}, {1, 2}, {2, 2}}; // Rotated L-shape
        orientation = 2;
    } else if (orientation == 2) {
        shape = {{0, 0}, {1, 0}, {2, 0}, {2, 1}}; // L-shape rotated 180 degrees
        orientation = 3;
    } else {
        shape = {{1, 0}, {1, 1}, {1, 2}, {0, 0}}; // Rotated L-shape
        orientation = 0;
    }
}

Piece::PieceType Piece::getPieceType() const {
  return pieceType;
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
