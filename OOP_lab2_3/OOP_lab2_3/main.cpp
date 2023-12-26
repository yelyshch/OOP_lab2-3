#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <windows.h>
#include <iomanip>
#include <vector>
#include "Manager.h"

using std::string;
using std::cout;
using std::endl;
using std::setw;

const int FIELD_SIZE = 5;

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Manager mainManager;
    return 0;
}