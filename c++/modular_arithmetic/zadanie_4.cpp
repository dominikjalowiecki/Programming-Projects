#include <iostream>
#include <cstdlib>

using namespace std;

unsigned int getNWD(int a, int b)
{
    if(b == 0) return abs(a);

    return getNWD(b, a % b);
}

unsigned int getNWW(int a, int b)
{
    unsigned int nwd = getNWD(a, b);

    return abs(a * b) / nwd;
}

int main()
{
    cout << getNWW(6, 14) << endl; // "42"

    return 0;
}
