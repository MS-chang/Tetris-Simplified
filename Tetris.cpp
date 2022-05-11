#include<iostream>
#include"Mscontrol.h"
#include"blocks.h"
using namespace std;
//游戏区域的表示，0为空白，否则为有方块。！！！因为一个方格占据两个列，地图上一个列就是两个字符长度，注意输出位置
//对应位置的数字就是对应的颜色
int map[32][20] = { 0 };
//俄罗斯方块的x区域
const int Game_Yarea = 30;
//俄罗斯方块的y区域
const int Game_Xarea = 18;
//设置坐标原点，即坐标的偏移量，在绘制背景时使用了
const int ORIGIN[2] = { 2,0 };
//游戏得分
int Gamecount=0;
//方块下降速度
int Downspeed=1;
//游戏模式，奇数为单人，偶数为双人
int Gamemode;
//双人模式的操作键位,奇数是字母键位
int Conkey;
//画出底部框架(2,0)到(40,31)
void Drawbk() 
{
	for (int i = 0; i < 20; i++) {
		map[0][i] = (i+20)%6+1;
	}
	for (int i = 0; i < 4; i++) {
		map[i + 1][0] = (i + 20) % 6 + 1;
		map[i + 1][19] = (i + 20) % 6 + 1;
	}
	for (int i = 4; i < 30; i++) {
		map[i+1][0] = 7;
	}
	for (int i = 0; i < 19; i++) {
		map[31][i] = 7;
	}
	for (int i = 4; i < 31; i++) {
		map[i+1][19] = 7;
	}
}
//展示游戏信息
void ShowInfo() {
	Gotoxy(43, 3);
	Setcolor(2 + 8);
	cout << "得分：";
	Gotoxy(47, 5);
	Setcolor(4 + 8);
	cout << Gamecount;
	Gotoxy(43, 8);
	Setcolor(2 + 8);
	cout << "下一个是：";
	Setcolor(0);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			Gotoxy(54+j*2, 8 + i);
			cout << "■";
		}
	}
	for (int i = 0; i < 4; i++) {
		Gotoxy((nextBlock[i].x )* 2+40, nextBlock[i].y+7);
		Setcolor(nBcolor);
		cout << "■";
	}
	
	Setcolor(6 + 8);
	Gotoxy(46, 15);
	cout << "↓ S 加速向下";
	Gotoxy(46, 16);
	cout << "↑ W 恢复原速";
	Gotoxy(46, 17);
	cout << "← A 向左移动";
	Gotoxy(46, 18);
	cout << "→ D 向右移动";
	Gotoxy(46, 19);
	cout << "L  R 进行旋转";
	Gotoxy(46, 20);
	cout << "单人游戏使用箭头符号";
	Gotoxy(46, 21);
	cout << "双人字母先操作,箭头后操作";
	Gotoxy(46, 25);
	Setcolor(4 + 8);
	cout<< "方块累加到彩色边界时，游戏结束";
	
}
//消除计分函数-----------------------------
void Clearup() {
	int k = 30;
	for (int i = 30; i > 4; i--) {
		int count = 0;
		for (int j = 0; j < 20; j++) {
			if (map[i][j]) {
				count++;
			}
			map[k][j] = map[i][j];
		}
		if (count < 20) {
			k--;
		}
		else {
			Gamecount += 10;
		}
	}
}
//创建新俄罗斯方块，存储到nextBlock
void NewNextBlock() {
	//设置相对位置
	Originp.x = 9;
	Originp.y = 1;
	nextBlockind = rand() % 7;//选出哪一种,blocks[blockind]就是对应的方块模式
	for (int i = 0; i < 4; i++) {
		nextBlock[i].x = blocks[nextBlockind][i] % 2 + Originp.x;//blocks[blockind][i] % 2是在小方块在相对位置上x的偏移量
		nextBlock[i].y = blocks[nextBlockind][i] / 2 + Originp.y;//blocks[blockind][i] / 2是相对y位置
	}
	nBcolor = rand() % 6 + 1;//设置新方块颜色
}
//将存储到nextBlock的数据具化到map上
void ShowNextBlock() {
	Clearup();
	cBcolor = nBcolor;
	blockind = nextBlockind;
	for (int i = 0; i < 4; i++) {
		currentBlock[i] = nextBlock[i];
	}
	for (int i = 0; i < 4; i++) {
		map[currentBlock[i].y][currentBlock[i].x] = cBcolor;
	}
}
//检查移动后的放块是不是有已存在的方块重叠
bool check() {
	for (int i = 0; i < 4; i++) {
		if (map[currentBlock[i].y][currentBlock[i].x]) {
			return false;
		}
	}
	return true;
}
//实现方块自动下降
void Automove(int *a) {
	for (int k = 0; k < *a; k++) {
		for (int i = 0; i < 4; i++) {
			bakBlock[i] = currentBlock[i];
			map[bakBlock[i].y][bakBlock[i].x] = 0;
			currentBlock[i].y += 1;
		}
		if (check() == false) {
			for (int i = 0; i < 4; i++) {
				map[bakBlock[i].y][bakBlock[i].x] = cBcolor;
			}
			if (Gamemode == 2) {
				Conkey++;
			}
			ShowNextBlock();
			NewNextBlock();
		}
		else {
			for (int i = 0; i < 4; i++) {
				map[currentBlock[i].y][currentBlock[i].x] = cBcolor;
			}
		}
	}
}
//控制方块运动左右移
void MoveLorR(int a) {
	for (int i = 0; i < 4; i++) {
		bakBlock[i] = currentBlock[i];
		map[bakBlock[i].y][bakBlock[i].x] = 0;
		currentBlock[i].x -= a;
	}
	if (!check()) {
		for (int i = 0; i < 4; i++) {
			currentBlock[i] = bakBlock[i];
		}
	}
	for (int i = 0; i < 4; i++) {
		map[currentBlock[i].y][currentBlock[i].x] = cBcolor;
	}
}
//旋转函数
void BlockTurn() {
	/*利用已知的数学公式，进行旋转，求得每一个小方块旋转后的坐标*/
	//先备份当前方块,并进行原位置清空
	for (int i = 0; i < 4; i++) {
		bakBlock[i] = currentBlock[i];
		map[bakBlock[i].y][bakBlock[i].x] = 0;
	}
	//确定旋转中心，这里选取第二个方块
	//套公式进行计算
	/*   x坐标： a[i].x  =  p.y - a[i].y + p.x  
	     y坐标： a[i].y  =  a[i].x - p.x + p.y  */
	for (int i = 0; i < 4; i++) {
		Point temp = currentBlock[i];
		currentBlock[i].x = bakBlock[1].y - temp.y + bakBlock[1].x;
		currentBlock[i].y = temp.x - bakBlock[1].x + bakBlock[1].y;
	}
	//检查合法性
	if (!check() ){
		for (int i = 0; i < 4; i++) {
			currentBlock[i] = bakBlock[i];
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			map[currentBlock[i].y][currentBlock[i].x] = cBcolor;
		}
	}
}
//调用中枢
void TetrisContronl() {
	if (_kbhit()) {
		int c1=_getch();
		if (Conkey%2==0) {
			//左右移动--------------------------------
			if (c1 == 224) {
				c1 = _getch();
				switch (c1) {
				case 72://上键
					Downspeed = 1;
					break;
				case 80://下键
					Downspeed = 2;
					break;
				case 75://左键
					MoveLorR(1);
					break;
				case 77://右键
					MoveLorR(-1);
					break;
				}
			}
			//翻转操作---------------------------------
			if (c1 == 'l' || c1 == 'L') {
				if (blockind != 6) {
					BlockTurn();
				}
			}
		}
		else{
			switch (c1) {
			case'w':
			case'W'://上键
				Downspeed = 1;
				break;
			case 'S':
			case's'://下键
				Downspeed = 2;
				break;
			case 'A':
			case 'a'://左键
				MoveLorR(1);
				break;
			case 'D':
			case 'd'://右键
				MoveLorR(-1);
				break;
			}
			//翻转操作---------------------------------
			if (c1 == 'R' || c1 == 'r') {
				if (blockind != 6) {
					BlockTurn();
				}
			}
		}

	}
}
//游戏结束函数,返回值true则结束
bool EndGame() {
	for (int i = 0; i < 4; i++) {
		map[currentBlock[i].y][currentBlock[i].x] = 0;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j < 19; j++){
			if (map[i + 1][j] != 0) {
				return true;
			}
	    }
	}
	for (int i = 0; i < 4; i++) {
		map[currentBlock[i].y][currentBlock[i].x] = cBcolor;
	}
	return false;
}
//形成画面
void Drawblocks() {
	for (int i = 0; i < 32; i++) {//行循环
		for (int j = 0; j < 20; j++) {//列循环
			//画方块
			Setcolor(map[i][j]);
			Gotoxy(ORIGIN[0]+j*2, ORIGIN[1]+i);
			printf("■");
		}
	}
}
int main() {
	cout << "请选择游戏模式：\n1 for 单人\n2 for 双人\n";
	Gamemode = _getch();
	Conkey = Gamemode - 1;
	Setcolor(4 + 8);
	if (Gamemode%2==0) {
		cout << "双人字母先操作,箭头后操作";
	}
	else {
		cout << "箭头进行操作";
	}
	Sleep(2500);
	system("mode con cols=80 lines=35");
	srand((unsigned)time(NULL));
	HideCursor();
	Drawbk();
	NewNextBlock();
	ShowNextBlock();
	NewNextBlock();
	Drawblocks();
	while (!EndGame()) {
		Drawblocks();
		Sleep(20);
		TetrisContronl();
		Sleep(20);
		ShowInfo();
		Sleep(20);
		Automove(&Downspeed);
		Sleep(40);
		Conkey %= 2;
	}
	memset(map, 0, 32 * 20*4);
	Drawblocks();
	return 0;
}