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
		//�����ڱ�
		DelAColumn(0, data_[0]);
		data_[0] = data_[i];
		DrawAColumn(0, data_[0], 14);
		Sleep(SLEEPTIME * 2);
		
		//��ֵ
		DelAColumn(i, data_[i]);
		DrawAColumn(i, data_[i], 12, 2 * RANGE + 2);
		Sleep(SLEEPTIME * 8);
		int j = i;

		//Ѱ�Ҳ���λ�ã��Ƚϲ�Ų��
		while (data_[0] < data_[j - 1]) {
			//���ƱȽ���
			DelAColumn(j - 1, data_[j - 1]); 
			DrawAColumn(j - 1, data_[j - 1], 58);
			Sleep(SLEEPTIME * 5);
			//ɾ���Ƚ���
			DelAColumn(j - 1, data_[j - 1]); 
			//ɾ���ƶ��� 
			DelAColumn(j - 1, data_[j - 1]);
			//�����ƶ��� 
			DrawAColumn(j, data_[j - 1], 185);
			Sleep(SLEEPTIME * 2);
			//ɾ����ɫ���� 
			DelAColumn(j, data_[0], 2 * RANGE + 2);
			//���µĺ�ɫ 
			DrawAColumn(j - 1, data_[0], 12, 2 * RANGE + 2);
			Sleep(SLEEPTIME * 5);
			//�����ƶ� 
			data_[j] = data_[j - 1];
			j--;
		}

		//�ҵ�����λ�ý��кϲ�
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
