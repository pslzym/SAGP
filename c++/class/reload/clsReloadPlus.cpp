/*
 * 您可以重定义或重载大部分 C++
 * 内置的运算符。这样，您就能使用自定义类型的运算符。+
 *
 * 重载的运算符是带有特殊名称的函数，函数名是由关键字 operator
 * 和其后要重载的运算符符号构成的。与其他函数一样，重载运算符有一个返回类型和一个参数列表。+
 *
 *
 * 声明加法运算符用于把两个 Box 对象相加，返回最终的 Box
 * 对象。大多数的重载运算符可被定义为普通的非成员函数或这被定义为类成员函数。
 *
 * Box  operator+(const  Box&,  const  Box&);
 *
 */

#include <iostream>
using namespace std;

class Box
{
    public:
        double getVolume(void)
        {
            return length * breadth * height;
        }
        void setLenght(double len)
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
    private:
        double length;
        double breadth;
        double height;

    public :
    Box operator+(const Box & b)
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

    volume = box1.getVolume();
    cout << "Volume of box1 : " << volume << endl;

    volume = box2.getVolume();
    cout << "Volume of box2 : " << volume << endl;

    box3 = box1 + box2;

    volume = box3.getVolume();
    cout << "Volume of box3 : " << volume << endl;

    return 0;
}
