#include "Position.h"

Position Position::operator-(const Position& other) const {
    Position result;
    result.x = x - other.x;
    result.y = y - other.y;
    return result;
}

void Position::setCoordinates(int valueX, int valueY)
{
    x = valueX;
    y = valueY;
}

Position Position::calculationDelta(Position reduced, Position subtractor) {
    return reduced - subtractor;
}