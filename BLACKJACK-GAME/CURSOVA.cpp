#include <iostream>
#include <windows.h>
#include <conio.h>

#include "blackjack.hpp"

#define KEY_ARROW_UP    72
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_DOWN  80
#define KEY_ARROW_LEFT  75
#define ATTR1           240
#define ATTR2           15

using namespace std;

char m[4][15] = { "  S T A R T  ", " A B O U T !! ", " H E L P ?? ", "  E X I T  " };
void frame(HANDLE h, COORD frame_begin, COORD frame_end);								 //BUILDING A FRAME
void draw(HANDLE h, COORD c, int k, int n, int len);									// MENU
void Start(HANDLE h);																	// START
void About(HANDLE h);																	//ABOUT
void Help(HANDLE h);																	 //HELP


static char ask_hint() {
    char c = getchar();
    char ch;																	// ask menu
    while ((ch = getchar()) != '\n' && ch != EOF) continue;
    return tolower(c);
}

int main_1() {
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 32);
    system("cls");

    cout << endl << "\t\t\t\t\t\t  B";
    SetConsoleTextAttribute(h, 36);
    cout << "L";
    SetConsoleTextAttribute(h, 32);
    cout << "A";
    SetConsoleTextAttribute(h, 36);
    cout << 'C';
    SetConsoleTextAttribute(h, 32);
    cout << 'K';
    SetConsoleTextAttribute(h, 36);
    cout << 'J';
    SetConsoleTextAttribute(h, 32);
    cout << 'A';
    SetConsoleTextAttribute(h, 36);
    cout << 'C';
    SetConsoleTextAttribute(h, 32);
    cout << 'K';
    SetConsoleTextAttribute(h, 36);
    cout << " G";
    SetConsoleTextAttribute(h, 32);
    cout << 'A';
    SetConsoleTextAttribute(h, 36);
    cout << 'M';
    SetConsoleTextAttribute(h, 32);
    cout << "E" << endl;

    Blackjack bj;
    while (true) {
        for (int i = 0, j = 2; i < 120; i++) {
            SetConsoleTextAttribute(h, 34 + j);
            cout << char(205);
            j *= -1;
        }
        cout << "\n\n START A NEW ROUND    (Press N)\n" <<" DO YOU WANT TO EXIT? (Press E)\n" <<" SHOW LEADERBOARD!    (Press S)\n";
        char hint = ask_hint();
        if (hint == 'n') bj.play();
        else if (hint == 's') bj.dump_leaderboard();
        else if (hint == 'e') break;
    }
    return 0;
}

int main() {

	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 240);
	system("cls");
	SetConsoleTitle(L"BLACKJACK");

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.dwFontSize.X = 10;														// Width of each character in the font
	cfi.dwFontSize.Y = 25;														// Height
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(h, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(h, &structCursorInfo);


	COORD frame_begin = { 0, 4 };										 // BEGIN OF FRAME
	COORD frame_end = { 119, 7 };                                       // END FRAME
	COORD c = { 8, 5 };													 // COODR for key
	int fl = 1, ch, k = 0, n = 4, len = 32;

	draw(h, c, k, n, len);
	frame(h, frame_begin, frame_end);


	while (fl) {

		if (_kbhit()) {

			ch = _getch();

			switch (ch) {

			case 27: {
				fl = 0;
				SetConsoleTextAttribute(h, 240);          // ESC
				system("cls");
				break;
			}

			case 13: {											 // ENTER
				switch (k) {

					case 0: {
						Start(h);
						SetConsoleTextAttribute(h, 240);
						system("cls");
						break;
					}
							
					case 1: {
						About(h);
						break;
					}

					case 2: {
						Help(h);
						break;
					}

					case 3: {
						SetConsoleTextAttribute(h, 240);
						fl = 0;
						system("cls");
					}
				}
			}

			case 77: {
				if (k == n - 1) {
					break;
				}

				else {
					k++;
					draw(h, c, k, n, len);
					frame(h, frame_begin, frame_end);
					break;
				}
			}

			case 75: {
				if (k == 0) {
					break;
				}

				else {
					k--;
					draw(h, c, k, n, len);
					frame(h, frame_begin, frame_end);
					break;
				}
			}
			}
		}
	}
	return 0;
}

