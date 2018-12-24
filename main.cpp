#include <iostream>
#include <iomanip>
#include <vector>
#include <queue> 
using namespace std;

class Ppoint
{
	public:
		int x, y;
		Ppoint(int _x, int _y)
		{
			x = _x;
			y = _y;
		}
		Ppoint(){}

		void setXY(int _x, int _y)
		{
			x = _x;
			y = _y;
		}		
};

//方格大小
#define M 7
#define N 7

//保存该电路板当前布线方案（-1表示该第一层的连线 -2表示第二层 -3表示第三层）
int currentBoard[M][N]={
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0
};

int points[M][N];//活结点表
int dist = 1;//与初始结点的距离
vector<Ppoint>thePath;//存储路径的坐标 
queue<Ppoint>visitPoints;//队列 存储当前可以访问的点 

//查看currentBoard 
void showBoard()
{
	//cout << "currentBoard:" << endl;
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cout << currentBoard[i][j] << ' ';
		}
		cout << endl;
	}
}

//添加一个点(px,py)并将距离起始点的距离存入currentBoard 且存入队列中 
bool addIntoPoints(int px, int py, int layer)
{
	if (px < 0 || py < 0 || px > M - 1 || py > N - 1 || (currentBoard[px][py] != 0 && currentBoard[px][py] != -layer) || points[px][py] == -1)
		return false;
	
	else if (currentBoard[px][py] == -layer)
	{
		return true;
	}
	//cout << "添加点:(" << px << ',' << py << ")" << endl;
	currentBoard[px][py] = dist;
	points[px][py] = 1;
	Ppoint tempPpoint(px, py);
	visitPoints.push(tempPpoint); 
	//showBoard();
	return true;
}

////从活结点表中取出一个节点，返回-1表示活结点中无可用节点 
//int getIndexFromPoints()
//{
//	for (int i = 0; i < M; ++i)
//		for (int j = 0; j < N; ++j)
//		{
//			if (points[i][j] > 0)
//			{
//				cout << "访问点:(" << i << ',' << j << ")" << endl;
//				return i*M+j;
//			}
//				
//		}
//	return -1;
//} 
 
//判断点(x,y)是否可以连接  layer--当前是哪一层线网 
bool ifConnect(int x, int y, int layer)
{
	if (currentBoard[x][y] + layer == 0)
	{
		//cout << "点:(" << x << ',' << y << ")可以连接" << endl;
		return true;
	}
	//cout << "点:(" << x << ',' << y << ")无法连接" << endl;
	return false;
}
 
