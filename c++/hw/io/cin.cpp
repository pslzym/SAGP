/*
 * cin 是istream类的一个实例。cin对象附属到标准输入设备，通常是键盘。
 * cin 是与流提取运算符>> 结合使用的。
 */

#include <iostream>

using namespace std;

int main()
{
    char name[50];

    cout << "please input you name : ";
    cin >> name;
    cout << "you name is : " << name << endl;

    return 0;
}
