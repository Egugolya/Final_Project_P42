#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "console_stuff.h"
#include "warehouse_funcs.h"
#include "filesystem_funcs.h"
#include <fstream>


using namespace std;

Product* warehouse = NULL;
int productCount = 0;

void addProduct() {
    ClearConsole();
    string name, manufacturer, group, arrivalDate, expiryDate;
    int quantity;
    double price;

    cout << "Enter product name: ";
    getline(cin >> ws, name);

    cout << "Enter quantity: ";
    cin >> quantity;

    cout << "Enter manufacturer: ";
    getline(cin >> ws, manufacturer);

    cout << "Enter price: ";
    cin >> price;

    cout << "Enter product group: ";
    getline(cin >> ws, group);

    cout << "Enter arrival date (YYYY-MM-DD): ";
    getline(cin >> ws, arrivalDate);

    cout << "Enter expiry date (YYYY-MM-DD): ";
    getline(cin >> ws, expiryDate);

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

    ofstream out("products.txt", ios::app);
    out << name << "|"
        << quantity << "|"
        << manufacturer << "|"
        << price << "|"
        << group << "|"
        << arrivalDate << "|"
        << expiryDate << "\n";
    out.close();

    cout << "Product added and saved.\n";
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
        cout << "--- Products in the Warehouse ---\n\n";
        for (int i = 0; i < productCount; ++i) {
            cout << (i + 1) << ". " << warehouse[i].name << "\n"
                << "   Quantity      : " << warehouse[i].quantity << "\n"
                << "   Manufacturer  : " << warehouse[i].manufacturer << "\n"
                << "   Price         : " << warehouse[i].price << " UAH\n"
                << "   Group         : " << warehouse[i].group << "\n"
                << "   Arrival Date  : " << warehouse[i].arrivalDate << "\n"
                << "   Expiry Date   : " << warehouse[i].expiryDate << "\n\n";
        }
    }
    system("pause");
}

void editMenu() {
    const char* editItems[] = {
        "Rename product",
        "Change quantity",
        "Back"
    };
    const int editSize = sizeof(editItems) / sizeof(editItems[0]);

    while (true) {
        ClearConsole();
        int choice = ShowMenu(editItems, editSize, 5, 2);
        switch (choice) {
        case 0: renameProduct(); break;
        case 1: changeQuantity(); break;
        default: return;
        }
        _getch();
    }
}

void searchByName() {
    ClearConsole();
    cout << "Enter product name to search: ";
    string query;
    getline(cin >> ws, query);
    bool found = false;
    for (int i = 0; i < productCount; ++i) {
        if (warehouse[i].name.find(query) != string::npos) {
           cout << "   Quantity      : " << warehouse[i].quantity << "\n"
                << "   Manufacturer  : " << warehouse[i].manufacturer << "\n"
                << "   Price         : " << warehouse[i].price << " UAH\n"
                << "   Group         : " << warehouse[i].group << "\n"
                << "   Arrival Date  : " << warehouse[i].arrivalDate << "\n"
                << "   Expiry Date   : " << warehouse[i].expiryDate << "\n\n";
            found = true;
        }
    }
    if (!found) cout << "No matching products found.\n";
    system("pause");
}

void searchByManufacturer() {
    ClearConsole();
    cout << "Enter manufacturer: ";
    string query;
    getline(cin >> ws, query);
    bool found = false;
    for (int i = 0; i < productCount; ++i) {
        if (warehouse[i].manufacturer == query) {
            cout << i + 1 << ". " << warehouse[i].name << " by " << warehouse[i].manufacturer << "\n";
            found = true;
        }
    }
    if (!found) cout << "No products from this manufacturer.\n";
    system("pause");
}

void searchByPrice() {
    ClearConsole();
    cout << "Enter minimum price: ";
    double minPrice;
    cin >> minPrice;
    cout << "Enter maximum price: ";
    double maxPrice;
    cin >> maxPrice;

    bool found = false;
    for (int i = 0; i < productCount; ++i) {
        if (warehouse[i].price >= minPrice && warehouse[i].price <= maxPrice) {
            cout << i + 1 << ". " << warehouse[i].name << " - " << warehouse[i].price << " UAH\n";
            found = true;
        }
    }
    if (!found) cout << "No products found in this price range.\n";
    system("pause");
}

void searchByGroup() {
    ClearConsole();
    cout << "Enter product group: ";
    string group;
    getline(cin >> ws, group);

    bool found = false;
    for (int i = 0; i < productCount; ++i) {
        if (warehouse[i].group == group) {
            cout << i + 1 << ". " << warehouse[i].name << " (" << warehouse[i].group << ")\n";
            found = true;
        }
    }
    if (!found) cout << "No products found in this group.\n";
    system("pause");
}

void searchByArrivalDate() {
    ClearConsole();
    cout << "Enter arrival date (YYYY-MM-DD): ";
    string date;
    getline(cin >> ws, date);

    bool found = false;
    for (int i = 0; i < productCount; ++i) {
        if (warehouse[i].arrivalDate == date) {
            cout << i + 1 << ". " << warehouse[i].name << " (Arrived: " << warehouse[i].arrivalDate << ")\n";
            found = true;
        }
    }
    if (!found) cout << "No products found with this arrival date.\n";
    system("pause");
}

void searchByExpiryDate() {
    ClearConsole();
    cout << "Enter expiry date (YYYY-MM-DD): ";
    string date;
    getline(cin >> ws, date);

    bool found = false;
    for (int i = 0; i < productCount; ++i) {
        if (warehouse[i].expiryDate == date) {
            cout << i + 1 << ". " << warehouse[i].name << " (Expires: " << warehouse[i].expiryDate << ")\n";
            found = true;
        }
    }
    if (!found) cout << "No products found with this expiry date.\n";
    system("pause");
}

void sortByPrice() {
    for (int i = 0; i < productCount - 1; ++i) {
        for (int j = i + 1; j < productCount; ++j) {
            if (warehouse[i].price > warehouse[j].price)
                swap(warehouse[i], warehouse[j]);
        }
    }
    saveProductsToFile("products.txt");
    cout << "Sorted by price.\n";
    system("pause");
}

void sortByGroup() {
    for (int i = 0; i < productCount - 1; ++i) {
        for (int j = i + 1; j < productCount; ++j) {
            if (warehouse[i].group > warehouse[j].group)
                swap(warehouse[i], warehouse[j]);
        }
    }
    saveProductsToFile("products.txt");
    cout << "Sorted by group.\n";
    system("pause");
}

void sortMenu() {
    const char* sortItems[] = {
        "By price",
        "By group",
        "Back"
    };
    const int sortSize = sizeof(sortItems) / sizeof(sortItems[0]);

    while (true) {
        ClearConsole();
        int choice = ShowMenu(sortItems, sortSize, 5, 2);
        switch (choice) {
        case 0: sortByPrice(); break;
        case 1: sortByGroup(); break;
        default: return;
        }
    }
}

void searchMenu() {
    const char* searchItems[] = {
        "By name",
        "By manufacturer",
        "By price",
        "By group",
        "By arrival date",
        "By expiry date",
        "Back"
    };
    const int searchSize = sizeof(searchItems) / sizeof(searchItems[0]);

    while (true) {
        ClearConsole();
        int choice = ShowMenu(searchItems, searchSize, 5, 2);
        switch (choice) {
        case 0: searchByName(); break;
        case 1: searchByManufacturer(); break;
        case 2: searchByPrice(); break;
        case 3: searchByGroup(); break;
        case 4: searchByArrivalDate(); break;
        case 5: searchByExpiryDate(); break;
        case 6: return;
        }
    }
}