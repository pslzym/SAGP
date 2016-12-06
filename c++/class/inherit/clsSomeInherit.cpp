/*
 * C++ 类可以从多个类继承成员，语法如下：+
 *
 * class derived-class: access baseA, access baseB....
 *
 * 其中，访问修饰符 access 是 public、protected 或 private
 * 其中的一个，用来修饰每个基类，各个基类之间用逗号分隔
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

class PaintCost
{
    public :
        int getCost(int area)
        {
            return area * 70;
        }
};

class Rectangle: public Shape, public PaintCost
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

    int area = Rect.getArea();

    cout << "Total area : " << Rect.getArea() << endl;
    cout << "Total Paint cost : " << Rect.getCost(area) << endl;

    return 0;
}
