/*
 * 二元运算符需要两个参数，下面是二元运算符的实例。我们平常使用的加运算符（ +
 * ）、减运算符（ - ）、乘运算符（ * ）和除运算符（ /
 * ）都属于二元运算符。就像加(+)运算符。+
 *
 */

#include <iostream>

using namespace std;

class Box
{
    double length;
    double breadth;
    double height;

    public:
        double getVolume(void)
        {
            return length * breadth * height;
        }

        void setLength(double len)
        {
            length = len;
        }

        void setBreadth(double bre)
        {
            breadth = bre;
        }
        void setHeight(double hei)
        {
            height = hei;
        }

        Box operator+(const Box& b)
        {
            Box box;
            box.length = this->length + b.length;
            box.breadth = this->breadth + b.breadth;
            box.height = this->height + b.height;
            return box;
        }
};

int main()
{
    Box box1;
    Box box2;
    Box box3;

    double volume = 0.0;

    box1.setLenght(2.0);
    box1.setHeight(3.0);
    box1.setBreadth(4.0);

    box2.setLenght(3.0);
    box2.setHeight(4.0);
    box2.setBreadth(5.0);


}
