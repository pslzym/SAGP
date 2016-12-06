/*
 * class derived-class: access-specifier base-class
 *
 * 其中，访问修饰符 access-specifier 是 public、protected 或 private
 * 其中的一个，base-class 是之前定义过的某个类的名称。如果未使用访问修饰符
 * access-specifier，则默认为 private。
 *
 * 一个派生类继承了所有的基类方法，但下列情况除外：+
 * 1.基类的构造函数、析构函数和拷贝构造函数。
 * 2.基类的重载运算符。
 * 3.基类的友元函数。
 *
 * 继承类型
 *
 * 公有继承（public）：当一个类派生自公有基类时，基类的公有成员也是派生类的公有成员，基类的保护成员也是派生类的保护成员，基类的私有成员不能直接被派生类访问，但是可以通过调用基类的公有和保护成员来访问。
 *
 * 保护继承（protected）：
 * 当一个类派生自保护基类时，基类的公有和保护成员将成为派生类的保护成员。
 *
 * 私有继承（private）：当一个类派生自私有基类时，基类的公有和保护成员将成为派生类的私有成员。
 *
 */

#include <iostream>

using namespace std;

class Shape
{
    public:
        void setWidth(int w)
        {
            width = w;
        }
        void setHeight(int h)
        {
            heigth = h;
        }

    protected:
        int width;
        int heigth;
};

class Rectangle: public Shape
{
    public:
        int getArea()
        {
            return (width * heigth);
        }
};

int main()
{
    Rectangle Rect;

    Rect.setHeight(5);
    Rect.setWidth(6);

    cout << "Total area : " << Rect.getArea() << endl;

    return 0;
}
