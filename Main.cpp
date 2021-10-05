#include <iostream>
#include <windows.h>
#include <string>

#define MAX_NUM 10
#define MAX_CUL MAX_NUM
#define Sleepcount 100

using namespace std;

int a[MAX_NUM] = { 0, }, b[MAX_NUM] = { 0, }; //a,b / 2진수
int c1[MAX_CUL] = { 0, }, c2[MAX_CUL] = { 0, }; //c == save / c1 == plus , c2 == minus
int al = 0, bl = 0; //a,b / l=length
int rpc1_1[MAX_CUL] = { 0, }, rpc1_2[MAX_CUL] = { 0, }, rpc2_1[MAX_CUL] = { 0, }, rpc2_2[MAX_CUL] = { 0, }; //ex) rpc1_1 / 1(number)_1(보수, 2 == 2의 보수)
int rpc1_2_ru[MAX_CUL] = { 0, }, rpc2_2_ru[MAX_CUL] = { 0, }; //2의 보수 올림(up) 저장
int ru1[MAX_CUL] = { 0, }, ru2[MAX_CUL] = { 0, }; //ru == 올림(up) 올림을 잠시 저장 / ru1 == plus , ru2 == minus

void arrayin();
void arraychange();
void plusbinary();
void minusbinary();
void printcul(int l, int ot);
void plusprint(int l);
void minusprint(int l);
void linepm(int l, int tf);
int comparison(int com);

void gotoxy(int x, int y);
void CursorView(char show);

//1101 0111 / 0111 1101

int main()
{
	system("title 2진수 계산기");
	CursorView(true);
	arrayin();
	system("cls");
	arraychange();
	CursorView(false);
	plusbinary();
	minusbinary();
	system("cls");

	printcul(1, 1);
	plusprint(4);

	gotoxy(0, 17);
	system("pause");
	system("cls");

	printcul(1, 2);
	minusprint(4);

	gotoxy(0, 20);
}

void arrayin()
{
	while (1) //2진수 길이 입력 0 < x < 9 외 반복
	{
		cout << "1, 2번의 2진수 길이를 각각 입력! 최대 9자리" << endl;
		cout << "1. 2진수 길이 : ";
		cin >> al;
		cout << "2. 2진수 길이 : ";
		cin >> bl;
		system("cls");
		if (al > 0 && al <= 9)
			if (bl > 0 && bl <= 9)
				break;
	}
}

void arraychange()
{
	int num1 = 0, num2 = 0, i = 0;
	cout << "2개의 2진수를 입력!" << endl << "1. (" << al << ") 2. (" << bl << ")" << endl;
	cin >> num1 >> num2;
	while (num1)
	{
		a[i] = num1 % 10;
		num1 /= 10;
		i++;
	}
	i = 0;
	while (num2)
	{
		b[i] = num2 % 10;
		num2 /= 10;
		i++;
	}
}

void plusbinary()
{
	//num1 + num2 = (3 == 1up, 1save) , (2 == 1up, 0save) , (1 == 0up, 1save)
	int n = 0, num = 0;
	num = comparison(num);
	for (int i = 0; i < num; i++)
	{
		n = a[i] + b[i] + ru1[i - 1];
		if (n == 3)
		{
			ru1[i] = 1;
			c1[i] = 1;
		}
		else if (n == 2)
		{
			ru1[i] = 1;
			c1[i] = 0;
		}
		else if (n == 1)
		{
			ru1[i] = 0;
			c1[i] = 1;
		}
	}
	num--;
	if (num < 0)
		num = 0;
	if (ru1[num] == 1)
		c1[num + 1] = 1;
}

void minusbinary()
{
	int n = 0, num1 = bl, num2 = 0, num3 = 0, sru = 1;
	if (al <= bl)
		num2 = bl;
	else
		num2 = al;
	for (int i = 0; i < num1; i++)
	{
		if (b[i] == 1)
			rpc1_1[i] = 0;
		else if (b[i] == 0)
			rpc1_1[i] = 1;
	}
	for (int i = 0; i < num1; i++)
	{
		n = rpc1_1[i] + rpc1_2_ru[i - 1] + sru;
		if (n == 2)
		{
			rpc1_2_ru[i] = 1;
			rpc1_2[i] = 0;
			sru = 0;
		}
		else if (n == 1)
		{
			rpc1_2_ru[i] = 0;
			rpc1_2[i] = 1;
			sru = 0;
		}
	}
	num1--;
	if (num1 < 0)
		num1 = 0;
	if (rpc1_2_ru[num1] == 1)
		rpc1_2[num1 + 1] = 1;
	for (int i = 0; i < num2; i++)
	{
		n = a[i] + rpc1_2[i] + ru2[i - 1];
		if (n == 3)
		{
			ru2[i] = 1;
			c2[i] = 1;
		}
		else if (n == 2)
		{
			ru2[i] = 1;
			c2[i] = 0;
		}
		else if (n == 1)
		{
			ru2[i] = 0;
			c2[i] = 1;
		}
	}
	num2--;
	if (num2 < 0)
		num2 = 0;
	if (ru2[num2] == 1)
		c2[num2 + 1] = 1;
	if (c2[num2 + 1] == 0)
	{
		num3 = num2 + 1;
		sru = 1;
		for (int i = 0; i < num3; i++)
		{
			if (c2[i] == 1)
				rpc2_1[i] = 0;
			else if (c2[i] == 0)
				rpc2_1[i] = 1;
		}
		for (int i = 0; i < num3; i++)
		{
			n = rpc2_1[i] + rpc2_2_ru[i - 1] + sru;
			if (n == 2)
			{
				rpc2_2_ru[i] = 1;
				rpc2_2[i] = 0;
				sru = 0;
			}
			else if (n == 1)
			{
				rpc2_2_ru[i] = 0;
				rpc2_2[i] = 1;
				sru = 0;
			}
		}
	}
}

