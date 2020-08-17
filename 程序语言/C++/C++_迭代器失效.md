#C++迭代器失效

##map
map::erase()
1. iterator erase(const_iterator position);
2. iterator erase(const key_type &k);
3. iterator erase(const_iterator first, const_iterator last);

/*C++11的erase函数返回下一个有效的迭代器，当前迭代器已失效*/

example
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
        nextiter = testmap.erase(iter);
        iter = nextiter;
    }

    return 0;
}
---------------------------------------------------------------
