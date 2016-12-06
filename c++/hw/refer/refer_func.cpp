#include <iostream>

using namespace std;

void swap(int& a, int& b);

int
main()
{
    int a = 100;
    int b = 200;

    cout << "swap before a : " << a << endl;
    cout << "swap before b : " << b << endl;

    swap(a, b);

    cout << "swap after a : " << a << endl;
    cout << "swap after b : " << b << endl;
}

void swap(int& a, int& b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}
