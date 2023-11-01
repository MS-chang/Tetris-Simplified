#pragma once
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
//指定位置输出
void Gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//设置颜色,说明：0 黑色1 蓝色2 绿色3 青色 4红色5 紫色6 黄色7 白色 + 8加强色
void Setcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
/*bool _kbhit()
检测是否有按键按下，系统函数直接调用。该函数是非阻塞函数。
*/
/*int _getch()
     获取按键的值，但不在屏幕回显，系统函数直接调用。
*/
/*使用 _getch()实现读取上下左右键
c1=getch();
if (c1=="\0")
{ c1=getch();
if (c1==72) .... ; //上键
if (c1==80) .....; //下键
if (c1==75) .....; //左键
if (c1==77) .....; //右键
.....;
}*/