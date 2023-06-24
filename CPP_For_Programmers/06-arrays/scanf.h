#ifndef SCANF_H
#define SCANF_H
#include <iostream>

class Scanf
{
public:
    Scanf() {}
    void average()
    {
        int result=0;
        int min = 100;
        int max = 0;

        for(int i=0; i<15; i++)
        {
            int newVar;
            std::scanf("%d",&newVar);
            result += newVar;
            if(newVar<min) min=newVar;
            else if(newVar>max) max=newVar;
        }
        result /= 15;
        std::cout<<"average:"<<result<<std::endl;
        std::cout<<"min:"<<min<<std::endl;
        std::cout<<"max:"<<max<<std::endl;
    }
};
#endif // SCANF_H
