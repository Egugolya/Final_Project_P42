#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "console_stuff.h"
#include "warehouse_funcs.h"
#include "filesystem_funcs.h"
#include <clocale>

using namespace std;

struct Product {
    string name = "";
    int quantity = 0;
    string manufacturer = "";
    double price = 0.0;
    string group = "";
    string arrivalDate = "";
    string expiryDate = "";
};


void addProduct();

void deleteProduct();

void renameProduct();

void changeQuantity();

void showProducts();

void editMenu();

void searchByName();

void searchByManufacturer();

void searchByPrice();

void searchByGroup();

void searchByArrivalDate();

void searchByExpiryDate();

void sortByPrice();

void sortByGroup();

void sortMenu();

void searchMenu();