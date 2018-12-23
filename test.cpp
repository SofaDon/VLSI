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
		Ppoint()
		{
			
		}
};

vector<Ppoint> path;

int main()
{
	Ppoint temp(1,1);
	path.push_back(temp);
	Ppoint p = path[0];
	cout << p.x << p.y << endl;

	return 0;
}
