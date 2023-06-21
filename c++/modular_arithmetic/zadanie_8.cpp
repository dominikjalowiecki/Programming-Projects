#include <iostream>

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

unsigned int getEuler(unsigned int number)
{
    if(number == 2) return 1;
    if(number < 2) return 0;

    float result = number;

    bool *eratosthenes_sieve = generateEratosthenesSieve(number);

    int divisor = 2;
    bool is_divided = false;

    while(number != 1)
    {
        // Checking if divisor is a prime number
        if(eratosthenes_sieve[divisor])
        {
            while(number % divisor == 0)
            {
                number /= divisor;
                is_divided = true;
            }

            if(is_divided)
            {
                result *= (1.0 - 1.0 / divisor);
                is_divided = false;
            }
        }

        ++divisor;
    }

    delete eratosthenes_sieve;
    eratosthenes_sieve = NULL;

    return result;
}

int main()
{
    cout << getEuler(72) << endl; // "24"

    return 0;
}
