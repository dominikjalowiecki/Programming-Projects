#include <iostream>
#include <cstdlib>

using namespace std;

unsigned int getNWD(int a, int b)
{
    if(b == 0) return abs(a);

    return getNWD(b, a % b);
}

int main()
{
    cout << getNWD(6, 14) << endl; // "2"

    return 0;
}
