#ifndef MULTIDIMENTION_H
#define MULTIDIMENTION_H
#include <iostream>

class MultiDim
{
public:
    MultiDim() {}
    void dot()
    {
        int size = 2;
        int matrix[size][size];
        int vector[size];
        int result[size];

        for(int i=0; i<size; i++)
        {
            for(int j=0; j<size; j++)
            {
              std::cin >> matrix[i][j];
            }
        }

        for(int i=0; i<size; i++)
        {
            std::cin >> vector[i];
        }

        for(int i=0; i<size; i++)
        {
            result[i]=0;
            for(int j=0; j<size; j++)
            {
              result[i]+=(matrix[i][j] * vector[j]);
            }
        }
        std::cout<<"\n\n";
        for(int i=0; i<size; i++)
        {
          std::cout<<result[i]<<std::endl;
        }

    }
};
#endif // MULTIDIMENTION_H
