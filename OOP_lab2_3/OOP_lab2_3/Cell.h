#pragma once

class Cell {
private:
    bool isObstacle;
    bool isUnitPresent;
public:
    Cell();

    void setObstacle(bool obstacle);
    void setUnitPresent(bool unitPresent);

    bool hasObstacle() const;
    bool hasUnitPresent() const;
};