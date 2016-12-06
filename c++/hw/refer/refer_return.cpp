#include <iostream>
#include <ctime>

using namespace std;

double vals[] = {10.1, 12.6, 33.1, 24.1, 50.0};

double& setValue(int i){
    return vals[i];
}

int main(){

    cout << "before : " << endl;
    for (int i = 0; i < 5; i++){
        cout << "vals[" << i << "] = ";
        cout << vals[i] << endl;
    }

    setValue(1) = 20.1;
    setValue(3) = 70.8;

    cout << "after : " << endl;
    for (int i = 0; i < 5; i++){
        cout << "vals[" << i << "] = ";
        cout << vals[i] << endl;
    }

    return 0;

}
