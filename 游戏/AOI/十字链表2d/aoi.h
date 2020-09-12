#include<iostream>
using namespace std;
#include<vector>

struct ListUnit {
    int x;
    int y;
    int id;

    ListUnit *prevx, *nextx;
    ListUnit *prevy, *nexty;
    ListUnit(int eid, int posx, int posy) : id(eid), x(posx), y(posy), prevx(NULL), nextx(NULL), prevy(NULL), nexty(NULL) {}
};

class Space {
private:
    int width;
    int height;
    int aoi;

    ListUnit *head, *tail;

public:
    Space(int width, int height, int aoi);
    ~Space();

    void Enter(int id, int x, int y);
    void Move(int id, int x, int y);
    void Leave(int id, int x, int y);
    void GetAoiEntitys(int x, int y, vector<int> &aoiEntitys); 

};