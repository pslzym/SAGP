/*
 * 一元运算符只对一个操作数进行操作
 * 一元运算符通常出现在它们所操作的对象的左边，比如 !obj、-obj 和
 * ++obj，但有时它们也可以作为后缀，比如 obj++ 或 obj--。+
 *
 */

#include <iostream>

using namespace std;

class Distance
{
    private:
        int feet;
        int inches;

    public:
        Distance()
        {
            feet = 0;
            inches = 0;
        }
        Distance(int f, int i)
        {
            feet = f;
            inches = i;
        }

        void displayDistance()
        {
            cout << "F: " << feet << " I : " << inches << endl;
        }
        Distance operator- ()
        {
            feet = -feet;
            inches = -inches;
            return Distance(feet, inches);
        }
};

int main()
{
    Distance D1(11, 10), D2(-5, 11);

    -D1;
    D1.displayDistance();

    -D2;
    D2.displayDistance();

    return 0;
}
