#include<bits/stdc++.h>

using namespace std;

//基础数据
struct BasisData
{
    //质量上限
    const int weightLimit = 1200;
    //初始资金
    const int beginMoney = 10000;
    //基础收益
    const int basisIncome = 200;
    //截止日期
    const int lastDay = 10;
    //水每箱质量
    const int waterHeight = 3;
    //食物每箱质量
    const int foodHeight = 2;
    //水基准价格
    const int waterMoney = 5;
    //食物基准价格
    const int foodMoney = 10;
    //水晴天消耗量
    const int sunnyDayWater = 3;
    //食物晴天消耗量
    const int sunnyDayFood = 4;
    //水高温消耗量
    const int heatDayWater = 9;
    //食物高温消耗量
    const int heatDayFood = 9;
}basisData;

//创造路径  此题路径唯一
const int path[6] = {1,4,3,9,11,13};
//天气变量 1 为晴天     2 为高温
vector<int> weather;
vector<int> atMine;
//动作  1为走 2为停不挖矿   3为挖矿
vector<int> work; 
//消耗的物资
struct Goods
{
    int allConsumeWater = 0;
    vector<int> water;
    int allConsumeFood = 0;
    vector<int> food;
}goods;

//第二天天气
void nextDayWeather(int days){
    const int heatProbability = 5556;
    int probability = rand() % 10000 + 1;
    if(probability <= heatProbability){
        weather.push_back(2);
        return;
    }
    else{
        weather.push_back(1);
        return;
    }
}

//是否继续呆在矿山 true为呆
bool stayAtmine(){
    const int stayProbability = 5556;
    int probability = rand() % 10000 + 1;
    if(probability < stayProbability){
        return true;
    }
    else return false;
}

void CreativeAll(){
    // 第0天不算
    weather.push_back(0);
    goods.water.push_back(0);
    goods.food.push_back(0);
    goods.allConsumeFood = 0;
    goods.allConsumeWater = 0;
    return;
}

//花费物资 1为走 2为停不挖矿   3为挖矿
void consume(int work, int days){
    switch (weather[days])
    {
    // 晴天
    case 1:
        switch (work)
        {
        //走    
        case 1:
            goods.water.push_back(basisData.sunnyDayWater * 2);
            goods.food.push_back(basisData.sunnyDayFood * 2);
            break;
        //停
        case 2:
            goods.water.push_back(basisData.sunnyDayWater);
            goods.food.push_back(basisData.sunnyDayFood);
            break;
        //挖矿
        case 3:
            goods.water.push_back(basisData.sunnyDayWater * 3);
            goods.food.push_back(basisData.sunnyDayFood * 3);
            break;
        }
        break;
    case 2:
        switch (work)
        {
        //走    
        case 1:
            goods.water.push_back(basisData.heatDayWater * 2);
            goods.food.push_back(basisData.heatDayFood * 2);
            break;
        case 2:
            goods.water.push_back(basisData.heatDayWater);
            goods.food.push_back(basisData.sunnyDayFood);
            break;
        case 3:
            goods.water.push_back(basisData.heatDayWater * 3);
            goods.food.push_back(basisData.heatDayFood * 3);
            break;
        }
    }
}

int main(){
    srand((unsigned)time(NULL));
    long long allmoney = 0;
    int c = 0;
    freopen("data4_7_13.txt","w",stdout);
    while(c < 1000){
        c++;
        int mineGet = 0;
        weather.clear();
        goods.water.clear();
        goods.food.clear();
        atMine.clear();
        CreativeAll();
        int days = 1;
        nextDayWeather(days);
        //从4->7->12->13
        consume(1,days);
        days++;
        nextDayWeather(days);
        consume(1,days);
        days++;
        nextDayWeather(days);
        consume(1,days);
        days++;
        nextDayWeather(days);
        consume(1,days);
        for(int i = 1; i < goods.food.size();i++){
            goods.allConsumeFood += goods.food[i];
        }
        for(int i = 1; i < goods.water.size();i++){
            goods.allConsumeWater += goods.water[i];
        }
        int spend = goods.allConsumeWater * 5 + goods.allConsumeFood * 10;
        int weight = goods.allConsumeFood * 2 + goods.allConsumeWater * 3;
        //if(mineGet + basisData.beginMoney - spend > 9760){
            cout<<"spend: "<<spend<<endl;
            cout<<"get: " << mineGet <<endl;
            cout<<"money: " << mineGet + basisData.beginMoney - spend<<endl;
            cout<<"weight: "<<weight<<endl;
            cout<<days<<endl;
            for(int i = 1; i < weather.size();i++){
                cout<<weather[i]<<" ";
            }
            cout<<endl;
            cout<<"food:"<<endl;
            for(int i = 1; i < goods.food.size();i++){
                cout<<goods.food[i]<<" ";
            }
            cout<<endl;
            cout<<"water: "<<endl;
            for(int i = 1; i < goods.water.size();i++){
                cout<<goods.water[i]<<" ";
            }
            cout<<endl;
            cout<<endl;
            allmoney += mineGet + basisData.beginMoney - spend;
        //}
    }
    allmoney /= 1000;
    cout<<"allmoney: "<<allmoney<<endl;
    return 0;
}