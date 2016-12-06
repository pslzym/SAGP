/*
 * C++ 引用vs C++指针
 *
 * 1. 不存在空引用。引用必须连接到一块合法的内存。
 * 2. 一旦引用被初始化为一个对象，就不能被指向到另一个对象。指针可以在任何时候指向到另一个对象。
 * 3. 引用必须在创建时被初始化。指针可以在任何时间被初始化。
 *
 */
#include <iostream>

using namespace std;


int
main()
{
    int i;
    double d;

    int& ir = i;
    double& dr = d;

    i = 5;
    cout << "i is : " << i << ", ir is :" << ir << endl;

    d = 11.2;
    cout << "d is : " << d << ", dr is :" << dr << endl;

    return 0;

}
