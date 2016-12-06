/*
 * 类的友元函数是定义在类外部，但有权访问类的所有私有（private）成员和保护（protected）成员。尽管友元函数的原型有在类的定义中出现过，但是友元函数并不是成员函数。+
 *
 * 友元可以是一个函数，该函数被称为友元函数；友元也可以是一个类，该类被称为友元类，在这种情况下，整个类及其所有成员都是友元。+
 *
 * 声明类 ClassTwo 的所有成员函数作为类 ClassOne 的友元，需要在类 ClassOne
 * 的定义中放置如下声明：+
 *
 * friend  class  ClassTwo;
 *
 */

#include <iostream>
using namespace std;



class Box
{
    double width;

    public:
        double length;
        friend void printWidth(Box box);
        void setWidth(double wid);
};

// 定义成员函数
void Box::setWidth(double wid)
{
    width = wid;
}

//定义友原函数, 他不属于类的任何成员
void printWidth(Box box)
{
    //因为printWidth是Box的友元函数，所以它可以访问该类的任何成员变量
    cout << "Width of box : " << box.width << endl;
}

int main()
{
    Box box;

    box.setWidth(10.0);

    printWidth(box);

    return 0;
}
