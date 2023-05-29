/*
TicTacToc  Copyright(C) 2023 slacr  <https://slacr.site>
QQ: 2845391871
Date: 2023-5-23
This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
This is free software, and you are welcome to redistribute it
under certain conditions; type `show c' for details.
*/


#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
using namespace std;

// 游戏状态
enum class GameState {
	PLAYING,
	DRAW,
	PLAYER_X_WIN,
	PLAYER_O_WIN
};

// 棋盘大小
const int BOARD_SIZE = 3;

// 棋盘数组
char board[BOARD_SIZE][BOARD_SIZE];

// 当前玩家
char currentPlayer = 'X';

// 游戏状态
GameState gameState = GameState::PLAYING;

// 局数
int N_Round = 1;
int N_Draw = 0;
int N_Player_X = 0;
int N_Player_O = 0;

// 光标位置
int cursorRow = 0;
int cursorCol = 0;

// 初始化棋盘
void initBoard() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board[i][j] = ' ';
		}
	}
}

// 绘制棋盘
void drawBoard() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, { 0, 7 });
	cout << "     ACC   " << "R:" << N_Round << "  P_X:" << N_Player_X << "  P_O:" << N_Player_O << "  D:" << N_Draw << endl;
	cout << endl;
	cout << setw(15) << left << " ";
	for (int i = 0; i < BOARD_SIZE; i++) {
		cout << " " << i + 1 << "  ";
	}
	cout << endl;


	for (int i = 0; i < BOARD_SIZE; i++) {
		cout << setw(13) << left << " " << i + 1 << " ";
		for (int j = 0; j < BOARD_SIZE; j++) {
			// 光标当前所在格子
			if (i == cursorRow && j == cursorCol) {
				if (board[i][j] == 'X') {
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					cout << " " << board[i][j] << " ";
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				} else if (board[i][j] == 'O') {
					SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
					cout << " " << board[i][j] << " ";
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				} else {
					cout << "[" << currentPlayer << "]";
				}
			} else {
				if (board[i][j] == 'X') {
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					cout << " " << board[i][j] << " ";
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				} else if (board[i][j] == 'O') {
					SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
					cout << " " << board[i][j] << " ";
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				} else {
					cout << " " << board[i][j] << " ";
				}
			}
			if (j != BOARD_SIZE - 1) {
				cout << "┃";
			}
		}
		cout << endl;
		if (i != BOARD_SIZE - 1) {
			cout << setw(15) << left << " ";
			for (int j = 0; j < BOARD_SIZE; j++) {
				cout << "━━━";
				if (j != BOARD_SIZE - 1) {
					cout << "╋";
				}
			}
			cout << endl;
		}
	}
}

// 检查是否有玩家获胜
bool checkWin(char player) {
	// 检查行
	for (int i = 0; i < BOARD_SIZE; i++) {
		bool win = true;
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] != player) {
				win = false;
				break;
			}
		}
		if (win) {
			return true;
		}
	}
	// 检查列
	for (int j = 0; j < BOARD_SIZE; j++) {
		bool win = true;
		for (int i = 0; i < BOARD_SIZE; i++) {
			if (board[i][j] != player) {
				win = false;
				break;
			}
		}
		if (win) {
			return true;
		}
	}
	// 检查对角线
	bool win = true;
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (board[i][i] != player) {
			win = false;
			break;
		}
	}
	if (win) {
		return true;
	}
	win = true;
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (board[i][BOARD_SIZE - 1 - i] != player) {
			win = false;
			break;
		}
	}
	if (win) {
		return true;
	}
	return false;
}

// 检查是否平局
bool checkDraw() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == ' ') {
				return false;
			}
		}
	}
	return true;
}

