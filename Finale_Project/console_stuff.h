#pragma once

enum Colors {
    BLACK = 0, WHITE = 7,
};



void SetColor(int, int);

void ShowConsoleCursor(bool);

void SetCursorPosition(int, int);

void ClearConsole();

int ShowMenu(const char*[], int, int, int);