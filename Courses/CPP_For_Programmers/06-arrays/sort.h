#ifndef SORT_H
#define SORT_H
#include <iostream>

class Sort
{
public:
    Sort() {}
    void ascending()
    {
        int inputSize = 5;
        int userInput[inputSize];
        for(int i = 0; i <inputSize; i++)
        {
            std::cin>>userInput[i];
        }

        for(int i=0; i<inputSize; i++)
        {
            std::cout<<userInput[i]<<" ";
        }
        std::cout<<std::endl;

        for(int i=0; i<inputSize; i++)
        {
            std::cout<<userInput[inputSize-i-1]<<" ";
        }
        std::cout<<std::endl;

        for(int i=0; i<inputSize; i++)
        {
            for(int j=i; j>0; j--)
            {
                if(userInput[j]<userInput[j-1])
                {
                    int temp = userInput[j-1];
                    userInput[j-1]=userInput[j];
                    userInput[j]=temp;
                }
                else break;
            }
        }

        for(int i=0; i<inputSize; i++)
        {
            std::cout<<userInput[i]<<" ";
        }
    }
};
#endif // SORT_H
