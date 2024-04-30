#include "Player.h"

Player::Player(const string &name, Color color) : name(name), color(color) {}

string Player::getName() const
{
    return name;
}

Color Player::getColor() const
{
    return color;
}

vector<Move> Player::getMoveHistory() const
{
    return moveHistory;
}

void Player::addMoveToHistory(const Move &move)
{
    moveHistory.push_back(move);
}

bool Player::operator==(const Player &other) const
{
    return (name == other.name) && (color == other.color);
}

void Player::initializePlayer()
{
    string newName;
    cin >> newName;
    int newColor;
    cin >> newColor;
    this->color = (newColor == 0) ? Color::WHITE : Color::BLACK;
    this->name = newName;
    moveHistory.clear();
}