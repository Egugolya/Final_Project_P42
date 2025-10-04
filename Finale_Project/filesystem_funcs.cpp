#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "console_stuff.h"
#include "warehouse_funcs.h"
#include "filesystem_funcs.h"
#include <fstream>


using namespace std;

extern Product* warehouse;
extern int productCount;

void saveProductsToFile(const string& filename) {
    ofstream out(filename);
    if (!out) {
        cout << "Error opening file for writing.\n";
        return;
    }

    for (int i = 0; i < productCount; ++i) {
        out << warehouse[i].name << "|"
            << warehouse[i].quantity << "|"
            << warehouse[i].manufacturer << "|"
            << warehouse[i].price << "|"
            << warehouse[i].group << "|"
            << warehouse[i].arrivalDate << "|"
            << warehouse[i].expiryDate << "\n";
    }

    out.close();
}

void loadProductsFromFile(const string& filename) {
    ifstream in(filename);
    string line;
    productCount = 0;
    delete[] warehouse;
    warehouse = nullptr;

    while (getline(in, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        size_t pos4 = line.find('|', pos3 + 1);
        size_t pos5 = line.find('|', pos4 + 1);
        size_t pos6 = line.find('|', pos5 + 1);

        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos ||
            pos4 == string::npos || pos5 == string::npos || pos6 == string::npos)
            continue;

        string name = line.substr(0, pos1);
        int quantity = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        string manufacturer = line.substr(pos2 + 1, pos3 - pos2 - 1);
        double price = stod(line.substr(pos3 + 1, pos4 - pos3 - 1));
        string group = line.substr(pos4 + 1, pos5 - pos4 - 1);
        string arrivalDate = line.substr(pos5 + 1, pos6 - pos5 - 1);
        string expiryDate = line.substr(pos6 + 1);

        Product* newArray = new Product[productCount + 1];
        for (int i = 0; i < productCount; ++i)
            newArray[i] = warehouse[i];

        newArray[productCount].name = name;
        newArray[productCount].quantity = quantity;
        newArray[productCount].manufacturer = manufacturer;
        newArray[productCount].price = price;
        newArray[productCount].group = group;
        newArray[productCount].arrivalDate = arrivalDate;
        newArray[productCount].expiryDate = expiryDate;

        delete[] warehouse;
        warehouse = newArray;
        ++productCount;
    }
    in.close();
}