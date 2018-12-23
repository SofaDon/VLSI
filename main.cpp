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

//�����С
#define M 7
#define N 7

//����õ�·�嵱ǰ���߷�����-1��ʾ�õ�һ������� -2��ʾ�ڶ��� -3��ʾ�����㣩
int currentBoard[M][N]={
    0,0,-1,0,0,0,0,
    0,0,-1,0,0,0,0,
    0,0,-1,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0
};

int points[M][N];//�����
int dist = 1;//���ʼ���ľ���
vector<Ppoint>thePath;//�洢·�������� 

//���һ����(px,py)����������ʼ��ľ������currentBoard 
bool addIntoPoints(int px, int py, int layer)
{
	if (px < 0 || py < 0 || px > M - 1 || py > N - 1 || (currentBoard[px][py] != 0 && currentBoard[px][py] != -layer) || points[px][py] == -1)
		return false;
	
	else if (currentBoard[px][py] == -layer)
	{
		return true;
	}
	cout << "��ӵ�:(" << px << ',' << py << ")" << endl;
	currentBoard[px][py] = dist;
	points[px][py] = 1;
	return true;
}

//�ӻ������ȡ��һ���ڵ㣬����-1��ʾ�������޿��ýڵ� 
int getIndexFromPoints()
{
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j)
		{
			if (points[i][j] > 0)
			{
				cout << "���ʵ�:(" << i << ',' << j << ")" << endl;
				return i*M+j;
			}
				
		}
	return -1;
} 
 
//�жϵ�(x,y)�Ƿ��������  layer--��ǰ����һ������ 
bool ifConnect(int x, int y, int layer)
{
	if (currentBoard[x][y] + layer == 0)
	{
		cout << "��:(" << x << ',' << y << ")��������" << endl;
		return true;
	}
	cout << "��:(" << x << ',' << y << ")�޷�����" << endl;
	return false;
}
 
//�Թ��㷨��ȡ·�� ���յ���� ���������������ӵĵ㣬�ͻ��ݵõ���ǰ��·��������path��   layer--��ǰ����һ������ 
void mazeAlg(int sx, int sy, int layer)
{
	//��һ�� �ȴ����յ��������ҵ��ĸ��� 
	addIntoPoints(sx-1, sy, layer);
	addIntoPoints(sx+1, sy, layer);
	addIntoPoints(sx, sy-1, layer);
	addIntoPoints(sx, sy+1, layer);
	
	//�Ƿ��ҵ������ӵĵ� 
	bool ifFind = false;
	//����Ŀ����ӵĵ������ 
	int aimPoint[2];
	
	//Ѱ�ҿ����ӵĵ� 
	while(1)
	{
		int index = getIndexFromPoints();
		//indexΪ-1 �����л���ȫ�������� 
		if (index == -1) break;
		
		int px = index / M;
		int py = index % M;
		
		dist = currentBoard[px][py]+1;
		//��ǰ���㱻������ ���Ϊ-1
		points[px][py] = -1;
		
		//���ʵ�ǰ������������� �ж��Ƿ��п������ӵĵ�
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
		cout << "NO PATH��" << endl;
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
	cout << "��������ʼ�������:" << endl;
	cin >> x1 >> y1; 
	points[x1][y1] = -1;
    mazeAlg(x1, y1, 1);
    for (int i = 0; i < thePath.size(); ++i)
	{
		cout << '(' << thePath[i].x << ',' << thePath[i].y << ')' << endl;
	}
} 

