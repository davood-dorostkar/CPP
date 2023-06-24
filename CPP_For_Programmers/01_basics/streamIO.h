#ifndef STREAMIO_H
#define STREAMIO_H
#include <iostream>
#include <fstream>
#include <string>

class StreamIO
{
public:
    StreamIO() {}
    void lineByLineReading()
    {
        std::string name, address, phone;
        std::cout << "enter your name: " << std::endl;
        std::getline(std::cin, name);
        std::cout << "enter your address: " << std::endl;
        std::getline(std::cin, address);
        std::cout << "enter your phone: " << std::endl;
        std::getline(std::cin, phone);

        std::cout << "\t\t"<< name << std::endl;
        std::cout << "\t\t" << address << std::endl;
        std::cout << "\t\t" << phone << std::endl;
    }
};
#endif // STREAMIO_H
