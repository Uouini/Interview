#include"aoi.h"

const int UNIT_AOI = 3000;
const int UNIT_SIZE = 1024;

Space::Space(int w, int h, int aoi):width(w), height(h), unit_size(aoi) {
    width_units = width / unit_size + 1;
    height_units = height / unit_size + 1;
    unit_cnt = width_units * height_units;

    units = vector<unit_t>(unit_cnt);
    for(int i = 0; i < unit_cnt; i++) {
        unit_t *unit = &units[i];
        unit->uid = i;
        unit->cnt = 0;
    }
}

Space::~Space() {

}

void Space::Enter(int id, int x, int y) {
    int uid = GetUnitId(x, y);
    unit_t *unit = &units[uid];
    unit->setid.insert(id);
    unit->cnt++;
}

void Space::Move(int id, int uid, int x, int y) {
    int old_uid = uid;
    int new_uid = GetUnitId(x, y);
    if (old_uid == new_uid )
        return;

    unit_t *old_unit = &units[old_uid];
    old_unit->setid.erase(id);
    old_unit->cnt--;

    unit_t *new_unit = &units[new_uid];
    new_unit->setid.insert(id);
    new_unit->cnt++;
}

void Space::Leave(int id, int x, int y) {
    int uid = GetUnitId(x, y);
    unit_t *unit = &units[uid];
    unit->setid.erase(id);
    unit->cnt++;
}

void Space::GetAoiEntitys(int x, int y, vector<int> &aoiEntitys) {
    int uid = GetUnitId(x, y);
    vector<int> offset(9);
    offset[0] = 0;
    offset[1] = -1;
    offset[2] = 1;
    offset[3] = -width_units;
    offset[4] = width_units;
    offset[5] = -width_units - 1;
    offset[6] = -width_units + 1;
    offset[7] = width_units - 1;
    offset[8] = width_units + 1;

    for(int i = 0; i < 9; i++) {
        int index = uid + offset[i];
        if(index < 0 || index >= unit_cnt)
            continue;

        unit_t *unit = &units[index];
        for(set<int>::iterator iter = unit->setid.begin(); iter != unit->setid.end(); iter++) {
            aoiEntitys.push_back(*iter);
        }
    }
}

int Space::GetUnitId(int x, int y) {
    int width_n = x / unit_size + 1;
    int height_n = y / unit_size + 1;
    int uid = (height_n -1) * width_units + width_n - 1;
    return uid;
}