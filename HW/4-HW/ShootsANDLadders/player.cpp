#include "player.h"
#include "position.h"
Player::Player() {}


Player::Player(string name, int playerID): name_(name), playerID_(playerID){}
void Player::setPosition(Position* position) {
    if (position_) { // if there's a current position
        position_->removePlayerFromPosition(this); // remove this player from the current position
    }
    position_ = position; // set the new position
    if (position_) { // if the new position is not null
        position_->addPlayerToPosition(this); // adding the player to the new position
    }
    emit positionChanged(position);
}

void Player::removePosition() {
    if (position_) { // if there's a current position
        position_->removePlayerFromPosition(this); // remove this player from the current position
        position_ = nullptr;
    }
}
