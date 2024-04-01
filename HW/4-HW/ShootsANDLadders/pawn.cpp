#include "pawn.h"

Pawn::Pawn() {}



void Pawn::onPlayerPositionChanged(std::pair<int,int> newPosition) {
    position_ = newPosition;
}

void Pawn::movePawn(std::pair<int,int> newPosition) {
    position_ = newPosition;
    emit positionChanged(newPosition);
}
