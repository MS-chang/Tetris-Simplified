#pragma once
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
//ָ��λ�����
void Gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//������ɫ,˵����0 ��ɫ1 ��ɫ2 ��ɫ3 ��ɫ 4��ɫ5 ��ɫ6 ��ɫ7 ��ɫ + 8��ǿɫ
void Setcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//���ع��
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
/*bool _kbhit()
����Ƿ��а������£�ϵͳ����ֱ�ӵ��á��ú����Ƿ�����������
*/
/*int _getch()
     ��ȡ������ֵ����������Ļ���ԣ�ϵͳ����ֱ�ӵ��á�
*/
/*ʹ�� _getch()ʵ�ֶ�ȡ�������Ҽ�
c1=getch();
if (c1=="\0")
{ c1=getch();
if (c1==72) .... ; //�ϼ�
if (c1==80) .....; //�¼�
if (c1==75) .....; //���
if (c1==77) .....; //�Ҽ�
.....;
}*/