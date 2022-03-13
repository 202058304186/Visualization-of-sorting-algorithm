#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<iostream>
#include "Tools.H"
using namespace std;
#define MAXSIZE 40 //最多定义域 
#define RANGE 50 //数值范围 
#define SLEEPTIME 100

//定义采用顺序表存储的矩形的结构体
/*
	int length:定义定义域[0, length - 1]。 
	int longs[MAXSIZE]: 定义与定义域个数相对应的个数。 
*/
typedef struct node
{
	int longs[MAXSIZE]; 
	int length;
}rectangle;
 
/*
Name: void gotoxy(int x, int y)
Founction: 让指针跳转到pos(x, y)去。
Essentials: 运行窗口上第一个像素点是(0,0) 
*/
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}

//初始化图形：输入一个rectangle结构体和长度，进行初始化 
void InitRectangle(rectangle& data, int length)
{
	data.length = length;
}

//初始化化值域：采用随机数进行初始化 
void CreatRectangle(rectangle& data)
{
	for (int j = 0; j < data.length; j++)
	{
		data.longs[j] = rand() % RANGE + 1;
	}
}

//参数初始化 
void ParameterInit(int* length) {
	InputLimit(length, 0, MAXSIZE);
	if (*length == -1) {
		cout << "初始化失败,程序结束。" ;
		exit(1);
	}
} 

//绘制图像 
void Visualization(rectangle data)
{
	for (int i = 0; i < data.length; i++)
	{
		for (int j = 0; j < data.longs[i]; j++)
		{
			gotoxy(i * 2, RANGE - j);
			printf("□");
		}
	}
}

//绘制一列
void DrawAColumn(int x, int y) {
	for (int i = 0; i < RANGE; i++)
		{
			gotoxy(x * 2, RANGE - i);
			printf("  ");
		}
	for (int i = 0; i < y; i++) {
		gotoxy(x * 2, RANGE); 
		printf("□");
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
		for (int z = 0; z < RANGE; z++)
		{
			gotoxy(i * 2, RANGE - z);
			printf("  ");
		}
		for (int h = 0; h < data.longs[i]; h++)
		{
			gotoxy(i * 2, RANGE - h);
			printf("□");
		}
		for (int x = 0; x < data.longs[i + 1]; x++)
		{
			gotoxy((i + 1) * 2, RANGE - x);
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

