#include "../Founction.H"

int main() {
	rectangle data;
	InitRectangle(data, 2);
	CreatRectangle(data);
	Visualization(data);
	gotoxy(0, RANGE + 10);
	return 0;
} 
