#include <iostream>

using namespace std;

bool checkPrimary(unsigned int number)
{
    for(int divi = 2; divi * divi <= number; divi++)
        if(number % divi == 0)
            return false;

    return true;
}

int main()
{
    cout << boolalpha << checkPrimary(6) << endl; // "false"

    return 0;
}
