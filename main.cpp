#include <iostream>
#include <iomanip>
#include <vector>
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
    0,0,-1,0,0,0,0,
    0,0,-1,0,0,0,0,
    0,0,-1,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0
};

int points[M][N];//活结点表
int dist = 1;//与初始结点的距离
vector<Ppoint>thePath;//存储路径的坐标 

//添加一个点(px,py)并将距离起始点的距离存入currentBoard 
bool addIntoPoints(int px, int py, int layer)
{
	if (px < 0 || py < 0 || px > M - 1 || py > N - 1 || (currentBoard[px][py] != 0 && currentBoard[px][py] != -layer) || points[px][py] == -1)
		return false;
	
	else if (currentBoard[px][py] == -layer)
	{
		return true;
	}
	cout << "添加点:(" << px << ',' << py << ")" << endl;
	currentBoard[px][py] = dist;
	points[px][py] = 1;
	return true;
}

//从活结点表中取出一个节点，返回-1表示活结点中无可用节点 
int getIndexFromPoints()
{
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j)
		{
			if (points[i][j] > 0)
			{
				cout << "访问点:(" << i << ',' << j << ")" << endl;
				return i*M+j;
			}
				
		}
	return -1;
} 
 
//判断点(x,y)是否可以连接  layer--当前是哪一层线网 
bool ifConnect(int x, int y, int layer)
{
	if (currentBoard[x][y] + layer == 0)
	{
		cout << "点:(" << x << ',' << y << ")可以连接" << endl;
		return true;
	}
	cout << "点:(" << x << ',' << y << ")无法连接" << endl;
	return false;
}
 
//迷宫算法获取路径 从终点出发 但凡遇到可以连接的点，就回溯得到当前的路径并存入path中   layer--当前是哪一层线网 
void mazeAlg(int sx, int sy, int layer)
{
	//第一步 先处理终点上下左右的四个点 
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
		int index = getIndexFromPoints();
		//index为-1 则所有活结点全部遍历完 
		if (index == -1) break;
		
		int px = index / M;
		int py = index % M;
		
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
			cout << "tempPoint " << tempPoint.x << ' ' << tempPoint.y << endl;
			thePath.push_back(tempPoint);
			//cout << "thePath.size():" << thePath.size() << endl;
		}
        else if(currentBoard[tempX][tempY+1] == temp)
        {
			tempY++;
			tempPoint.setXY(tempX, tempY);
			cout << "tempPoint " << tempPoint.x << ' ' << tempPoint.y << endl;
			thePath.push_back(tempPoint);
			//cout << "thePath.size():" << thePath.size() << endl;
		}
		else if(currentBoard[tempX-1][tempY] == temp)
        {
			tempX--;
			tempPoint.setXY(tempX, tempY);
			cout << "tempPoint " << tempPoint.x << ' ' << tempPoint.y << endl;
			thePath.push_back(tempPoint);
			//cout << "thePath.size():" << thePath.size() << endl;
		}
		else if(currentBoard[tempX+1][tempY] == temp)
        {
			tempX++;
			tempPoint.setXY(tempX, tempY);
			cout << "tempPoint " << tempPoint.x << ' ' << tempPoint.y << endl;
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
 
int main()
{
	int x1, y1;
	cout << "请输入起始点的坐标:" << endl;
	cin >> x1 >> y1; 
	points[x1][y1] = -1;
    mazeAlg(x1, y1, 1);
    for (int i = 0; i < thePath.size(); ++i)
	{
		cout << '(' << thePath[i].x << ',' << thePath[i].y << ')' << endl;
	}
} 

