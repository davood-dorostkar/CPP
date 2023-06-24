#ifndef CHALLENGES_H
#define CHALLENGES_H

int Factorial(int n)
{
    int result = 1;
    for(int i = n; i > 0; --i)
    {
        result *= i;
    }
    return result;
}

#endif // CHALLENGES_H
