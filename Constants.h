#pragma once

const int NotUsed = system("color 20"); //���� ���� �������� ����

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

enum Suits //Hearts - �����, Diamonds - �����, Clubs - ������, Spades - ����
{
    Hearts = 3,
    Diamonds,
    Clubs,
    Spades
};

//������ �������� ���� field
int const sizeFLine = 104;
int const sizeFColumn = 10;

//������ deck2 (��������� �����)
int const amDeck2 = 104;

//���� ���������
const int WIDTH = 1500;
const int HIGHT = 900;
const int TOP = 180;
const int LEFT = 100;
const int yb = HIGHT / 60;
const int xb = WIDTH / 22;