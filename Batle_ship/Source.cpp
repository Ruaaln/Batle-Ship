#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstdlib>
#include <Windows.h>
#include <chrono>
#include <thread>

using namespace std;



//0 - Qara, 1 - Göy, 2 - Yaşıl, 3 - Firuzəyi, 4 - Qırmızı, 5 - Bənövşəyi,
//6 - Sarı, 7 - Ağ(standart), 8 - Boz, 9 - Açıq göy, 10 - Açıq yaşıl, 
//12 - Açıq qırmızı, 14 - Açıq sarı, 15 - Ağ(parlaq)
void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}



#pragma region BatlrShip

void PrintArr(char** arr, int size, bool opasty) {
    cout << "   |";
    for (size_t i = 0; i < size; i++)
        cout << setw(2) << char(i + 'A');

    cout << "\n---|";
    for (size_t i = 0; i < size; i++)
        cout << "--";
    cout << endl;
    if (opasty) {
        for (size_t i = 0; i < size; i++) {
            cout << setw(3) << i + 1 << "| ";
            for (size_t k = 0; k < size; k++)
                if (arr[i][k] == '~') {
                    SetColor(1);
                    cout << arr[i][k] << " ";
                }
                else if (arr[i][k] == '#') {
                    SetColor(15);
                    cout << arr[i][k] << " ";
                }
                else if (arr[i][k] == 'X') {
                    SetColor(4);
                    cout << arr[i][k] << " ";
                }
                else if (arr[i][k] == '0') {
                    SetColor(8);
                    cout << arr[i][k] << " ";
                }
            SetColor(7);
            cout << endl;
        }
    }
    else {
        for (size_t i = 0; i < size; i++) {
            cout << setw(3) << i + 1 << "| ";
            for (size_t k = 0; k < size; k++)
                if (arr[i][k] == 'X') {
                    SetColor(4);
                    cout << arr[i][k] << " ";
                }
                else if (arr[i][k] == '0') {
                    SetColor(8);
                    cout << arr[i][k] << " ";
                }
                else {
                    SetColor(1);
                    cout << "~" << " ";
                }
            SetColor(7);
            cout << endl;
        }
    }
}

void InitArr(char** arr, int size) {
    for (size_t i = 0; i < size; i++)
        for (size_t k = 0; k < size; k++)
            arr[i][k] = '~';
}

//GPT Komeyi ile yazilib funksiya 
//Nece islediyi aydirndi
bool CanPlaceShip(char** arr, int size, int x, int y, int length, bool isVertical) {
    for (int i = -1; i <= length; i++) {
        for (int j = -1; j <= 1; j++) {
            int nx = x + (isVertical ? i : 0);
            int ny = y + (isVertical ? 0 : i);
            int adjX = nx + (isVertical ? 0 : j);
            int adjY = ny + (isVertical ? j : 0);
            if (adjX >= 0 && adjX < size && adjY >= 0 && adjY < size) {
                if (arr[adjX][adjY] == '#') return false;
            }
        }
    }
    return true;
}

void PlaceShips(char** arr, int size) {
    int ships[] = { 4,
                   3, 3,
                   2, 2, 2,
                   1, 1, 1, 1 };

    for (int s = 0; s < 10; s++) {
        int length = ships[s];
        bool placed = false;

        while (!placed) {
            int x = rand() % size;
            int y = rand() % size;
            bool isVertical = rand() % 2;

            if (isVertical && x + length >= size) continue;
            if (!isVertical && y + length >= size) continue;

            if (CanPlaceShip(arr, size, x, y, length, isVertical)) {
                for (int i = 0; i < length; i++) {
                    int nx = x + (isVertical ? i : 0);
                    int ny = y + (isVertical ? 0 : i);
                    arr[nx][ny] = '#';
                }
                placed = true;
            }
        }
    }
}

