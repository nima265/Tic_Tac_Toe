#include <iostream>
#include<Windows.h>
#include <iomanip>
#include "game.h"
#include "user.h"
using namespace std;

void main() {
	int a;
	char b;
	int x;
	system("color e2");
	
PlaySound(TEXT("maintheme.wav"), NULL, SND_FILENAME | SND_ASYNC);
	cout << "\n" << setw(77) << "******************************\n" << setw(73) << "Welcome to Tic Tac Toe\n" << setw(77) << "******************************\n";
	Game tictactoe;
	user U;
	cout << setw(63) << "1.START\n" << setw(65) << "2.Details\n" << setw(62) << "3.Exit\n";
	cin >> a;
	if (a == 1) {
		cout << setw(65) << "choose your Enemy:\n" << setw(62) << "1.Human\n" << setw(65) << "2.Computer\n";
		cin >> x;
		PlaySound(TEXT("start.wav"), NULL, SND_FILENAME | SND_ASYNC);
		tictactoe.play(x);
		cout << "\n\n" << setw(60) << "Do You wana retun to Menu?(y,n):\n";
		cin >> b;
		if (b == 'y') {
			system("cls");
			main();
		}
		else { }
	}

	else if (a == 2) {
		cout << setw(66) << "What's the Tic Tac Toe\n" << "Tic-tac-toe, noughts and crosses, or Xs and Os, is a paper-and-pencil game for two players, X and O, who take turns\n marking the spaces in a 3×3 grid. The player who succeeds in placing three of their marks in a horizontal, vertical,\n or diagonal row is the winner\n\n\nCreate and Develop by Nima Etemad Golestani Student of Software Engineering, Islamic Azad University of Mashhad ";
		cout << "\n\n" << setw(55) << "Do you wana return to Menu?(y,n)\n";
		cin >> b;
		if (b == 'y') {
			system("cls");
			main();
		}
	}
		else if (a==3)
		{
			cout << "\n\n" << setw(60) << "Thanks to play this Game =)\n";
			Sleep(1300);
		} 
	

}