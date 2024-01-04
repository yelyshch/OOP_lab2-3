#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <windows.h>
#include <iomanip>
#include <vector>
#include "Manager.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::setw;

const int FIELD_SIZE = 7;

void PrintField(Field* field) {
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            if (field->cells[i][j].hasObstacle())
                cout << setw(3) << 'x';
            else if (field->cells[i][j].hasUnitPresent())
                cout << setw(3) << 'u';
            else
                cout << setw(3) << 0;
        }
        cout << endl;
    }
}

void displayHero(const string& title, Character* character) {
    cout << title << ":" << endl;
    cout << "position: (" << character->getPosition().x << ", " << character->getPosition().y << "), health: " << character->getHealth()
        << ", damage: " << character->getDamage() << ", protection: " << character->getProtection()
        << ", speed: " << character->getSpeed() << ", distance: " << character->getDistance() << endl;
}

void displayMonster(const string& title, Character* character) {
    cout << title << ":" << endl;
    cout << "position: (" << character->getPosition().x << ", " << character->getPosition().y << "), health: " << character->getHealth()
        << ", damage: " << character->getDamage() << ", protection: " << character->getProtection() << endl;
}

bool setTypeHero() {
    cout << "Please select a hero type:" << endl << "0 - Archer" << endl << "1 - Swordsman" << endl;
    bool selectType;
    cin >> selectType;
    return selectType;
}

void TestGame(Manager mainManager) {
    //Start game: creation and generation.

    //Field
    mainManager.createField(FIELD_SIZE, FIELD_SIZE, 1, 1, setTypeHero());
    cout << "Current level = " << mainManager.CurrentLevel << endl << endl;
    PrintField(mainManager.gameField);
    
    
    //Hero
    //Initial values ​​of the hero
    displayHero("\nHero status before dice results", mainManager.gameField->hero);
    //Generating values
    mainManager.gameField->hero->diceResults();
    displayHero("Hero status after dice results", mainManager.gameField->hero);
    cout << endl;

    
    //Monster
    //Initial values of the monster
    displayMonster("Monster status", mainManager.gameField->monster);
    //Generating values
    mainManager.gameField->monster->diceResults();
    displayMonster("Monster status after dice results", mainManager.gameField->monster);
    cout << endl;


    //Round Phase:
    while (mainManager.gameField->monster->getHealth() > 0 || mainManager.gameField->hero->getHealth() > 0) {
        int deltaX = mainManager.gameField->hero->getPosition().x - mainManager.gameField->monster->getPosition().x;
        int deltaY = mainManager.gameField->hero->getPosition().y - mainManager.gameField->monster->getPosition().y;

        if (deltaX >= mainManager.gameField->hero->getDistance() && deltaY >= mainManager.gameField->hero->getDistance()) {
            cout << "Enter the number to perform the desired action: 0 - attack, 1 - move, other - miss :";
            short int choice;
            cin >> choice;

            switch (choice) {
            case 0:
                mainManager.gameField->hero->attack(*mainManager.gameField->monster, mainManager.gameField);
                break;
            case 1:
                Position newPosition;
                short int x;
                short int y;
                cout << "Enter the values ​​of the new coordinates:" << endl << "x: ";
                cin >> x;
                cout << "y: ";
                cin >> y;
                newPosition.setCoordinates(x, y);
                mainManager.gameField->hero->move(newPosition, mainManager.gameField);
                break;
            default:
                break;
            }

        }
        else {
            cout << "Enter the number to perform the desired action: 0 - miss, 1 - move:";
            bool choice;
            cin >> choice;
            if (choice) {
                Position newPosition;
                short int x;
                short int y;
                cout << "Enter the values ​​of the new coordinates:" << endl << "x: ";
                cin >> x;
                cout << "y: ";
                cin >> y;
                newPosition.setCoordinates(x, y);
                mainManager.gameField->hero->move(newPosition, mainManager.gameField);
            }

        }

        cout << "Current level = " << mainManager.CurrentLevel << endl << endl;
        PrintField(mainManager.gameField);

        displayHero("\nHero status", mainManager.gameField->hero);
        displayMonster("Monster status", mainManager.gameField->monster);

        mainManager.gameField->monster->activityInGame(*mainManager.gameField->monster, *mainManager.gameField->hero, mainManager.gameField);
    }
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Manager mainManager;

    
    TestGame(mainManager);
    return 0;
}