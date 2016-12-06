
#include <iostream>
using namespace std;

class Box
{
    public:
        static int objectCount;
        Box(double l = 2.0, double b=2.0, double h = 2.0)
        {
            cout << "Constructor called." << endl;
            length = l;
            breadth = b;
            height = h;
            objectCount++;
        }

        double Volume()
        {
            return length * breadth * height;
        }

        int compare(Box box)
        {
            return this->Volume() > box.Volume();
        }

        static int getCount()
        {
            return objectCount;
        }
    private:
        double length;
        double breadth;
        double height;

};

//需要加上 类型的定义 int
int Box::objectCount = 0;

int main()
{
    Box Box1(3.3, 1.2, 1.5);
    Box Box2(8.5, 6.0, 2.0);

    cout << "Total object : " << Box::objectCount << endl;

    cout << "getCount : " << Box::getCount() << endl;

    return 0;
}
