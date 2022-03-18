/*
* 头文件意义--->
* 存放所有的核心文件
* 关于其中可能不明白的解释：
* 1.关于HANDLE语句以及很多奇怪的语句
*	除了所学的基本知识以外，我只添加了颜色功能。
*	详见：https://blog.csdn.net/dengjin20104042056/article/details/90488100?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522162143687116780274160567%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=162143687116780274160567&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-90488100.first_rank_v2_pc_rank_v29&utm_term=%E3%80%90C%E8%AF%AD%E8%A8%80%E3%80%91%E6%8E%A7%E5%88%B6%E5%8F%B0%E7%AA%97%E5%8F%A3%E5%9B%BE%E5%BD%A2%E7%95%8C%E9%9D%A2%E7%BC%96%E7%A8%8B&spm=1018.2226.3001.4187
*/
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<iostream>
#include "Tools.H"
using namespace std;
#define MAXSIZE 40 //最多定义域 
#define RANGE 30 //数值范围 
#define SLEEPTIME 100 //休眠时间

//定义句柄,配置初始化环境参数
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO src;
void init() {
	GetConsoleScreenBufferInfo(hOut, &src);
}

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
void CreatRectangle(rectangle &data)
{
	srand(time(NULL));
	for (int j = 0; j < data.length; j++)
	{
		data.longs[j] = abs(rand() % RANGE) + 1;
	}
}

/*
* Parameters--->
* int* length: 一个指向长度信息的指针
* Founction--->
* 初始化长度等。
*/
void ParameterInit(int* length) {
	InputLimit(length, 0, MAXSIZE);
	if (*length == -1) {
		cout << "初始化失败,程序结束。" ;
		exit(1);
	}
} 

//绘制图像:静态的打印数据图像
void Visualization(int* data, int length, int Start = RANGE)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < data[i]; j++)
		{
			gotoxy(i * 2, Start - j);
			printf("□");
		}
	}
}

/*
* parameters--->
* int x: 绘图的行坐标
* int y: 绘图的长度
* DWORD color：颜色字段
* int start（默认属性）：莫认值为RANGE = 30，指定绘图开始地点
* Founction--->
* To draw a column of rectangle with the color you want.
*/
void DrawAColumn(int x, int y, DWORD color, int start = RANGE) {
	
	SetConsoleTextAttribute(hOut, color);
	for (int i = 0; i < y; i++) {
		gotoxy(x * 2, start - i); 
		printf("□");
	}	
	SetConsoleTextAttribute(hOut, src.wAttributes);
} 

//删除一列
void DelAColumn(int x, int y, int Start = RANGE) {
	for (int i = 0; i < y; i++){
		gotoxy(x * 2, Start - i);
		printf("  ");
	}	
} 

//显示扫描的列，12表示绘图颜色，7表示绘图颜色
void Scanning(int x, int y, int start = RANGE) {
	DelAColumn(x, y, start);
	DrawAColumn(x, y, 12, start);
	Sleep(SLEEPTIME);
	DelAColumn(x, y, start);
	DrawAColumn(x, y, 7, start);
} 

//交换显示 
void Swap(rectangle data, int pre, int after, int start = RANGE) {
	DelAColumn(after, data.longs[after], start);
	DrawAColumn(after, data.longs[after], 12, start);
	Sleep(SLEEPTIME);
	DelAColumn(pre, data.longs[pre], start);
	DelAColumn(after, data.longs[after], start);
	DrawAColumn(pre, data.longs[after], 12, start);
	DrawAColumn(after, data.longs[pre], 12, start);
	Sleep(SLEEPTIME);
	DelAColumn(pre, data.longs[after], start);
	DelAColumn(after, data.longs[pre], start);
	DrawAColumn(pre, data.longs[after], 7, start);
	DrawAColumn(after, data.longs[pre], 7, start);
} 

//有序列表显示
void showOrder (int x, int y, int start = RANGE) {
	DelAColumn(x, y, start);
	DrawAColumn(x, y, 12, start);
}

