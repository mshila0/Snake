#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <fstream>
#include "Fruit.h"
#include <iomanip>

using namespace std;

bool game_start = true;    //Переменная выхода из страртового меня
bool game_over = false;    //Переменная окончания игры
int width = 30;            //Ширина игрового поля
int height = 20;           //Высота игрового поля
int headX, headY;          //Координаты головы змейки
int score;                 //Колличество набранных очков
vector<int> tailX, tailY;  //Координаты тела змейки
int speed;                 //Задержка прорисовки кадров
int start_menu = 0;        //Переменная подкартинкикартинки в главном меню
int menu = 0;              //Переменная картинки в данном меню
string name;               //Имя игрока
int life;                  //Жизни игрока
bool pause = false;        //Переменная паузы
int difficulty = 1;        //Сложность игры
enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
direction dir;
Fruit fruit1, fruit2;
vector<string> record_name;
vector<int> record_count;
int start_time;
int end_time;

void Setup();        //Базовые настройки игры
void Draw();         //Отрисовка игрового поля
void DrawMenu(int);  //Отрисовка меню
void Input();        //Проверка нажатий клавиш
void Logic();        //Логика игры
void Eat(int type);  //Дейвия при съеденном фрукте
void iorecords(string name, int count);   //Запись результатов в файл
void setCursor(int x, int y) //мерцание
{
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Добавление цвета в консоль

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	setCursor(0, 0);    //Установка позиции курсора
	CONSOLE_CURSOR_INFO curs = { 0 };
	curs.dwSize = sizeof(curs);
	curs.bVisible = FALSE;
	::SetConsoleCursorInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &curs);
	
	DrawMenu(menu);
	while (game_start)
	{
		Input();
	}

	Setup();
	start_time = clock();
	while (!game_over)
	{
		if (!pause)
		{
			Draw();
			Input();
			Logic();
		}
		else Input();
	}
	end_time = clock();
	DrawMenu(1);
	iorecords(name, score);
	
	return 0;
}

void Setup() {
	fruit1 = Fruit(width, height);
	fruit2 = Fruit(width, height);
	dir = STOP;
	headX = width / 2;
	headY = height / 2;
	tailX.push_back(headX);
	tailY.push_back(headY - 1);
	score = 0;
	if (difficulty == 1)
	{
		life = 3;
		speed = 300;
	}
	if (difficulty == 2)
	{
		life = 2;
		speed = 200;
	}
	if (difficulty == 3)
	{
		life = 1;
		speed = 100;
	}
}

