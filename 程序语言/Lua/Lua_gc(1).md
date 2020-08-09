##Lua垃圾回收





#标记扫描算法
--三色标记：白（白0，白1）、灰、黑
--白色：可回收状态。未被GC标记的白色Object为待访问状态，如新建的对象为白色Object；被GC标记的white object 为可回收状态
--灰色：待标记状态。当前对象已被GC标记，但期引用的对象还没被标记
--黑色：不可回收状态。

--白0：不回收。在GC标记阶段结束，清除阶段未开始，产生的新对象为WHITE0BIT
--白1：回收。在GC标记的白色对象




                          new object
                              |
                              |
                              |
                              |------- free object
                              |  
lua_garbage_collection ---- white ---- gray ---- black





                          stepgenfull  
                              |
                              |
                              |               
Lua_gc ---- luaC_step ---- genstep ---- youngcollection ---- markold ---- atomic ---- sweepgen ---- finishgencycle
                |                                             --markold:firstold1 --> reallyold /*GCSpropagate*/
                |                                             --markold:finobj --> finobjjrold
                |                                             --markold:tobefnz --> NULL
            singlestep   





##markold (global_State *g, GCObject *from, GCObject *to)
1.changeage:G_OLD1 --> G_OLD
2.back2gray
3.reallymarkobject


##reallymarkobject (global_State *g, GCObject *o)
**userdata, strings, and closed upvalues are visited and turned black here**
**other objects are marked gray and added to list and turned black later**
1.white --> gray
2.LUA_VSHRSTR,LUAVLNGSTR:  gray --> black
3.LUA_VUSERDATA: open upvalue:keep gray, other:gray --> black
4.link GCObject to gc list


##singlestep
**gcstate:GCSpause, GCSpropagate, GCSenteratomic, GCSswpallgc, GCSswpfinobj, GCSswptobefnz, GCSswpend, GCScallfin**

run ---- GCSpause ---- GCSpropagate ---- GCSenteratomic ---- GCSswpallgc ---- GCSswpfinobj ---- GCSswptobefnz ---- GCSswpend ---- CSScallfin
            |               |                   |                 |                |                   |               |              |
            |               |                   |                 |                |                   |               |              |
    restartcollection       |                 atomic          sweepstep        sweepstep          sweepstep        sweepstep       sweepstep
                            |                   |
                      gray != NULL              |
                            |               entersweep
                            |
                      propagatemark
                            |
                            |
                        gray2back


##restartcollection [重新开始执行垃圾回收]
**清除灰色链表：cleargraylists**
**标记白色对象：mainthread**
**标记白色对象：l_registry**
**标记白色对象：metamethods**
**标记白色对象：标记上一个循环剩下的结束对象**


##propagatemark [遍历灰色链表]
**遍历一个灰色对象，将其变为黑色**
**threads永远保持灰色**


##atomic [原子操作]
**没有灰色对象就执行原子操作**
**再次进入灰色链表执行propatemark**
**标记处理global metatables**
**重新标记upvalue**
**清除弱表中的值**
**设置清除终点object**
**标记对象：begin --> finalized**
**清除弱表中死亡的对象**
**清除弱表中的值**


##entersweep [开始清除]
**每次循环清理指定数量object，直到遇到存活或链表尾部**
**如果是non-dead object，back --> white，下次回收**

##GCSswpallgc
**change to sweep: sweep "regular" objects**

##GCSswpfinobj
**change to sweep: sweep objects with finalizers**

##GCSswptobefnz
**change to sweep: sweep objects to be finalized**