//是否有序检查
int Check(int* data, int length, int start = RANGE)
{
	int count = 0;
	HANDLE hOut = NULL;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, 10);

	for (int i = 0; i < length - 1; i++)
	{
		for (int z = 0; z < RANGE; z++)
		{
			gotoxy(i * 2, RANGE - z);
			printf("  ");
		}
		for (int h = 0; h < data[i]; h++)
		{
			gotoxy(i * 2, RANGE - h);
			printf("□");
		}
		for (int x = 0; x < data[i + 1]; x++)
		{
			gotoxy((i + 1) * 2, RANGE - x);
			printf("□");
		}
		Sleep(SLEEPTIME * 0.1);

		if (data[i] > data[i + 1])
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

//冒泡排序可视化
int Bubble_sort() {
	RunningTips("Bubble Sort");
	init();
	rectangle data;
	int length = 0;
	int times = 0;
	int swap_times = 0;
	ParameterInit(&length);
	InitRectangle(data, length);
	CreatRectangle(data);
	Visualization(data.longs, data.length);
	for (int i = 0; i < data.length - 1; ++i) {
		int flag = 0;
		for (int j = 0; j < data.length - i - 1; ++j) {
			Scanning(j, data.longs[j]);
			times++;
			if (data.longs[j] > data.longs[j + 1]) {
				flag++;
				swap_times++;
				Swap(data, j, j + 1);
				int tmp = data.longs[j];
				data.longs[j] = data.longs[j + 1];
				data.longs[j + 1] = tmp;
			}
		}
		showOrder(data.length - i - 1, data.longs[data.length - i - 1]);
		if (!flag) {
			break;
		}
	}
	Check(data.longs, data.length);
	gotoxy(0, RANGE + 3);
	cout << "共扫描：" << times << "行。" << endl;
	cout << "共交换：" << swap_times << "次。";
	system("pause");
	system("cls");
	return 0;
}

//直接插入排序可视化
int DIS() {
	RunningTips("Direct Insert Sort");
	int length;
	rectangle data;
	ParameterInit(&length);
	InitRectangle(data, length);
	CreatRectangle(data);

	int* data_ = (int*)malloc(sizeof(int) * (length + 3));
	*data_ = 0;
	for (int i = 0; i < length - 1; ++i) {
		data_[i + 1] = data.longs[i];
	}
	Visualization(data_, length + 1);

	for (int i = 1; i < length + 1; ++i) {
		//绘制哨兵
		DelAColumn(0, data_[0]);
		*data_ = data_[i];
		DrawAColumn(0, data_[0], 14);
		Sleep(SLEEPTIME * 2);

		//存值
		DelAColumn(i, data_[i]);
		DrawAColumn(i, data_[i], 12, 2 * RANGE + 2);
		Sleep(SLEEPTIME * 8);
		int j = i;

		//寻找插入位置，比较并挪动
		while (data_[0] < data_[j - 1]) {
			//绘制比较列
			DelAColumn(j - 1, data_[j - 1]);
			DrawAColumn(j - 1, data_[j - 1], 58);
			Sleep(SLEEPTIME * 5);
			//删除比较列
			DelAColumn(j - 1, data_[j - 1]);
			//删除移动列 
			DelAColumn(j - 1, data_[j - 1]);
			//绘制移动列 
			DrawAColumn(j, data_[j - 1], 185);
			Sleep(SLEEPTIME * 2);
			//删除红色残留 
			DelAColumn(j, data_[0], 2 * RANGE + 2);
			//画新的红色 
			DrawAColumn(j - 1, data_[0], 12, 2 * RANGE + 2);
			Sleep(SLEEPTIME * 5);
			//数据移动 
			data_[j] = data_[j - 1];
			j--;
		}

		//找到插入位置进行合并,由于加入了哨兵，所以这里并不需要进行溢出判断
		data_[j] = data_[0];
		DelAColumn(j, data_[j], 2 * RANGE + 2);
		DrawAColumn(j, data_[j], 12);
		Sleep(SLEEPTIME * 5);
		DelAColumn(j, data_[j]);
		DrawAColumn(j, data_[j], 185);
		Sleep(SLEEPTIME * 10);
	}
	Check(data_, length + 1);
	gotoxy(0, RANGE + 5);
	free(data_);
	system("cls");
	return 0;
}