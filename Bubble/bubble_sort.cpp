#include "../Founction.H"

int main() {
	init();
	rectangle data;
	int length = 0;
	int times = 0;
	int swap_times = 0;
	ParameterInit(&length); 
	InitRectangle(data, length);
	CreatRectangle(data);
	Visualization(data);
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
	Check(data);
	gotoxy(0, RANGE + 3);
	cout << "共扫描：" << times << "行。" << endl;
	cout << "共交换：" << swap_times << "次。";
	system("pause");
	return 0;
} 
