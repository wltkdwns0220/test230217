#pragma once
#include <string>
#include <iostream>
#include <memory.h>
#include <Windows.h>
#include <queue>
#include <wincrypt.h>
using namespace std;
class MineSweeper
{
private:
    string name;
    int row = 0;
    int col = 0;
    int mode = 0;
    int mine = 0;
    unique_ptr<unique_ptr<int[]>[]> mineMap;
    unique_ptr<unique_ptr<int[]>[]> gameMap;
    queue <int> replay;
    queue <int> replayKey;
public:
    MineSweeper();
    ~MineSweeper();
    void showMineMap();
    void showGameMap();
    void showGameMap1(int i, int j);
    void printGM(int i, int j);
    void printMM(int i, int j);
    void showIfZero(int i, int j);
    void start();
    void setMine(const int& m);
    void setMap();
    void startGame();
    void pushToReplay(int x, int y);
    void EndReplay();
    void gotoxy(int x, int y) {

        COORD Pos = { x,y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
    }
    void setCursorView(bool visible) {
        CONSOLE_CURSOR_INFO cursor = { 1, visible };
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    }
};

