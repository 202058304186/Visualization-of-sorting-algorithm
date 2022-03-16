#include "../Founction.H"
using namespace std;

int main() {
	int length;
	rectangle data;
	ParameterInit(&length);
	InitRectangle(data, length);
	CreatRectangle(data);
	
	int* data_ = (int *)malloc(sizeof(int) * (length + 1));
	data_[0] = 0;
	for (int i = 0; i < length; ++i) {
		data_[i + 1] = data.longs[i];
	}
	Visualization(data_, length + 1);
	
	for (int i = 1; i < length + 1; ++i) {
		//绘制哨兵
		DelAColumn(0, data_[0]);
		data_[0] = data_[i];
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

		//找到插入位置进行合并
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
	return 0;
} 
