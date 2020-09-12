#include<iostream>
using namespace std;
#include<vector>
#include<set>
#include<unordered_map>

typedef struct {
    int uid;
    int cnt;
    set<int> setid;
}unit_t;

class Space {
private:
    int width;
    int height;
    int length;
    int unit_cnt;
    int unit_size;
    int length_units;
    int width_units;
    int height_units;
    vector<unit_t> units;
    unordered_map<int, int> hashuid;

public:
    Space(int width, int height, int unit_size);
    ~Space();

    void Enter(int id, int x, int y, int z);
    void Move(int id, int x, int y, int z);
    void Leave(int id);
    void GetAoiEnttiys(int x, int y, int z, vector<int> &aoiEntitys);
    int GetUnitId(int x, int y, int x);
};