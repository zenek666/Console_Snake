// snakeKonsolowyTets.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

void gotoxy(int x, int y) {

    COORD c;

    c.X = x;
    c.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void clear(int fieldX, int fieldY) {

    for (int i = 1; i < fieldX-2; i++) {

        for (int j = 1; j <= fieldY; j++) {

            gotoxy(i, j);
            cout << " ";
        }
    }
}

void clearSnake(int* bodyX, int* bodyY, int sizeBody) {

    for (int i = 0; i < sizeBody; i++) {

        gotoxy(bodyX[i], bodyY[i]);
        cout << " ";
    }
}

void drawFrame(int fieldX, int fieldY) {

    for (int j = 1; j < fieldX; j++) {

        cout << "#";
    }

    cout << endl;

    for (int i = 0; i < fieldY; i++) {

        cout << "#";

        for (int j = 1; j < fieldX-2; j++) {

            cout << " ";
        }

        cout << "#" <<endl;
    }

    for (int j = 1; j < fieldX; j++) {

        cout << "#";
    }
}

void drawSnake(int* bodyX, int* bodyY, int sizeBody) {

    for (int i = 0; i < sizeBody; i++) {

        gotoxy(bodyX[i], bodyY[i]);
        cout << "o";
    }
}

void drawFood(int foodX, int foodY) {

    gotoxy(foodX, foodY);
    cout << "$";
}

void drawPoints(int points, int x, int y) {

    gotoxy(x, y);
    cout << "Punkty: " << points;
}

int main()
{
    HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = false;
    cursor.dwSize = 1;

    SetConsoleCursorInfo(myconsole, &cursor);

    int* bodyX = new int[1];
    int* bodyY = new int[1];

    bodyX[0] = 10;
    bodyY[0] = 10;

    int sizeBody = 1;

    int fieldX = 50;
    int fieldY = 20;

    int foodX = 30;
    int foodY = 15;
    
    bool doEnd = false;

    int direction = 0;

    int points = 0;

    drawFrame(fieldX, fieldY);
    drawSnake(bodyX, bodyY, sizeBody);
    drawFood(foodX, foodY);
    drawPoints(points, 60, 10);

    //dostepna powiezchnia do -3 od szerokosci i - 1 wysokosci

    while (!doEnd) {

        bool doFoodAte = false;

        Sleep(100);

        if (_kbhit()) {

            switch (_getch()) {

            case 27:

                doEnd = true;
                break;

            case 119: //W

                direction = 1;
                break;

            case 115: //S

                direction = 2;
                break;

            case 97: //A

                direction = 3;
                break;

            case 100: //D

                direction = 4;
                break;
            }
        }

        clearSnake(bodyX, bodyY, sizeBody);

        switch (direction) {

            case 1:

                for (int i = 0; i < sizeBody; i++) {

                    if (bodyY[i] > 1)
                        bodyY[i]--;
                }

            break;

            case 2:

                for (int i = 0; i < sizeBody; i++) {

                    if (bodyY[i] < fieldY)
                        bodyY[i]++;
                }

            break;

            case 3:

                for (int i = 0; i < sizeBody; i++) {

                    if (bodyX[i] > 1)
                        bodyX[i]--;
                }

            break;

            case 4:

                for (int i = 0; i < sizeBody; i++) {

                    if (bodyX[i] < fieldX - 3)
                        bodyX[i]++;
                }

            break;
        }

        if (direction > 0) {

            if (bodyX[0] == foodX && bodyY[0] == foodY) {

                while (true) {

                    bool fieldIsClear = false;

                    foodX = rand() % fieldX - 3 + 1;
                    foodY = rand() % fieldY + 1;

                    for (int i = 0; i < sizeBody; i++) {

                        if (bodyX[i] == foodX && bodyY[i] == foodY) {

                            fieldIsClear = false;
                            break;
                        }
                        else
                            fieldIsClear = true;
                    }

                    if (fieldIsClear)
                        break;
                }

                drawFood(foodX, foodY);
                points++;

                drawPoints(points, 60, 10);
            }

            drawSnake(bodyX, bodyY, sizeBody);
        }
    }
}

