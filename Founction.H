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
using namespace std;
//Tools区常量
#define S_POS_SWAP  15
#define S_POS_TIMES 39
#define S_POS_X 65
#define S_POS_Y 71

//Founction取常量
#define MAXSIZE 40 //最多定义域 
#define RANGE 30 //数值范围 
#define SLEEPTIME 100 //休眠时间
/*
* 函数申明区域
*/
void gotoxy(int x, int y);
void _QuickSort(int* data, int left, int right, int Start, int Info[2]);

/*
* Tool区域-----------------------------------------------------------------------------------------------------------------
*/
void InputLimit(int* input, float left_border, float right_border, float accuracy = 0.001) {
	cout << "请输入值（最大值为40）：";
	cin >> *input;
	int count = 0;
	while (*input - left_border < accuracy || *input - right_border > accuracy && count++ < 3) {
		printf("输入非法请重新输入（最大值为%d）：", (int)right_border);
		cin >> *input;
	}
	*input = count < 3 ? *input : left_border - 1;
	system("cls");
}

void RunningTips(const char* tips) {
	cout << "Running\t" << tips << endl;
	Sleep(1000);
	system("cls");
	return;
}

/*
* Parameters=====>
* None
* Founctions=====>
* show the initial infomation.
*/
void showInfo() {
	cout << "swapped times: 0000    |";
	cout << "scanned times: 0000    |";
	cout << "now scanning : x-00, y-00";
}

/*
* this founction will convert int data into char type array.
* Parameters===========>
* int bits: this parameter is used for specifying the number of the length of converstion array.
* int val: this parameter is the int data that will be converted the parrtern, for instance, 42 ----> 0042
* 
*/
char* intToCharArray(int bits, int val) {
	char* res = (char*)malloc(sizeof(char) * (bits + 1));
	*(res + bits) = '\0';
	for (int i = bits - 1, j = 0; i >= 0; --i) {
		if (val / (int)(pow(10, i)) == 0) {
			*(res + j++) = '0';
		}
		else {
			*(res + j++) = 48 + (val / (int)(pow(10, i)));
			val = val % (int)(pow(10, i));
		}
	}
	return res;
}

/*
* Parameters=====>
* int swaptimes: the times of swap.It should take four spaces.
* int scantimes: the times of scan.It should take four spaces.
* int X: the pos of X.It should take two spaces.
* int Y: the pos of Y.It should take two spaces.
* Founctions=====>
* To update the infomation of sorting.
*/
void updateInfo(int swaptimes, int scantimes, int X, int Y) {
	int j = 0;
	char* str1 = intToCharArray(4, swaptimes);
	gotoxy(S_POS_SWAP, 0);
	cout << str1;
	free(str1);

	char* str2 = intToCharArray(4, scantimes);
	gotoxy(S_POS_TIMES, 0);
	cout << str2;
	free(str2);

	char* str3 = intToCharArray(2, X);
	gotoxy(S_POS_X, 0);
	cout << str3;
	free(str3);

	char* str4 = intToCharArray(2, Y);
	gotoxy(S_POS_Y, 0);
	cout << str4;
	free(str4);

	gotoxy(0, 0);
}


/*
* Founction区--------------------------------------------------------------------------------------------------------------------------
*/
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
	COORD pos = { x, y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}

