// 晴朗 1   高温 2  沙暴 3
class BasisData{
public:
    //天气
    const int weather[31] = {
        2, 2, 1, 3, 1,
        2, 3, 1, 2, 2,
        3, 2, 1, 2, 2,
        2, 3, 3, 2, 2,
        1, 1, 2, 1, 3,
        2, 1, 1, 2, 2
    };
    //负重上限
    const int weightUpperLimit = 1200;
    //截止日期
    const int days = 30;
    //基础收益
    const int basisPay = 1000;
    //初始资金
    const int basisMoney = 10000;
    //水重量
    const int waterHeight = 3;
    //食物重量
    const int foodHeight = 2;
    //水基准价格
    const int basisWaterPices = 5;
    //食物基准价格
    const int basisFoodPices = 10;
    //晴天水消耗量
    const int sunnyDayWater = 5;
    //晴天食物消耗量
    const int sunnyDayFood = 7;
    //高温天气水消耗量
    const int heatDayWater = 8;
    //高温天气食物消耗量
    const int heatDayFood = 6;
    //沙尘暴天气水消耗量
    const int sandDayWater = 10;
    //沙城暴天气食物消耗量
    const int sandDayFood = 10;
    //起点
    const int begin = 1;
    //终点
    const int end = 64;
    //矿山
    const int mine[2] = {30,55};
    //村庄
    const int village[2] = {39,62};
};