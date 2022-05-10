#include <iostream>
#include <windows.h>
#include <ctime>
#include "Prototypes.h"
#include "Constants.h"

//Для цветного текста
#include <conio.h>
#include <stdio.h>

using namespace std;

void rules() {
    system("cls");
    setColour(Black);
    cout << "Spider Solitaire - 4 suits: rules of the card game.\n\n"
         "Spider of the 4th suit is the most difficult version, where you have to think a lot. On the playing field you can see 54 cards of all suits,\n"
         "which you need to arrange in the correct sequence. There are also 50 cards left in the corner of the screen, which can be used in difficult\n"
         "situations.\n\n"
         
         "Your main task is to clear the playing field of all the cards. To do this, you need to distribute the cards according to the principle of\n"
         "decreasing, for example, a queen can cover a king, a three - a two, and so on in order.Here the oldest suit is the king, the youngest is\n"
         "the ace.\n\n"

         "Accordingly, your chain should be laid out in the order of King, Queen, Jack, 10...2 and end with an Ace. The assembled column automatically\n"
         "disappears from the field and frees up space for further analysis.\n\n"

         "It is considered that the Spider is assembled when each suit is stacked in the correct sequence. If you do not see the necessary cards\n"
         "to continue the game, use the postponed deck located in the corner of the screen.Then new cards will open, which will randomly cover\n"
         "the cards lying in ten columns.\n\n"

         "A player can transfer any number of cards from stack to stack, but provided that the chain consists of the same suit.When the chain is\n"
         "in sequence from King to Ace (of the SAME suit!) when it is collected, it will move to the collected decks.\n\n"
        
         "Good luck!\n"
         "(press ESC to back to menu)"; 

    int key;
    while (true) {
        key = _getch();
        if (key == 27)
        {
            system("cls");
            return;
            menu(xb, yb);
        }
    }
}

int menu(int x = xb, int y = yb) {
    system("cls");
    int key;
    int a = 1;
    while (true) {
        blackMenu();
        gotoxy(64, 13, Black);
        cout << "SPIDER SOLITAIRE";
        gotoxy(x, y, Blue);
        if (y == yb) cout << "NEW GAME";
        else if (y == yb + 2) cout << "RULES";
        else if (y == yb + 4) cout << "EXIT";
        key = _getch();
        switch (key) {
        case 80:
            y += 2;
            break;
        case 72:
            y -= 2;
            break;
        case 27:
            exit(0);
        case 13:
            if (y == yb) return a = 2;
            else if (y == yb + 2) rules();
            else if (y == yb + 4)
            {
                setColour(Black);
                exit(0);
            }
        }
        if (y < yb) y += 6;
        else if (y > yb + 4) y -= 6;
    }
}

void blackMenu() {
    setColour(Black);
    int x = xb;
    int y = yb;
    gotoxy(x, y);
    cout << "NEW GAME";
    y += 2;
    gotoxy(x, y);
    cout << "RULES";
    y += 2;
    gotoxy(x, y);
    cout << "EXIT";
}