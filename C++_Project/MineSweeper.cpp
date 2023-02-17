#define _CRT_NONSTDC_NO_WARNINGS
#include "MineSweeper.h"
#include <stdlib.h>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>

MineSweeper::MineSweeper()
{
}

MineSweeper::~MineSweeper()
{
}

void MineSweeper::showMineMap()
{
    for (int i = 0; i < row; i++) {
        //cout << "\t";
        for (int j = 0; j < col; j++) {
            printMM(i, j);
        }
        cout << endl;
    }
}

void MineSweeper::showGameMap()
{
    for (int i = 0; i < row; i++) {
        //cout << "\t";
        for (int j = 0; j < col; j++) {
            printGM(i, j);
        }
        cout << endl;
    }
}

void MineSweeper::showGameMap1(int p, int q)
{
    for (int i = 0; i < row; i++) {
        //cout << "\t";
        for (int j = 0; j < col; j++) {
            if (i == p && j == q) {
                cout << "▣";
            }
            else {
                printGM(i, j);
            }
        }
        cout << endl;
    }
}

void MineSweeper::printGM(int i, int j)
{
    switch (gameMap[i][j]) {
    case -1: cout << "★"; break;
    case 9: cout << "■"; break;
    case 0: cout << "□"; break;
    case 1: cout << "①"; break;
    case 2: cout << "②"; break;
    case 3: cout << "③"; break;
    case 4: cout << "④"; break;
    case 5: cout << "⑤"; break;
    case 6: cout << "⑥"; break;
    case 7: cout << "⑦"; break;
    case 8: cout << "⑧"; break;
    }
}

void MineSweeper::printMM(int i, int j)
{
    switch (mineMap[i][j]) {
    case -1: cout << "★"; break;
    case 0: cout << "□"; break;
    case 1: cout << "①"; break;
    case 2: cout << "②"; break;
    case 3: cout << "③"; break;
    case 4: cout << "④"; break;
    case 5: cout << "⑤"; break;
    case 6: cout << "⑥"; break;
    case 7: cout << "⑦"; break;
    case 8: cout << "⑧"; break;
    }
}

void MineSweeper::showIfZero(int p, int q)
{
    if (p != 0 && mineMap[p - 1][q] >= 0 && mineMap[p - 1][q] <= 8 && gameMap[p - 1][q] == 9) {
        gameMap[p - 1][q] = mineMap[p - 1][q];

        if (mineMap[p - 1][q] == 0)
            showIfZero(p - 1, q);
    }

    if (p != row - 1 && mineMap[p + 1][q] >= 0 && mineMap[p + 1][q] <= 8 && gameMap[p + 1][q] == 9) {
        gameMap[p + 1][q] = mineMap[p + 1][q];

        if (mineMap[p + 1][q] == 0)
            showIfZero(p + 1, q);
    }

    if (q != 0 && mineMap[p][q - 1] >= 0 && mineMap[p][q - 1] <= 8 && gameMap[p][q - 1] == 9) {
        gameMap[p][q - 1] = mineMap[p][q - 1];

        if (mineMap[p][q - 1] == 0)
            showIfZero(p, q - 1);
    }

    if (q != col - 1 && mineMap[p][q + 1] >= 0 && mineMap[p][q + 1] <= 8 && gameMap[p][q + 1] == 9) {
        gameMap[p][q + 1] = mineMap[p][q + 1];

        if (mineMap[p][q + 1] == 0)
            showIfZero(p, q + 1);
    }

    if (q != col - 1 && p != row - 1 && mineMap[p + 1][q + 1] >= 1 && mineMap[p + 1][q + 1] <= 8 && gameMap[p + 1][q + 1] == 9)
        gameMap[p + 1][q + 1] = mineMap[p + 1][q + 1];

    if (p != row - 1 && q != 0 && mineMap[p + 1][q - 1] >= 1 && mineMap[p + 1][q - 1] <= 8 && gameMap[p + 1][q - 1] == 9)
        gameMap[p + 1][q - 1] = mineMap[p + 1][q - 1];

    if (p != 0 && q != col - 1 && mineMap[p - 1][q + 1] >= 1 && mineMap[p - 1][q + 1] <= 8 && gameMap[p - 1][q + 1] == 9)
        gameMap[p - 1][q + 1] = mineMap[p - 1][q + 1];

    if (p != 0 && q != 0 && mineMap[p - 1][q - 1] >= 1 && mineMap[p - 1][q + 1] <= 8 && gameMap[p - 1][q - 1] == 9)
        gameMap[p - 1][q - 1] = mineMap[p - 1][q - 1];

}