void  DrawMenu(int menu) {
	system("cls");
	if (menu == 0) {
		SetConsoleTextAttribute(hConsole, 2); //Зеленый цвет текста
		cout << endl;
		cout << "                                      $$                  " << endl;
		cout << "           $$$$    $$   $$  $$$$$$  $$  $$  $$  $$   $$$$ " << endl;
		cout << "          $    $$  $$$ $$$  $$      $$  $$  $$ $$   $$  $$" << endl;
		cout << "             $$$   $$ $ $$  $$$$    $$ $$$  $$$$    $$$$$$" << endl;
		cout << "          $    $$  $$   $$  $$      $$$ $$  $$ $$   $$  $$" << endl;
		cout << "            $$$$   $$   $$  $$$$$$  $$  $$  $$  $$  $$  $$" << endl << endl << endl;
		SetConsoleTextAttribute(hConsole, 15); //Белый цвет текста
		if (start_menu == 0)
		{
			SetConsoleTextAttribute(hConsole, 14); //Желтый цвет текста
			cout << "             >   Правила" << endl << endl;
			SetConsoleTextAttribute(hConsole, 15);
			cout << "                  Начать игру" << endl << endl;
			cout << "                  Таблица рекордов" << endl << endl;
			cout << "                  Выйти из игры" << endl << endl;
		}
		else if (start_menu == 1)
		{
			cout << "                  Правила" << endl << endl;
			SetConsoleTextAttribute(hConsole, 14);
			cout << "             >   Начать игру" << endl << endl;
			SetConsoleTextAttribute(hConsole, 15);
			cout << "                  Таблица рекордов" << endl << endl;
			cout << "                  Выйти из игры" << endl << endl;
		}
		else if (start_menu == 2)
		{
			cout << "                  Правила" << endl << endl;
			cout << "                  Начать игру" << endl << endl;
			SetConsoleTextAttribute(hConsole, 14);
			cout << "             >   Таблица рекордов" << endl << endl;
			SetConsoleTextAttribute(hConsole, 15);
			cout << "                  Выйти из игры" << endl << endl;
		}
		else
		{
			cout << "                  Правила" << endl << endl;
			cout << "                  Начать игру" << endl << endl;
			cout << "                  Таблица рекордов" << endl << endl;
			SetConsoleTextAttribute(hConsole, 14);
			cout << "             >   Выйти из игры" << endl << endl;
			SetConsoleTextAttribute(hConsole, 15);
		}
	}
	else if (menu == 1)
	{
		int search_time = (end_time - start_time) / 1000;
		int hour = 0, minute = 0, second = 0;
		if (search_time > 3600)
		{
			hour /= 3600;
			search_time %= 3600;
		}
		if (search_time > 60)
		{
			minute /= 60;
			search_time %= 60;
		}
		second = search_time;
		SetConsoleTextAttribute(hConsole, 2);
		cout << endl << endl;
		cout << "                     $$  $$  $$$$$$  $$$$$    $$$$ " << endl;
		cout << "                     $$  $$  $$      $$  $$  $$  $$" << endl;
		cout << "                     $$ $$$  $$      $$$$$$  $$$$$$" << endl;
		cout << "                     $$$ $$  $$      $$      $$  $$" << endl;
		cout << "                     $$  $$  $$      $$      $$  $$" << endl << endl;
		cout << "           $$$$  $$  $$  $$$$  $$  $$ $$  $$ $$$$$$ $$  $$  $$$$" << endl;
		cout << "          $$  $$ $$ $$  $$  $$ $$  $$ $$  $$ $$     $$  $$ $$  $$" << endl;
		cout << "          $$  $$ $$$$   $$  $$ $$$$$$  $$$$$ $$$$   $$$$$$ $$$$$$" << endl;
		cout << "          $$  $$ $$ $$  $$  $$ $$  $$     $$ $$     $$  $$ $$  $$" << endl;
		cout << "           $$$$  $$  $$  $$$$  $$  $$     $$ $$$$$$ $$  $$ $$  $$" << endl << endl << endl;
		SetConsoleTextAttribute(hConsole, 15);
		cout << "                          Ваш счет: " << score << endl << endl;
		cout << "                          Время игры: " << hour << " : " << minute << " : " << second << endl << endl;
		cout << "                          Введите свое имя: ";
		cin >> name;
	}
	if (menu == 2)
	{
		SetConsoleTextAttribute(hConsole, 2);
		cout << endl << endl;
		cout << "          $$$$$$  $$$$$    $$$$   $$$$$   $$  $$     $$$   $$$$" << endl;
		cout << "          $$  $$  $$  $$  $$  $$  $$  $$  $$  $$    $ $$  $$  $$" << endl;
		cout << "          $$  $$  $$$$$$  $$$$$$  $$$$$   $$ $$$   $  $$  $$$$$$" << endl;
		cout << "          $$  $$  $$      $$  $$  $$  $$  $$$ $$  $$  $$  $$  $$" << endl;
		cout << "          $$  $$  $$      $$  $$  $$$$$   $$  $$  $$  $$  $$  $$" << endl << endl << endl;
		SetConsoleTextAttribute(hConsole, 15);
		cout << "             * Стрелки вверх, вниз – переключение между пунктами в меню" << endl;
		cout << "             * Стрелка влево – возврат в предыдущее меню" << endl;
		cout << "             * W, s, a, d – управление движением змейки вверх, вниз, вправо, влево, соответственно" << endl;
		cout << "             * ESC – выход из игры" << endl;
		cout << "             * P – пауза в игре" << endl;
		cout << "             * Каждый съеденный фрукт немного увеличивает скорость змейки" << endl << endl;
		cout << "             * В игре есть 4 вида фруктов:" << endl;
		cout << "	                 ~ Яблоко    – дает 5 очков" << endl;
		cout << "	                 ~ Ананас    – дает 10 очков" << endl;
		cout << "	                 ~ Банан     – дает 20 очков и увеличевает змейку на  3 сегмента" << endl;
		cout << "	                 ~ Грейпфрут – не дает очков, но уменьшает змейку на 4 сегмента" << endl << endl;
		cout << "             * Игрок может выбрать уровень сложности:" << endl;
		cout << "	                 ~ Лекгий  – медленная начальная скорость, 3 жизни" << endl;
		cout << "	                 ~ Средний – средняя начальная скорость, 2 жизни" << endl;
		cout << "	                 ~ Сложный – быстрая начальная скорость, 1 жизнь" << endl;


	}
	if (menu == 3)
	{
		SetConsoleTextAttribute(hConsole, 2);
		cout << endl << endl;
		cout << "         $$$$$   $$$$$$  $$  $$   $$$$   $$$$$     $$$    $$   $$" << endl;
		cout << "         $$  $$  $$      $$ $$   $$  $$  $$  $$   $$ $$   $$   $$" << endl;
		cout << "         $$$$$$  $$$$    $$$$    $$  $$  $$$$$$   $$ $$   $$$$ $$" << endl;
		cout << "         $$      $$      $$ $$   $$  $$  $$      $$$$$$$  $$ $ $$" << endl;
		cout << "         $$      $$$$$$  $$  $$   $$$$   $$      $     $  $$$$ $$" << endl << endl << endl;
		SetConsoleTextAttribute(hConsole, 15);
		ifstream file1;
		file1.open("records.txt");
		int n = 1;
		if (file1.is_open())
		{
			string name;
			int count;
			while (file1 >> name >> count)
			{
				cout << "                " << n << ". " << left << setw(10) << name << " " << count << endl;
				n++;
			}
			for (; n <= 10; n++)
			{
				cout << "                " << n << ". --" << endl;
			}
		}
		file1.close();
	}
	if (menu == 4)
	{
		SetConsoleTextAttribute(hConsole, 2); //Зеленый цвет текста
		cout << endl << endl;
		cout << "          $$$$     $$$  $$$$  $$ $ $$ $$  $$  $$$$   $$$$  $$$$$$$$" << endl;
		cout << "         $$  $$   $ $$ $$  $$  $$$$$  $$  $$ $$  $$ $$  $$   $$   $$ " << endl;
		cout << "         $$      $  $$ $$  $$   $$$   $$$$$$ $$  $$ $$       $$   $$$$" << endl;
		cout << "         $$  $$ $$  $$ $$  $$  $$$$$  $$  $$ $$  $$ $$  $$   $$   $$  $$" << endl;
		cout << "          $$$$  $$  $$  $$$$  $$ $ $$ $$  $$  $$$    $$$$    $$   $$$$$" << endl << endl << endl;
		if (difficulty == 1)
		{
			SetConsoleTextAttribute(hConsole, 14); //Желтый цвет текста
			cout << "             >   Легкая" << endl << endl;
			SetConsoleTextAttribute(hConsole, 15);
			cout << "                  Средння" << endl << endl;
			cout << "                  Сложнная" << endl << endl;
		}
		if (difficulty == 2)
		{
			SetConsoleTextAttribute(hConsole, 15);
			cout << "                  Легкая" << endl << endl;
			SetConsoleTextAttribute(hConsole, 14);
			cout << "             >   Средння" << endl << endl;
			SetConsoleTextAttribute(hConsole, 15);
			cout << "                  Сложнная" << endl << endl;
		}
		if (difficulty == 3)
		{
			SetConsoleTextAttribute(hConsole, 15);
			cout << "                  Легкая" << endl << endl;
			cout << "                  Средння" << endl << endl;
			SetConsoleTextAttribute(hConsole, 14);
			cout << "             >   Сложнная" << endl << endl;
		}
		SetConsoleTextAttribute(hConsole, 2);
		cout << "             * Нажмите стрелку влево (->) чтобы выбрать сложность игры" << endl << endl;
	}
}

