#include <iostream>
#include <windows.h>
#include <ctime>
#include "Prototypes.h"
#include "Constants.h"

//Для цветного текста
#include <conio.h>
#include <stdio.h>

#define random(a,b) a+rand()%b+1-a;
#define line cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Cards
{
    int suit;     //масть
    int nominal;  //номинал
    bool flag;    //скрывать масть или нет
};

//Создаём общую "колоду" карт для игры (через динамический массив структур) - работает (=^-^=)
Cards* createDeck(int n, int s)
{
    Cards* deck = new Cards[n];
    for (int i = 0; i < 13; i++)
    {
        deck[i].suit = s;
        deck[i].nominal = i + 1;
        deck[i].flag = false;
    }
    s += 1;
    for (int i = 13; i < 26; i++)
    {
        deck[i].suit = s;
        deck[i].nominal = i + 1 - 13;
        deck[i].flag = false;
    }
    s += 1;
    for (int i = 26; i < 39; i++)
    {
        deck[i].suit = s;
        deck[i].nominal = i + 1 - 26;
        deck[i].flag = false;
    }
    s += 1;
    for (int i = 39; i < 52; i++)
    {
        deck[i].suit = s;
        deck[i].nominal = i + 1 - 39;
        deck[i].flag = false;
    }

    s = Hearts;
    for (int i = 52; i < 65; i++)
    {
        deck[i].suit = s;
        deck[i].nominal = i + 1 - 52;
        deck[i].flag = false;
    }
    s += 1;
    for (int i = 65; i < 78; i++)
    {
        deck[i].suit = s;
        deck[i].nominal = i + 1 - 65;
        deck[i].flag = false;
    }
    s += 1;
    for (int i = 78; i < 91; i++)
    {
        deck[i].suit = s;
        deck[i].nominal = i + 1 - 78;
        deck[i].flag = false;
    }
    s += 1;
    for (int i = 91; i < 104; i++)
    {
        deck[i].suit = s;
        deck[i].nominal = i + 1 - 91;
        deck[i].flag = false;
    }
    return deck;
}

//Выводим эту колоду на экран
void showDeck(Cards*& deck)
{
    int size1 = _msize(deck) / sizeof(deck[0]);
    for (int i = 0; i < size1; i++)
    {
        if (deck[i].suit == Hearts || deck[i].suit == Diamonds) setColour(Red);
        else setColour(Black);

        cout << char(deck[i].suit);

        switch (deck[i].nominal)
        {
        case 1:
            cout << "A" << " ";
            break;
        case 11:
            cout << "J" << " ";
            break;
        case 12:
            cout << "Q" << " ";
            break;
        case 13:
            cout << "K" << " ";
            break;
        default:
            cout << deck[i].nominal << " ";;
            break;
        }

        if (i == 12 || i == 25 || i == 38 || i == 51 || i == 64 || i == 77 || i == 90) cout << endl;
    }
    setColour(Black);
}

//Выводим колоду оставшихся карт
void showDeckLeft(Cards*& deck)
{
    int size1 = _msize(deck) / sizeof(deck[0]);
    if (size1 == 0) cout << "Empty :)" << endl;
    for (int i = 0; i < size1; i++)
    {
        setColour(Black);
        cout << "** ";
        if (i == 9 || i == 19 || i == 29 || i == 39 || i == 49) cout << endl;
    }
    
}

//Перемешиваем элементы в общей "колоде" карт
void suetaDeck(Cards* deck)
{
    int size = _msize(deck) / sizeof(deck[0]);
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        index = random(i, size - 1);
        swap(deck[i].suit, deck[index].suit);
        swap(deck[i].nominal, deck[index].nominal);
    }
}

//Удаление карты из массива deck
Cards* deleteCard(Cards*& deck)
{
    int size = _msize(deck) / sizeof(deck[0]);
    Cards* buf = new Cards[size - 1];
    for (int i = 0; i < size - 1; i++)
    {
        buf[i] = deck[i];
    }
    delete[]deck;
    deck = buf;
    return deck;
}

