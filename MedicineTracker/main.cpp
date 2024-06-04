#include <iostream>
#include "Date.h"
#include "Database.h"
#include "Menu.h"

int main()
{
    if (!Database::Initialize("medical.db")) {
        std::cout << "Failed to open database/More than one instance of application is open.\nClosing...\n";
        Sleep(2500);
        return 1;
    }
   
    while (Menu::isRunning) {
        Menu::Display();
    }

    Database::Shutdown();
    return 0;
}