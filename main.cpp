#include <iostream>
#include <iomanip>
#include <vector>
#include <queue> 
#include <time.h>
#include <fstream>
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
#define M 100
#define N 100

//����õ�·�嵱ǰ���߷�����-1��ʾ�õ�һ������� -2��ʾ�ڶ��� -3��ʾ�����㣩
//int currentBoard[M][N]={
//    0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0
//};
int currentBoard[M][N];

int points[M][N];//�����
int dist = 1;//���ʼ���ľ���
vector<Ppoint>thePath;//�洢·�������� 
queue<Ppoint>visitPoints;//���� �洢��ǰ���Է��ʵĵ� 
int pathLength = 0;//�������ߵĳ��� 

//�鿴currentBoard 
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

//���һ����(px,py)����������ʼ��ľ������currentBoard �Ҵ�������� 
bool addIntoPoints(int px, int py, int layer)
{
	if (px < 0 || py < 0 || px > M - 1 || py > N - 1 || (currentBoard[px][py] != 0 && currentBoard[px][py] != -layer) || points[px][py] == -1)
		return false;
	
	else if (currentBoard[px][py] == -layer)
	{
		return true;
	}
	
	//cout << "��ӵ�:(" << px << ',' << py << ")" << endl;
	currentBoard[px][py] = dist;
	points[px][py] = 1;
	Ppoint tempPpoint(px, py);
	visitPoints.push(tempPpoint); 
	//showBoard();
	return true;
}

////�ӻ������ȡ��һ���ڵ㣬����-1��ʾ�������޿��ýڵ� 
//int getIndexFromPoints()
//{
//	for (int i = 0; i < M; ++i)
//		for (int j = 0; j < N; ++j)
//		{
//			if (points[i][j] > 0)
//			{
//				cout << "���ʵ�:(" << i << ',' << j << ")" << endl;
//				return i*M+j;
//			}
//				
//		}
//	return -1;
//} 
 
//�жϵ�(x,y)�Ƿ��������  layer--��ǰ����һ������ 
bool ifConnect(int x, int y, int layer)
{
	if (currentBoard[x][y] + layer == 0)
	{
		//cout << "��:(" << x << ',' << y << ")��������" << endl;
		return true;
	}
	//cout << "��:(" << x << ',' << y << ")�޷�����" << endl;
	return false;
}
 
