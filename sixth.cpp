#include<bits/stdc++.h>
using namespace std;

struct BasisData
{
    //质量上限
    const int weightLimit = 1200;
    //初始资金
    const int beginMoney = 10000;
    //基础收益
    const int basisIncome = 1000;
    //截止日期
    const int lastDay = 30;
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
    //水沙暴消耗量
    const int sandDayWater = 10;
    //食物沙暴消耗量
    const int sandDayFood = 10;
}basisData;

//消耗的物资
//  在 vector 中用正数表示购买的物资
//  用负数表示消耗的物资
struct Goods
{
    int allConsumeWater = 0;
    vector<int> water;
    int allConsumeFood = 0;
    vector<int> food;
}goods[3];

//模拟第二天天气    1为晴天 2为高温 3为沙暴
vector<int> weather;
//在矿山天数
vector<int> atMine;

//第二天天气
void createNextDayWeather(){
    weather.push_back(0);
    for(int i = 1;i <= 30; i++){
        int probability = rand() % 10000 + 1;
        if(probability < 2000){
            weather.push_back(3);
        }
        else{
            //  根据权重 0.4667 0.2 0.3333 排除0.2后剩余0.8算出加权后沙暴为 0.5834
            probability = rand() % 10000 + 1;
            if(probability < 5834){
                weather.push_back(2);
                continue;
            }
            else{
                weather.push_back(1);
                continue;
            }
        }
    }
}

//在路上走还是停
int walkOrStay(int weatherNow){
    int probability = rand() % 10000 + 1;
    switch(weatherNow){
        case 1:
            if(probability <= 8000) return 1;
            else return 2;
            break;
        case 2:
            if(probability <= 2860) return 2;
            else return 1;
            break;
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

// true为足够
bool isFoodEnough(int who){
    for(int i = 0; i < goods[who].food.size(); ++i)
        goods[who].allConsumeFood += goods[who].food[i];
    if(goods[who].allConsumeFood >= 0){ 
        goods[who].allConsumeFood = 0;
        return true;
    }
    goods[who].allConsumeFood = 0;
    return false;
}

//  true为足够
bool isWaterEnough(int who){
    for(int i = 0; i < goods[who].water.size(); ++i)
        goods[who].allConsumeWater += goods[who].water[i];
    if(goods[who].allConsumeWater >= 0){
        goods[who].allConsumeWater = 0;
        return true;
    }
    goods[who].allConsumeWater = 0;
    return false;
}

//  初始化数据
void rebuildData(){
    for(int i = 0; i < 3; i++){
        goods[i].food.clear();
        goods[i].water.clear();
    }
    //初始物资
    for(int i = 1; i < 3; i++){
        goods[i].water.push_back(220);
        goods[i].food.push_back(220);
    }
    //直接到终点的人
    goods[0].water.push_back(170);
    goods[0].food.push_back(107);
    // 第0天不算
    for(int i = 0; i < 3; i++){
        goods[i].allConsumeFood = 0;
        goods[i].allConsumeWater = 0;
    }
    return;
}

//多人一起消耗的物资
int ManyPeopleGoods(int poeple){
    if(poeple == 1) return 1;
    return 2 * poeple;
}

//多人一起购买
int ManyPeopleBuy(int people){
    if(people == 1 ) return 1;
    return 2 * people;
}

void consume(int work, int days, int people, int who){
    //人数为基准
    if(people == 1){
        switch(weather[days])
        {
        //晴朗
        case 1:
            switch (work)
            {
            //走
            case 1:
                goods[who].water.push_back(-basisData.sunnyDayWater * 2 * ManyPeopleGoods(people));
                goods[who].food.push_back(-basisData.sunnyDayFood * 2 * ManyPeopleGoods(people));
                break;
            //停
            case 2:
                goods[who].water.push_back(-basisData.sunnyDayWater * ManyPeopleGoods(people));
                goods[who].food.push_back(-basisData.sunnyDayFood * ManyPeopleGoods(people));
                break;
            //挖矿
            case 3:
                goods[who].water.push_back(-basisData.sunnyDayWater * 3 * ManyPeopleGoods(people));
                goods[who].food.push_back(-basisData.sunnyDayFood * 3 * ManyPeopleGoods(people));
                break;
            }
            break;
        //高温
        case 2:
        switch (work)
            {
            //走
            case 1:
                goods[who].water.push_back(-basisData.heatDayWater * 2 * ManyPeopleGoods(people));
                goods[who].food.push_back(-basisData.heatDayFood * 2 * ManyPeopleGoods(people));
                break;
            //停
            case 2:
                goods[who].water.push_back(-basisData.heatDayWater * ManyPeopleGoods(people));
                goods[who].food.push_back(-basisData.heatDayFood * ManyPeopleGoods(people));
                break;
            //挖矿
            case 3:
                goods[who].water.push_back(-basisData.heatDayWater * 3 * ManyPeopleGoods(people));
                goods[who].food.push_back(-basisData.heatDayFood * 3 * ManyPeopleGoods(people));
                break;
            }
            break;
        //沙尘暴
        case 3:
        switch (work)
            {
            //走
            case 1:
                goods[who].water.push_back(-basisData.sandDayWater * 2 * ManyPeopleGoods(people));
                goods[who].food.push_back(-basisData.sandDayFood * 2 * ManyPeopleGoods(people));
                break;
            //停
            case 2:
                goods[who].water.push_back(-basisData.sandDayWater * ManyPeopleGoods(people));
                goods[who].food.push_back(-basisData.sandDayFood * ManyPeopleGoods(people));
                break;
            //挖矿
            case 3:
                goods[who].water.push_back(-basisData.sandDayWater * 3 * ManyPeopleGoods(people));
                goods[who].food.push_back(-basisData.sandDayFood * 3 * ManyPeopleGoods(people));
                break;
            }
            break;
        }
    }
}