//迷宫算法获取路径 从终点出发 但凡遇到可以连接的点，就回溯得到当前的路径并存入path中   layer--当前是哪一层线网 
void mazeAlg(int sx, int sy, int layer)
{
	//第一步 先处理终点上下左右的四个点 
	if (ifConnect(sx-1, sy, layer) || ifConnect(sx+1, sy, layer) || ifConnect(sx, sy-1, layer) || ifConnect(sx, sy+1, layer))
		return;
	
	addIntoPoints(sx-1, sy, layer);
	addIntoPoints(sx+1, sy, layer);
	addIntoPoints(sx, sy-1, layer);
	addIntoPoints(sx, sy+1, layer);

	//是否找到可连接的点 
	bool ifFind = false;
	//最近的可连接的点的坐标 
	int aimPoint[2];
	
	//寻找可连接的点 
	while(1)
	{
//		int index = getIndexFromPoints();
//		//index为-1 则所有活结点全部遍历完 
//		if (index == -1) break;
//		
//		int px = index / M;
//		int py = index % M;

		//获取队列的第一个结点
		if (visitPoints.size() == 0) break;
		
		Ppoint firstPoint = visitPoints.front(); 
		int px = firstPoint.x;
		int py = firstPoint.y;
		visitPoints.pop();
		
		dist = currentBoard[px][py]+1;
		//当前活结点被访问了 标记为-1
		points[px][py] = -1;
		
		//访问当前活结点的上下左右 判断是否有可以连接的点
		if(addIntoPoints(px, py-1, layer))
		{
			if (ifConnect(px, py-1, layer))
			{
				ifFind = true;
				aimPoint[0] = px;
				aimPoint[1] = py - 1;
				break;
			}
		}
		
		if(addIntoPoints(px, py+1, layer))
		{
			if (ifConnect(px, py+1, layer))
			{
				ifFind = true;
				aimPoint[0] = px;
				aimPoint[1] = py + 1;
				break;
			}
		}
		
		if(addIntoPoints(px-1, py, layer))
		{
			if (ifConnect(px-1, py, layer))
			{
				ifFind = true;
				aimPoint[0] = px - 1;
				aimPoint[1] = py;
				break;
			}
		}
				
		if(addIntoPoints(px+1, py, layer))
		{
			if (ifConnect(px+1, py, layer))
			{
				ifFind = true;
				aimPoint[0] = px + 1;
				aimPoint[1] = py;
				break;
			}
		}
	}
	
	if (!ifFind)
	{
		cout << "NO PATH！" << endl;
		return;
	}
		
	int temp = dist - 1;
	int tempX = aimPoint[0];
	int tempY = aimPoint[1];
	Ppoint tempPoint(tempX, tempY);
	//cout << "tempPoint " << tempPoint.x << ' ' << tempPoint.y << endl;
	thePath.push_back(tempPoint);
	//cout << "thePath.size():" << thePath.size() << endl;
	while (temp > 0)
	{	
		//cout << tempX << ' ' << tempY << endl;
		if(currentBoard[tempX][tempY-1] == temp)
		{
			tempY--;
			tempPoint.setXY(tempX, tempY);
			//cout << "tempPoint " << tempPoint.x << ' ' << tempPoint.y << endl;
			thePath.push_back(tempPoint);
			//cout << "thePath.size():" << thePath.size() << endl;
		}
        else if(currentBoard[tempX][tempY+1] == temp)
        {
			tempY++;
			tempPoint.setXY(tempX, tempY);
			//cout << "tempPoint " << tempPoint.x << ' ' << tempPoint.y << endl;
			thePath.push_back(tempPoint);
			//cout << "thePath.size():" << thePath.size() << endl;
		}
		else if(currentBoard[tempX-1][tempY] == temp)
        {
			tempX--;
			tempPoint.setXY(tempX, tempY);
			//cout << "tempPoint " << tempPoint.x << ' ' << tempPoint.y << endl;
			thePath.push_back(tempPoint);
			//cout << "thePath.size():" << thePath.size() << endl;
		}
		else if(currentBoard[tempX+1][tempY] == temp)
        {
			tempX++;
			tempPoint.setXY(tempX, tempY);
			//cout << "tempPoint " << tempPoint.x << ' ' << tempPoint.y << endl;
			thePath.push_back(tempPoint);
			//cout << "thePath.size():" << thePath.size() << endl;
		}
        temp--;
	}
	//cout << tempX << ' ' << tempY << endl;
	tempPoint.setXY(sx, sy);
	//cout << "tempPoint " << tempPoint.x << ' ' << tempPoint.y << endl;
	thePath.push_back(tempPoint);
	//cout << "thePath.size():" << thePath.size() << endl;
	
 } 
 
//更新currentBoard 
void updateBoard(vector<Ppoint>pv, int layer)
{
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (currentBoard[i][j] >= 0)
				currentBoard[i][j] = 0;
			
			points[i][j] = 0;
		}
	}
	for (int i = 0; i < pv.size(); ++i)
	{
		int x = pv[i].x, y = pv[i].y;
		currentBoard[x][y] = -layer;
	}
	
	thePath.clear();
	
	while (!visitPoints.empty())
	{
		visitPoints.pop();
	 } 
	dist = 1;
}

