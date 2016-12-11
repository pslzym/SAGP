#include <iostream>

using namespace std;

class Test
{
    public :
        Test(int a = 0)
        {
            Test::a = a;
        }

        friend Test& operator++(Test&);
        friend const Test operator++(Test&, int);
    public:
        int a;
};

Test& operator++(Test& t) //前递增
{
    t.a++;
    return t;
}
const Test operator++(Test& t, int) // 后递增，这里int 只是起到区分作用，没有实际意思
{
    Test temp(t);
    t.a++;
    cout << "ttt aa : " << t.a << endl;
    return temp;
}

int main()
{
    Test test(5);
    ++++test;
    cout << "test.a = " << test.a << endl;
    cout << "test.a = " << (test++).a << endl;
    cout << "test.a = " << test.a << endl;
}
