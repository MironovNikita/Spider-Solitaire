#pragma once

const int NotUsed = system("color 20"); //Цвет фона игрового поля

enum CardsColour
{
    Black,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Brown,
    LightGray,
    DarkGray,
    LightBlue,
    LightGreen,
    LightCyan,
    LightRed,
    LightMagenta,
    Yellow,
    White
};

enum Suits //Hearts - черви, Diamonds - бубны, Clubs - крести, Spades - пики
{
    Hearts = 3,
    Diamonds,
    Clubs,
    Spades
};

//Размер игрового поля field
int const sizeFLine = 104;
int const sizeFColumn = 10;

//Размер deck2 (собранные карты)
int const amDeck2 = 104;

//Окно программы
const int WIDTH = 1500;
const int HIGHT = 900;
const int TOP = 180;
const int LEFT = 100;
const int yb = HIGHT / 60;
const int xb = WIDTH / 22;