void Draw() {
	system("cls");

	for (int i = 0; i < width; i++) {
		SetConsoleTextAttribute(hConsole, 8);
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
			{
				SetConsoleTextAttribute(hConsole, 8); //тмено-серый
				cout << "#";
				if (i == 4 && j == width - 1)
				{
					SetConsoleTextAttribute(hConsole, 7);
					cout << "        Счет: " << score;
				}
				if (i == 6 && j == width - 1)
				{
					SetConsoleTextAttribute(hConsole, 7);
					cout << "        Длина змейки: " << tailX.size() + 1;
				}
				if (i == 8 && j == width - 1)
				{
					SetConsoleTextAttribute(hConsole, 7);
					cout << "        Жизни: " << life;
				}
			}
			else if (i == headY && j == headX)
			{
				SetConsoleTextAttribute(hConsole, 10);
				cout << "0";
			}
			else if (i == fruit1.y && j == fruit1.x)
			{
				SetConsoleTextAttribute(hConsole, fruit1.color);
				cout << fruit1.symbol;
			}
			else if (i == fruit2.y && j == fruit2.x)
			{
				SetConsoleTextAttribute(hConsole, fruit2.color);
				cout << fruit2.symbol;
			}
			else {
				bool print = false;
				for (int k = 0; k < tailX.size(); k++) {
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						SetConsoleTextAttribute(hConsole, 2);
						cout << "o";
					}
				}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width; i++) {
		SetConsoleTextAttribute(hConsole, 8);
		cout << "#";
	}
	SetConsoleTextAttribute(hConsole, 15);
	cout << endl << endl;
	cout << "   ~ Яблоко 'A' – дает 5 очков" << endl;
	cout << "	~ Ананас 'P' – дает 10 очков" << endl;
	cout << "	~ Банан  'B' – дает 20 очков и увеличевает змейку на  3 сегмента" << endl;
	cout << "	~ Грейпфрут 'G' – не дает очков, но уменьшает змейку на 4 сегмента" << endl;

	Sleep(speed);
}

