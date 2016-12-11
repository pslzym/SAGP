/*
 * 本教程介绍如何从文件读取流和向文件写入流。这就需要用到 C++ 中另一个标准库
 * fstream，它定义了三个新的数据类型：+
 *
 * ofstream: 该数据类型表示输出文件流，用于创建文件并向文件写入信息。
 * ifstream: 该数据类型表示输入文件流，用于从文件读取信息。
 * fstream: 该数据类型通常表示文件流，且同时具有 ofstream 和 ifstream
 * 两种功能，这意味着它可以创建文件，向文件写入信息，从文件读取信息。
 *
 * 要在 C++ 中进行文件处理，必须在 C++ 源代码文件中包含头文件 <iostream> 和
 * <fstream>。+
 *
 */

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    char data[100];

    ofstream outfile;
    outfile.open("afile.dat");

    cout << "Writing to the file" << endl;
    cout << "Enter your name :" ;
    cin.getline(data, 100);

    outfile << data << endl;

    cout << "Enter your age :" ;
    cin >> data;
    cin.ignore();

    outfile << data << endl;

    outfile.close();

    ifstream infile;
    infile.open("afile.dat");

    cout << "Reading from the file" << endl;
    infile >> data;
    cout << data << endl;
    infile >> data;
    cout << data << endl;

    infile.close();

    infile.close();

    return 0;

}
