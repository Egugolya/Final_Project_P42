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
    for (int i = 0; i < productCount; ++i)
        out << warehouse[i].name << "|" << warehouse[i].quantity << "\n";
    out.close();
}

void loadProductsFromFile(const string& filename) {
    ifstream in(filename);
    string line;
    productCount = 0;
    delete[] warehouse;
    warehouse = nullptr;

    while (getline(in, line)) {
        size_t sep = line.find('|');
        if (sep == string::npos) continue;

        string name = line.substr(0, sep);
        int quantity = stoi(line.substr(sep + 1));

        Product* newArray = new Product[productCount + 1];
        for (int i = 0; i < productCount; ++i)
            newArray[i] = warehouse[i];
        newArray[productCount].name = name;
        newArray[productCount].quantity = quantity;
        delete[] warehouse;
        warehouse = newArray;
        ++productCount;
    }
    in.close();
}