//初始化图矩形数组：输入一个rectangle结构体和长度，进行初始化 
void InitRectangle(rectangle& data, int length)
{
	data.length = length;
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
void DrawAColumn(int x, int y, WORD color, int start = RANGE) {
	
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

//交换显示,显示比较并且交换 
void Swap(rectangle data, int pre, int after, int Start = RANGE) {
	DelAColumn(after, data.longs[after], Start);
	DrawAColumn(after, data.longs[after], 12, Start);
	Sleep(SLEEPTIME);

	DelAColumn(pre, data.longs[pre], Start);
	DelAColumn(after, data.longs[after], Start);
	DrawAColumn(pre, data.longs[after], 12, Start);
	DrawAColumn(after, data.longs[pre], 12, Start);
	Sleep(SLEEPTIME);

	DelAColumn(pre, data.longs[after], Start);
	DelAColumn(after, data.longs[pre], Start);
	DrawAColumn(pre, data.longs[after], 7, Start);
	DrawAColumn(after, data.longs[pre], 7, Start);
} 
void Swap(int* data, int pre, int after, int Start = RANGE, WORD Emphases = 12, WORD Recovery = 7, WORD Change = 12, int sTime = 1) {
	//突出显示after的值
	DelAColumn(after, data[after], Start);
	DrawAColumn(after, data[after], Emphases, Start);
	Sleep(SLEEPTIME * sTime);
	
	//显示交换后的值
	DelAColumn(pre, data[pre], Start);
	DelAColumn(after, data[after], Start);
	DrawAColumn(pre, data[after], Change, Start);
	DrawAColumn(after, data[pre], Change, Start);
	Sleep(SLEEPTIME * sTime);

	//重绘结束后的值
	DelAColumn(pre, data[after], Start);
	DelAColumn(after, data[pre], Start);
	DrawAColumn(pre, data[after], Recovery, Start);
	DrawAColumn(after, data[pre], Recovery, Start);
}

//标记一个窗口内的所有矩形
void TargetSegment(rectangle data, int left, int right, int Start = RANGE) {
	for (int x = left; x <= right; x++) {
		DelAColumn(x, *(data.longs + x), Start);
		DrawAColumn(x, *(data.longs + x), 12, Start);
	}
	Sleep(SLEEPTIME * 5);
}
//重载函数用于支持整形数组
void TargetSegment(int* data, int left, int right, int Start = RANGE) {
	for (int x = left; x <= right; x++) {
		DelAColumn(x, *(data + x), Start);
		DrawAColumn(x, *(data + x), 12, Start);
	}
	Sleep(SLEEPTIME * 5);
}
//取消标记一个窗口内的所有矩形
void CancelSegment(rectangle data, int left, int right, int Start = RANGE) {
	for (int x = left; x <= right; x++) {
		DelAColumn(x, *(data.longs + x), Start);
		DrawAColumn(x, *(data.longs + x), 7, Start);
	}
	Sleep(SLEEPTIME);
}
//重载函数用于支持整型数组
void CancelSegment(int* data, int left, int right, int Start = RANGE) {
	for (int x = left; x <= right; x++) {
		DelAColumn(x, *(data + x), Start);
		DrawAColumn(x, *(data + x), 7, Start);
	}
	Sleep(SLEEPTIME);
}

//有序列表显示
void showOrder (int x, int y, WORD color = 12, int start = RANGE) {
	DelAColumn(x, y, start);
	DrawAColumn(x, y, color, start);
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
		DelAColumn(i, data[i], start);
		DrawAColumn(i, data[i], 10, start);
		DelAColumn(i + 1, data[i + 1], start);
		DrawAColumn(i + 1, data[i + 1], 10, start);
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

	int* data_ = (int*)malloc(sizeof(int) * (length + 3));
	data_[0] = 0;
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

//希尔排序：第一个突破O(n^2)的算法，是简单插入排序的升级版
/*
*	选择一个增量序列 t1，t2，……，tk，其中 ti > tj, tk = 1；
*
*	按增量序列个数 k，对序列进行 k 趟排序；
*
*	每趟排序，根据对应的增量 ti，将待排序列分割成若干长度为 m 的子序列，分别对各子表进行直接插入排序。
*
*	仅增量因子为 1 时，整个序列作为一个表来处理，表长度即为整个序列的长度。
*/
int Shell_sort() {
	//初始化过程
	RunningTips("Shell Sort");
	init();
	rectangle data;
	int length = 0;
	//扫描次数
	int times = 0;
	//交换次数
	int swap_times = 0;
	//参数初始化
	ParameterInit(&length);
	//生成矩形数组
	InitRectangle(data, length);
	showInfo();
	//静态打印初始图形
	Visualization(data.longs, data.length, RANGE + 1);
	//排序过程
	int gap;//增量
	int temp;//哨兵
	int i, j;
	WORD color = 2;
	//外循环得到分组
	for (gap = data.length >> 1; gap > 0; gap >>= 1) {
		//分组
		for (i = gap; i < data.length; ++i) {
			
			//存值
			temp = data.longs[i];
			
			
			//绘制开始位置，决定主色调
			WORD color_may = (i % 5 + 10);
			color = color_may == color ? (i + 1) % 5 + 10 : color_may;
			//显示temp
			DelAColumn(i, temp, RANGE + 1);
			DrawAColumn(i, temp, color, RANGE + 1);
			//向下temp
			DelAColumn(i, temp, RANGE + 1);
			DrawAColumn(i, temp, color, 2 * (RANGE + 1));
		
			Visualization(data.longs, data.length, RANGE + 1);
			times++;
			updateInfo(swap_times, times, i, data.longs[i]);
			//进行比较,并移动位置
			for (j = i - gap; j >= 0 && data.longs[j] > temp; j -= gap) {
				//统计次数
				swap_times++;
				
				//绘制比较行
				DelAColumn(j, data.longs[j], RANGE + 1);
				DrawAColumn(j, data.longs[j], color, RANGE + 1);
				DelAColumn(j + gap, data.longs[j + gap], RANGE + 1);
				DrawAColumn(j + gap, data.longs[j + gap], color, RANGE + 1);
				Sleep(SLEEPTIME * 5);

				//清除移动行 与 被移动行
				DelAColumn(j, data.longs[j], RANGE + 1);
				DelAColumn(j + gap, data.longs[j + gap], RANGE + 1);
				//清除之前的temp
				DelAColumn(j + gap, data.longs[j + gap], RANGE * 2 + 2);
				//绘制新的temp
				DrawAColumn(j, data.longs[j], color, RANGE * 2 + 2);

				//移动值
				updateInfo(swap_times, times, i, data.longs[i]);
				data.longs[j + gap] = data.longs[j];

				//绘制移动后的行
				DrawAColumn(j + gap, data.longs[j + gap], color, RANGE + 1);
				Sleep(SLEEPTIME * 5);
			}
			//插入
			//清除temp
			DelAColumn(j + gap, data.longs[j + gap], 2 * RANGE + 2);
			DelAColumn(j + gap, data.longs[j + gap], RANGE + 1);
			data.longs[j + gap] = temp;
			DrawAColumn(j + gap, data.longs[j + gap], color, RANGE + 1);
			Sleep(SLEEPTIME * 5);
		}
	}
	//更新数据
	updateInfo(swap_times, times, i, data.longs[i]);
	//检查是否有序
	Check(data.longs, data.length, RANGE + 1);
	//显示执行次数
	gotoxy(0, RANGE + 3);
	cout << "共扫描：" << times << "行。" << endl;
	cout << "共交换：" << swap_times << "次。";
	system("pause");
	system("cls");
	return 0;
}




//快速排序： 目前
int QuickSort() {
	//初始化过程
	RunningTips("Quick Sort");
	init();
	rectangle data;
	int length = 0;
	//扫描次数
	int times = 0;
	//交换次数
	int swap_times = 0;
	//开始位置 
	int Start = RANGE + 1;
	//参数初始化
	ParameterInit(&length);
	//生成矩形数组
	InitRectangle(data, length);
	showInfo();
	//静态打印初始图形
	Visualization(data.longs, data.length, Start);
	int Info[2] = { times, swap_times };
	_QuickSort(data.longs, 0, data.length - 1, Start, Info);
	return 0;
}

//快速排序的递归
void _QuickSort(int* data, int left, int right, int Start, int Info[2]) {
	int i, j;
	int temp;
	int RVP;
	if (left < right)
	{
		//标记现在排序的所有方块
		TargetSegment(data, left, right, Start);



		i = left; 
		j = right;
		RVP = i;
		while (i < j) {
			//基准值标粉13
			DelAColumn(2 * RANGE + 3, *(data + RVP), Start);
			DrawAColumn(2 * RANGE + 3, *(data + RVP), 13, Start);
			while (i < right && *(data + RVP) >= *(data + i)) {
				showOrder(i, data[i], 10, Start);
				Sleep(SLEEPTIME * 3);
				i++;
				Info[0]++;
			}
			updateInfo(Info[1], Info[0], i, data[i]);
			while (*(data + RVP) < *(data + j)) {
				showOrder(j, data[j], 14, Start);
				Sleep(SLEEPTIME * 3);
				j--;
				Info[0]++;
			}
			updateInfo(Info[1], Info[0], j, data[j]);
			gotoxy(0, 0);
			//交换
			if (i < j) {
				Info[1]++;
				updateInfo(Info[1], Info[0], i, data[i]);
				Swap(data, i, j, Start, 252U, 12, 252, 5);
				temp = *(data + i);
				*(data + i) = *(data + j);
				*(data + j) = temp;
			}
		}
		//移动基准值
		Swap(data, RVP, j, Start, 253U, 12, 253, 5);
		temp = *(data + RVP);
		*(data + RVP) = *(data + j);
		*(data + j) = temp;
		//取消标记并恢复成原色
		CancelSegment(data, left, right, Start);

		for (int x = left; x < right; x++) {
			DelAColumn(x, *(data + x), Start);
			DrawAColumn(x, *(data + x), 15, Start);
		}
		DelAColumn(2 * RANGE + 3, *(data + j), Start);
		_QuickSort(data, left, j - 1, Start, Info);
		_QuickSort(data, j + 1, right, Start, Info);
	}
}