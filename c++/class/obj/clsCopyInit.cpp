/*
 * 拷贝构造函数是一种特殊的构造函数，它在创建对象时，是使用同一类中之前创建的对象来初始化新创建的对象。拷贝构造函数通常用于：+
 *
 * 1.通过使用另一个同类型的对象来初始化新创建的对象。
 * 2.复制对象把它作为参数传递给函数.
 * 3.复制对象，并从函数返回这个对象
 *
 *
 * 如果在类中没有定义拷贝构造函数，编译器会自行定义一个。如果类带有指针变量，并有动态内存分配，则它必须有一个拷贝构造函数。拷贝构造函数的最常见形式如下：+
 */

#include <iostream>

using namespace std;

class Line
{
    public :
        void setLength(double len);
        double getLength(void);
        int getptr(void);
        Line(void);
        Line(double);
        ~Line(void);
        Line(const Line &obj);

    private :
        double length;
        int * ptr;
};

int Line::getptr(void)
{
    cout << "ptr num is :" << *ptr << endl;
    return *ptr;
}

Line::Line(const Line &obj)
{
    cout << "Copy constuctor allocating ptr." << endl;
    ptr = new int;
    *ptr = *obj.ptr;
}

Line::~Line()
{
    cout << "Line is destory." << endl;
    delete ptr;
}

Line::Line(double len)
{
    length = len;
    cout << "Line creating." << endl;
    ptr = new int;
}

Line::Line(void)
{
    cout << "Object is being created..." << endl;
    ptr = new int;
    *ptr = 1;
}

void Line::setLength(double len)
{
    length = len;
}

double Line::getLength()
{
    return length;
}

int main()
{
    Line line1;
    Line line2(line1);
    cout << "Line num is : " << line1.getptr() << endl;
    cout << "Line1 num is : " << line1.getptr() << endl;

    return 0;
}
