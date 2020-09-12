#include<aoi.h>
#include<algorithm>

Space::Space(int l, int w, int h, int aoi) {
    head = new ListUnit(-1, -1, -1, -1);
    tail = new ListUnit(-1, -1, -1, -1);
    head->nextx = tail;
    tail->prevx = head;
}

Space::~Space() {
    ListUnit *unitx = head;
    ListUnit *rmunitx, *rmunity, *rmunitz;
    while(unitx != NULL) {
        ListUnit *unity = unitx->nexty;
        while(unity != NULL) {
            ListUnit *unitz = unity->nextz;
            while(unitz != NULL) {
                rmunitx = unitz;
                unitz = unitz->nextz;
                delete rmunitz;
            }

            rmunity = unity;
            unity = unity->nexty;
            delete rmunity;
        }

        rmunitx = unitx
        unitx = unitx->nextx;
        delete rmunitx;
    }
}

void Space::Enter(int id, int x, int y, int z) {
    ListUnit *unit = new ListUnit(id, x, y, z);

    //空链表
    if(head == tail) {
        unit->nextx = tail;
        tail->prevx = unit;
        unit->prevx = head;
        head->nextx = unit;
        return;
    }

    ListUnit *unitx = head;
    while(unitx != tail && unitx->x < x) {
        unitx = unitx->nextx;
    }

    /*
     *1.新插在x链表头部
     *2.新插在x链表尾部
     *3.新插在x链表内部
    */
    if(unitx->x != x) {
        if(unitx->prevx == head) {
            head->nextx->prevx = unit;
            unit->nextx = head->nextx;
            head->nextx = unit;
            unit->prevx = head;
        }else (unitx == tail) {
            unitx->prevx->nextx = unit;
            unit->prevx = unitx->prevx;
            unit->nextx = unitx;
            unitx->prevx = unit;
        }
        return;
    } 


    /*
     *插在y链表上
     *1.新插在y链表头部
     *2.新插在y链表尾部
     *3.新插在y链表内部
    */
    ListUnit *unity = unitx;
    while(unity->nexty != NULL && unity->y < y) {
        unity = unity->nexty;
    }

    if(unity->y != y) {
        if(unity->prevy == NULL) {
            if(unity->y > y) {
                unity->nextx->prevx = unit;
                unit->nextx = unity->nextx;
                unity->prevx->nextx = unit;
                unit->prevx = unity->prevx;

                unity->prevy = unit;
                unit->nexty = unity;
                unity->prevx = NULL;
                unity->nextx = NULL;
            }else {
                unity->nexty = unit;
                unit->prevy = untiy;
            }
            return;
        }

        if(unity->nexty == NULL) {
            if(unity->y > y) {
                unity->prevy->nexty = unit;
                unit->prevy = unity->prevy;
                unit->nexty = unity;
                unity->prevy = unit;
            }else {
                unity->nexty = unit;
                unit->prevy = unity;
            }
            return;
        }

        unity->prevy->nexty = unit;
        unit->prevy = unity->prevy;
        unity->prevy = unit;
        unit->nexty = unity;
        return;
    }


    /*
     *新插在z链表头部
     *新插在z链表尾部
     *新插在z链表内部
    */
    ListUnit *unitz = unity;
    while(unitz->nextz != NULL && unitz->z <= z) {
        unitz = unitz->nextz;
    }

    if(unitz->prevz == NULL) {
        if(unitz->z > z) {
            unitz->nexty->prevy = unit;
            unit->nexty = unitz->nexty;
            unitz->prevy->nexty = unit;
            unit->prevy = unitz->prevy;
            unitz->prevy = NULL;
            unitz->nexty = NULL;
        }else {
            unitz->nextz = unit;
            unit->prevz = unitz;
        }
        return;
    }

    if(unitz->nextz == NULL) {
        if(unitz->z > z) {
            unitz->prevz->nextz = unit;
            unit->prevz = unitz->prevz;
            unitz->prevz = unit;
            unit->nextz = unitz;
        }else {
            unitz->nextz = unit;
            unit->prevz = unitz;
        }
        return;
    }

    unitz->prevz->nextz = unit;
    unit->prevz = unitz->prevz;
    unitz->prevz = unit;
    unit->nextz = unitz;

}

void Space::Move(int id, int x, int y, int z) {
    Leave(id, x, y, z);
    Enter(id, x, y, z);
}

void Space::Leave(int id, int x, int y, int z) {
    ListUnit *unitx = head;
    while(unitx != tail && unitx->x != x) {
        unitx = unitx->nextx;
    }

    ListUnit *unity = unitx;
    while(unity != NULL && unity->y != y)
        unity = unity->nexty;

    ListUnit *unitz = unity;
    while(unitz != NULL && unitz->z != z)
        unitz = unitz->nextz;

    //删除x链表节点
    if(unitz->nexty == NULL) {
        unitz->nextx->prevx = unitz->prevx;
        unitz->prevx->nextx = unitz->nextx;
        delete unitz;
        return;
    }
    if(unitz->prevy == NULL) {
        unitz->next->prevx = unitz->nexty;
        unitz->nexty->nextx = unitz->next;
        unitz->prevx->nextx = unitz->nexty;
        unitz->nexty->prevx = unitz->prevx;
        delete unitz;
        return;
    }

    //删除y链表节点
    if(unitz->nextz == NULL) {
        unitz->nexty->prevy = unitz->prevy;
        unitz->prevz->nexty = unitz->nexty;
        delete unitz;
        return;
    }
    if(unitz->prevy == NULL) {
        unitz->nexty->prevy = unitz->nextz;
        unitz->nextz->nexty = unitz->nexty;
        unitz->prevy->nexty = unitz->nextz;
        unitz->nextz->prevy = unitz->prevy;
        delete unitz;
        return;
    }

    //删除z链表节点:尾节点
    if(unitz->nextz == NULL) {
        unitz->prevz->nextz = NULL;
        delete unitz;
    }else {
        unitz->nextz->prevz = unitz->prevz;
        unitz->prevz->nextz = unitz->nextz;
    }
}

void GetAoiEntitys(int x, int y, int z, vector<int> &aoiEntitys) {
    ListUnit *unitx = head->next;
    while(unitx != NULL) {
        if(unitx.x - x > aoi)
            break;

        if(unitx.x - x >= -aoi) {
            ListUnit *unity = unitx->nexty;
            while(unity != NULL) {
                if(unitx.y - y > aoi)
                    break;

                if(unity.y - y >= -aoi) {
                    ListUnit *unitz = unity->nextz;
                    while(unitz != NULL) {
                        if(unitz.z - z > aoi)
                            break;
                        
                        if(uitz.z - z >= -aoi)
                            aoiEntitys.push_back(unitz.id)
                        
                        unitz = unitz->nextz;
                    }
                }

                unity = unity->nexty;
            }

        }

        unitx = unitx->nextx;
    }
}