void frame(HANDLE h, COORD frame_begin, COORD frame_end) {
	COORD t = frame_begin;
	int len_x = frame_end.X - t.X - 2;
	int len_y = frame_end.Y - t.Y - 2;

	SetConsoleTextAttribute(h, 240);
	SetConsoleCursorPosition(h, frame_begin);

	cout << char(457);
	for (int i = 0; i < len_x; i++) {
		cout << char(461);
	}

	cout << char(443);
	frame_begin.Y++;
	for (int i = 0; i < len_y; i++, frame_begin.Y++) {
		SetConsoleCursorPosition(h, frame_begin);
		cout << char(442);
	}

	SetConsoleCursorPosition(h, frame_begin);
	cout << char(456);
	for (int i = 0; i < len_x; i++) {
		cout << char(461);
	}

	cout << char(444);
	SetConsoleCursorPosition(h, frame_begin);
	frame_begin.X = frame_end.X;
	frame_begin.X--;
	frame_begin.Y--;
	for (int i = 0; i < len_y; i++, frame_begin.Y--) {
		SetConsoleCursorPosition(h, frame_begin);
		cout << char(442);
	}

	SetConsoleTextAttribute(h, 240);
	for (short i = 30; i < 120; i = i + 30) {

		SetConsoleCursorPosition(h, { 4 + i , 4 });
		cout << char(457);

		SetConsoleCursorPosition(h, { 3 + i , 4 });
		cout << char(443);

		SetConsoleCursorPosition(h, { 3 + i , 5 });
		cout << char(442);

		SetConsoleCursorPosition(h, { 4 + i , 5 });
		cout << char(442);

		SetConsoleCursorPosition(h, { 4 + i , 6 });
		cout << char(456);

		SetConsoleCursorPosition(h, { 3 + i , 6 });
		cout << char(444);
	}
	SetConsoleCursorPosition(h, { 113, 10 });
}

void draw(HANDLE h, COORD c, int k, int n, int len) {
	SetConsoleTextAttribute(h, 240);


	SetConsoleCursorPosition(h, { 50,0 });
	cout << "------------------" << endl;
	SetConsoleCursorPosition(h, { 50, 1 });
	cout << "| BLACKJACK GAME |" << endl;
	SetConsoleCursorPosition(h, { 50,2 });
	cout << "------------------" << endl;

	SetConsoleTextAttribute(h, ATTR1);
	COORD cc = c;

	for (int i = 0; i < n; i++) {
		cc.X = c.X + i * len;
		SetConsoleCursorPosition(h, cc);
		cout << m[i];
	}

	cc.X = c.X + k * len;
	SetConsoleTextAttribute(h, ATTR2);
	SetConsoleCursorPosition(h, cc);
	cout << m[k];
}

void Start(HANDLE h) {
	SetConsoleTextAttribute(h, 240);
	system("cls");
	main_1();
	return;
}

void About(HANDLE h) {
	int ch;
	SetConsoleTextAttribute(h, 240);
	system("cls");
	cout << "\nThis program was created by \nVersion 1.0.0\nLicensed product.\n\n\n" << endl;

	cout << "Enter ESC for exit......";

	while (1) {

		ch = _getch();

		if (ch == 27) {

			SetConsoleTextAttribute(h, 240);
			system("cls");
			break;
		}
	}

	system("cls");
}

void Help(HANDLE h) {
	int ch;

	SetConsoleTextAttribute(h, 244);
	system("cls");

	cout << "\n________________________________________________________________________________________________________________________\n" << endl;
	SetConsoleTextAttribute(h, 242);
	cout << "\t\t\t\t\tProgram Overview:\n " << endl;
	SetConsoleTextAttribute(h, 240);
	cout << "Blackjack is the American variant of a globally popular banking game known as Twenty-One." << endl;
	cout << "It is a comparing card game between one player and a dealer, where player competes against the dealer" << endl;
	cout << "It is played with one or more decks of 52 cards, and is the most widely played casino banking game in the world." <<endl;
	cout << "The objective of the game is to beat the dealer in one of the following ways:\n" << endl;
	cout << "1) Get 21 points on the player's first two cards (called a \"blackjack\"), without a dealer blackjack;" << endl;
	cout << "2) Reach a final score higher than the dealer without exceeding 21" << endl;
	cout << "3) Let the dealer draw additional cards until their hand exceeds 21 (\"busted\").\n" << endl;
	cout << "The value of cards two through ten is their pip value (2 through 10).\nFace cards (Jack, Queen, and King) are all worth ten. Aces can be worth one or eleven.\n";
	SetConsoleTextAttribute(h, 244);
	cout << "\n________________________________________________________________________________________________________________________" << endl;
	SetConsoleTextAttribute(h, 242);
	cout << "\n\t\t\t\t\tRules of play:\n\n" << endl;
	SetConsoleTextAttribute(h, 240);
	cout << "The players' object is to win money by creating card totals that turn out to be higher than the dealer's\nhand but do not exceed 21, or alternatively by allowing the dealer to take additional cards until he/she busts.";
	cout << "\nOn their turn, players must choose whether to \"HIT\" (take a card), \"stand\" (end their turn)" << endl;
	cout << "After all boxes have finished playing, the dealer's hand is resolved by drawing cards until the\nhand busts or achieves a value of 17 or higher (a dealer total of 17 including an ace valued as 11,\nalso known as a \"soft 17\",must be drawn to in some games and must stand in others). " << endl;

	SetConsoleTextAttribute(h, 244);
	cout << "________________________________________________________________________________________________________________________\n" << endl;

	SetConsoleCursorPosition(h, { 0, 0 });
	SetConsoleTextAttribute(h, 240);

	cout << "Enter ESC for exit......";

	while (1) {

		ch = _getch();

		if (ch == 27) {

			SetConsoleTextAttribute(h, 240);
			system("cls");
			break;
		}
	}
}