//Копирование элемента deck в field
void copyCard(Cards* deck, Cards field[sizeFLine][sizeFColumn])
{
    int sizeDeck = _msize(deck) / sizeof(deck[0]);
    bool flag = false;
    for (int i = 0, k = sizeDeck - 1; i < sizeFColumn; i++)
    {
        for (int j = 0; j < sizeFLine; j++)
        {
            if (field[i][j].suit == 0)
            {
                field[i][j].suit = deck[k].suit;
                field[i][j].nominal = deck[k].nominal;
                field[i][j].flag = deck[k].flag;
                flag = true;
                break;
            }
        }
        if (flag == true) break;
    }
}

/*Создаём игровое поле размером 104х10 - 104 карты на 10 столбцов(наихудишй вариант)
Осуществляется вызов функций copyCard и deleteCard (копировать и удалить одну карту)*/
Cards* createField(Cards*& deck, Cards field[sizeFLine][sizeFColumn])
{
    int sizeDeck = _msize(deck) / sizeof(deck[0]);
    while (sizeDeck != 50)
    {
        copyCard(deck, field);
        deleteCard(deck);
        sizeDeck--;
    }
    return deck;
}

//Вывод игрового поля field со скрытыми элементами
void showField(Cards field[sizeFLine][sizeFColumn])
{
    setColour(Black);
    int counter = 0; //счётчик для вывода номера строк
    //Вывод подписей столбцов
    cout << "\t";
    for (int i = 0; i < sizeFColumn; i++)
    {
        cout << i + 1 << "\t";
    }
    cout << endl;
    //Вывод самого массива с подписью строчек
    for (int i = 0; i < sizeFLine; i++)
    {
        counter = 0;
        for (int j = 0; j < sizeFColumn; j++)
        {
            if (field[i][j].suit != 0)
            {
                setColour(Black);
                cout << i + 1 << "\t";
                break;
            }
            else counter++;
        }
        if (counter == 10) break;
        //Вывод игрового поля с подписью строчек
        for (int j = 0; j < sizeFColumn; j++)
        {
            if (field[i][j].suit == Hearts || field[i][j].suit == Diamonds) setColour(Red);
            else setColour(Black);

            if (field[i][j].flag == false && field[i][j].suit != 0)
            {
                setColour(Black);
                cout << "**" << "\t";
            }
            else
            {
                if (field[i][j].flag == true && field[i][j].suit != 0)
                {
                    cout << char(field[i][j].suit);
                    switch (field[i][j].nominal)
                    {
                    case 1:
                        cout << "A" << "\t";
                        break;
                    case 11:
                        cout << "J" << "\t";
                        break;
                    case 12:
                        cout << "Q" << "\t";
                        break;
                    case 13:
                        cout << "K" << "\t";
                        break;
                    default:
                        cout << field[i][j].nominal << "\t";
                        break;
                    }
                } 
                else
                {
                    cout << "  \t";
                }
            }
        }
        cout << endl;
    }
}

/*Первоначальный показ элементов в поле field
flag = false - карта скрыта, flag = true, карта открыта*/
void makeTrue(Cards* deck)
{
    //flag = false - карта скрыта, flag = true, карта открыта
    deck[50].flag = true;
    deck[51].flag = true;
    deck[52].flag = true;
    deck[53].flag = true;
    deck[54].flag = true;
    deck[55].flag = true;
    deck[56].flag = true;
    deck[57].flag = true;
    deck[58].flag = true;
    deck[59].flag = true;
}

/*Функция подсчёта количества уже собранных карт по масти и номиналу с конца столбца поля field,
т.е. сколько их можно перенести с выбранного столбца*/
int checkSimCards(Cards field[sizeFLine][sizeFColumn], int col1, int counter1)
{
    int simCard1 = 1; //По умолчанию всегда можно перенести одну карту
    for (int i = counter1; i > 1; i--)
    {
        if (field[i - 1][col1 - 1].suit == field[i - 2][col1 - 1].suit && field[i - 1][col1 - 1].flag == true && field[i - 2][col1 - 1].flag == true)
        {
            if (field[i - 1][col1 - 1].nominal == (field[i - 2][col1 - 1].nominal - 1))
            {
                simCard1++;
            }
            else break;
        }
        else break;
    }
    if (simCard1 > 1) cout << "Number of cards you can move: " << simCard1 << endl;
    return simCard1;
}

