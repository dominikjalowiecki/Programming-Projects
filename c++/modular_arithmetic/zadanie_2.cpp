#include <iostream>
#include <string>

using namespace std;

bool* generateEratosthenesSieve(unsigned int top_number)
{
    int n = top_number + 1;
    bool *eratosthenes_sieve = new bool[n];

    for(int i = 0; i < n; i++) eratosthenes_sieve[i] = true;

    for(int i = 2; i * i < n; i++)
        if(eratosthenes_sieve[i])
            for(int j = i * i; j < n; j += i)
                eratosthenes_sieve[j] = false;

    return eratosthenes_sieve;
}

string getFactors(unsigned int number)
{
    if(number < 2) return "[]";

    bool *eratosthenes_sieve = generateEratosthenesSieve(number);

    string result = "[";
    int divisor = 2;
    int counter = 0;

    while(number != 1)
    {
        // Checking if divisor is a prime number
        if(eratosthenes_sieve[divisor])
        {
            while(number % divisor == 0)
            {
                number /= divisor;
                ++counter;
            }

            string counter_str = to_string(counter);
            if(result != "[") result += ',';
            result += counter_str;

            counter = 0;
        }

        ++divisor;
    }

    result += ']';

    delete eratosthenes_sieve;
    eratosthenes_sieve = NULL;

    return result;
}

int main()
{
    cout << getFactors(72) << endl; // "[3,2]"

    return 0;
}