// 处理键盘输入
void handleInput() {
	// 获取键盘输入
	int key = _getch();
	// 根据输入移动光标
	if (currentPlayer == 'X') {  // 玩家一移动
		switch (key) { 
		case 'w': // 上
			cursorRow--;
			if (cursorRow < 0) {
				cursorRow = BOARD_SIZE - 1;
			}
			drawBoard();
			break;
		case 's': // 下
			cursorRow++;
			if (cursorRow >= BOARD_SIZE) {
				cursorRow = 0;
			}
			drawBoard();
			break;
		case 'a': // 左
			cursorCol--;
			if (cursorCol < 0) {
				cursorCol = BOARD_SIZE - 1;
			}
			drawBoard();
			break;
		case 'd': // 右
			cursorCol++;
			if (cursorCol >= BOARD_SIZE) {
				cursorCol = 0;
			}
			drawBoard();
			break;
		case ' ': // 确认
			// 如果当前位置已经有棋子了，则不做处理
			if (board[cursorRow][cursorCol] != ' ') {
				return;
			}
			// 在当前位置填入当前玩家的棋子
			board[cursorRow][cursorCol] = currentPlayer;
			// 绘制棋盘
			drawBoard();
			// 检查游戏是否结束
			if (checkWin(currentPlayer)) {
				if (currentPlayer == 'X') {
					gameState = GameState::PLAYER_X_WIN;
				} else {
					gameState = GameState::PLAYER_O_WIN;
				}
			} else if (checkDraw()) {
				gameState = GameState::DRAW;
			}
			// 切换玩家
			if (currentPlayer == 'X') {
				currentPlayer = 'O';
			} else {
				currentPlayer = 'X';
			}
			break;
		}
	} else {   // 玩家二移动
		switch (key) {
		case 'i': // 上
			cursorRow--;
			if (cursorRow < 0) {
				cursorRow = BOARD_SIZE - 1;
			}
			drawBoard();
			break;
		case 'k': // 下
			cursorRow++;
			if (cursorRow >= BOARD_SIZE) {
				cursorRow = 0;
			}
			drawBoard();
			break;
		case 'j': // 左
			cursorCol--;
			if (cursorCol < 0) {
				cursorCol = BOARD_SIZE - 1;
			}
			drawBoard();
			break;
		case 'l': // 右
			cursorCol++;
			if (cursorCol >= BOARD_SIZE) {
				cursorCol = 0;
			}
			drawBoard();
			break;
		case ' ': // 确认
			// 如果当前位置已经有棋子了，则不做处理
			if (board[cursorRow][cursorCol] != ' ') {
				return;
			}
			// 在当前位置填入当前玩家的棋子
			board[cursorRow][cursorCol] = currentPlayer;
			// 绘制棋盘
			drawBoard();
			// 检查游戏是否结束
			if (checkWin(currentPlayer)) {
				if (currentPlayer == 'X') {
					gameState = GameState::PLAYER_X_WIN;
				} else {
					gameState = GameState::PLAYER_O_WIN;
				}
			} else if (checkDraw()) {
				gameState = GameState::DRAW;
			}
			// 切换玩家
			if (currentPlayer == 'X') {
				currentPlayer = 'O';
			} else {
				currentPlayer = 'X';
			}
			break;
		}	
	}
	// 移动光标
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, { (short)(cursorCol * 4 + 17), (short)(cursorRow * 2 + 10) });
}

int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// 标题
	cout <<   "     ======================================== "<< endl;
	cout <<   "     |           TicTacToc  v0.0.2          |" << endl;
	cout <<   "     |                                      |" << endl;
	cout <<   "     |                       author:   slacr|" << endl;
	cout <<   "     |                       license: GPL3.0|" << endl;
	cout <<   "     ======================================== " << endl;
	cout << endl;

	// 底部栏
	SetConsoleCursorPosition(hConsole, { 0, 16 });
	cout << "     +_____________________________________+" << endl;
	cout << "     | Player_X: W A S D SPACE             |" << endl;
	cout << "     | Player_O: I J K L SPACE             |" << endl;
	cout << "     |                                     |" << endl;
	cout << "     |_____________________________________| " << endl;


	while (true) {
		// 初始化棋盘
		initBoard();
		// 绘制棋盘
		drawBoard();
		// 第一次定位光标到第一个格子位置
		SetConsoleCursorPosition(hConsole, { 17, 10 });
		// 循环处理键盘输入
		while (gameState == GameState::PLAYING) {
			handleInput();
		}
		// 根据游戏状态输出结果
		if (gameState == GameState::PLAYER_X_WIN) {
			SetConsoleCursorPosition(hConsole, { 0, 22 });
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			cout << "            \\\\\\";
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			cout << " Player X wins! "; 
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			cout << "///" << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			N_Player_X++;
			drawBoard();
		} else if (gameState == GameState::PLAYER_O_WIN) {
			SetConsoleCursorPosition(hConsole, { 0, 22 });
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			cout << "            \\\\\\";
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
			cout << " Player O wins! "; 
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			cout << "///" << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			N_Player_O++;
			drawBoard();
		} else {
			SetConsoleCursorPosition(hConsole, { 0, 22 });
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			cout << "            \\\\\\";
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			cout << " Draw! ";
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			cout << "///" << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			N_Draw++;
			drawBoard();
		}
		N_Round = 1 + N_Player_X + N_Player_O + N_Draw;   // 更新总局数
		SetConsoleCursorPosition(hConsole, { 0, 23 });
		cout << "press 'q' to quit, 'r' to restart, 'c' to continue" << endl;
		while (int key = _getch()) {
			if (key == 'q') return 0;
			else if (key == 'r') {
				gameState = GameState::PLAYING;
				N_Round = 1;
				N_Player_X = N_Player_O = N_Draw = 0;
				cursorRow = 0;
				cursorCol = 0;
				break;
			} else if (key == 'c') {
				gameState = GameState::PLAYING;
				cursorRow = 0;
				cursorCol = 0;
				break;
			}
		}
		SetConsoleCursorPosition(hConsole, { 0, 22 }); // 清空结果信息
		cout << "                                                     " << endl;
		cout << "                                                     " << endl;
	}
	return 0;
}
