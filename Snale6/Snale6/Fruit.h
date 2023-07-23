#pragma once
#include <stdlib.h>
#include <time.h>

class Fruit {

public:
	int color;    //Цвет фрукта
	int x;        //Координата по х
	int y;        //Координата по y
	int score;    //Колличество даваемых очков
	char symbol;  //Внешний вид
	int type;     //Тип

	Fruit() {}

	Fruit(int width, int height)
	{
		update_type(width, height);
	}

	void update_type(int width, int height)  //Функция задает координаты фрукта,а также его свойства в зависимости от рандомно выбранного типа
	{
		x = rand() % (width - 2) + 1;
		y = rand() % (height - 2) + 1;
		int chance = rand() % 100 + 1;
		if (chance <= 40) type = 0;
		else if (chance <= 70) type = 1;
		else if (chance <= 90) type = 2;
		else if (chance <= 100) type = 3;
		switch (type)
		{
		case 0:           //Шанс появления 40 %, красный
			score = 5;
			symbol = 'A';
			color = 4;
			break;
		case 1:           //Шанс появления 30 %, желтый
			score = 10;
			symbol = 'P';
			color = 6;
			break;
		case 2:           //Шанс появления 20 %, дополнительное увеличение змейки, белый
			score = 20;
			symbol = 'B';
			color = 7;
			break;
		case 3:           ////Шанс появления 40 %, уменьшение змейки, голубой
			score = 0;
			symbol = 'G';
			color = 3;
			break;
		}
	}
};