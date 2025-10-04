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
    ClearConsole();
    while (true) {
        SetColor(WHITE, BLACK);
        const char* menuItems[] = {
            "Add product",
            "Delete product",
            "Edit product", 
            "Show all products",
            "Search products",
            "Sort products",
            "Exit"
        };
        const int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);

        ClearConsole();
        int choice = ShowMenu(menuItems, menuSize, 5, 2);
        switch (choice) {
        case 0: addProduct(); break;
        case 1: deleteProduct(); break;
        case 2: editMenu(); break;   
        case 3: showProducts(); break;
        case 4: searchMenu(); break;
        case 5: sortMenu(); break;
        case 6: return 0;
        }
    }
}