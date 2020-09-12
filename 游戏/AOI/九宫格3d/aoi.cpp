#include<aoi.h>

Space::Space(int l, int w, int h, int aoi): length(l), width(w), height(h), unit_size(aoi) {
    length_units = length / unit_size + 1;
    width_units = width / unit_size + 1;
    height_units = height / unit_size + 1;
    unit_cnt = length_units * width_units * height_units;

    units = vector<unit_t>(unit_cnt);
    for(int i = 0; i < unit_cnt; i++) {
        unit_t *unit = &units[i];
        unit->uid = i;
        unit->cnt = 0;
    } 
}

Space::~Space() {

}

void Space::Enter(int id, int x, int y, int z) {
    int uid =GetUnitId(x, y, z);
    unit_t *unit = &units[uid];
    unit->setid.insert(id);
    unit->cnt++;

    hashuid[id] = uid;
}

void Space::Move(int id, int x, int y, int z) {
    int uid = hashuid[id];

    unit_t *unit = &units[uid];
    unit->setid.erase(id);
    unit->cnt--;

    int newUid = GetUnitId(x, y, z);
    unit_t *newUnit = &units[newUid];
    newUnit->setid.insert(id);
    newUnit->cnt++;

    hashuid[id] = newUid;
}

void Space::Leave(int id) {
    int uid = hashuid[id];
    unit_t *unit = &units[uid];
    unit->setid.erase(id);
    unit->cnt--;

    hashuid[id] = -1;
}

void Space::GetAoiEntitys(int x, int y, int z, vector<int> &aoiEntitys) {
    int length_n = x / unit_size + 1;
    int width_n = x / unit_size + 1;

    int zUid = height_units / unit_size - 1;
    int xyUid = (width_n - 1) * length_units + length_n - 1;

    vector<int> offset(9);
    offset[0] = 0;
    offset[1] = -1 * height_units;
    offset[2] = 1 * height_units;
    offset[3] = -length_units * height_units;
    offset[4] = length_units * height_units;
    offset[5] = (-length_units - 1) * height_units;
    offset[6] = (-length_units + 1) * height_units;
    offset[7] = (length_units - 1) * height_units;
    offset[8] = (length_units + 1) * height_units;

    for(int i = 0; i < 9; i++) {
        int index = uid + offset[i] + zUid;
        if(index < 0 || index >= unit_cnt)
            continue;

        unit_t *unit = &units[index];
        for(set<int>::iterator iter = unit->setid.begin(); iter != unit->setid.end(); iter++) {
            aoiEntitys.push_back(*iter);
        }
    }
}

int Space::GetUnitId(int x, int y, int z) {
    int length_n = x / unit_size + 1;
    int width_n = y / unit_size + 1;
    int height_n = z / unit_size + 1;

    int uid = (width_n - 1) * length_units + length_n - 1 + height_n - 1;
    return uid;
}