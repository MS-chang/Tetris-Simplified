#pragma once
//���ĸ�λ�ò��ϱ仯�ķ���ȷ����ͨ�������ʾ
int blocks[7][4] = {
	{1,3,5,7},// I
	{0,2,3,5},//Z 
	{1,2,3,4},//Z 
	{1,2,3,5},//T 
	{0,1,3,5},//L
	{1,3,4,5},//J
	{0,1,2,3}//��
};
//����ṹ�壬ר�Ź�������
struct Point {
	int x;
	int y;
};
//��ǰ���������λ�ô洢,Point ��һ���ṹ��
Point currentBlock[4];
//����
Point bakBlock[4];
//��һ�����������洢
Point nextBlock[4];
//�洢Block��������λ��
Point Originp;//ע�⣬currentBlock�е����꣬����Originp+���ƫ����
//��ǰ���������
int blockind;
//��һ���������
int nextBlockind;
//��ǰ�������ɫ
int cBcolor;
//��һ�������ɫ
int nBcolor;