int Atakt(char** arr, int size, int X, int Y) {
    if (X > 0 && X < size + 1 && Y > 0 && Y < size + 1) {
        X--;
        Y--;
        if (arr[Y][X] == '~') {
            arr[Y][X] = 'X';
            return 2;
        }
        else if (arr[Y][X] == '#') {
            arr[Y][X] = '0';
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return -1;
    }

}

void BattleShip() {
    const int size = 10;
    int Bot = 0;

    cout << "[1] Player vs Player" << endl;
    cout << "[2] Player vs Bot" << endl;
    cout << "Secim: ";
    cin >> Bot;
    if (Bot == 1) {
        Bot--;
    }
    else if (Bot == 2) {
        Bot--;
    }
    else {
        Bot = 0;
    }

    char** ArrPlayer = new char* [size];
    char** ArrBot = new char* [size];

    for (int i = 0; i < size; i++) {
        ArrPlayer[i] = new char[size];
    }
    for (int i = 0; i < size; i++) {
        ArrBot[i] = new char[size];
    }



    InitArr(ArrPlayer, size);
    InitArr(ArrBot, size);
    PlaceShips(ArrPlayer, size);
    PlaceShips(ArrBot, size);

    int  LineY, n, x;
    int BotYon, BotX, BotY, BotOn = 1;
    char LineX;
    int PlayerShipLen = 0, BotShipLen = 0;
    int Kon = rand() % 2;
    while (true) {
        system("cls");
        if (PlayerShipLen == 20) {
            cout << "Player 2 Win!!" << endl;
            PrintArr(ArrPlayer, size, false);
            break;
        }
        else if (BotShipLen == 20) {
            cout << "Player 1 Win!!" << endl;
            PrintArr(ArrBot, size, false);
            break;
        }

        //0 - Qara, 1 - Göy, 2 - Yaşıl, 3 - Firuzəyi, 4 - Qırmızı, 5 - Bənövşəyi,
        //6 - Sarı, 7 - Ağ(standart), 8 - Boz, 9 - Açıq göy, 10 - Açıq yaşıl, 
        //12 - Açıq qırmızı, 14 - Açıq sarı, 15 - Ağ(parlaq)

        SetColor(2);
        cout << "Player 1 map" << endl << ">--------------------------------------<" << endl;
        x = PlayerShipLen / 2;
        cout << endl << "Player1 ilerleme: ";
        for (size_t i = 0; i < x; i++)
        {
            cout << "#";
        }
        cout << " " << x * 10 << "%" << endl;
        cout << endl;

        SetColor(7);
        if (Bot == 1) {
            PrintArr(ArrPlayer, size, true);
        }
        else {
            PrintArr(ArrPlayer, size, false);
        }
        SetColor(4);

        cout << "\nPlayer 2 map" << endl << ">--------------------------------------<" << endl;
        x = BotShipLen / 2;
        cout << endl << "Player2 ilerleme: ";
        for (size_t i = 0; i < x; i++)
        {
            cout << "#";
        }
        cout << " " << x * 10 << "%" << endl;
        cout << endl;
        SetColor(7);
        PrintArr(ArrBot, size, false);

        //Player 1 atakt
        if (Kon == 0) {
            SetColor(2);
            cout << endl << "Player 1 " << endl;
            cout << "X: ";
            cin >> LineX;
            cout << "Y: ";
            cin >> LineY;

            SetColor(7);

            //chardan her halda indexe cevirme
            if (int(LineX) >= 48 && int(LineX) <= 57) {
                LineX = int(LineX) - 48;
            }
            else if ((int(LineX) >= 65 && int(LineX) <= 90)) {
                LineX = int(LineX) - 64;
            }
            else if (int(LineX) >= 97 && int(LineX) <= 122) {
                LineX = int(LineX) - 96;
            }

            n = Atakt(ArrBot, size, LineX, LineY);
            if (n == 2) {
                cout << "deymedi deymedi" << endl;
                Kon = 1;
            }
            else if (n == 1) {
                cout << "Vurdu" << endl;
                BotShipLen++;
            }
            else if (n == 0) {
                cout << "Invalid input!" << endl;
            }
            else if (n == -1) {
                cout << "Not valid!" << endl;
            }
        }
        //Player 2 atakt
        else {
            if (Bot == 0) {
                SetColor(4);
                cout << endl << "Player 2 " << endl;
                cout << "X: ";
                cin >> LineX;
                cout << "Y: ";
                cin >> LineY;
                SetColor(7);

                if (int(LineX) >= 48 && int(LineX) <= 57) {
                    LineX = int(LineX) - 48;
                }
                else if ((int(LineX) >= 65 && int(LineX) <= 90)) {
                    LineX = int(LineX) - 64;
                }
                else if (int(LineX) >= 97 && int(LineX) <= 122) {
                    LineX = int(LineX) - 96;
                }

                n = Atakt(ArrPlayer, size, LineX, LineY);
                if (n == 2) {
                    cout << "deymedi deymedi" << endl;
                    Kon = 0;
                }
                else if (n == 1) {
                    cout << "Vuruldu" << endl;
                    PlayerShipLen++;
                }
                else if (n == 0) {
                    cout << "Invalid input!" << endl;
                }
                else if (n == -1) {
                    cout << "Not valid!" << endl;
                }
            }
            //Bot Atakt
            else
            {
                BotX = 1 + rand() % (size);
                BotY = 1 + rand() % (size);
                while (Kon == 1) {
                    cout << BotX << " " << BotY << endl;
                    n = Atakt(ArrPlayer, size, BotX, BotY);
                    if (n == 2) {
                        cout << "Ugursuz atis" << endl;
                        Kon = 0;
                    }
                    else if (n == 1) {
                        while (ArrPlayer[BotY - 1][BotX - 1] == 'X' || ArrPlayer[BotY - 1][BotX - 1] == '0') {
                            BotX = rand() % size + 1;
                            BotY = rand() % size + 1;
                        }
                        PlayerShipLen++;
                    }
                    else if (n == 0) {
                        BotX = 1 + rand() % (size);
                        BotY = 1 + rand() % (size);
                    }
                    else if (n == -1) {
                        BotX = 1 + rand() % (size);
                        BotY = 1 + rand() % (size);
                    }
                }


                Kon = 0;
            }
        }
    }
    //massivi silme
    for (int i = 0; i < size; i++) {
        delete[] ArrPlayer[i];
    }
    delete[] ArrPlayer;
}
#pragma endregion




int main() {
    char secim;
    while (true) {
        cout <<
            "[1] Battle ship \n"
            "[q] Quit\n";
        cout << "Enter index: ";
        cin >> secim;

        if (secim == '1') {
            BattleShip();
        }
        else if (secim == 'q' || secim == 'Q') {
            break;
        }
    }

    return 0;
}