#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> num;
    int element;

    while(cin >> element)
        num.push_back(element);

    sort(num.begin(), num.end());

    for (int i = 0; i < num.size(); i++){
        cout << num[i] << "\n";
    }
}
