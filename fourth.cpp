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

const int roadBeginToMine[8] = {1, 2, 3, 4, 9, 14, 19, 18};
const int roadMineToVillage[3] = {18, 13, 14};
const int roadVillageToMine[3] = {14, 19, 18};
const int roadVillageToEnd[4] = {14, 19, 24, 25};

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
    //雨天
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

// true为足够
bool isFoodEnough(){
    for(int i = 0; i < goods.food.size(); ++i)
        goods.allConsumeFood += goods.food[i];
    if(goods.allConsumeFood >= 0){ 
        goods.allConsumeFood = 0;
        return true;
    }
    goods.allConsumeFood = 0;
    return false;
}

//  true为足够
bool isWaterEnough(){
    for(int i = 0; i < goods.water.size(); ++i)
        goods.allConsumeWater += goods.water[i];
    if(goods.allConsumeWater >= 0){
        goods.allConsumeWater = 0;
        return true;
    }
    goods.allConsumeWater = 0;
    return false;
}

//  初始化数据
void rebuildData(){
    weather.clear();
    goods.food.clear();
    goods.water.clear();
    //初始物资
    goods.water.push_back(220);
    goods.food.push_back(220);
    // 第0天不算
    weather.push_back(0);
    goods.allConsumeFood = 0;
    goods.allConsumeWater = 0;
    return;
}

int main(){
    srand((unsigned)time(NULL));
    long long allMoney = 0;
    int g=0;
    int c = 0;
    while(c < 10000){
        c++;
        rebuildData();
        int income = 0;
        bool isDie = false;
        int days = 1;
        createNextDayWeather(days);
        //走至村庄，第一次到村庄不买东西
        for(int step = 1; step <= 5;){
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
            if(isFoodEnough() == false || isWaterEnough() == false){
                isDie = true;
                break;
            }
        }
        if(isDie == true){
            // cout << "die at 1" << endl << endl;
            continue;
        }
        if(days > 30){
            // cout << "no at 1" << endl << endl;
            continue;
        }
        //走至矿坑
        for(int step = 1; step <= 2;){
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
            if(isFoodEnough() == false || isWaterEnough() == false){
                isDie = true;
                break;
            }
        }
        if(isDie == true){
            // cout << "die at 2" << endl << endl;
            continue;
        }
        if(days > 30){
            // cout << "no at 2" << endl << endl;
            continue;
        }
        //在矿坑挖矿
        while (true)
        {
            if(stayAtmine()){
                income += basisData.basisIncome;
                atMine.push_back(days);
                consume(3,days);
                days++;
                createNextDayWeather(days);
            }
            else{
                consume(1,days);
                days++;
                createNextDayWeather(days);
                break;
            }
            if(isFoodEnough() == false || isWaterEnough() == false){
                isDie = true;
                break;
            }
        }
        if(isDie == true){
            // cout << "die at 3" << endl << endl;
            continue;
        }
        if(days > 30){
            // cout << "no at 3" << endl << endl;
            continue;
        }
        //矿坑回到村庄
        for(int step = 1; step <= 2;){
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
            if(isFoodEnough() == false || isWaterEnough() == false){
                isDie = true;
                break;
            }
        }
        if(isDie == true){
            // cout << "die at 4" << endl << endl;
            continue;
        }
        if(days > 30){
            // cout << "no at 4" << endl << endl;
            continue;
        }
        goods.water.push_back(70);
        goods.food.push_back(70);
        //从村庄走到终点
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
            if(isFoodEnough() == false || isWaterEnough() == false){
                isDie = true;
                break;
            }
        }
        if(isDie == true){
            // cout << "die at 5" << endl << endl;
            continue;
        }
        days--;
        if(days > 30){
            // cout << "no at 5" << endl << endl;
            continue;
        }
        //统计
        for(int i = 0; i < goods.water.size(); ++i)
            goods.allConsumeWater += goods.water[i];
        for(int i = 0; i < goods.food.size(); ++i)
            goods.allConsumeFood += goods.food[i];
        double returnBack = (double)goods.allConsumeWater * 2.5 + (double)goods.allConsumeFood * 5;
        double spend = (double)220 * 10.0 + (double)220 * 5.0 + (double)70 * 5.0 * 2 + (double)70 * 20.0 ;
        cout << "last money: " << returnBack + basisData.beginMoney - spend << endl << endl;
        allMoney += (long long)(returnBack + basisData.beginMoney - spend);
        ++g;
    }
    cout << "average money: " << allMoney / g <<endl;
    return 0;
}