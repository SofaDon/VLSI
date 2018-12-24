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
		Ppoint()
		{
			
		}
};

vector<Ppoint> path;
queue<Ppoint> savePoints;

int main()
{
//	Ppoint temp(1,1);
//	path.push_back(temp);
//	Ppoint p = path[0];
//	cout << p.x << p.y << endl;
	
	Ppoint temp1(1,1);
	Ppoint temp2(2,1);
	Ppoint temp3(3,1);
	Ppoint temp4(4,1);
	savePoints.push(temp1);
	savePoints.push(temp2);
	savePoints.push(temp3);
	savePoints.push(temp4);
	
	Ppoint temp = savePoints.front();
	cout << temp.x << ' ' << temp.y << endl;
	
	savePoints.pop();
	temp = savePoints.front();
	cout << temp.x << ' ' << temp.y << endl;
}
