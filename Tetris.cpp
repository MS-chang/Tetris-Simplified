#include<iostream>
#include"Mscontrol.h"
#include"blocks.h"
using namespace std;
//��Ϸ����ı�ʾ��0Ϊ�հף�����Ϊ�з��顣��������Ϊһ������ռ�������У���ͼ��һ���о��������ַ����ȣ�ע�����λ��
//��Ӧλ�õ����־��Ƕ�Ӧ����ɫ
int map[32][20] = { 0 };
//����˹�����x����
const int Game_Yarea = 30;
//����˹�����y����
const int Game_Xarea = 18;
//��������ԭ�㣬�������ƫ�������ڻ��Ʊ���ʱʹ����
const int ORIGIN[2] = { 2,0 };
//��Ϸ�÷�
int Gamecount=0;
//�����½��ٶ�
int Downspeed=1;
//��Ϸģʽ������Ϊ���ˣ�ż��Ϊ˫��
int Gamemode;
//˫��ģʽ�Ĳ�����λ,��������ĸ��λ
int Conkey;
//�����ײ����(2,0)��(40,31)
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
//չʾ��Ϸ��Ϣ
void ShowInfo() {
	Gotoxy(43, 3);
	Setcolor(2 + 8);
	cout << "�÷֣�";
	Gotoxy(47, 5);
	Setcolor(4 + 8);
	cout << Gamecount;
	Gotoxy(43, 8);
	Setcolor(2 + 8);
	cout << "��һ���ǣ�";
	Setcolor(0);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			Gotoxy(54+j*2, 8 + i);
			cout << "��";
		}
	}
	for (int i = 0; i < 4; i++) {
		Gotoxy((nextBlock[i].x )* 2+40, nextBlock[i].y+7);
		Setcolor(nBcolor);
		cout << "��";
	}
	
	Setcolor(6 + 8);
	Gotoxy(46, 15);
	cout << "�� S ��������";
	Gotoxy(46, 16);
	cout << "�� W �ָ�ԭ��";
	Gotoxy(46, 17);
	cout << "�� A �����ƶ�";
	Gotoxy(46, 18);
	cout << "�� D �����ƶ�";
	Gotoxy(46, 19);
	cout << "L  R ������ת";
	Gotoxy(46, 20);
	cout << "������Ϸʹ�ü�ͷ����";
	Gotoxy(46, 21);
	cout << "˫����ĸ�Ȳ���,��ͷ�����";
	Gotoxy(46, 25);
	Setcolor(4 + 8);
	cout<< "�����ۼӵ���ɫ�߽�ʱ����Ϸ����";
	
}
//�����Ʒֺ���-----------------------------
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
//�����¶���˹���飬�洢��nextBlock
void NewNextBlock() {
	//�������λ��
	Originp.x = 9;
	Originp.y = 1;
	nextBlockind = rand() % 7;//ѡ����һ��,blocks[blockind]���Ƕ�Ӧ�ķ���ģʽ
	for (int i = 0; i < 4; i++) {
		nextBlock[i].x = blocks[nextBlockind][i] % 2 + Originp.x;//blocks[blockind][i] % 2����С���������λ����x��ƫ����
		nextBlock[i].y = blocks[nextBlockind][i] / 2 + Originp.y;//blocks[blockind][i] / 2�����yλ��
	}
	nBcolor = rand() % 6 + 1;//�����·�����ɫ
}
//���洢��nextBlock�����ݾ߻���map��
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
//����ƶ���ķſ��ǲ������Ѵ��ڵķ����ص�
bool check() {
	for (int i = 0; i < 4; i++) {
		if (map[currentBlock[i].y][currentBlock[i].x]) {
			return false;
		}
	}
	return true;
}
//ʵ�ַ����Զ��½�
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
//���Ʒ����˶�������
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
//��ת����
void BlockTurn() {
	/*������֪����ѧ��ʽ��������ת�����ÿһ��С������ת�������*/
	//�ȱ��ݵ�ǰ����,������ԭλ�����
	for (int i = 0; i < 4; i++) {
		bakBlock[i] = currentBlock[i];
		map[bakBlock[i].y][bakBlock[i].x] = 0;
	}
	//ȷ����ת���ģ�����ѡȡ�ڶ�������
	//�׹�ʽ���м���
	/*   x���꣺ a[i].x  =  p.y - a[i].y + p.x  
	     y���꣺ a[i].y  =  a[i].x - p.x + p.y  */
	for (int i = 0; i < 4; i++) {
		Point temp = currentBlock[i];
		currentBlock[i].x = bakBlock[1].y - temp.y + bakBlock[1].x;
		currentBlock[i].y = temp.x - bakBlock[1].x + bakBlock[1].y;
	}
	//���Ϸ���
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
//��������
void TetrisContronl() {
	if (_kbhit()) {
		int c1=_getch();
		if (Conkey%2==0) {
			//�����ƶ�--------------------------------
			if (c1 == 224) {
				c1 = _getch();
				switch (c1) {
				case 72://�ϼ�
					Downspeed = 1;
					break;
				case 80://�¼�
					Downspeed = 2;
					break;
				case 75://���
					MoveLorR(1);
					break;
				case 77://�Ҽ�
					MoveLorR(-1);
					break;
				}
			}
			//��ת����---------------------------------
			if (c1 == 'l' || c1 == 'L') {
				if (blockind != 6) {
					BlockTurn();
				}
			}
		}
		else{
			switch (c1) {
			case'w':
			case'W'://�ϼ�
				Downspeed = 1;
				break;
			case 'S':
			case's'://�¼�
				Downspeed = 2;
				break;
			case 'A':
			case 'a'://���
				MoveLorR(1);
				break;
			case 'D':
			case 'd'://�Ҽ�
				MoveLorR(-1);
				break;
			}
			//��ת����---------------------------------
			if (c1 == 'R' || c1 == 'r') {
				if (blockind != 6) {
					BlockTurn();
				}
			}
		}

	}
}
//��Ϸ��������,����ֵtrue�����
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
//�γɻ���
void Drawblocks() {
	for (int i = 0; i < 32; i++) {//��ѭ��
		for (int j = 0; j < 20; j++) {//��ѭ��
			//������
			Setcolor(map[i][j]);
			Gotoxy(ORIGIN[0]+j*2, ORIGIN[1]+i);
			printf("��");
		}
	}
}
int main() {
	cout << "��ѡ����Ϸģʽ��\n1 for ����\n2 for ˫��\n";
	Gamemode = _getch();
	Conkey = Gamemode - 1;
	Setcolor(4 + 8);
	if (Gamemode%2==0) {
		cout << "˫����ĸ�Ȳ���,��ͷ�����";
	}
	else {
		cout << "��ͷ���в���";
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