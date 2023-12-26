#include "Cell.h"

Cell::Cell() : isObstacle(false), isUnitPresent(false) {}

void Cell::setObstacle(bool obstacle) {
    isObstacle = obstacle;
}

void Cell::setUnitPresent(bool unitPresent) {
    isUnitPresent = unitPresent;
}

bool Cell::hasObstacle() const {
    return isObstacle;
}

bool Cell::hasUnitPresent() const {
    return isUnitPresent;
}