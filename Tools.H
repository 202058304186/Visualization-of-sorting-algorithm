#include<iostream>
using namespace std;

void InputLimit(int* input, float left_border, float right_border, float accuracy = 0.001) {
	cout << "请输入值（最大值为40）：";
	cin >> *input;
	int count = 0;
	while (*input - left_border < accuracy || *input - right_border > accuracy && count++ < 3) {
		printf("输入非法请重新输入（最大值为%d）：", (int) right_border);
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