//Проверка количества карт возможных для переноса
int checkSimCard(Cards field[sizeFLine][sizeFColumn], int col1, int counter1)
{
    int simCard2 = 1; //По умолчанию всегда можно перенести одну карту
    for (int i = counter1; i > 1; i--)
    {
        if (field[i - 1][col1].suit == field[i - 2][col1].suit && field[i - 1][col1].flag == true && field[i - 2][col1].flag == true)
        {
            if (field[i - 1][col1].nominal == (field[i - 2][col1].nominal - 1))
            {
                simCard2++;
            }
            else break;
        }
        else break;
    }
    return simCard2;
}

//Пернос карты или нескольких карт из одной строки в другую
void moveCard(Cards field[sizeFLine][sizeFColumn], int col1, int col2)
{
    //Подсчёт количества элементов в столбце, откуда берём карты
    int counter1 = 0;
    for (int i = 0; i < sizeFLine; i++)
    {
        if (field[i][col1 - 1].suit != 0) counter1++;
        else break;
    }
    //cout << counter1 << endl;
    //Подсчёт количества элементов в столбце, куда переносим карты
    int counter2 = 0;
    for (int i = 0; i < sizeFLine; i++)
    {
        if (field[i][col2 - 1].suit != 0) counter2++;
        else break;
    }
    //cout << counter2 << endl;

    int quant = checkSimCards(field, col1, counter1); //Посчитали, сколько карт можно перенести (по умолчанию одну)

    if (quant == 1)
    {
        //номинал - 1, чтобы условно 2 переместить на 3: если 2 == 3-1, то ок
        if (field[counter1 - 1][col1 - 1].nominal == (field[counter2 - 1][col2 - 1].nominal - 1) || counter2 == 0)
        {
            field[counter2][col2 - 1].suit = field[counter1 - 1][col1 - 1].suit;
            field[counter2][col2 - 1].nominal = field[counter1 - 1][col1 - 1].nominal;
            field[counter2][col2 - 1].flag = field[counter1 - 1][col1 - 1].flag;

            if (counter1 > 1) field[counter1 - 2][col1 - 1].flag = true;

            field[counter1 - 1][col1 - 1].suit = 0;
            field[counter1 - 1][col1 - 1].nominal = 0;
            field[counter1 - 1][col1 - 1].flag = 0;
        }
        else
        {
            setColour(Black);
            cout << "You can't move such way!" << endl << "Please, choose another card!" << endl;
            system("pause");
        }
    }
    //Второй путь, если мы можем переместить больше карт, чем одну
    else
    {
        int userQuant;
        setColour(Black);
        /*Это нужно для того, что если у меня будет две похожих окончания колод на поле field, я смогу переместить не все карты
          одинаковой масти, а только несколько*/
        cout << "How many cards you wish to move? (max is: " << quant << "): ";
        cin >> userQuant;
        //Проверка на то, чтобы количество карт было больше нуля и не больше quant'a
        while (userQuant < 1 || userQuant > quant)
        {
            cout << "Error! Please, input correct quantity: ";
            cin >> userQuant;
        }
        //Проверяем выбранную карту, от которой поль-ль хочет выполнить перемещение с последней в том столбце, куда перемещаем, можно ли
        //номинал -1, чтобы условно 2 переместить на 3: если 2 == 3-1, то ок
        int userQ = userQuant;
        if (field[counter1 - userQuant][col1 - 1].nominal == (field[counter2 - 1][col2 - 1].nominal - 1) || counter2 == 0)
        {
            if (field[counter1 - userQ - 1][col1 - 1].flag == false) field[counter1 - userQ - 1][col1 - 1].flag = true;

            for (int i = counter2; i < counter2 + userQuant; i++)
            {
                field[i][col2 - 1].suit = field[counter1 - userQ][col1 - 1].suit;
                field[i][col2 - 1].nominal = field[counter1 - userQ][col1 - 1].nominal;
                field[i][col2 - 1].flag = field[counter1 - userQ][col1 - 1].flag;

                field[counter1 - userQ][col1 - 1].suit = 0;
                field[counter1 - userQ][col1 - 1].nominal = 0;
                field[counter1 - userQ][col1 - 1].flag = 0;
                userQ--;
            }
        }
        else
        {
            /*Это нужно для того, что если у меня будет две похожих окончания колод на поле field, я смогу переместить не все карты
            одинаковой масти, а только несколько*/
            cout << "Error! This card is incorrect!" << endl;
            system("pause");
        }
    }
}

