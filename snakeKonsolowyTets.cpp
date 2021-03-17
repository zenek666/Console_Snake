// snakeKonsolowyTets.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

void drawAll(int* bodyX, int* bodyY, int sizeBody) {

    // rozmiar planszy to 50:20
    // rozmiar do poruszania 48:18

    for (int i = 0; i < 50; i++)
        cout << "#";

    cout << endl;

    for (int i = 0; i < 20; i++) {

        cout << "#";

        for (int j = 0; j < 48; j++) {

            bool doFit = false;

            for (int k = 0; k < sizeBody; k++) {

                if (bodyX[k] == j && bodyY[k] == i) {

                    cout << 'o';

                    doFit = true;
                    break;
                }
            }

            if(!doFit)
                cout << " ";
        }

        cout << "#\n";
    }

    for (int i = 0; i < 50; i++)
        cout << "#";
}

void gotoxy(int x, int y) {

    COORD c;

    c.X = x;
    c.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void respFood(int* foodX, int* foodY, bool newValues = true) {

    if (newValues) {

        *foodX = (int)rand() % 48;
        *foodY = (int)rand() % 19;
    }
    else {

        gotoxy(*foodX, *foodY);

        cout << "x";
    }
}

void update(int* bodyX, int* bodyY, int sizeBody, int* foodX, int* foodY) {

    for (int i = 0; i < 20; i++) {

        for (int j = 0; j < 48; j++) {

            if (foodX != NULL) {

                if (*foodX == j && *foodY == i) {

                    respFood(foodX, foodY, false);
                }
            }

            for (int k = 0; k < sizeBody; k++) {

                if (bodyX[k] == j && bodyY[k] == i) {

                    gotoxy(j+1, i+1);

                    cout << 'o';

                    break;
                }
            }
        }
    }

    gotoxy(bodyX[0], bodyY[0]);
}

void clear(int* bodyX, int* bodyY, int sizeBody) {

    for (int i = 0; i < 20; i++) {

        for (int j = 0; j < 48; j++) {

            bool doFit = false;

            for (int k = 0; k < sizeBody; k++) {

                if (bodyX[k] == j && bodyY[k] == i) {

                    gotoxy(j+1, i+1);

                    cout << " ";

                    doFit = true;
                    break;
                }
            }
        }
    }
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

    int moveFieldX = 48;
    int moveFieldY = 18;

    int* foodX = new int(1);
    int* foodY = new int(1);
    
    bool doEnd = false;

    drawAll(bodyX, bodyY, sizeBody);

    respFood(foodX, foodY);

    while (!doEnd) {

        bool doFoodAte = false;

        switch (_getch()) {

            case 27:
            
                doEnd = true;
                break;

            case 119:

                clear(bodyX, bodyY, sizeBody);

                for (int i = 0; i < sizeBody; i++) {

                    if (bodyY[i] - 1 >= 0)
                        bodyY[i]--;
                }

                doFoodAte = false;

                if (foodX != NULL) {

                    if (*foodX == bodyX[0] && *foodY == bodyY[0]) {

                        respFood(foodX, foodY);
                    }
                }

                update(bodyX, bodyY, sizeBody, foodX, foodY);

                break;

            case 115:

                clear(bodyX, bodyY, sizeBody);

                for (int i = 0; i < sizeBody; i++) {

                    if (bodyY[i] + 1 < 20)
                        bodyY[i]++;
                }

                if (foodX != NULL) {

                    if (*foodX == bodyX[0] && *foodY == bodyY[0]) {

                        respFood(foodX, foodY);
                    }
                }

                update(bodyX, bodyY, sizeBody, foodX, foodY);

                break;

            case 97:

                clear(bodyX, bodyY, sizeBody);

                for (int i = 0; i < sizeBody; i++) {

                    if (bodyX[i] - 1 >= 0)
                        bodyX[i]--;
                }

                if (foodX != NULL) {

                    if (*foodX == bodyX[0] && *foodY == bodyY[0]) {

                        respFood(foodX, foodY);
                    }
                }

                update(bodyX, bodyY, sizeBody, foodX, foodY);

                break;

            case 100:

                clear(bodyX, bodyY, sizeBody);

                for (int i = 0; i < sizeBody; i++) {

                    if (bodyX[i] + 1 < 48)
                        bodyX[i]++;
                }

                if (foodX != NULL) {

                    if (*foodX == bodyX[0] && *foodY == bodyY[0]) {

                        respFood(foodX, foodY);
                    }
                }

                update(bodyX, bodyY, sizeBody, foodX, foodY);

                break;
        }
    }
}

