#include <iostream>
#include <sstream>
#include <iomanip>
#include<Windows.h>
#include "game.h"
using namespace std;

Game::Game() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = '-';
		}
	}
}

void Game::printBoard() {
	cout << setw(63) << "-------------------";
	for (int i = 0; i < 3; i++) {
		cout << "\n" << setw(45) << "|";
		for (int j = 0; j < 3; j++) {
			cout << setw(3) << board[i][j] << setw(3) << " |";
		}
	}
	cout << '\n' << setw(63) << "-------------------" << '\n';
}

bool Game::gameOver() {
	if (checkWin(HUMAN)) return true;
	else if (checkWin(AI)) return true;

	bool emptySpace = false;
	for (int i = 0; i < 3; i++) {
		if (board[i][0] == '-' || board[i][1] == '-' || board[i][2] == '-')
			emptySpace = true;
	}
	return !emptySpace;
}

bool Game::checkWin(Player player) {
	char playerChar;
	if (player == HUMAN) playerChar = human;
	else playerChar = ai;

	for (int i = 0; i < 3; i++) {
		if (board[i][0] == playerChar && board[i][1] == playerChar
			&& board[i][2] == playerChar)
			return true;

		if (board[0][i] == playerChar && board[1][i] == playerChar
			&& board[2][i] == playerChar)
			return true;
	}

	if (board[0][0] == playerChar && board[1][1] == playerChar
		&& board[2][2] == playerChar) {
		return true;
	}
	else if (board[0][2] == playerChar && board[1][1] == playerChar
		&& board[2][0] == playerChar) {
		return true;
	}

	return false;
}

int Game::score() {
	int s = 0;
	if (checkWin(HUMAN)) { s = s + 10; return s; }
	else if (checkWin(AI)) { s = s - 10; return s; }
	return 0;
}

Move Game::minimax(char AIboard[3][3]) {
	int bestMoveScore = 1000;
	Move bestMove;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (AIboard[i][j] == '-') {
				AIboard[i][j] = ai;
				int tempMoveScore = maxSearch(AIboard);
				if (tempMoveScore <= bestMoveScore) {
					bestMoveScore = tempMoveScore;
					bestMove.x = i;
					bestMove.y = j;
				}
				AIboard[i][j] = '-';
			}
		}
	}

	return bestMove;
}

int Game::maxSearch(char AIboard[3][3]) {
	if (gameOver()) return score();
	Move bestMove;

	int bestMoveScore = -1000;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (AIboard[i][j] == '-') {
				AIboard[i][j] = human;
				int tempMoveScore = minSearch(AIboard);
				if (tempMoveScore >= bestMoveScore) {
					bestMoveScore = tempMoveScore;
					bestMove.x = i;
					bestMove.y = j;
				}
				AIboard[i][j] = '-';
			}
		}
	}

	return bestMoveScore;
}

int Game::minSearch(char AIboard[3][3]) {
	if (gameOver()) return score();
	Move bestMove;

	int bestMoveScore = 1000;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (AIboard[i][j] == '-') {
				AIboard[i][j] = ai;
				int tempMove = maxSearch(AIboard);
				if (tempMove <= bestMoveScore) {
					bestMoveScore = tempMove;
					bestMove.x = i;
					bestMove.y = j;
				}
				AIboard[i][j] = '-';
			}
		}
	}

	return bestMoveScore;
}

void Game::getHumanMove(int t) {
	int x = -1;
	int y = -1;
	int z = 1;
	if (t % 2 == 0) z = 1;
	else z = 2;
	while (x < 0 || x > 2 || y < 0 || y > 2) {
		cout << endl << "                                       Enter your move in coordinate form,(Row,Column) ex: (1,3)." << endl;
		cout << setw(50) <<"Human"<<z<< " Move: ";
		char c;
		string restofline;
		cin >> c >> c;
		x = c - '0' - 1;
		cin >> c >> c;
		y = c - '0' - 1;
		getline(cin, restofline);
	}
	if (t % 2 == 0) {
		board[x][y] = human;
	}
	else
	{
		board[x][y] = ai;
	}
}

void Game::play(int x) {
	int turn = 0;
	printBoard();
	while (!checkWin(HUMAN) && !checkWin(AI) && !gameOver()) {
		if (turn % 2 == 0) {
			getHumanMove(turn);
			if (checkWin(HUMAN)) {
				PlaySound(TEXT("victory.wav"), NULL, SND_FILENAME | SND_ASYNC);
				cout << setw(60) << "Human1 Player Wins" << "\n" << setw(54) << "score:" << score() << endl;
			}
			PlaySound(TEXT("movement.wav"), NULL, SND_FILENAME | SND_ASYNC);
			turn++;
			printBoard();
		}
		else {
			if (x == 1) {
				getHumanMove(turn);
				if (checkWin(HUMAN)) {
					PlaySound(TEXT("victory.wav"), NULL, SND_FILENAME | SND_ASYNC);
					cout << setw(60) << "Human2 Player Wins" << "\n" << setw(54) << "score:" << score() << endl;
				}
				PlaySound(TEXT("movement.wav"), NULL, SND_FILENAME | SND_ASYNC);
				turn++;
				printBoard();
			}
			else if (x == 2)
			{
				Sleep(700);
				cout << "\n" << setw(54) << "computer move:\n";
				Move AImove = minimax(board);
				board[AImove.x][AImove.y] = ai;
				if (checkWin(AI)) {
					PlaySound(TEXT("lose.wav"), NULL, SND_FILENAME | SND_ASYNC);
					cout << setw(60) << "Computer Player Wins" << "\n" << setw(54) << "score:" << score() << endl;
				}
				PlaySound(TEXT("movement.wav"), NULL, SND_FILENAME | SND_ASYNC);
				turn++;
				printBoard();
			}
		}
		if (gameOver() == true && checkWin(HUMAN) == false && checkWin(AI) == false) {
			PlaySound(TEXT("draw.wav"), NULL, SND_FILENAME | SND_ASYNC);
			cout << "\n" << setw(54) << "Draw\n" << setw(54) << "score:" << score() << endl;
			printBoard();
		}

	}
}