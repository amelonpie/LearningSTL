// Iterator.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <list>

using namespace std;

template <class T>
void printList(list<T> const& list)
{
    copy(list.begin(),
        list.end(),
        ostream_iterator<T>(cout, " "));
    cout << endl;
}

template <class T>
void printVector(vector<T> const& vector)
{
    copy(vector.begin(),
        vector.end(),
        ostream_iterator<T>(cout, " "));
    cout << endl;
}

template <class T>
void printReverseVector(vector<T> const& vector)
{
    copy(vector.rbegin(),
        vector.rend(),
        ostream_iterator<T>(cout, " "));
    cout << endl;
}

void learn_inseter() {
    cout << "Start of learn_iterator" << endl;

    list<int> lst = { 1,2,3,4 };
    list<int> lst1, lst2, lst3;

    lst.insert(++lst.begin(), 5);

    copy(lst.cbegin(), lst.cend(), back_inserter(lst1));
    printList(lst);
    printList(lst1);

    copy(lst.cbegin(), lst.cend(), front_inserter(lst2));
    printList(lst2);

    copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin()));
    printList(lst3);

    copy(lst2.cbegin(), lst2.cend(), inserter(lst3, lst3.begin()));
    printList(lst3);

    copy(lst2.cbegin(), lst2.cend(), inserter(lst3, lst3.end()));
    printList(lst3);

    cout << "End of learn_iterator" << endl;
}

void learn_advance() {
    vector<int> v{ 3, 1, 4 };
    //list<int> v{ 3, 1, 4 };

    auto vi = v.begin();
    advance(vi, 2);
    cout << *vi << ' ';

    vi = v.end();
    advance(vi, -2);
    cout << *vi << '\n';

    //vi = v.end();
    //advance(vi, 2);
    //cout << *vi << '\n';
}

void learn_distance() {
    vector<int> v{ 3, 1, 4 };
    //list<int> v{ 3, 1, 4 }; // If list, then distance(end_it, begin_ite) would be 1. Why?
    cout << "distance(first, last) = "
        << distance(v.begin(), v.end()) << '\n'
        << "distance(last, first) = "
        << distance(v.end(), v.begin()) << '\n';
}

void learn_convert_const_it_to_it() {
    vector<int> v{ 3, 1, 4 };
    printVector(v);
    auto ci = ++v.cbegin();
    cout << "Now const_iterator ci points to " << *ci << endl;
    //copy(v.cbegin(), ci, ci); // 错误，无法生成

    vector<int>::iterator i(v.begin());
    cout << "Now iterator i points to " << *i << endl;
    advance(i, distance<vector<int>::const_iterator>(i, ci));
    
    cout << "Now iterator i points to " << *i << " so we get what we expect" << endl;

    // 在指定处修改新值
    copy(v.cbegin(), ci, i); 
    printVector(v);

    // 在指定处插入新值
    copy(v.cbegin(), ci, inserter(v,i));
    printVector(v);
}

void learn_item28_insert1() {
    // 插入元素
    vector<int> v{ 3,1,4 };
    vector<int> v1, v2, v3;
    cout << "Original vector: ";
    printVector(v);
    cout << "Reverse iterator demo";
    printReverseVector(v);

    // 使ri指向3
    vector<int>::reverse_iterator ri = ++v.rbegin();
    cout << "Now reverse_iterator ri points to " << *ri << endl;
    vector<int>::iterator i_base(ri.base());
    cout << "Now reverse_iterator i_base points to " << *i_base << endl;
    vector<int>::iterator i = ++v.begin();
    cout << "Now reverse_iterator i points to " << *i << endl;

    //在第2个元素“1”之后插入1个元素
    cout << endl;
    // 通过反向迭代器会错误，因为insert只接受iterator类型
    //v, insert(ri, 2);
    v.insert(i_base, 2);
    // duplicate最后一位
     //不能再使用ri，因为v已经改变了
    //copy(v.rbegin(), ri, back_inserter(v));
    copy(v.rbegin(), ++v.rbegin(), back_inserter(v));
    printVector(v);
}

void learn_item28_insert2() {
    // 插入元素
    vector<int> v{ 1,2,3,4,5 };
    vector<int> v2{ 1,2,3,4,5 };
    cout << "Original vector: ";
    printVector(v);
    cout << "Reverse iterator demo ";
    printReverseVector(v);

    // 使ri指向3
    vector<int>::reverse_iterator ri = ++v.rbegin();
    cout << "Now reverse_iterator ri points to " << *ri << endl;
    vector<int>::iterator i_base(ri.base());
    cout << "Now reverse_iterator i_base points to " << *i_base << endl;
    vector<int>::iterator i = ++v.begin();
    cout << "Now reverse_iterator i points to " << *i << endl;

    //插入1个元素
    cout << endl;
    // 通过正向迭代器
    v2.insert(i_base, { 2 });
    printVector(v2);
}

void learn_item28_delete() {
    // 删除元素
    vector<int> v{ 3,1,4 };
    auto ri = ++v.rbegin();
    cout << "Now reverse_iterator ri points to " << *ri << endl;

    // 容器的erase函数只支持iterator，下行提示编译错误
    //v.erase(ri);
    v.erase(ri.base());
    printVector(v);
}


int main()
{
    std::cout << "Hello World!\n";
    // Item 27
    //learn_inseter();
    //learn_advance();
    //learn_distance();
    //learn_convert_const_it_to_it();

    // Item 28
    //learn_item28_insert1();
    //learn_item28_insert2();
    learn_item28_delete();

   
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