void printcul(int l, int ot)
{
	int num1 = 0, num2 = 0;
	num1 = comparison(num1);
	num2 = MAX_NUM - num1;
	for (int i = 0; i < al; i++)
	{
		gotoxy(12 - num2 - i, l);
		cout << a[i];
	}
	for (int i = 0; i < bl; i++)
	{
		gotoxy(12 - num2 - i, l + 1);
		cout << b[i];
	}
	linepm(l + 1, ot);
}

void plusprint(int l)
{
	int num1 = 0, num2 = 0;
	num1 = comparison(num1);
	num2 = MAX_NUM - num1;
	for (int i = 0; i < num1; i++)
	{
		Sleep(Sleepcount);
		gotoxy(12 - num2 - i, l + 1);
		cout << c1[i];
		if (ru1[i] == 1)
		{
			Sleep(Sleepcount);
			gotoxy(11 - num2 - i, l);
			cout << ru1[i];
		}
	}
	Sleep(Sleepcount);
	num1--;
	if (num1 < 0)
		num1 = 0;
	if (ru1[num1] == 1)
	{
		gotoxy(2, l + 1);
		cout << "1";
	}
}

void minusprint(int l)
{
	int num1 = 0, num2 = 0;
	num1 = comparison(num1);
	num2 = MAX_NUM - num1;
	for (int i = 0; i < num1; i++)
	{
		Sleep(Sleepcount);
		gotoxy(12 - num2 - i, l);
		cout << rpc1_1[i];
	}
	gotoxy(12 - num2 + 3, l);
	cout << "1의 보수";
	gotoxy(12 - num2, l + 1);
	cout << "1";
	for (int i = 0; i < num1; i++)
	{
		Sleep(Sleepcount);
		gotoxy(12 - num2 - i, l + 2);
		cout << rpc1_2[i];
		if (rpc1_2_ru[i] == 1)
		{
			Sleep(Sleepcount);
			gotoxy(11 - num2 - i, l + 1);
			cout << rpc1_2_ru[i];
		}
	}
	gotoxy(12 - num2 + 3, l + 2);
	cout << "2의 보수";
	linepm(l + 2, 0);
	for (int i = 0; i < num1; i++)
	{
		Sleep(Sleepcount);
		gotoxy(12 - num2 - i, l + 4);
		cout << a[i];
	}
	gotoxy(12 - num2 + 3, l + 4);
	cout << "첫번째 입력 값";
	for (int i = 0; i < num1; i++)
	{
		Sleep(Sleepcount);
		gotoxy(12 - num2 - i, l + 5);
		cout << rpc1_2[i];
	}
	gotoxy(12 - num2 + 3, l + 5);
	cout << "두번째 입력 값의 2의 보수";
	linepm(l + 5, 1);
	for (int i = 0; i < num1; i++)
	{
		Sleep(Sleepcount);
		gotoxy(12 - num2 - i, l + 8);
		cout << c2[i];
		if (ru2[i] == 1)
		{
			Sleep(Sleepcount);
			gotoxy(11 - num2 - i, l + 7);
			cout << ru2[i];
		}
	}
	num1--;
	if (num1 < 0)
		num1 = 0;
	if (ru2[num1] == 1)
	{
		Sleep(Sleepcount);
		gotoxy(2, l + 8);
		cout << "1";
		Sleep(Sleepcount);
		gotoxy(12 - num2 + 3, l + 8);
		cout << "숫자 " << num1 + 1 << "에서 1자리 증가/1자리 삭제!";
		gotoxy(2, l + 8);
		cout << " ";
	}
	if (ru2[num1] == 0)
	{
		num1++;
		linepm(l + 8, 0);
		for (int i = 0; i < num1; i++)
		{
			Sleep(Sleepcount);
			gotoxy(12 - num2 - i, l + 10);
			cout << rpc2_1[i];
		}
		gotoxy(12 - num2 + 3, l + 10);
		cout << "1의 보수";
		gotoxy(12 - num2, l + 11);
		cout << "1";
		for (int i = 0; i < num1; i++)
		{
			Sleep(Sleepcount);
			gotoxy(12 - num2 - i, l + 12);
			cout << rpc2_2[i];
			if (rpc2_2_ru[i] == 1)
			{
				Sleep(Sleepcount);
				gotoxy(11 - num2 - i, l + 11);
				cout << rpc2_2_ru[i];
			}
		}
		gotoxy(12 - num2 + 3, l + 12);
		cout << "2의 보수";
		linepm(l + 12, 0);
		for (int i = 0; i < num1; i++)
		{
			Sleep(Sleepcount);
			gotoxy(12 - num2 - i, l + 14);
			cout << rpc2_2[i];
		}
		gotoxy(12 - num2 + 3, l + 14);
		cout << "계산값";
	}
}

void linepm(int l, int tf)
{
	int num1 = 0;
	num1 = comparison(num1);
	gotoxy(1, l);
	if (tf == 1)
		cout << "+";
	else if (tf == 2)
		cout << "-";
	gotoxy(1, l + 1);
	for (int i = 0; i < num1 + 2; i++)
		cout << "-";
}

int comparison(int com)
{
	if (al <= bl)
		com = bl;
	else
		com = al;
	return com;
}

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CursorView(char show) 
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}