//Копирование 10 карт из deck в field: по 1 карте в каждый столбец
void copyTenCards(Cards* deck, Cards field[sizeFLine][sizeFColumn])
{
    int sizeDeck1 = _msize(deck) / sizeof(deck[0]); //Размер массива deck (оставшихся карт)
    int counter3;       //Подсчёт числа элементов в столбце
    int counter4 = 0;   //Номер столбца, в котором подсчитываются элементы
    
    while (counter4 < 10)
    {
        counter3 = 0;
        for (int i = 0; i < sizeFLine; i++)
        {
            if (field[i][counter4].suit != 0) counter3++;
            else break;
        }
        deck[sizeDeck1 - 1 - counter4].flag = true;
        field[counter3][counter4] = deck[sizeDeck1 - 1 - counter4];
        counter4++;
    }
}

//Добавление новых 10-ти карт из оставшихся в массиве deck на поле в field
Cards* delTenCards(Cards*& deck)
{
    int sizeDeck2 = _msize(deck) / sizeof(deck[0]); //Размер массива deck (оставшихся карт)

    Cards* buf = new Cards[sizeDeck2 - 10];
    for (int i = 0; i < sizeDeck2 - 10; i++)
    {
        buf[i] = deck[i];
    }
    delete[]deck;
    deck = buf;
    return deck;
}

//Проверка, остались ли элементы в deck
bool checkDeck(Cards* deck)
{
    bool fact;
    if (_msize(deck) / sizeof(deck[0]) > 0) fact = true;
    else fact = false;
    return fact;
}

//Копирование собранной колоды в deck2
void copyPack(Cards field[sizeFLine][sizeFColumn], Cards deck2[amDeck2], int col)
{
    int counter6 = 0;
    int size2 = 0;
    //Посчитаем кол-во элементов в копируемой в deck2 колонке
    for (int i = 0; i < sizeFLine; i++)
    {
        if (field[i][col].suit != 0) counter6++;
        else break;
    }
    //Определение размера deck2
    for (int i = 0; i < amDeck2; i++)
    {
        if (deck2[i].nominal != 0) size2++;
        else break;
    }
    //Копирование собранных элементов из field'a в deck2
    for (int i = counter6 - 1; i >= counter6 - 13; i--)
    {
        deck2[size2] = field[i][col];
        field[i][col].suit = 0;
        field[i][col].nominal = 0;
        field[i][col].flag = 0;
        size2++;
    }
    if (counter6 - 13 >= 0)
    {
        if (counter6 > 13)
        {
            field[counter6 - 14][col].flag = true;
        }
    }
}

//Проверка столбцов поля field на собранность колоды от А до К
void packToWin(Cards field[sizeFLine][sizeFColumn], Cards deck2[amDeck2])
{
    int counter5;   //Подсчёт числа элементов в столбце
    int col = 0;    //Номер столбца, в котором подсчитываются элементы
    int pack;       //Подсчёт количества элементов в столбце по порядку с совпадением масти

    //Считаем количество элементов в колонке
    //Мне нужно это делать 10 раз, т.е. проверить каждый столбец
    while (col < 10)
    {
        counter5 = 0;
        pack = 0;
        //Считаем число элементов в столбце
        for (int i = 0; i < sizeFLine; i++)
        {
            if (field[i][col].suit != 0) counter5++;
            else break;
        }
        //Здесь мы получаем наш counter5 cout << counter5 << " ";
        if (counter5 >= 13) //в любом случае, если в колонке не будет "лишних" карт, минимум карт для сбора - 13
        {
            if (field[counter5 - 1][col].nominal == 1)
            {
                for (int k = counter5; k - 2 >= 0; k--)
                {
                    if (field[k - 1][col].suit == field[k - 2][col].suit && field[k - 1][col].nominal + 1 == field[k - 2][col].nominal)///
                    {
                        pack++;
                        if (pack == 12)
                        {
                            copyPack(field, deck2, col);
                        }
                    }
                    else break;
                }
            }
            else break;
        }
        col++;
    }
}

