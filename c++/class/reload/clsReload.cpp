/*
 * C++
 * 允许在同一作用域中的某个函数和运算符指定多个定义，分别称为函数重载和运算符重载。+
 *
 * 重载声明是指一个与之前已经在该作用域内声明过的函数或方法具有相同名称的声明，但是它们的参数列表和定义（实现）不相同。+
 *
 *
 */

#include <iostream>
using namespace std;

class printData
{
    public:
        void print(int i)
        {
            cout << "Printing int: " << i << endl;
        }

        void print(double f)
        {
            cout << "Printing double : " << f << endl;
        }

        void print(char *c)
        {
            cout << "Printing character : " << c << endl;
        }
};

int main()
{
    printData pd;

    pd.print(5);

    pd.print(4.01);

    pd.print("Hello C++");

    return 0;
}
