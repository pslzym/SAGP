/*
 * public
 * :公有成员在程序中类的外部是可访问的。您可以不使用任何成员函数来设置和获取公有变量的值;
 *
 * private :
 * 私有成员变量或函数在类的外部是不可访问的，甚至是不可查看的。只有类和友元函数可以访问私有成员.
 * 默认情况下，类的所有成员都是私有的.
 *
 * protected : 
 * 保护成员变量或函数与私有成员十分相似，但有一点不同，保护成员在派生类（即子类）中是可访问的.
 *
 */
#include <iostream>

using namespace std;

class Box
{
    protected :
        double width;
};

class smallBox:Box
{
    public :
        void setSmallBoxWidth(double wid);
        double getSmallBoxWidth(void);
};

void smallBox::setSmallBoxWidth(double wid)
{
    width = wid;
}

double smallBox::getSmallBoxWidth()
{
    return width;
}

int main()
{
    smallBox box;

    box.setSmallBoxWidth(5.0);

    cout << "get smallBox width : " << box.getSmallBoxWidth() << endl;
}
