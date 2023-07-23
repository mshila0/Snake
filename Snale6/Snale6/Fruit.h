#pragma once
#include <stdlib.h>
#include <time.h>

class Fruit {

public:
	int color;    //���� ������
	int x;        //���������� �� �
	int y;        //���������� �� y
	int score;    //����������� �������� �����
	char symbol;  //������� ���
	int type;     //���

	Fruit() {}

	Fruit(int width, int height)
	{
		update_type(width, height);
	}

	void update_type(int width, int height)  //������� ������ ���������� ������,� ����� ��� �������� � ����������� �� �������� ���������� ����
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
		case 0:           //���� ��������� 40 %, �������
			score = 5;
			symbol = 'A';
			color = 4;
			break;
		case 1:           //���� ��������� 30 %, ������
			score = 10;
			symbol = 'P';
			color = 6;
			break;
		case 2:           //���� ��������� 20 %, �������������� ���������� ������, �����
			score = 20;
			symbol = 'B';
			color = 7;
			break;
		case 3:           ////���� ��������� 40 %, ���������� ������, �������
			score = 0;
			symbol = 'G';
			color = 3;
			break;
		}
	}
};