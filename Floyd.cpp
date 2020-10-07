#include <stdio.h>
#include <iostream>
#include<Path.h>
using namespace std;

const int INF = 99999999;

// 邻接矩阵
int d[101][101] = {0};
// 路径矩阵， path[i][j]表示从i -> j需要经过的第一个点
int path[101][101];
//点点之间长度都为1
const int twoPoint = 1;

//初始化函数, n 为点数  m 为边数
/*
矩阵录入方式
E：
从1点到2点
因为两个点间距为1
所以录入方式为
1 2
1 3
*/
void IN(int n,int m){
    int i,j;
    int a,b,t;
    for(i = 1; i <= n; ++i){
        for(j = 1;j <= n; ++j){
            d[i][j] = INF;
            path[i][j] = j;
        }
    }
    for(i = 1; i <= m; ++i)
    {
        cin >> a >> b;
        d[a][b] = d[b][a] = twoPoint;
    }
}

//弗洛伊德算法   n 为点数
void Floyd(int n)
{
    int i, j, k;
    for(k = 1; k <= n; ++k)
        for(i = 1;i <= n; ++i)
            for(j = 1;j <= n; ++j)
                if(d[i][k] + d[k][j] < d[i][j]){
                    d[i][j] = d[i][k] + d[k][j];
                    path[i][j] = path[i][k];
                }
}

Path Floyd_Main(){
    Path p;
    int n,m,x,y,en;
    freopen("fristData.txt","r",stdin);
    cin >> n >>m;
    IN(n,m);
    Floyd(n);
    cin >> x >> y;
    // 从第x个点到第y个点
    cout << "1: ";
    en = x;
    //路径
    while (en != y)
    {
        cout << en << "->";
        p.road.push_back(en);
        en = path[en][y];
    }
    cout << y <<endl;
    p.road.push_back(y);
    //输出步数
    p.step = d[x][y];
    cout << "2: " << d[x][y] <<endl;
    return p;
}