//Вывод собранных карт deck2
void showDeck2(Cards deck2[amDeck2])
{
    int m = 0; //ставить endl на каждой новой собранной колоде
    for (int i = 0; i < amDeck2; i++)
    {
        if (deck2[i].suit == 0) break;
        if (deck2[i].suit == Hearts || deck2[i].suit == Diamonds) setColour(Red);
        else setColour(Black);
        cout << char(deck2[i].suit);
        switch (deck2[i].nominal)
        {
        case 1:
            cout << "A" << "  ";
            break;
        case 11:
            cout << "J" << "  ";
            break;
        case 12:
            cout << "Q" << "  ";
            break;
        case 13:
            cout << "K" << "  ";
            break;
        default:
            cout << deck2[i].nominal << "  ";
            break;
        }
        m++;
        if (m % 13 == 0) cout << endl;
    }
}

//Проверка на победу
int checkWin(Cards field[sizeFLine][sizeFColumn], Cards deck2[amDeck2], int status = 2, int counter = 0)
{
    //Проверяем последний элемент deck2, если он не нулевой, значит все колоды собраны
    if (deck2[103].suit != 0)
    {
        //Проверяем, что игровое поле field пустое
        for (int i = 0; i < sizeFLine; i++)
        {
            for (int j = 0; j < sizeFColumn; j++)
            {
                if (field[i][j].suit == 0) counter++;
                else break;
            }
        }
        if (counter == sizeFLine * sizeFColumn)
        {
            status = 1;
            return status;
        }
    }
    else
    {
        status = 2;
        return status;
    }
}

//Проверка на поражение
int checkLoose(Cards field[sizeFLine][sizeFColumn], Cards* deck, int status = 2)
{
    int col1 = 0; //Cравниваемая "колонка" поля
    int col2 = 0; //Номер колонок поля, с которыми сравниваем
    //Подсчёт номера последних карт в "колонках"
    int counter1 = 0, counter2 = 0;
    //Если по итогу ни один элемент нельзя никуда переместить
    bool flag = false;

    //Проверяем на наличие "запасные" карты, при проигрыше их не должно быть
    if (_msize(deck) / sizeof(deck[0]) == 0)
    {
        //Сначала проверяем, есть ли пустые столбцы, где нет карт
        for (int i = 0; i < sizeFColumn; i++)
        {
            if (field[0][i].nominal == 0)
            {
                status = 2;
                return status;
            }
        }
        //Далее проверяем, если в колонке доступен только 1 элемент для перемещения, сверяем его со всеми последними в других колонках
        int col1 = 0; //Cравниваемая "колонка" поля
        int col2 = 0; //Номер колонок поля, с которыми сравниваем
        //Подсчёт номера последних карт в "колонках"
        int counter1 = 0, counter2 = 0;
        //Cколько карт можно перенести (по умолчанию одну)
        int quant;

        //Проверяем на наличие "запасные" карты, при проигрыше их не должно быть, если они есть, их всегда можно добавить на поле
        if (_msize(deck) / sizeof(deck[0]) == 0)
        {
            while (col1 != 10 && col2 != 10)
            {
                counter1 = 0;
                for (int i = 0; i < sizeFLine; i++)
                {
                    if (field[i][col1].suit != 0)counter1++;
                    else break;
                }

                for (int j = 0; j < sizeFLine; j++)
                {
                    if (field[j][col2].suit != 0) counter2++;
                    else break;
                }

                int quant = checkSimCard(field, col1, counter1); //Посчитали, сколько карт можно перенести (по умолчанию одну)

                if (quant == 1)
                {
                    if (field[counter1 - 1][col1].nominal + 1 == field[counter2 - 1][col2].nominal || counter2 == 0)
                    {
                        status = 2;
                        return status;
                    }
                    else
                    {
                        col2++;
                        counter2 = 0;
                    }
                }
                else
                {
                    if (field[counter1 - quant][col1].nominal + 1 == field[counter2 - 1][col2].nominal || counter2 == 0)
                    {
                        status = 2;
                        return status;
                    }
                    else
                    {
                        col2++;
                        counter2 = 0;
                    }
                }

                if (col2 == 10)
                {
                    col1++;
                    col2 = 0;
                    counter1 = 0;
                    counter2 = 0;
                }
                if (col1 == 10)
                {
                    status = 3;
                    return status;
                }
            }
        }
    }
    else
    {
        status = 2;
        return status;
    }
}

