#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<iostream>
using namespace std;
#define bottom 50
#define MaxSize 40
#define Range 50
#define SLEEPTIME 100

typedef struct node
{
	int longs[MaxSize];
	int length;
}rectangle;

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}

void InitRectangle(rectangle& data, int i)
{
	data.length = i;
}

void CreatRectangle(rectangle& data)
{
	for (int j = 0; j < data.length; j++)
	{
		data.longs[j] = rand() % Range + 1;
	}
}

void Visualization(rectangle data)
{
	for (int i = 0; i < data.length; i++)
	{
		for (int j = 0; j < Range; j++)
		{
			gotoxy(i * 2, Range - j);
			printf("  ");
		}
		for (int j = 0; j < data.longs[i]; j++)
		{
			gotoxy(i * 2, Range - j);
			printf("□");
		}
	}
}

int Check(rectangle data)
{
	int count = 0;
	HANDLE hOut = NULL;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, 10);

	for (int i = 0; i < data.length - 1; i++)
	{
		for (int z = 0; z < Range; z++)
		{
			gotoxy(i * 2, Range - z);
			printf("  ");
		}
		for (int h = 0; h < data.longs[i]; h++)
		{
			gotoxy(i * 2, Range - h);
			printf("□");
		}
		for (int x = 0; x < data.longs[i + 1]; x++)
		{
			gotoxy((i + 1) * 2, Range - x);
			printf("□");
		}
		Sleep(SLEEPTIME * 5);

		if (data.longs[i] > data.longs[i + 1])
		{
			count = 1;
		}
	}

	if (count == 0)
	{
		SetConsoleTextAttribute(hOut, 7);
		return 1;
	}
	else return 0;
}

