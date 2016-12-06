/*
 * 友元函数没有 this 指针，因为友元不是类的成员。只有成员函数才有 this 指针。+
 *
 */

#include <iostream>
using namespace std;

class Box
{
    public : 
        Box(double l = 2.0, double b=2.0, double h = 2.0)
        {
            cout << "Constructor called." << endl;
            length = l;
            breadth = b;
            height = h;
        }

        double Volume()
        {
            return length * breadth * height;
        }

        int compare(Box box)
        {
            return this->Volume() > box.Volume();
        }

    private:
        double length;
        double breadth;
        double height;
};

int main()
{
    Box Box1(3.3, 1.2, 1.5);
    Box Box2(8.5, 6.0, 2.0);

    if (Box1.compare(Box2))
    {
        cout << "Box2 is smaller than Box1" << endl;
    } else {
        cout << "Box1 is smaller than Box2" << endl;
    }

}
