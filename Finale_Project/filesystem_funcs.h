#pragma once
#include <string>
#include "warehouse_funcs.h"

void saveProductsToFile(const std::string& filename);
void loadProductsFromFile(const std::string& filename);