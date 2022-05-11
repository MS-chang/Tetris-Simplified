#pragma once
//由四个位置不断变化的方块确定，通过数组表示
int blocks[7][4] = {
	{1,3,5,7},// I
	{0,2,3,5},//Z 
	{1,2,3,4},//Z 
	{1,2,3,5},//T 
	{0,1,3,5},//L
	{1,3,4,5},//J
	{0,1,2,3}//田
};
//定义结构体，专门管理坐标
struct Point {
	int x;
	int y;
};
//当前方块的坐标位置存储,Point 是一个结构体
Point currentBlock[4];
//备份
Point bakBlock[4];
//下一个方块的坐标存储
Point nextBlock[4];
//存储Block方块的相对位移
Point Originp;//注意，currentBlock中的坐标，等于Originp+相对偏移量
//当前方块的种类
int blockind;
//下一方块的种类
int nextBlockind;
//当前方块的颜色
int cBcolor;
//下一方块的颜色
int nBcolor;