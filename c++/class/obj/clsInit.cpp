/*
 * 构造函数的名称与类的名称是完全相同的，并且不会返回任何类型，也不会返回 void。
 *
 * 析构函数的名称与类的名称是完全相同的，只是在前面加了个波浪号（~）作为前缀，它不会返回任何值，也不能带有任何参数。析构函数有助于在跳出程序（比如关闭文件、释放内存等）前释放资源。
 *
 */

#include <iostream>

using namespace std;

class Line
{
    public :
        void setLength(double len);
        double getLength(void);
        Line(void);
        Line(double);
        ~Line(void);

    private :
        double length;
};

Line::~Line()
{
    cout << "Line is destory." << endl;
}

Line::Line(double len)
{
    length = len;
    cout << "Line creating." << endl;
}

Line::Line(void)
{
    cout << "Object is being created..." << endl;
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
    Line line;
    Line line1(2.1);
    line.setLength(1.1);

    cout << "Line num is : " << line.getLength() << endl;
    cout << "Line1 num is : " << line1.getLength() << endl;

    return 0;
}
