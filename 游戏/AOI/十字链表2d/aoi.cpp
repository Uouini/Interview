#include"aoi.h"
#include<algorithm>

Space::Space(int w, int h, int a) : width(w), height(h), aoi(a) {
    head = new ListUnit(-1, -1, -1);
    tail = new ListUnit(-1, -1, -1);
    head->nextx = tail;
    tail->prevx = head;
}

Space::~Space() {
    ListUnit *unitx = head;
    ListUnit *rmunitx, *rmunity;

    while(unitx != NULL) {
        ListUnit *unity = unitx->nexty;
        while(unity != NULL) {
            rmunity = unity;
            unity = unity->nexty;
            delete rmunity;
        }

        rmunitx = unitx;
        unitx = unitx->nextx;
        delete rmunitx;
    }
}

void Space::Enter(int id, int x, int y) {
    ListUnit *unit = new ListUnit(id, x, y);

    ListUnit *unitx = head;
    while(unitx != tail && unitx->x < x) {
        unitx = unitx->nextx;
    }

    //插入y链表上
    if(unitx->x == x) {
        ListUnit *unity = unitx;
        while(unity->nexty != NULL && unity->y < y)
            unity = unity->nexty;

        //插入尾节点
        if(unity->y < y) {
            unity->nexty = unit;
            unit->prevy = unity;
            return;
        }

        //插入内部节点
        unity->prevy->nexty = unit;
        unit->prevy = unity->prevy;
        unit->nexty = unity;
        unity->prevy = unit;
        return;
    }

    //插入x链表,新建y链表头节点
    ListUnit *heady = new ListUnit(-1, x, -1);
    unitx->prevx->nextx = heady;
    heady->prevx = unitx->prevx;
    heady->nextx = unitx;
    unitx->prevx = heady;

    heady->nexty = unit;
    unit->prevy = heady;

}

void Space::Move(int id, int x, int y) {
    Leave(id, x, y);
    Enter(id, x, y);
}

void Space::Leave(int id, int x, int y) {
    ListUnit *unitx = head->nextx;
    while(unitx != tail && unitx->x != x) {
        unitx = unitx->nextx;
    }

    ListUnit *unity = unitx->nexty;
    while(unity != NULL && unity->id != id) {
        unity = unity->nexty;
    }

    //删除尾部节点
    if(unity->nexty == NULL) {
        unity->prevy->nexty = NULL;
        delete unity;
        return;
    }

    //删除内部节点
    unity->prevy->nexty = unity->nexty;
    uinty->nexty->prevy = unity->prevy;
    delete unity;
}

void Space::GetAoiEntitys(int x, int y, vector<int> &aoiEntitys) {
    ListUnit *unitx = head->nextx;
    while(unitx != tail) {
        if(unitx->x - x < -aoi || unitx->x - x > aoi)
            break;

        ListUnit *unity = unitx->nexty;
        while(unity != NULL) {
            if(unity->y - y < -aoi || unity->y - y > aoi)
                break;

            aoiEntitys.push_back(unity->id);
            unity = unity->nexty;
        }
        unitx = unitx->nextx;
    }
}