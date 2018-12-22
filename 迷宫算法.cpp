#include <iostream>
#include <iomanip>
using namespace std;
#define n 7//方格大小
#define m 7
 
int a[n][m]={
    0,0,0,0,0,0,0,
    0,0,-1,-1,0,0,0,
    0,0,0,0,-1,0,0,
    0,0,0,-1,-1,0,0,
    -1,0,0,0,0,0,0,
    -1,-1,-1,0,0,0,0,
    -1,-1,-1,0,0,0,0
};//保存该电路板当前布线方案（-1表示该方格被锁定即障碍物）
int s[n][m];//活结点表
int dist = 1;//与初始结点的距离
 
//把结点（px，py）添加进活结点表，并设置与开始结点的距离
bool AddIntoS(int px,int py,int s[n][m],int a[n][m])
{
    if(px<0||px>n-1||py<0||py>m-1||a[px][py]!=0||s[px][py]==-1)return false;
    a[px][py]=dist;
    s[px][py]=1;
    return true;
}
 
//从活结点表中取出一个结点，返回-1表示活结点表为空
int FindOfIndexFromS(int s[n][m])
{
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
          if(s[i][j]>0)return i*m+j;
    return -1;
}
//初始结点(sx,sy)，目标结点(ex,ey)
void FindPath(int sx,int sy,int ex,int ey,int s[n][m],int a[n][m])
{
    AddIntoS(sx+1,sy,s,a);
    AddIntoS(sx-1,sy,s,a);
    AddIntoS(sx,sy+1,s,a);
    AddIntoS(sx,sy-1,s,a);//先单独处理初始结点周围的结点
    while(true)
    {
        int index=FindOfIndexFromS(s);
        if(index==-1)break;
        int px=index/m,
            py=index%m;
        dist=a[px][py]+1;
        s[px][py]=-1;
        AddIntoS(px+1,py,s,a);
        if(px+1==ex&&py==ey)break;
        AddIntoS(px-1,py,s,a);
        if(px-1==ex&&py==ey)break;
        AddIntoS(px,py+1,s,a);
        if(px==ex&&py+1==ey)break;
        AddIntoS(px,py-1,s,a);
        if(px==ex&&py-1==ey)break;
    }
    int temp=dist-1;
    
    cout << "迷宫路径的长度为：" << dist+1 << endl;
    cout << "迷宫路径为: " << endl;
    while(temp>0)//生成路径，从目标结点开始查找与初始结点距离小1的邻结点
    {
    	
        if(a[ex+1][ey]==temp)ex++;
        else if(a[ex-1][ey]==temp)ex--;
        else if(a[ex][ey+1]==temp)ey++;
        else if(a[ex][ey-1]==temp)ey--;
        else {
            cout<<"No Path!"<<endl;
            break;
        }
        cout<<ex<<" "<<ey<<endl;
        temp--;
    }
}
 
 
int main()
{
	int x1, y1, x2, y2;
	cout << "请输入起始点和终点坐标：" << endl;
	cin >> x1 >> y1 >> x2 >> y2; 
    a[2][1]=0;//起点
    a[3][5]=0;//终点
    FindPath(x1,y1,x2,y2,s,a);
}
