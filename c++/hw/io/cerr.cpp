/*
 * 预定义对象cerr 是ostream
 * 类的一个实例。cerr对象附属到标准错误输出设备，通常也是显示器。
 *
 * 但是cerr设备是非缓冲的，且每一个流插入到cerr都会立即输出。
 *
 */
#include <iostream>
using namespace std;

int main()
{
    char str[] = "Unable to read....";

    cerr << "Error Message : " << str << endl;

    return 0;
}
