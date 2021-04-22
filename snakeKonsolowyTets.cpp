#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

int* bodyX = new int[5];
int* bodyY = new int[5];

int sizeBody = 5;

int fieldX = 50;
int fieldY = 20;

int foodX = 30;
int foodY = 15;

int points = 0;

int direction = 0;

void gotoxy(int x, int y) { // ustawienie pozycji kursora (kreska w konsoli)

    COORD c;

    c.X = x;
    c.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void clearSnake() {

    for (int i = 0; i < sizeBody; i++) {

        gotoxy(bodyX[i], bodyY[i]);
        cout << " ";
    }
}

void drawFrame() {

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

void drawSnake() {

    for (int i = 0; i < sizeBody; i++) {

        gotoxy(bodyX[i], bodyY[i]);
        cout << "o";
    }
}

void drawFood() {

    gotoxy(foodX, foodY);
    cout << "$";
}

void drawPoints(int x, int y) {

    gotoxy(x, y);
    cout << "Punkty: " << points;
}

void keyUse() {

    if (_kbhit()) {

        switch (_getch()) {

        case 27:

            //doEnd = true;
            break;

        case 119: //W

            if (direction != 2)
                direction = 1;
            break;

        case 115: //S

            if (direction != 1)
                direction = 2;
            break;

        case 97: //A

            if (direction != 4)
                direction = 3;
            break;

        case 100: //D

            if (direction != 3)
                direction = 4;
            break;
        }
    }
}

void moving() {

    int *prevBodyX = new int[sizeBody]; // dynamiczne, gdyz nie wiedzialem jak zrobic zwykla tablice o rozmiarze rownym zmiennej
    int *prevBodyY = new int[sizeBody];

    for (int i = 0; i < sizeBody; i++) {

        prevBodyX[i] = bodyX[i];
        prevBodyY[i] = bodyY[i];
    }

    switch (direction) {

        case 1:

            if (bodyY[0] >= 1) {

                bodyY[0]--;

                for (int i = 1; i < sizeBody; i++) {

                    bodyX[i] = prevBodyX[i - 1];
                    bodyY[i] = prevBodyY[i - 1];
                }
            }

            break;

        case 2:

            if (bodyY[0] <= fieldY) {

                bodyY[0]++;

                for (int i = 1; i < sizeBody; i++) {

                    bodyX[i] = prevBodyX[i - 1];
                    bodyY[i] = prevBodyY[i - 1];
                }
            }

            break;

        case 3:

            if (bodyX[0] >= 1) {

                bodyX[0]--;

                for (int i = 1; i < sizeBody; i++) {

                    bodyX[i] = prevBodyX[i - 1];
                    bodyY[i] = prevBodyY[i - 1];
                }
            }

            break;

        case 4:

            if (bodyX[0] <= fieldX - 3) {

                bodyX[0]++;

                for (int i = 1; i < sizeBody; i++) {

                    bodyX[i] = prevBodyX[i - 1];
                    bodyY[i] = prevBodyY[i - 1];
                }
            }

            break;
    }

    delete [] prevBodyX;
    delete [] prevBodyY;
}

void incrementBody() {

    sizeBody++;

    int* newBodyX = new int[sizeBody];
    int* newBodyY = new int[sizeBody];

    for (int i = 0; i < sizeBody - 1; i++) {

        newBodyX[i] = bodyX[i];
        newBodyY[i] = bodyY[i];
    }

    newBodyX[sizeBody - 1] = 0;
    newBodyY[sizeBody - 1] = 0;

    delete[] bodyX;
    delete[] bodyY;

    bodyX = newBodyX;
    bodyY = newBodyY;

    switch (direction) {

        case 1:

            bodyX[sizeBody - 1] = bodyX[sizeBody - 2];
            bodyY[sizeBody - 1] = bodyY[sizeBody - 2] + 1;

            break;

        case 2:

            bodyX[sizeBody - 1] = bodyX[sizeBody - 2];
            bodyY[sizeBody - 1] = bodyY[sizeBody - 2] - 1;

            break;

        case 3:

            bodyX[sizeBody - 1] = bodyX[sizeBody - 2] + 1;
            bodyY[sizeBody - 1] = bodyY[sizeBody - 2];

            break;

        case 4:

            bodyX[sizeBody - 1] = bodyX[sizeBody - 2] - 1;
            bodyY[sizeBody - 1] = bodyY[sizeBody - 2];

            break;
    }
}

void eatingFoodLogic() {

    if (bodyX[0] == foodX && bodyY[0] == foodY) {

        incrementBody();

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

        points++;
    }
}

bool checkDoTouchWall() {

    switch (direction) {

        case 1:

            if (bodyY[0] < 1) {

                return true;
            }

        case 2:

            if (bodyY[0] > fieldY) {

                return true;
            }

        case 3:

            if (bodyX[0] < 1) {

                return true;
            }

        case 4:

            if (bodyX[0] > fieldX - 3) {

                return true;
            }
    }

    return false;
}

bool checkDoAteItself() {

    for (int i = 1; i < sizeBody; i++) {

        if (bodyX[0] == bodyX[i] && bodyY[0] == bodyY[i]) {

            return true;
        }
    }

    return false;
}

int main()
{
    // kod od 346-352 jest potrzebny, aby ukryc konsolowy kursor
    HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = false;
    cursor.dwSize = 1;

    SetConsoleCursorInfo(myconsole, &cursor);

    bodyX[0] = 10;
    bodyY[0] = 10;
    bodyX[1] = 9;
    bodyY[1] = 10;
    bodyX[2] = 8;
    bodyY[2] = 10;
    bodyX[3] = 7;
    bodyY[3] = 10;
    bodyX[4] = 6;
    bodyY[4] = 10;

    drawFrame();
    drawSnake();
    drawFood();
    drawPoints(60, 10);

    while (true) {

        Sleep(100);

        clearSnake();

        keyUse();

        moving();

        if (checkDoTouchWall() || checkDoAteItself())
            break;

        eatingFoodLogic();

        drawFood();
        drawSnake();
        drawPoints(60, 10);
    }
}

