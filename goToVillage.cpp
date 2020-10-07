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

vector<int> weather;
//在矿山天数
vector<int> atMine;

//第二天天气
void createNextDayWeather(int days){
    int probability = rand() % 10000 + 1;
    if(probability < 2000){
        weather.push_back(3);
    }
    else{
        //  根据权重 0.4667 0.2 0.3333 排除0.2后剩余0.8算出加权后沙暴为 0.5834
        probability = rand() % 10000 + 1;
        if(probability < 5834){
            weather.push_back(2);
            return;
        }
        else{
            weather.push_back(1);
            return;
        }
    }
}

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

//是否继续呆在矿山 true为呆
bool stayAtmine(){
    const int stayProbability = 5556;
    int probability = rand() % 10000 + 1;
    if(probability < stayProbability){
        return true;
    }
    else return false;
}

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
    //炎热
    case 2:
        switch (work)
        {
        //走    
        case 1:
            goods.water.push_back(-basisData.heatDayWater * 2);
            goods.food.push_back(-basisData.heatDayFood * 2);
            break;
        //停
        case 2:
            goods.water.push_back(-basisData.heatDayWater);
            goods.food.push_back(-basisData.heatDayFood);
            break;
        //挖矿
        case 3:
            goods.water.push_back(-basisData.heatDayWater * 3);
            goods.food.push_back(-basisData.heatDayFood * 3);
            break;
        }
        break;
    //沙尘暴
    case 3:
        switch (work)
        {
        case 1:
        //停
        case 2:
            goods.water.push_back(-basisData.sandDayWater);
            goods.food.push_back(-basisData.sandDayFood);
            break;
        //挖矿
        case 3:
            goods.water.push_back(-basisData.sandDayWater * 3);
            goods.food.push_back(-basisData.sandDayFood * 3);
            break;
        }
        break;
    }
}

//  初始化数据
void rebuildData(){
    weather.clear();
    goods.food.clear();
    goods.water.clear();
    atMine.clear();
    // 第0天不算
    weather.push_back(0);
    goods.water.push_back(0);
    goods.food.push_back(0);
    goods.allConsumeFood = 0;
    goods.allConsumeWater = 0;
    return;
}

int main(){
    srand((unsigned)time(NULL));
    int g = 0;
    long long food = 0;
    long long water = 0;
    while(g < 10){
        g++;
        int c = 0;
        int allFood = 0;
        int allWater = 0;
        while(c < 1000){
            c++;
            rebuildData();
            int days = 1;
            createNextDayWeather(days);
            for(int step = 1; step <= 3;){
                int go = 0;
                switch(weather[days]){
                    //晴天
                    case 1: 
                        go = walkOrStay(1);
                        consume(go, days);
                        if(go == 1) step++;
                        break;
                    //炎热
                    case 2:
                        go = walkOrStay(2);
                        consume(go, days);
                        if(go == 1) step++;
                        break;
                    //沙尘暴
                    case 3:
                        consume(2, days);
                        break;
                }
                days++;
                createNextDayWeather(days);
            }


            //总用水量
            for(int i = 1; i < goods.water.size(); ++i){
                // cout << goods.water[i] << " ";
                goods.allConsumeWater += goods.water[i];
            }
            // cout<<endl;
            //总食物
            for(int i = 1; i < goods.food.size(); ++i){
                // cout << goods.food[i] << " ";
                goods.allConsumeFood += goods.food[i];
            }
            // cout<<endl;
            allFood += goods.allConsumeFood;
            allWater += goods.allConsumeWater;
            // cout << "all food: " << goods.allConsumeFood <<endl;
            // cout << "all water: " << goods.allConsumeWater <<endl;
            // cout << " at mine: ";
            // for(int i = 0; i < atMine.size(); ++i){
            //     cout << atMine[i] << " ";
            // }
            // cout<<endl;
            // cout<<endl;
        }
        cout << "all food: " << allFood / 1000 <<endl;
        cout << "all water: " << allWater / 1000 <<endl;
        cout << endl;
        food += allFood / 1000;
        water += allWater / 1000;
    }
    cout << "average food: " << food / 10 <<endl;
    cout << "average water: " << water / 10 <<endl;
    return 0;
}