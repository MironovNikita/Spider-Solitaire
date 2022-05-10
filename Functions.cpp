#include <iostream>
#include <windows.h>
#include "Constants.h"
using namespace std;

//Присвоение цвета
void setColour(int text)
{
    HANDLE hField = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hField, (WORD)((Green << 4) | text));
}

//Размещение в координатах
void gotoxy(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hConsole, coord);
}

//Размещение в координатах с цветом
void gotoxy(int x, int y, int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hConsole, coord);
    SetConsoleTextAttribute(hConsole, (WORD)((Green << 4) | color));
}


void sizeWindow(int width = 500, int hight = 500, int top = 0, int left = 0) {
    HWND hWindowConsole = GetConsoleWindow();
    MoveWindow(hWindowConsole, top, left, width, hight, true);
}