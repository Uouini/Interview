#C++迭代器失效

##序列容器vector
<tag 
    序列容器的元素分配在连续的内存中，删除当前的iter会使后面的所以元素的iter失效，删除点后的元素向前移动一个位置，不能使用erase(iter++)的方式，erase返回下一个有效的iter。
>

code
------------------------------------------------------------
#include<iostream>
#include<vector>
int main()
{
    vector<int> test;
    for(int i = 0; i < 4; i++)
        test.push_back(i)

    vector<int>::iterator nextiter;
    vector<int>::iterator iter = test.begin()
    while(iter != test.end())
    {
        nextiter = test.erase(iter);
        iter = nextiter;
    }

    return 0;
}
------------------------------------------------------------


##关联容器map
<tag
    关联容器(map, set, multimap, multiset)删除当前iterator，仅仅当前的iter失效，可以使用erase(iter++)的方式
>

code
-------------------------------------------------------------
#include<iostream>
#include<map>
int main()
{
	map<char, int> testmap;
	map<char, int>::iterator iter, nextiter;

    testmap['a'] = 10;
    testmap['b'] = 20;
    testmap['c'] = 30;
    testmap['d'] = 40;

    iter = testmap.begin();
    while(iter != testmap.end())
    {
        testmap.erase(iter++)
    }

    return 0;
}
---------------------------------------------------------------
