#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;

void signalHandler(int signum)
{
    cout << "Signal num is : " << signum << endl;
}

int main()
{
    signal(SIGINT, signalHandler);

    int i = 0;

    while(++i)
    {
        cout << "Going to sleep..." << endl;
        sleep(2);
        if (i == 3)
        {
            raise(SIGINT);
        }
    }

    return 0;
}
