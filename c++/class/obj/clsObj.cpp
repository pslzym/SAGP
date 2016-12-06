/*
 * 关键字public 确定了类成员的访问属性。
 * 还可以定义为：private protected
 *
 */

#include <iostream>

using namespace std;

class Box
{
    public:
        double length;
        double breadth;
        double height;
        double getLen(void);
        double size()
        {
            return length * breadth * height;
        }
};

double Box::getLen(void)
{
    return length;
}

int main()
{
    Box box1, box2;

    box1.height = 5.0;
    box1.length = 3.0;
    box1.breadth = 4.0;

    box2.height = 5.0;
    box2.length = 4.0;
    box2.breadth = 4.0;

    cout << box1.size() << endl;
    cout << box2.size() << endl;

    cout << "box1 len: " << box1.getLen() << endl;
    cout << "box2 len: " << box2.getLen() << endl;

    return 0;
}
