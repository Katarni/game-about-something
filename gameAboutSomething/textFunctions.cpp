#include "textFunctions.h"
#include <iostream>
#include <Windows.h>

using namespace std;

void help() {
	for (int i = 0; i < 90; i++) {
		for (int j = 0; j < 25; j++) {
			if (i == 30 && j == 10) {
				cout << "Добро пожаловать";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
	Sleep(3000);
	system("cls");

	for (int i = 0; i < 90; i++) {
		for (int j = 0; j < 25; j++) {
			if (i == 5) {
				switch (j)
				{
				case 4:
					cout << "Условные обозначения:";
				case 6:
					cout << "\'&\' - ваш персонаж";
				case 8:
					cout << "\'_\' - границы карты";
				case 10:
					cout << "\'#\' - стены";
				case 12:
					cout << "\'*\' - закрытые двери, \'~\' - сломаные двери";
				}
			}
		}
		cout << endl;
	}
	Sleep(4000);
	system("cls");

	for (int i = 0; i < 90; i++) {
		for (int j = 0; j < 25; j++) {
			if (i == 5) {
				switch (j)
				{
				case 4:
					cout << "Правила:";
				case 6:
					cout << "Нельзя ходить через стены и закрытые двери, но двери можно ломать";
				case 8:
					cout << "Клавиши \'WASD\' работают не перемешение";
				case 10:
					cout << "Чтобы ударить в сторону последнего шага нажмите \'Enter\'";
				case 12:
					cout << "Не рекомендуется зажимать клавиши \'WAASD\', ТК персонажа заносит";
				}
			}
		}
		cout << endl;
	}
	Sleep(4000);
	system("cls");
}