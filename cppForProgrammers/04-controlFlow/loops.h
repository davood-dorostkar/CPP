#ifndef LOOPS_H
#define LOOPS_H
#include <iostream>
#include <sstream>
#include <string>

class Loops
{
public:
    Loops() {}
    void switchCalc()
    {
        float in1, in2;
        std::cout<<"Enter two numbers:\n";
        std::cin>>in1;
        std::cin>>in2;
        std::cout<<"Enter the operation '+','-','*','/': ";
        char operation;
        std::cin >> operation;

        switch (operation)
        {
            case '+': std::cout << in1+in2 << std::endl; break;
            case '-': std::cout << in1-in2 << std::endl; break;
            case '*': std::cout << in1*in2 << std::endl; break;
            case '/': std::cout << in1/in2 << std::endl; break;
            default:std::cout << "not a valid operation"<< std::endl;
        }

    }
    void forCalc()
    {
        std::cout << "Enter 5 numbers: " <<std::endl;
        float result = 0;
        for(int i=0; i<5; i++)
        {
            float num;
            std::string numS;
            std::cin >> numS;
            std::stringstream(numS) >> num;
            result += num;
        }
        std::cout << "sum: " << result << std::endl;
        std::cout << "avg: " << result/5 << std::endl;
    }
    void whileGuess()
    {
        int target = 55;
        int guess = -1;
        std::cout<<"Guess a number between 0 and 100: ";

        while(guess!=target)
        {
            std::cin>>guess;
            std::cout<<guess<<std::endl;

            if(guess==-1)
            {
                std::cout<<"bye!";
                break;
            }

            std::string hint;
            if(guess<target) hint="too low\n";
            else if(guess>target) hint="too high\n";
            else hint="correct!\n";
            std::cout<<hint;


        }
    }
};
#endif // LOOPS_H
