#include "../Founction.H"

int main() {
	rectangle data;
	int length = 0;
	ParameterInit(&length); 
	InitRectangle(data, length);
	CreatRectangle(data);
	Visualization(data);
	DrawAColumn(0, 35);
	gotoxy(0, RANGE + 10);
	system("pause");
	return 0;
} 
