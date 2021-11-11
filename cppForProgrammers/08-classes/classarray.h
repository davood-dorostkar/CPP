#ifndef CLASSARRAY_H
#define CLASSARRAY_H
#include<iostream>
#include "dog.h"
using namespace std;

void printRoster(Dog roster[], int size);

void printRoster(Dog roster[], int size)
{
    for(int i=0;i<size;i++)
    {
        roster[i].printInfo();
        cout<<"\n\n";
    }
}

#endif // CLASSARRAY_H
