#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "console_stuff.h"
#include "warehouse_funcs.h"
#include "filesystem_funcs.h"

using namespace std;

struct Product {
    string name;
    int quantity;
};


void addProduct();

void deleteProduct();

void renameProduct();

void changeQuantity();

void showProducts();

void editMenu();
