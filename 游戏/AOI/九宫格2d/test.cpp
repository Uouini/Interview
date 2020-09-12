
#include"aoi.cpp"
#include<random>
#include<time.h>
#include<chrono>


int main() {

    Space space(100, 100, 1);

    for(int i = 0; i < 1000000; i++) {
        space.Enter(i, random() % 100, random()%100);
    }

    vector<int> aoiEntitys;
    space.GetAoiEntitys(10, 10, aoiEntitys);
    return 0;
}