void Input() {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT; break;
		case 'd':
			dir = RIGHT; break;
		case 'w':
			dir = UP; break;
		case 's':
			dir = DOWN; break;

		case 27: // ESC
			game_over = true; break;
		case 'p':
			if (pause == false)
			{
				pause = true; break;
			}
			else
				pause = false; break;

		case 80: // Стрелка вниз "menu: 0 - главная 1 - правила, 2 - конец, 3 - рекорды, 4 - сложность"
			if (menu == 0)
			{
				if (start_menu == 3)
					start_menu = 0;
				else
					start_menu++;
				DrawMenu(menu);
			}
			if (menu == 4)
			{
				if (difficulty == 3)
					difficulty = 1;
				else
					difficulty++;
				DrawMenu(menu);
			}
			break;
		case 72: // Стрелка вверх "start_menu: 0 - правила, 1 - игра, 2 - рекорды, 3 - выход"
			if (menu == 0)
			{
				if (start_menu == 0)
					start_menu = 3;
				else
					start_menu--;
				DrawMenu(menu);
			}
			if (menu == 4)
			{
				if (difficulty == 1)
					difficulty = 3;
				else
					difficulty--;
				DrawMenu(menu);
			}
			break;
		case 75: // Стрелка влево
			if (menu == 2 or menu == 3)
				menu = 0;
				DrawMenu(menu);
			break;
		case 77: // Стрелка вправо
			if (difficulty == 1 && menu == 4)
				game_start = false;
			if (difficulty == 2 && menu == 4)
				game_start = false;
			if (difficulty == 3 && menu == 4)
				game_start = false;
			break;
		case 13:  // Enter
			if (start_menu == 0)
			{
				menu = 2;
				DrawMenu(menu);
			}
			else if (start_menu == 3)
				exit(0);
			else if (start_menu == 2)
			{
				menu = 3;
				DrawMenu(menu);
			}
			else if (start_menu == 1)
			{
				menu = 4;
				DrawMenu(menu);
			}
			break;
		}
	}
}

