#pragma once

class Position {
public:
    int x;
    int y;

    Position operator-(const Position& other) const;

    void setCoordinates(int valueX, int valueY);
    Position calculationDelta(Position current, Position newValue);
};