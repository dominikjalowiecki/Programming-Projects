#include <iostream>

using namespace std;

bool checkCoprimary(unsigned int a, unsigned int b)
{
    unsigned int min_number;

    if(a < b) min_number = a;
    else min_number = b;

    if(a % min_number == 0 && b % min_number == 0) return false;

    for(int divi = 2; divi * divi <= min_number; divi++)
        if(a % divi == 0 && b % divi == 0) return false;

    return true;
}

int main()
{
    cout << boolalpha << checkCoprimary(6, 14) << endl; // "false"

    return 0;
}
