#include <iostream>

using namespace std;

class Box
{
    public :
        Box()
        {
            cout << "create Box ins." << endl;
        }

        ~Box()
        {
            cout << "delete Box ins." << endl;
        }
};

int main()
{
    double * pvalue = NULL;
    pvalue = new double;

    *pvalue = 29494.99;
    cout << "Value of pvalue : " << *pvalue << endl;

    delete pvalue;// 释放内存

    //数组的动态内存分配和释放
    char *parr = NULL;
    parr = new char[20];

    delete [] parr;

    double** parr2 = NULL;
    parr2 = new double * [4];

    delete [] parr2; // 与一维数据释放内存的方式一样

    Box * myBoxArray = new Box[4];
    delete [] myBoxArray;

    return 0;
}
