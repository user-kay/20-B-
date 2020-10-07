#include<bits/stdc++.h>
#include"Path.h"
#include"Consume.h"
#include"BasisData.h"
using namespace std;


/*
    弗洛伊德函数计算路径
*/
const int INF = 99999999;

int Fmap[221][2] = 
{27,104,
1,2,
1,25,
2,1,
2,3,
3,2,
3,4,
3,25,
4,3,
4,5,
4,24,
4,25,
5,4,
5,6,
5,24,
6,5,
6,7,
6,23,
6,24,
7,6,
7,8,
7,22,
8,7,
8,9,
8,22,
9,8,
9,10,
9,15,
9,17,
9,21,
10,9,
10,11,
10,13,
10,15,
11,10,
11,12,
11,13,
12,11,
12,13,
12,14,
13,10,
13,11,
13,12,
13,14,
13,15,
14,12,
14,13,
14,15,
14,16,
15,9,
15,10,
15,13,
15,14,
15,16,
16,9,
16,14,
16,15,
16,17,
16,18,
17,9,
17,16,
17,18,
17,21,
18,16,
18,17,
18,19,
18,20,
19,18,
19,20,
20,18,
20,19,
20,21,
21,9,
21,17,
21,20,
21,22,
21,23,
21,27,
22,7,
22,8,
22,9,
22,21,
22,23,
23,6,
23,21,
23,22,
23,24,
23,26,
24,4,
24,5,
24,6,
24,23,
24,25,
24,26,
25,1,
25,3,
25,4,
25,24,
25,26,
26,23,
26,24,
26,25,
26,27,
27,21,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26,
27,26
};

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
        a = Fmap[i][0];
        b = Fmap[i][1];
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

Path Floyd_Main(int x, int y){
    Path p;
    int n,m,en;
    //freopen("fristData.txt","r",stdin);
    //cin >> n >>m;
    n = Fmap[0][0];
    m = Fmap[0][1];
    IN(n,m);
    Floyd(n);
    // 从第x个点到第y个点
    //cout << "1: ";
    en = x;
    //路径
    while (en != y)
    {
        //cout << en << "->";
        p.road.push_back(en);
        en = path[en][y];
    }
    //cout << y <<endl;
    p.road.push_back(y);
    //输出步数
    p.step = d[x][y];
    //cout << "2: " << d[x][y] <<endl;
    freopen("BeginCarry.txt","r",stdin);
    return p;
}

Consume villageSeeFuture(int days, vector<Path>& p){
    //  n 为离开村庄去的地方的路径和步数
    int n = p.size() - 1;
    //在矿山预计呆的天数
    const int daysInMine = 4;
    Consume consume;
    BasisData basisData;
    //离开矿山的步数
    int daysAfterMine = max(Floyd_Main(basisData.mine[0], basisData.village[0]).step, Floyd_Main(basisData.mine[0],basisData.end).step);
    //去矿山
    if(p[n].road[p[n].road.size() - 1] == basisData.mine[0]){
        //除去在矿山的天数
        int allDays = p[n].step + daysAfterMine;
        for(int step_i = 1; step_i <= allDays; step_i++){
            switch (basisData.weather[step_i + days])
            {
            case 3:
                consume.water += basisData.sandDayFood;
                consume.food += basisData.sandDayFood;
                break;
            
            case 2:
                consume.water += basisData.heatDayWater * 2;
                consume.food += basisData.heatDayFood * 2;
                break;
            case 1:
                consume.water += basisData.sunnyDayWater * 2;
                consume.food += basisData.sunnyDayFood * 2;
                days++;
                break;
            }
        }
        consume.water += basisData.heatDayWater * 3;
        consume.food += basisData.heatDayFood * 3;
    }
    //去终点
    else{
        int allDays = p[n].step;
        for(int step_i = 1; step_i <= allDays; step_i++){
            switch (basisData.weather[step_i + days])
            {
            case 3:
                consume.water += basisData.sandDayFood;
                consume.food += basisData.sandDayFood;
                break;
            
            case 2:
                consume.water += basisData.heatDayWater * 2;
                consume.food += basisData.heatDayFood * 2;
                break;
            case 1:
                consume.water += basisData.sunnyDayWater * 2;
                consume.food += basisData.sunnyDayFood * 2;
                days++;
                break;
            }
        }
    }
    return consume;
}

