#include <iostream>
#include <vector>
#include <cstdlib>  // for system("clear") or system("cls") to clear the console

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

// Constants
const int BOARD_SIZE = 3;
const char EMPTY = '-';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

// Function prototypes
void drawBoard(const std::vector<std::vector<char>>& board);
void clearConsole();
bool isGameOver(const std::vector<std::vector<char>>& board);
bool isWin(const std::vector<std::vector<char>>& board, char player);
bool isDraw(const std::vector<std::vector<char>>& board);
int evaluateBoard(const std::vector<std::vector<char>>& board);
int minimax(std::vector<std::vector<char>>& board, int depth, bool isMaximizingPlayer);
void makeMove(std::vector<std::vector<char>>& board, int move, char player);
int getPlayerMove(const std::vector<std::vector<char>>& board, char player);
int getAIMove(std::vector<std::vector<char>>& board);

// Function to draw the Tic Tac Toe board
void drawBoard(const std::vector<std::vector<char>>& board) {
	clearConsole();
	std::cout << "  Tic Tac Toe" << std::endl << std::endl;

	for (int i = 0; i < BOARD_SIZE; ++i) {
		std::cout << " ";
		for (int j = 0; j < BOARD_SIZE; ++j) {
			std::cout << " " << board[i][j] << " ";
			if (j < BOARD_SIZE - 1) {
				std::cout << "|";
			}
		}
		std::cout << std::endl;

		if (i < BOARD_SIZE - 1) {
			std::cout << " ";
			for (int j = 0; j < BOARD_SIZE - 1; ++j) {
				std::cout << "---+";
			}
			std::cout << "---" << std::endl;
		}
	}

	std::cout << std::endl;
}

// Function to clear the console
void clearConsole() {
	std::system(CLEAR_COMMAND);
}

// Function to check if the game is over
bool isGameOver(const std::vector<std::vector<char>>& board) {
	return isWin(board, PLAYER_X) || isWin(board, PLAYER_O) || isDraw(board);
}

// Function to check if a player has won
bool isWin(const std::vector<std::vector<char>>& board, char player) {
	// Check rows
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
			return true;
		}
	}

	// Check columns
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
			return true;
		}
	}

	// Check diagonals
	if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
		(board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
		return true;
	}

	return false;
}

// Function to check if the game is a draw
bool isDraw(const std::vector<std::vector<char>>& board) {
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (board[i][j] == EMPTY) {
				return false;
			}
		}
	}
	return true;
}

// Function to evaluate the board
int evaluateBoard(const std::vector<std::vector<char>>& board) {
	if (isWin(board, PLAYER_X)) {
		return 1;
	}
	else if (isWin(board, PLAYER_O)) {
		return -1;
	}
	else {
		return 0;
	}
}

// Minimax algorithm implementation
int minimax(std::vector<std::vector<char>>& board, int depth, bool isMaximizingPlayer) {
	int score = evaluateBoard(board);

	// Base cases
	if (score == 1) {
		return score - depth;
	}
	if (score == -1) {
		return score + depth;
	}
	if (isDraw(board)) {
		return 0;
	}

	// Recursive cases
	if (isMaximizingPlayer) {
		int maxScore = -1000;
		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				if (board[i][j] == EMPTY) {
					board[i][j] = PLAYER_X;
					int currentScore = minimax(board, depth + 1, false);
					board[i][j] = EMPTY;
					maxScore = std::max(maxScore, currentScore);
				}
			}
		}
		return maxScore;
	}
	else {
		int minScore = 1000;
		for (int i = 0; i < BOARD_SIZE; ++i) {
			for (int j = 0; j < BOARD_SIZE; ++j) {
				if (board[i][j] == EMPTY) {
					board[i][j] = PLAYER_O;
					int currentScore = minimax(board, depth + 1, true);
					board[i][j] = EMPTY;
					minScore = std::min(minScore, currentScore);
				}
			}
		}
		return minScore;
	}
}

// Function to make a move on the board
void makeMove(std::vector<std::vector<char>>& board, int move, char player) {
	int row = move / BOARD_SIZE;
	int col = move % BOARD_SIZE;

	if (board[row][col] == EMPTY) {
		board[row][col] = player;
	}
}

// Function to get a player's move
int getPlayerMove(const std::vector<std::vector<char>>& board, char player) {
	int move;
	while (true) {
		std::cout << "Player " << player << ", enter your move (1-9): ";
		std::cin >> move;
		move--;

		int row = move / BOARD_SIZE;
		int col = move % BOARD_SIZE;

		if (move >= 0 && move < BOARD_SIZE * BOARD_SIZE && board[row][col] == EMPTY) {
			break;
		}

		std::cout << "Invalid move. Try again." << std::endl;
	}
	return move;
}

// Function to get the AI's move using the Minimax algorithm
int getAIMove(std::vector<std::vector<char>>& board) {
	int bestScore = -1000;
	int bestMove = -1;

	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (board[i][j] == EMPTY) {
				board[i][j] = PLAYER_X;
				int score = minimax(board, 0, false);
				board[i][j] = EMPTY;

				if (score > bestScore) {
					bestScore = score;
					bestMove = i * BOARD_SIZE + j;
				}
			}
		}
	}

	return bestMove;
}

// Main function
int main() {
	std::vector<std::vector<char>> board(BOARD_SIZE, std::vector<char>(BOARD_SIZE, EMPTY));
	int currentPlayer = 0;
	bool isPlayerVsAI = false;

	std::cout << "\033[43m";  // Set background color to yellow

	std::cout << "Tic Tac Toe" << std::endl;
	std::cout << "1. Player vs Player" << std::endl;
	std::cout << "2. Player vs AI" << std::endl;
	std::cout << "Enter game mode: ";
	int gameMode;
	std::cin >> gameMode;

	if (gameMode == 2) {
		isPlayerVsAI = true;
	}

	while (!isGameOver(board)) {
		drawBoard(board);

		char currentPlayerSymbol = (currentPlayer == 0) ? PLAYER_X : PLAYER_O;
		int move;
		if (isPlayerVsAI && currentPlayer == 1) {
			move = getAIMove(board);
			std::cout << "AI's move: " << move + 1 << std::endl;
		}
		else {
			move = getPlayerMove(board, currentPlayerSymbol);
		}

		makeMove(board, move, currentPlayerSymbol);
		currentPlayer = (currentPlayer + 1) % 2;
	}

	drawBoard(board);

	if (isWin(board, PLAYER_X)) {
		std::cout << "Player X wins!" << std::endl;
	}
	else if (isWin(board, PLAYER_O)) {
		std::cout << "Player O wins!" << std::endl;
	}
	else {
		std::cout << "It's a draw!" << std::endl;
	}

	std::cout << "\033[0m";  // Reset console colors

	return 0;
}