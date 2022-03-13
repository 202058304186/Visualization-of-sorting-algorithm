#include "../Founction.H"

int main() {
	rectangle data;
	int length = 0;
	ParameterInit(&length); 
	InitRectangle(data, length);
	CreatRectangle(data);
	Visualization(data);
	gotoxy(0, RANGE + 10);
	return 0;
} 
