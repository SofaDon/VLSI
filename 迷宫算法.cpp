#include <iostream>
#include <iomanip>
using namespace std;
#define n 7//�����С
#define m 7
 
int a[n][m]={
    0,0,0,0,0,0,0,
    0,0,-1,-1,0,0,0,
    0,0,0,0,-1,0,0,
    0,0,0,-1,-1,0,0,
    -1,0,0,0,0,0,0,
    -1,-1,-1,0,0,0,0,
    -1,-1,-1,0,0,0,0
};//����õ�·�嵱ǰ���߷�����-1��ʾ�÷����������ϰ��
int s[n][m];//�����
int dist = 1;//���ʼ���ľ���
 
//�ѽ�㣨px��py����ӽ�������������뿪ʼ���ľ���
bool AddIntoS(int px,int py,int s[n][m],int a[n][m])
{
    if(px<0||px>n-1||py<0||py>m-1||a[px][py]!=0||s[px][py]==-1)return false;
    a[px][py]=dist;
    s[px][py]=1;
    return true;
}
 
//�ӻ������ȡ��һ����㣬����-1��ʾ�����Ϊ��
int FindOfIndexFromS(int s[n][m])
{
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
          if(s[i][j]>0)return i*m+j;
    return -1;
}
//��ʼ���(sx,sy)��Ŀ����(ex,ey)
void FindPath(int sx,int sy,int ex,int ey,int s[n][m],int a[n][m])
{
    AddIntoS(sx+1,sy,s,a);
    AddIntoS(sx-1,sy,s,a);
    AddIntoS(sx,sy+1,s,a);
    AddIntoS(sx,sy-1,s,a);//�ȵ��������ʼ�����Χ�Ľ��
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
    
    cout << "�Թ�·���ĳ���Ϊ��" << dist+1 << endl;
    cout << "�Թ�·��Ϊ: " << endl;
    while(temp>0)//����·������Ŀ���㿪ʼ�������ʼ������С1���ڽ��
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
	cout << "��������ʼ����յ����꣺" << endl;
	cin >> x1 >> y1 >> x2 >> y2; 
    a[2][1]=0;//���
    a[3][5]=0;//�յ�
    FindPath(x1,y1,x2,y2,s,a);
}
