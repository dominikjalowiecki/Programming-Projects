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

unsigned int getPrimaryNumbers(unsigned int number)
{
    if(number < 2) return 0;

    bool *eratosthenes_sieve = generateEratosthenesSieve(number);

    int counter = 0;
    for(int i = 2; i < number + 1; i++)
        if(eratosthenes_sieve[i]) ++counter;

    delete eratosthenes_sieve;
    eratosthenes_sieve = NULL;

    return counter;
}

int main()
{
    cout << getPrimaryNumbers(14) << endl; // "6"

    return 0;
}
