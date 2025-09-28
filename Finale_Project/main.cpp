#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "console_stuff.h"
#include "warehouse_funcs.h"
#include "filesystem_funcs.h"

using namespace std;

int main() {
    loadProductsFromFile("products.txt");

    while (true) {
        const char* menuItems[] = {
            "Add product",
            "Delete product",
            "Rename product",
            "Change quantity",
            "Show all products",
            "Exit"
        };
        const int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);

        ClearConsole();
        int choice = ShowMenu(menuItems, menuSize, 5, 2);
        switch (choice) {
        case 0: addProduct(); break;
        case 1: deleteProduct(); break;
        case 2: renameProduct(); break;
        case 3: changeQuantity(); break;
        case 4: showProducts(); break;
        case 5: return 0;
        }
    }
}