void Logic() {
	// если игра началась начать двигаться
	if (dir != STOP)
	{
		int temp1[2] = { tailX[0], tailY[0] };
		int temp2[2];
		tailX[0] = headX;
		tailY[0] = headY;
		for (int q = 1; q < tailX.size(); q++)
		{
			temp2[0] = tailX[q];
			temp2[1] = tailY[q];

			tailX[q] = temp1[0];
			tailY[q] = temp1[1];

			temp1[0] = temp2[0];
			temp1[1] = temp2[1];
		}
	}

	switch (dir)
	{
	case LEFT:
		headX--; break;
	case RIGHT:
		headX++; break;
	case UP:
		headY--; break;
	case DOWN:
		headY++; break;
	}

	// перемещение через стенки 
	if (headX >= width - 1)
		headX = 0;
	else if (headX < 1)
		headX = width - 2;
	if (headY >= height)
		headY = 0;
	else if (headY < 0)
		headY = height - 1;

	// проверка на столкновение головы с хвостом
	for (int q = 0; q < tailX.size(); q++)
	{
		if (tailX[q] == headX && tailY[q] == headY)
			life--;
	}

	// столкновение с фруктом 1
	if (headX == fruit1.x && headY == fruit1.y)
	{
		score += fruit1.score;
		Eat(fruit1.type);
		fruit1.update_type(width, height);
		if (speed >= 10)
		{
			speed -= 5;
		}
	}
	// столкновение с фруктом 2
	if (headX == fruit2.x && headY == fruit2.y)
	{
		score += fruit2.score;
		Eat(fruit2.type);
		fruit2.update_type(width, height);
		if (speed >= 10)
		{
			speed -= 5;
		}
	}
	if (life == 0)
		game_over = true;
}

void Eat(int type) // изменение длины змейки, зависящие от типа съеденного фрукта
{
	if (type == 3)
	{
		if (tailX.size() <= 4)
		{
			game_over = true;
		}
		else
		{
			tailX.pop_back();
			tailX.pop_back();
			tailY.pop_back();
			tailY.pop_back();
			tailX.pop_back();
			tailY.pop_back();
			tailX.pop_back();
			tailY.pop_back();
		}
	}
	else if (type == 2)
	{
		tailX.push_back(NULL);
		tailY.push_back(NULL);
		tailX.push_back(NULL);
		tailY.push_back(NULL);
		tailX.push_back(NULL);
		tailY.push_back(NULL);
	}
	else
	{
		tailX.push_back(NULL);
		tailY.push_back(NULL);
	}
}

void iorecords(string player_name, int player_count)
{
	ifstream file1;
	ofstream file2;
	file1.open("records.txt");
	if (file1.is_open())
	{
		string name;
		int count;
		while (file1 >> name >> count)
		{
			if (record_name.empty() or (name != record_name.back() or count != record_count.back()))
			{
				record_name.push_back(name);
				record_count.push_back(count);
			}
		}
	}
	file1.close();

	file2.open("records.txt");
	if (file2.is_open())
	{
		int n = 10;
		for (int q = 0; q < record_name.size() and q < n; q++)
		{
			if (record_count[q] > player_count or n == 9)
			{
				file2 << record_name[q] << " " << record_count[q] << endl;
			}
			else if (n == 10)
			{
				file2 << player_name << " " << player_count << endl;
				q--;
				n--;
			}

			if (n == 10 and q == record_name.size() - 1 and q < 9)
			{
				file2 << player_name << " " << player_count << endl;
			}
		}
	}
	file2.close();
}