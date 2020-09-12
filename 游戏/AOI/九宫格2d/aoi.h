#include<iostream>
using namespace std;
#include<vector>
#include<set>
#include<unordered_map>

typedef struct {
    int x;
    int y;
    int id;
} entity_t;

/*
 *
*/
typedef struct {
    int uid;
    int cnt;
    set<int> setid;
} unit_t;

class Space {
private:
    int width;
    int height;
    int width_units;
    int height_units;
    int unit_size;
    int unit_cnt;
    vector<unit_t> units;
    unordered_map<int, int> hashuid;
public:
    Space(int width, int height, int unit_size);
    ~Space();

    void Enter(int id, int x, int y);
    void Move(int id, int uid, int x, int y);
    void Leave(int id, int x, int y);
    void GetAoiEntitys(int x, int y, vector<int> &aoiEntitys);

    int GetUnitId(int x, int y);
};