#include<iostream>
using namespace std;
#include<vector>

struct ListUnit {
    int x;
    int y;
    int z;
    int id;

    ListUnit *prevx, *nextx;
    ListUnit *prevy, *nexty;
    ListUnit *prevz, *nextz;
    ListUnit(int eid, int posx, int posy, int posz) : id(eid), x(posx), y(posy), z(posz),
        prevx(NULL), nextx(NULL), prey(NULL), nexty(NULL), prevz(NULL), nextz(NULL) {}
};

class Space {
private:
    int length;
    int width;
    int height;
    int aoi;

    ListUnit *head, *tail;

public:
    Space(int length, int width, int height);
    ~Space();

    void Enter(int id, int x, int y, int z);
    void Move(int id, int x, int y, int z);
    void Leave(int id, int x, int y, int z);
    void GetAoiEntitys(int x, int y, int z, vector<int> &aoiEntitys);
};