void MineSweeper::start()
{
    cout << "\t202011377 지상준" << endl << endl;
    cout << "\t1) 새로하기 2) 이전게임 다시하기" << endl;
    cout << "메뉴를 선택해 주세요 : ";
    cin >> mode;

    while (!(mode > 0 && mode < 3)) {
        cout << "올바른 메뉴를 입력하세요!" << endl;
        cout << "메뉴를 선택해 주세요 : ";
        cin >> mode;
    }

    if (mode == 1) {
        mode = 0;
        cout << "지뢰찾기 맵의 크기를 입력하세요 (ex. 5 3): ";
        cin >> row >> col;
        cout << "난이도 1은 10%, 2는 20%, 3은 30% 가 지뢰로 구성됩니다." << endl;
        cout << "지뢰찾기 게임의 난이도를 정하세요 (1, 2, 3 중 선택): ";
        cin >> mode;

        while (!(mode > 0 && mode < 4)) {
            cout << "올바른 난이도를 입력하세요!" << endl;
            cout << "지뢰찾기 게임의 난이도를 정하세요 (1, 2, 3 중 선택): ";
            cin >> mode;
        }

        mineMap = make_unique<unique_ptr<int[]>[]>(row);
        gameMap = make_unique<unique_ptr<int[]>[]>(row);

        for (int i = 0; i < row; i++) {
            mineMap[i] = make_unique<int[]>(col);
            gameMap[i] = make_unique<int[]>(col);
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                mineMap[i][j] = 0;
                gameMap[i][j] = 9;
            }
        }

        setMine(mode);

        setMap();

    }
    else if (mode == 2) {
        int replaySize;
        int replayKeySize;
        int isSaved;

        ifstream fin("mineInfo.txt");
        if (!fin.is_open()) {
            cerr << "파일 오픈 실패";
            exit(0);
        }

        fin >> isSaved;
        if (isSaved == 0) {
            cerr << "\n저장한 게임이 존재하지 않습니다.";
            exit(0);
        }

        fin >> row;
        fin >> col;

        mineMap = make_unique<unique_ptr<int[]>[]>(row);
        gameMap = make_unique<unique_ptr<int[]>[]>(row);

        for (int i = 0; i < row; i++) {
            mineMap[i] = make_unique<int[]>(col);
            gameMap[i] = make_unique<int[]>(col);
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                fin >> mineMap[i][j];
            }
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                fin >> gameMap[i][j];
            }
        }

        fin >> replaySize;
        int x;
        for (int i = 0; i < replaySize; i++) {
            fin >> x;
            replay.push(x);
        }

        fin >> replayKeySize;
        for (int i = 0; i < replayKeySize; i++) {
            fin >> x;
            replayKey.push(x);
        }

        fin.close();

    }

    startGame();

    EndReplay();

    cout << endl << endl << "\t\t202011377 지상준" << endl << "\t\t리플레이 종료!" << endl;

}

void MineSweeper::setMine(const int& m)
{
    double percent;
    int num = row * col;

    int* arr;
    arr = new int[num];

    srand((unsigned int)time(NULL));

    if (m == 1) {
        percent = 0.1;
        num = num * percent;
        if (num < 1)
            num = 1;
    }
    else if (m == 2) {
        percent = 0.2;
        num = num * percent;
        if (num < 1)
            num = 1;
    }
    else if (m == 3) {
        percent = 0.3;
        num = num * percent;
        if (num < 1)
            num = 1;
    }
    mine = num;
    for (int i = 0; i < mine; i++) {
        arr[i] = rand() % (row * col);
        for (int j = 0; j < i; j++) {
            if (arr[i] == arr[j]) {
                i--;
                break;
            }
        }
        mineMap[arr[i] / col][arr[i] % col] = -1; // 지뢰의 위치는 -1
    }
}