int main()
{ 
    srand(time(NULL));
    //Вывод меню (с размером окна)
    sizeWindow(WIDTH, HIGHT, TOP, LEFT);
    menu(xb, yb);
    //Нам необходимо 2 колоды карт (104шт., т.е. 4 масти по 13 карт дважды): 
    Cards* deck = createDeck(104, Hearts);

    //Вторая колода, куда будем записывать собранные карты
    Cards deck2[amDeck2]{};
    
    /*Переменная победы / поражения:
    - 2 - игра идёт;
    - 1 - победа;
    - 0 - поражение*/
    int status = 2;

    //Перемешиваем элементы в общей колоде карт deck
    suetaDeck(deck);
 
    //Новый двумерный массив для создания игрового поля (постоянного размера 10 колонок, каждая по 104 элемента)
    Cards field[sizeFLine][sizeFColumn]{}; //по началу заполнен нулями
    
    //Сделаем нескрытые элементы на будущем поле field
    makeTrue(deck);

    /*Создание поля field:
    Функция переноса карт из колоды deck на поле field.
      Содержит в себе:
      - функцию копирования карт из deck в field;
      - функцию удаления карт из deck'a.
    */
    createField(deck, field);

    while (status == 2)
    {
        system("cls");
        //Вывод игрового поля
        //Тут будут координаты
        showField(field);
        cout << endl;

        //Вывод отображения оставшихся карт (deck)
        setColour(Black);
        cout << "Left cards: " << endl;
        showDeckLeft(deck);
        cout << endl << endl;

        //Вывод отображения собранных карт (deck2)
        cout << "Collected cards: " << endl;
        showDeck2(deck2);
        setColour(Black);
        line;

        int col1, col2;
        bool fact;
        
        cout << "Input the number of column you wish to take the card from (1 - 10) \n(please push 0, if you wish to add 10 new cards): " ;
        cin >> col1;
        switch (col1)
        {
            //Проверка массива deck, остались ли там ещё карты. Если нет, то вывести ошибку.
            case 0:
                fact = checkDeck(deck);
                if (fact == true)
                {
                    //функция на то, чтобы добавить 10 карт
                    copyTenCards(deck, field);
                    //Удаляем добавленные 10 карт из deck
                    delTenCards(deck);
                    system("cls");
                    break;
                }
                else
                {
                    cout << "Error! There are no cards left!" << endl;
                    system("pause");
                    system("cls");
                    break;
                }
            default: 
                while (col1 < 1 || col1 > 10)
                {
                    cout << "Incorrect number! Please, input column number from 1 to 10: ";
                    cin >> col1;
                }
                cout << "Input the number of column you wish to put your card to (1 - 10): ";
                cin >> col2;
                while (col2 < 1 || col2 > 10)
                {
                    cout << "Incorrect number! Please, input column number from 1 to 10: ";
                    cin >> col2;
                }
                //Перемещение карты или нескольких карт
                moveCard(field, col1, col2);
                //Проверка на то, что собрали колоду
                packToWin(field, deck2);
                system("cls");
                //Вывод игрового поля
                showField(field);
                //Вывод отображения оставшихся карт (deck)
                setColour(Black);
                cout << "Left cards: " << endl;
                showDeckLeft(deck);
                cout << endl << endl;
                //Вывод отображения собранных карт (deck2)
                cout << "Collected cards: " << endl;
                showDeck2(deck2);
                setColour(Black);
                line;

                //Проверка на победу
                if (status == 2) status = checkWin(field, deck2);

                //Проверка на поражение
                if (status == 2) status = checkLoose(field, deck);
        }
    }
    if (status == 1)
    {
        system("cls");
        setColour(Black);
        cout << "Collected cards:" << endl;
        showDeck2(deck2);
        setColour(Black);
        cout << endl << endl << char(1) << " Congratulations! You won! " << char(1) << endl << endl;

        system("pause");
    }
    else if (status == 3)
    {
        setColour(Black);
        cout << endl << "There are no available moves anymore!" << endl << ":c Sorry! You've lost! :c" << endl;
    }
}