//�Թ��㷨��ȡ·�� ���յ���� ���������������ӵĵ㣬�ͻ��ݵõ���ǰ��·��������path��   layer--��ǰ����һ������ 
void mazeAlg(int sx, int sy, int layer)
{
	//��һ�� �ȴ����յ��������ҵ��ĸ��� 
	if (ifConnect(sx-1, sy, layer) || ifConnect(sx+1, sy, layer) || ifConnect(sx, sy-1, layer) || ifConnect(sx, sy+1, layer))
		return;
	
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
//		int index = getIndexFromPoints();
//		//indexΪ-1 �����л���ȫ�������� 
//		if (index == -1) break;
//		
//		int px = index / M;
//		int py = index % M;

		//��ȡ���еĵ�һ�����
		if (visitPoints.size() == 0) break;
		
		Ppoint firstPoint = visitPoints.front(); 
		int px = firstPoint.x;
		int py = firstPoint.y;
		visitPoints.pop();
		
		dist = currentBoard[px][py]+1;
		//��ǰ���㱻������ ���Ϊ-1
		points[px][py] = -1;
		
		//cout << "��ǰ���ʽڵ�:(" << px << ',' << py << ')' << endl; 
		
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
	pathLength += dist;
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
 
//����currentBoard 
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

//��ʼ��currentBoard 
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
	//ʱ�� 
	clock_t start, finish;
    double totaltime;
    start = clock(); 
    
	//�洢���������Ĳ�����Ϣ
	int pointBoard1[M][N], pointBoard2[M][N], pointBoard3[M][N]; 
	
	//�����������ж��ٸ��� 
	int pointSize[3] = {5, 5, 5};
	
	int points1[5][2] = {
	10, 90,
	20, 80,
	30, 40,
	50, 90,
	80, 30};
	
	int points2[5][2] = {
	50, 70,
	20, 50,
	40, 10,
	70, 20,
	30, 90};
	
	int points3[5][2] = {
	60, 40,
	10, 40,
	30, 60,
	50, 30,
	20, 0};
	
	//��һ�� ���� 
	//cout << "��ʼ�����һ��������" << endl;
	for (int i = 0; i < pointSize[1]; ++i)
	{
		int x = points2[i][0], y = points2[i][1];
		currentBoard[x][y] = -2;
	}
	for (int i = 0; i < pointSize[2]; ++i)
	{
		int x = points3[i][0], y = points3[i][1];
		currentBoard[x][y] = -3;
	}
	for (int i = 0; i < pointSize[0]; ++i)
	{
		int x = points1[i][0], y = points1[i][1];
		currentBoard[x][y] = -1;
	}
	//showBoard();
	for (int i = 0; i < pointSize[0]; ++i)
	{
		//cout << "���ڴ����1���" << i+1 << "����" << endl; 
		int x = points1[i][0], y = points1[i][1];
		currentBoard[x][y] = -1;
		points[x][y] = -1;
		mazeAlg(x, y, 1);

		//�洢��һ������
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
	//cout << "��һ������������ϣ�" << endl;
	//cout << "��һ�㴦����pathLength = " << pathLength << endl;
	//showBoard();
	
	//cout << "---------------------------------------" << endl;
	
	//�ڶ��� ���� 
	//cout << "��ʼ����ڶ���������" << endl;
	for (int i = 0; i < pointSize[0]; ++i)
	{
		int x = points1[i][0], y = points1[i][1];
		currentBoard[x][y] = -1;
	}
	for (int i = 0; i < pointSize[2]; ++i)
	{
		int x = points3[i][0], y = points3[i][1];
		currentBoard[x][y] = -3;
	}
	for (int i = 0; i < pointSize[1]; ++i)
	{
		int x = points2[i][0], y = points2[i][1];
		currentBoard[x][y] = -2;
	}
	initBoard(points2, pointSize[0], 2);
	//showBoard();
	for (int i = 0; i < pointSize[1]; ++i)
	{
		//cout << "���ڴ����2���" << i+1 << "����" << endl; 
		int x = points2[i][0], y = points2[i][1];
		currentBoard[x][y] = -2;
		points[x][y] = -1;
		mazeAlg(x, y, 2);
		
		//�洢��һ������
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
	//cout << "�ڶ�������������ϣ�" << endl;
	//cout << "�ڶ��㴦����pathLength = " << pathLength << endl;
	//showBoard();
	
	//cout << "---------------------------------------" << endl;
	
	//������ ���� 
	//cout << "��ʼ���������������" << endl;
	for (int i = 0; i < pointSize[0]; ++i)
	{
		int x = points1[i][0], y = points1[i][1];
		currentBoard[x][y] = -1;
	}
	for (int i = 0; i < pointSize[1]; ++i)
	{
		int x = points2[i][0], y = points2[i][1];
		currentBoard[x][y] = -2;
	}
	for (int i = 0; i < pointSize[2]; ++i)
	{
		int x = points3[i][0], y = points3[i][1];
		currentBoard[x][y] = -3;
	}
	initBoard(points3, pointSize[2], 3);
	//showBoard();
	for (int i = 0; i < pointSize[2]; ++i)
	{
		//cout << "���ڴ����3���" << i+1 << "����" << endl; 
		int x = points3[i][0], y = points3[i][1];
		currentBoard[x][y] = -3;
		points[x][y] = -1;
		mazeAlg(x, y, 3);
		
		//�洢����������
		for (int i = 0; i < M; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (currentBoard[i][j] == -3)
					pointBoard3[i][j] = -3;
				else 
					pointBoard3[i][j] = 0;
			}
		}
		
		updateBoard(thePath, 3);
		//showBoard();
	}
	//cout << "����������������ϣ�" << endl;
	//cout << "�����㴦����pathLength = " << pathLength << endl;
	//showBoard();
	
	//cout << "---------------------------------------" << endl;
	
	finish = clock();
    totaltime = (double)(finish-start) / CLOCKS_PER_SEC;

    cout << "�˳��������ʱ��Ϊ" << totaltime << "�룡" << endl;
    cout << endl;
    
    //����������������txt
	ofstream f1("layer1.txt");//��layer1.txt�ļ�
	for (int i = 0; i < pointSize[0]; ++i)
	{
		int x = points1[i][0], y = points1[i][1];
		pointBoard1[x][y] = 4;
	}
	
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (pointBoard1[i][j] < 0)
				f1 << -pointBoard1[i][j] << ' ';
			else
				f1 << pointBoard1[i][j] << ' ';
		}
		f1 << endl;
	 } 
	
	cout << "д��layer1.txt���" << endl;
	 
	ofstream f2("layer2.txt");//��layer2.txt�ļ�
	for (int i = 0; i < pointSize[1]; ++i)
	{
		int x = points2[i][0], y = points2[i][1];
		pointBoard2[x][y] = 4;
	}
	
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (pointBoard2[i][j] < 0)
				f2 << -pointBoard2[i][j] << ' ';
			else
				f2 << pointBoard2[i][j] << ' ';
		}
		f2 << endl;
	 }
	
	cout << "д��layer2.txt���" << endl;
	 
	ofstream f3("layer3.txt");//��layer3.txt�ļ�
	for (int i = 0; i < pointSize[2]; ++i)
	{
		int x = points3[i][0], y = points3[i][1];
		pointBoard3[x][y] = 4;
	}
	
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (pointBoard3[i][j] < 0)
				f3 << -pointBoard3[i][j] << ' ';
			else
				f3 << pointBoard3[i][j] << ' ';
		}
		f3 << endl;
	 }
	cout << "д��layer3.txt���" << endl;
	
	ofstream file("finalPoints.txt");//��finalPoints.txt�ļ�
	for (int i = 0; i < pointSize[0]; ++i)
	{
		int x = points1[i][0], y = points1[i][1];
		currentBoard[x][y] = 8;
	}
	for (int i = 0; i < pointSize[1]; ++i)
	{
		int x = points2[i][0], y = points2[i][1];
		currentBoard[x][y] = 8;
	}
	for (int i = 0; i < pointSize[2]; ++i)
	{
		int x = points3[i][0], y = points3[i][1];
		currentBoard[x][y] = 8;
	}
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (currentBoard[i][j] < 0)
				file << -currentBoard[i][j] << ' ';
			else
				file << currentBoard[i][j] << ' ';
		}
		file << endl;
	 }
	cout << "д��finalPoints.txt���" << endl;
		
} 

