#include"aoi.cpp"
#include<time.h>

int main() {
	Space space(100, 100, 4);

	for (int i = 0; i < 1000000; i++) {
		space.Enter(i, random() % 100, random() % 100);
	}

	vector<int> aoiEntitys;
	space.GetAoiEntitys(10, 10, aoiEntitys);

	vector<int>::iterator iter = aoiEntitys.begin();
	while (iter != aoiEntitys.end()) {
		cout << *iter << endl;
	}

	return 0;
}