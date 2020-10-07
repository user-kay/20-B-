#include<bits/stdc++.h>
using namespace std;

struct BasisData
{
    //质量上限
    const int weightLimit = 1200;
    //初始资金
    const int beginMoney = 10000 * 2;
    //基础收益
    const int basisIncome = 200;
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
}goods;

//模拟第二天天气    1为晴天 2为高温 3为沙暴
const int weather[11] = {0, 1, 2, 1, 1, 1, 1, 2, 2, 2, 2};
//在矿山
vector<int> atMine;

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
    goods.water.push_back(0);
    goods.food.push_back(0);
    goods.allConsumeFood = 0;
    goods.allConsumeWater = 0;
    return;
}

//高温停还是走 1为走
int goOnHeat(){
    int probability = rand() % 1000 + 1;
    if(probability < 714) return 0;
    else return 1;
}

//晴朗停还是走 1为走
int goOnSunny(){
    int probability = rand() % 1000 + 1;
    if(probability < 800) return 1;
    else return 0;
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
            goods.water.push_back(-basisData.sunnyDayWater * 2);
            goods.food.push_back(-basisData.sunnyDayFood * 2);
            break;
        //停
        case 2:
            goods.water.push_back(-basisData.sunnyDayWater);
            goods.food.push_back(-basisData.sunnyDayFood);
            break;
        //挖矿
        case 3:
            goods.water.push_back(-basisData.sunnyDayWater * 3);
            goods.food.push_back(-basisData.sunnyDayFood * 3);
            break;
        }
        break;
    case 2:
        switch (work)
        {
        //走    
        case 1:
            goods.water.push_back(-basisData.heatDayWater * 2);
            goods.food.push_back(basisData.heatDayFood * 2);
            break;
        case 2:
            goods.water.push_back(-basisData.heatDayWater);
            goods.food.push_back(-basisData.heatDayFood);
            break;
        case 3:
            goods.water.push_back(-basisData.heatDayWater * 3);
            goods.food.push_back(-basisData.heatDayFood * 3);
            break;
        }
    }
}

int main(){
    srand((unsigned)time(NULL));
    int c = 0;
    while(c < 10000){
        c++;
        CreativeAll();
        int days = 1;
        int income = 0;
        //人1走至矿山
        for(int step = 1; step <= 3;){
            int go = 0;
            switch (weather[days])
            {
            case 1:
                go = goOnSunny();
                consume(go, days);
                if(go == 1) step++;
                break;
            case 2:
                go = goOnHeat();
                consume(go, days);
                if(go == 1) step++;
                break;
            }
            days++;
        }
        if(days > 10){
            continue;
        }
        //在矿山挖矿
        while(true){
            if(stayAtmine()){
                income += basisData.basisIncome;
                atMine.push_back(days);
                consume(3, days);
                days++;
            }
            else{
                consume(1, days);
                days++;
                break;
            }
        }
        if(days > 10){
            continue;
        }
        //从矿山去终点
        for(int step = 1; step <= 2;){
            int go = 0;
            switch (weather[days])
            {
            case 1:
                go = goOnSunny();
                consume(go, days);
                if(go == 1) step++;
                break;
            case 2:
                go = goOnHeat();
                consume(go, days);
                if(go == 1) step++;
                break;
            }
            days++;
        }
        days = 1;
        //从起点直接到终点
        for(int step = 1; step <= 3;){
            int go = 0;
            switch (weather[days])
            {
            case 1:
                go = goOnSunny();
                consume(go, days);
                if(go == 1) step++;
                break;
            case 2:
                go = goOnHeat();
                consume(go, days);
                if(go == 1) step++;
                break;
            }
            days++;
        }
        days--;
        if(days > 10){
            continue;
        }
        for(int i = 1; i < goods.water.size(); i++){
            goods.allConsumeWater += goods.water[i];
        }
        for(int i = 1; i < goods.food.size(); i++){
            goods.allConsumeFood += goods.food[i];
        }
        if(-goods.allConsumeFood * 2 + -goods.allConsumeWater * 3 > 2400){
            continue;
        }
        int money = income + basisData.beginMoney + goods.allConsumeFood * 10 + goods.allConsumeWater * 5;
        cout << "money: " << money << endl << endl; 
    }
    return 0;
}