//初始化currentBoard 
void initBoard(int initPoint[5][2], int size, int layer)
{
	//cout << "initBoard!" << endl;
	if (size > 2)
	{
		for (int i = 0; i < 3; ++i)
		{
			int x = initPoint[i][0], y = initPoint[i][1];
			currentBoard[x][y] = -layer;
		}
		for (int i = 3; i < size; ++i)
		{
			int x = initPoint[i][0], y = initPoint[i][1];
			currentBoard[x][y] = 0;
		}
	}
	else
	{
		for (int i = 0; i < size; ++i)
		{
			int x = initPoint[i][0], y = initPoint[i][1];
			currentBoard[x][y] = -layer;
		}
	}
	
	
}
 
int main()
{
	//存储三层线网的布线信息
	int pointBoard1[M][N], pointBoard2[M][N], pointBoard3[M][N]; 
	
	//三层线网各有多少个点 
	int pointSize[3] = {5, 5, 2};
	
	int points1[5][2] = {
	0, 0,
	0, 3,
	3, 1,
	2, 2,
	2, 0};
	
	int points2[5][2] = {
	0, 0,
	0, 3,
	3, 1,
	2, 2,
	2, 0};
	
	int points3[5][2] = {
	0, 3,
	3, 1,
	0, 0,
	2, 2,
	2, 0};
	
	//第一层 线网 
	cout << "开始处理第一层线网！" << endl;
	initBoard(points1, pointSize[0], 1);
	//showBoard();
	for (int i = 0; i < pointSize[0]; ++i)
	{
		cout << "现在处理第1层第" << i+1 << "个点" << endl; 
		int x = points1[i][0], y = points1[i][1];
		currentBoard[x][y] = -1;
		points[x][y] = -1;
		mazeAlg(x, y, 1);

		//存储第一层线网
		for (int i = 0; i < M; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (currentBoard[i][j] == -1)
					pointBoard1[i][j] = -1;
				else 
					pointBoard1[i][j] = 0;
			}
		}
	
		updateBoard(thePath, 1);
		//showBoard();
	}
	cout << "第一层线网处理完毕！" << endl;
	showBoard();
	
	cout << "---------------------------------------" << endl;
	
	//第二层 线网 
	cout << "开始处理第二层线网！" << endl;
	initBoard(points2, pointSize[0], 2);
	//showBoard();
	for (int i = 0; i < pointSize[1]; ++i)
	{
		cout << "现在处理第2层第" << i+1 << "个点" << endl; 
		int x = points2[i][0], y = points2[i][1];
		currentBoard[x][y] = -2;
		points[x][y] = -1;
		mazeAlg(x, y, 2);
		
		//存储第一层线网
		for (int i = 0; i < M; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (currentBoard[i][j] == -2)
					pointBoard2[i][j] = -2;
				else 
					pointBoard2[i][j] = 0;
			}
		}
		
		updateBoard(thePath, 2);
		//showBoard();
	}
	cout << "第二层线网处理完毕！" << endl;
	showBoard();
	
	//第三层 线网 
	cout << "开始处理第三层线网！" << endl;
	initBoard(points3, pointSize[2], 3);
	//showBoard();
	for (int i = 0; i < pointSize[2]; ++i)
	{
		cout << "现在处理第3层第" << i+1 << "个点" << endl; 
		int x = points3[i][0], y = points3[i][1];
		currentBoard[x][y] = -3;
		points[x][y] = -1;
		mazeAlg(x, y, 3);
		
		//存储第三层线网
		for (int i = 0; i < M; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (currentBoard[i][j] == -3)
					pointBoard2[i][j] = -3;
				else 
					pointBoard2[i][j] = 0;
			}
		}
		
		updateBoard(thePath, 3);
		//showBoard();
	}
	cout << "第三层线网处理完毕！" << endl;
	showBoard();
		
} 