int main(){
    srand((unsigned)time(NULL));
    // freopen("BeginCarry.txt","r",stdin);
    int water,food;
    while(true){
        freopen("BeginCarry.txt","r",stdin);
        scanf("%d%d", &water, &food);
        //初始携带
        Consume beginCarry(water,food);
        int c = 0;
        while(c < 300){
            c++;
            BasisData basisData;
            int days = 0;
            long income = 0;
            //  现在所在的位置， 0为起点 1为路上 2为矿山 3为村庄 4为终点
            int location = 0;
            //去哪  0为起点 1为路上 2为矿山 3为村庄 4为终点
            int goToWhere = 2;
            double probability_1 = 0;   //判断停走概率
            double probability_2 = 0;   //判断是否停留矿山
            double probability_3 = 0;   //判断去村庄，终点；
            double probability_4 = 0;   //判断从村庄去终点、矿山
            //probability_1 = (rand() % 1000 + 1) / 1000;
            //实际消耗
            Consume realConsume(0,0);
            //村庄补充
            Consume supply;
            //多次在村庄补充总数
            Consume allSupply(0,0);
            vector<Path> p;
            p.push_back(Floyd_Main(basisData.begin,basisData.mine[0]));
            //step_i 走的步数
            for(int step_i = 1; step_i <  p[0].step;){
                days++;
                switch (basisData.weather[days])
                {
                    case 2:
                    //高温
                        probability_1 = (double)(rand() % 1000 + 1) / 1000;
                        //停
                        if(probability_1 < 0.4){
                            realConsume.water += basisData.heatDayWater;
                            realConsume.food += basisData.heatDayFood;
                        }
                        else{
                            realConsume.water += basisData.heatDayWater * 2;
                            realConsume.food += basisData.heatDayFood * 2;
                            step_i++;
                        }
                        break;
                    case 1:
                    //晴天
                        probability_1 = (double)(rand() % 1000 + 1) / 1000;
                        //走
                        if(probability_1 < 0.8){
                            realConsume.water += basisData.sunnyDayWater * 2;
                            realConsume.food += basisData.sunnyDayFood * 2;
                            step_i++;
                        }
                        //停
                        else{
                            realConsume.water += basisData.sunnyDayWater;
                            realConsume.food += basisData.sunnyDayFood;
                        }
                        break;
                    case 3:
                            realConsume.water += basisData.sandDayWater;
                            realConsume.food += basisData.sandDayFood;
                        break;
                    }
                }    
                bool ending = true;
                if(realConsume.water > beginCarry.water || realConsume.food > beginCarry.food){
                    //cout << "die at 1" << endl;
                    continue;
                }
                location = goToWhere;
                while(ending){
                    switch (location)
                    {
                    case 1:
                        for(int step_i = 1; step_i <=  p[p.size() - 1].step;){
                            days++;
                            switch (basisData.weather[days])
                            {
                                case 2:
                                //高温
                                    probability_1 = (double)(rand() % 1000 + 1) / 1000;
                                    //停
                                    if(probability_1 < 0.4){
                                        realConsume.water += basisData.heatDayWater;
                                        realConsume.food += basisData.heatDayFood;
                                    }
                                    else{
                                        realConsume.water += basisData.heatDayWater * 2;
                                        realConsume.food += basisData.heatDayFood * 2;
                                        step_i++;
                                    }
                                    break;
                                case 1:
                                //晴天
                                    probability_1 = (double)(rand() % 1000 + 1) / 1000;
                                    //走
                                    if(probability_1 < 0.8){
                                        realConsume.water += basisData.sunnyDayWater * 2;
                                        realConsume.food += basisData.sunnyDayFood * 2;
                                        step_i++;
                                    }
                                    //停
                                    else{
                                        realConsume.water += basisData.sunnyDayWater;
                                        realConsume.food += basisData.sunnyDayFood;
                                    }
                                    break;
                                case 3:
                                    realConsume.water += basisData.sandDayWater;
                                    realConsume.food += basisData.sandDayFood;
                                    break;
                            }
                    }
                    location = goToWhere;
                    break;
                case 2:
                    probability_2 = (double)(rand() % 1000 + 1) / 1000;
                    //留在矿山
                    if(probability_2 < 0.556){
                        income += basisData.basisPay;
                        switch (basisData.weather[days])
                        {
                        case 1:
                            realConsume.water += basisData.sunnyDayWater * 3;
                            realConsume.food += basisData.sunnyDayFood * 3;
                            break;
                        case 2:
                            realConsume.water += basisData.heatDayWater * 3;
                            realConsume.food += basisData.heatDayFood * 3;
                            break;
                        case 3:
                            realConsume.water += basisData.sandDayWater * 3;
                            realConsume.food += basisData.sandDayFood * 3;
                            break;
                        }
                        days++;
                    }
                    //剩余概率0.444 村庄为0.333 终点为0.111 即随机后去村庄的概率是0.75
                    else{
                        probability_3 = (double)(rand() % 1000 + 1) / 1000;
                        location = 1;
                        //去村庄
                        if(probability_3 < 0.75){
                            p.push_back(Floyd_Main(basisData.mine[0], basisData.village[0]));
                            goToWhere = 3;
                        }
                        //去终点
                        else{
                            p.push_back(Floyd_Main(basisData.mine[0], basisData.end));
                            goToWhere = 4;
                        }
                        days++;
                    }
                    break;
                case 3:
                    probability_4 = (double)(rand() % 1000 + 1) / 1000;
                    location = 1;
                    switch (basisData.weather[days])
                    {
                            case 2:
                            //高温
                                probability_1 = (double)(rand() % 1000 + 1) / 1000;
                                //停
                                if(probability_1 < 0.4){
                                    realConsume.water += basisData.heatDayWater;
                                    realConsume.food += basisData.heatDayFood;
                                    days++;
                                }
                                else{
                                    //去矿山
                                    if(probability_4 < 0.375){
                                        p.push_back(Floyd_Main(basisData.village[0], basisData.mine[0]));
                                        goToWhere = 2;
                                    }
                                    //去终点
                                    else{
                                        p.push_back(Floyd_Main(basisData.village[0], basisData.end));
                                        goToWhere = 4;
                                    }
                                }
                                break;
                            case 1:
                            //晴天
                                probability_1 = (double)(rand() % 1000 + 1) / 1000;
                                //走
                                if(probability_1 < 0.8){
                                    //去矿山
                                    if(probability_4 < 0.375){
                                        p.push_back(Floyd_Main(basisData.village[0], basisData.mine[0]));
                                        supply = villageSeeFuture(days, p);
                                        allSupply.water += supply.water;
                                        allSupply.food += supply.food;
                                        if(beginCarry.food * basisData.foodHeight + beginCarry.water * basisData.waterHeight > basisData.weightUpperLimit){
                                            //结束
                                        }
                                        goToWhere = 2;
                                    }
                                    //去终点
                                    else{
                                        p.push_back(Floyd_Main(basisData.village[0], basisData.end));
                                        supply = villageSeeFuture(days, p);
                                        allSupply.water += supply.water;
                                        allSupply.food += supply.food;
                                        if(beginCarry.food * basisData.foodHeight + beginCarry.water * basisData.waterHeight > basisData.weightUpperLimit){
                                            //结束
                                        }
                                        goToWhere = 4;
                                    }
                                }
                                //停
                                else{
                                    realConsume.water += basisData.sunnyDayWater;
                                    realConsume.food += basisData.sunnyDayFood;
                                    days++;
                                }
                                break;
                            case 3:
                                realConsume.water += basisData.sandDayWater;
                                realConsume.food += basisData.sandDayFood;
                                days++;
                                break;
                    }
                    break;
                case 4:
                    ending = false;
                    break;
                }
                if(realConsume.water > beginCarry.water + allSupply.water || realConsume.food > beginCarry.food + allSupply.food){
                    //cout << "die at 2" << endl;
                    break;
                }
                if(days > 30){
                    //cout << "no" << endl;
                    break;
                }
            }
            if(!ending){
                //freopen("B(1)answer.txt","w",stdout);
                int allSpand = allSupply.water * basisData.basisWaterPices * 2 + 
                    allSupply.food * basisData.basisFoodPices * 2 + beginCarry.food * basisData.basisFoodPices +
                        beginCarry.water * basisData.basisWaterPices;
                double back = (allSupply.water + beginCarry.water - realConsume.water) * 2.5 + (allSupply.food + beginCarry.food - realConsume.food) * 5;
                double profit = (double)(income + basisData.basisMoney - allSpand) + back;
                if(profit > 7000){
                cout << "the using day is: " << days << endl;
                cout << "The profit is: " << profit << endl;
                for(int i = 0; i < p.size(); ++i){
                    for(int j = 0; j < p[i].road.size(); ++j){
                        cout << p[i].road[j];
                        if(j != p[i].road.size() - 1){
                            cout << " -> ";
                        }
                    }
                    cout << endl;
                }
                cout<<endl;
                }
            }
        }
    }
    return 0;
}