#include "pawn.h"

Pawn::Pawn() {}



void Pawn::onPlayerPositionChanged(Position* newPosition) {
    position_ = newPosition;
}

void Pawn::movePawn(Position* newPosition) {
    position_ = newPosition;
    emit positionChanged(newPosition);
}
