/*
 * cout 是ostream类的一个实例。cout 对象“连接”到标准设备，通常是显示屏。
 * cout与流插入运算符<<结合使用
 */

#include <iostream>

using namespace std;

int main()
{
    char str[] = "Hello C++.";
    cout << "Value of str is : " << str << endl;

    return 0;
}