void MineSweeper::setMap()
{
    int count = 0;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (mineMap[i][j] == -1)
                continue;
            if (i != row - 1 && mineMap[i + 1][j] == -1)
                count++;
            if (i != 0 && mineMap[i - 1][j] == -1)
                count++;
            if (j != col - 1 && mineMap[i][j + 1] == -1)
                count++;
            if (j != 0 && mineMap[i][j - 1] == -1)
                count++;
            if (i != row - 1 && j != col - 1 && mineMap[i + 1][j + 1] == -1)
                count++;
            if (i != row - 1 && j != 0 && mineMap[i + 1][j - 1] == -1)
                count++;
            if (i != 0 && j != col - 1 && mineMap[i - 1][j + 1] == -1)
                count++;
            if (i != 0 && j != 0 && mineMap[i - 1][j - 1] == -1)
                count++;
            mineMap[i][j] = count;
            count = 0;
        }
    }
}

void MineSweeper::startGame()
{
    system("cls");
    setCursorView(false);
    showGameMap();

    cout << endl << endl << endl;
    cout << "\t    202011377 지상준" << endl << endl;
    cout << "\t===== 지뢰찾기 게임 =====" << endl;
    cout << "\t    현재 지뢰수 : " << mine << endl;
    cout << "\t    방향키 : wasd, 지뢰 표시 : l, 선택 : j , 저장 후 종료 : p" << endl << endl;

    char move;
    int select = 0;
    int x_point = 0, y_point = 0;
    gotoxy(x_point, y_point);

    while (1) {
        int isEnd = 0;
        int mineEnd = 0;
        int End = 0;

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (gameMap[i][j] == -1)
                    mineEnd++;
                if (gameMap[i][j] == 9)
                    isEnd++;

            }
        }

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (gameMap[i][j] == mineMap[i][j])
                    End++;
            }
        }

        if (mineEnd == mine && isEnd == 0 && End == row * col) {
            system("cls");

            showGameMap();

            cout << endl << endl << endl;
            cout << "\t    202011377 지상준" << endl << endl;
            cout << "\t===== 지뢰찾기 게임 =====" << endl;
            cout << "\t    현재 지뢰수 : " << mine << endl;
            cout << "\t    현재 찾은 지뢰 수 : " << select << endl << endl;
            cout << "\t    게임 승리!" << endl << endl;
            cout << "\t    5초 후 리플레이가 시작됩니다!" << endl;

            ofstream fout("mineInfo.txt");
            fout << "0";
            fout.close();

            break;
        }

        move = getch();

        if (move == 'w' && y_point != 0) {
            y_point--;
            system("cls");
            showGameMap1(y_point, x_point / 2);
            cout << endl << endl << endl;
            cout << "\t    202011377 지상준" << endl << endl;
            cout << "\t===== 지뢰찾기 게임 =====" << endl;
            cout << "\t    현재 지뢰수 : " << mine << endl;
            cout << "\t    현재 찾은 지뢰 수 : " << select << endl << endl;
        }
        else if (move == 'a' && x_point != 0) {
            x_point = x_point - 2;
            system("cls");
            showGameMap1(y_point, x_point / 2);
            cout << endl << endl << endl;
            cout << "\t    202011377 지상준" << endl << endl;
            cout << "\t===== 지뢰찾기 게임 =====" << endl;
            cout << "\t    현재 지뢰수 : " << mine << endl;
            cout << "\t    현재 찾은 지뢰 수 : " << select << endl << endl;
        }
        else if (move == 's' && y_point != row - 1) {
            y_point++;
            system("cls");
            showGameMap1(y_point, x_point / 2);
            cout << endl << endl << endl;
            cout << "\t    202011377 지상준" << endl << endl;
            cout << "\t===== 지뢰찾기 게임 =====" << endl;
            cout << "\t    현재 지뢰수 : " << mine << endl;
            cout << "\t    현재 찾은 지뢰 수 : " << select << endl << endl;
        }
        else if (move == 'd' && x_point != (col - 1) * 2) {
            x_point = x_point + 2;
            system("cls");
            showGameMap1(y_point, x_point / 2);
            cout << endl << endl << endl;
            cout << "\t    202011377 지상준" << endl << endl;
            cout << "\t===== 지뢰찾기 게임 =====" << endl;
            cout << "\t    현재 지뢰수 : " << mine << endl;
            cout << "\t    현재 찾은 지뢰 수 : " << select << endl << endl;
        }
        else if (move == 'j' && gameMap[y_point][x_point / 2] == 9) {
            if (mineMap[y_point][x_point / 2] == -1) {
                pushToReplay(y_point, x_point / 2);
                replayKey.push(1);
                system("cls");
                showMineMap();
                cout << endl << endl << endl;
                cout << "\t    202011377 지상준" << endl << endl;
                cout << "\t===== 지뢰찾기 게임 =====" << endl;
                cout << "\t    현재 지뢰수 : " << mine << endl;
                cout << "\t    현재 찾은 지뢰 수 : " << select << endl << endl;
                cout << "\t    게임 종료!" << endl << endl;
                cout << "\t    5초 후 리플레이가 시작됩니다!" << endl;

                ofstream fout("mineInfo.txt");
                fout << "0";
                fout.close();

                break;
            }
            else {
                gameMap[y_point][x_point / 2] = mineMap[y_point][x_point / 2];
                pushToReplay(y_point, x_point / 2);
                replayKey.push(1);
                if (gameMap[y_point][x_point / 2] == 0) {
                    showIfZero(y_point, x_point / 2);
                    //break;
                }
                system("cls");
                showGameMap();
                cout << endl << endl << endl;
                cout << "\t    202011377 지상준" << endl << endl;
                cout << "\t===== 지뢰찾기 게임 =====" << endl;
                cout << "\t    현재 지뢰수 : " << mine << endl;
                cout << "\t    현재 찾은 지뢰 수 : " << select << endl << endl;
            }
        }
        else if (move == 'l' && gameMap[y_point][x_point / 2] == 9) {
            gameMap[y_point][x_point / 2] = -1;
            pushToReplay(y_point, x_point / 2);
            replayKey.push(2);
            select++;
            system("cls");
            showGameMap();
            cout << endl << endl << endl;
            cout << "\t    202011377 지상준" << endl << endl;
            cout << "\t===== 지뢰찾기 게임 =====" << endl;
            cout << "\t    현재 지뢰수 : " << mine << endl;
            cout << "\t    현재 찾은 지뢰 수 : " << select << endl << endl;
        }
        else if (move == 'l' && gameMap[y_point][x_point / 2] == -1) {
            gameMap[y_point][x_point / 2] = 9;
            pushToReplay(y_point, x_point / 2);
            replayKey.push(2);
            select--;
            system("cls");
            showGameMap();
            cout << endl << endl << endl;
            cout << "\t    202011377 지상준" << endl << endl;
            cout << "\t===== 지뢰찾기 게임 =====" << endl;
            cout << "\t    현재 지뢰수 : " << mine << endl;
            cout << "\t    현재 찾은 지뢰 수 : " << select << endl << endl;
        }
        else if (move == 'p') {
            //파일로 저장 mine & game
            ofstream fout("mineInfo.txt");

            fout << "999" << "\n\n";

            fout << row << " " << col << "\n\n";

            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    fout << mineMap[i][j] << " ";
                }
                fout << "\n";
            }
            fout << "\n";
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    fout << gameMap[i][j] << " ";
                }
                fout << "\n";
            }
            fout << "\n\n";

            fout << replay.size() << "\n";

            while (!replay.empty()) {
                fout << replay.front() << " ";
                replay.pop();
                fout << replay.front() << " ";
                replay.pop();
            }
            fout << "\n";

            fout << replayKey.size() << "\n";
            while (!replayKey.empty()) {
                fout << replayKey.front() << " ";
                replayKey.pop();
            }

            fout.close();

            cout << "\t    게임 저장이 완료되었습니다." << endl << endl;

            exit(0);
        }
    }
}

void MineSweeper::pushToReplay(int x, int y)
{
    replay.push(x);
    replay.push(y);
}

void MineSweeper::EndReplay()
{
    Sleep(5000);

    int x, y;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            gameMap[i][j] = 9;
        }
    }

    system("cls");
    showGameMap();
    Sleep(2000);

    while (!replayKey.empty()) {

        system("cls");
        x = replay.front();
        replay.pop();
        y = replay.front();
        replay.pop();
        if (replayKey.front() == 1) {
            replayKey.pop();

            gameMap[x][y] = mineMap[x][y];
            if (gameMap[x][y] == 0) {
                showIfZero(x, y);
                //break;
            }
        }
        else if (replayKey.front() == 2) {
            replayKey.pop();
            if (gameMap[x][y] == 9) {
                gameMap[x][y] = -1;
            }
            else if (gameMap[x][x] == -1) {
                gameMap[x][y] = 9;
            }
        }

        showGameMap();
        Sleep(2000);

    }

    system("cls");
    showMineMap();
}
