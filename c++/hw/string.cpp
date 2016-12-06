/*
 * c++ 字符串的两种表现形式
 * 1. c风格字符串
 * 2. c++引入的string类类型
 *
 * 展示c++引入的类型
 *
 */

#include <iostream>
#include <string>

using namespace std;

int
main()
{
    string str1 = "Hello";
    string str2 = "World";
    string str3;
    int len;

    str3 = str1;
    cout << "str3: " << str3 << endl;

    str3 = str1 + str2;
    cout << "str1 + str2: " << str3 << endl;

    len = str3.size();
    cout << "str3.size() : " << len << endl;

    return 0;
}


