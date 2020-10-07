class Consume {
	public:
		Consume(int w1 = 0 , int f1 = 0):water(w1),food(f1) {}
		Consume consumables(int weather , bool flag);
		int water = 0, food = 0;
};

//flag = true 走 flag = false停 
Consume Consume::consumables(int weather, bool flag) {
	Consume t;
	if(flag) {
		if(weather == 1) {
			t.water = 10;
			t.food = 14;
		}
		else if(weather == 2) {
			t.water = 16;
			t.food = 12;
		}
		else {
			t.water = 10;
			t.food = 10;
		}
		return t;
	}
	else {
		if(weather == 1) {
			t.water = 5;
			t.food = 7;
		}
		else if(weather == 2) {
			t.water = 8;
			t.food = 6;
		}
		else {
			t.water = 10;
			t.food = 10;
		}
		return t;
	}
} 