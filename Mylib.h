#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <conio.h> // For keyboard input (getch())
#include <Windows.h>
#include <mmsystem.h>
#include <string>
#include <cstring>
#include <string.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <io.h>    // Call _setmode
#include <fcntl.h>
#include <chrono>
#include <thread>


#define FOREGROUND_YELLOW 0x6
#define FOREGROUND_WHITE 0x7
#define FOREGROUND_GREY 0x8
#define FOREGROUND_LIGHTBLUE 0x9
#define BACKGROUND_BLACK 0x100
#define FOREGROUND_BLACK 0x00
using namespace std;


struct Score
{
    time_t startTime;
	void start(){
        startTime = time(NULL);
    }
	int total(){
        return (int)floor(time(NULL) - startTime);
    }
    int changeScore(){
    	int t = total();
    	return (3000 - t);
	}
};



struct player
{
	string name = "";
	int point;
};


struct Coordinate
{
    int x;
    int y;
};

struct Board
{
    Coordinate cur, old, select; //Cur la vi tri hien tai, old la vi tri vua di qua, select la vi tri da chon
    int size;  //Kich thuoc bang la size x size
    int No_pokemon; //Tong so loai Pokemon
    int **Arr; //Mang hai chieu luu cac gia tri cua bang
    int sub_size; //Tong so loai Pokemon
    int *sub_arr;  //Mang luu so luong Pokemon cua tung loai
};

void changeColor(int color);

//Ham tinh kich thuoc man hinh console
void calculateColumnsConsole(int &columns, int &rows);

//Khoi tao gia tri bang
void setValueBoard (Board& Pikachu);

//Ham tro con tro van ban den vi tri co toa do x, y
void gotoXY(int x, int y);

bool matchShapeI(Board& Pikachu);

bool matchShapeL(Board& Pikachu);

bool matchShapeZ (Board& Pikachu);

bool matchShapeU (Board& Pikachu);

bool matchWholeShape (Board& Pikachu, int start_point);

void drawFrame (int pos_x, int pos_y, string str);

//Ham ve hinh chu nhat
void drawRec(int begin_x, int begin_y, int end_x, int end_y, char ch_1, char ch_2);

void highLightBlock(Coordinate select, int **arr, int color, int start_point);

//Ve man hinh bat dau;
void drawMenu(int middle);

//Ham ve bang
void drawBoard (Board Pikachu, int start_point);

void operateBoard (Board& Pikachu, int start_point, Score score, player p);

//lam noi bat khung chon menu
void selectOption (Coordinate select);

//thu hoi bo nho
void deleleDinamicArr(Board Pikachu);

void resetBoard (Board& Pikachu);

void selectLevel (int &size);

void drawLine (Board& Pikachu, int start_point);

void swapPokemon (Board& Pikachu);

void falseEffect (Board Pikachu, int start_point);

void play(Board& Pikachu);

void Operating_System();

void suggestionFunction(Board Pikachu, int start_point);

bool subMatchingForSuggestion(Board Pikachu);

void swapBoard (Board& Pikachu, int start_point);

bool isDone (Board Pikachu, int start_point);

bool subMatching (Board Pikachu);

void print3(int start_point);

void print2(int start_point);

void print1(int start_point);

void print(Coordinate select, int start_point, int size);

void printWin();

void getBackground3(char bg3[][72]);

void getBackground2(char bg2[][55]);

void getBackground1(char bg1[][36]);

void writeLeaderBoard(player p);

void readLeaderBoard();

void titleLeaderBoard();

void changeTime(int t);






