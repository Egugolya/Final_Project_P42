#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "console_stuff.h"
#include "warehouse_funcs.h"
#include "filesystem_funcs.h"


using namespace std;

Product* warehouse = NULL;
int productCount = 0;

void addProduct() {
    ClearConsole();
    cout << "Enter product name: ";
    string name;
    getline(cin >> ws, name);
    cout << "Enter quantity: ";
    int quantity;
    cin >> quantity;

    Product* newArray = new Product[productCount + 1];
    for (int i = 0; i < productCount; ++i)
        newArray[i] = warehouse[i];
    newArray[productCount].name = name;
    newArray[productCount].quantity = quantity;
    delete[] warehouse;
    warehouse = newArray;
    ++productCount;
    saveProductsToFile("products.txt");
    cout << "Product added.\n";
    system("pause");
}

void deleteProduct() {
    ClearConsole();
    if (productCount == 0) {
        cout << "No products in the Warehouse\n";
        system("pause");
        return;
    }
    cout << "Enter product number to delete (1-" << productCount << "): ";
    int index;
    cin >> index;
    if (index < 1 || index > productCount) {
        cout << "Invalid number.\n";
        system("pause");
        return;
    }
    Product* newArray = new Product[productCount - 1];
    for (int i = 0, j = 0; i < productCount; ++i) {
        if (i != index - 1)
            newArray[j++] = warehouse[i];
    }
    delete[] warehouse;
    warehouse = newArray;
    --productCount;
    saveProductsToFile("products.txt");
    cout << "Product deleted.\n";
    system("pause");
}

void renameProduct() {
    ClearConsole();
    if (productCount == 0) {
        cout << "No products in the Warehouse\n";
        system("pause");
        return;
    }
    cout << "Enter product number to replace (1-" << productCount << "): ";
    int index;
    cin >> index;
    if (index < 1 || index > productCount) {
        cout << "Invalid number.\n";
        system("pause");
        return;
    }
    cout << "Enter new product name: ";
    string name;
    getline(cin >> ws, name);

    warehouse[index - 1].name = name;
    saveProductsToFile("products.txt");
    cout << "Product replaced.\n";
    system("pause");
}

void changeQuantity() {
    ClearConsole();
    if (productCount == 0) {
        cout << "No products in the Warehouse\n";
        system("pause");
        return;
    }
    cout << "Enter product number to change quantity (1-" << productCount << "): ";
    int index;
    cin >> index;
    if (index < 1 || index > productCount) {
        cout << "Invalid number.\n";
        system("pause");
        return;
    }
    cout << "Current quantity: " << warehouse[index - 1].quantity << "\n";
    cout << "Enter new quantity: ";
    int quantity;
    cin >> quantity;
    warehouse[index - 1].quantity = quantity;
    saveProductsToFile("products.txt");
    cout << "Quantity updated.\n";
    system("pause");
}

void showProducts() {
    ClearConsole();
    if (productCount == 0) {
        cout << "No products in the Warehouse\n";
    }
    else {
        cout << "--- Products in the Warehouse ---\n";
        for (int i = 0; i < productCount; ++i)
            cout << (i + 1) << ". " << warehouse[i].name << " (Quantity: " << warehouse[i].quantity << ")\n";
    }
    system("pause");
}