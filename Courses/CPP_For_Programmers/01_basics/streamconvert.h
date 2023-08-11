#ifndef STREAMCONVERT_H
#define STREAMCONVERT_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class StreamConvert
{
public:
    StreamConvert() {}
    void stream2Float()
    {
        std::string length, width;
        float lengthF, widthF;
        std::cout << "enter the length: ";
        std::getline(std::cin, length);
//        std::cin >> length; // THE SAME
        std::cout << "enter the width: ";
        std::getline(std::cin, width);
//        std::cin >> width; // THE SAME
        std::stringstream(length) >> lengthF;
        std::stringstream(width) >> widthF;

        std::cout << lengthF * widthF << std::endl;
    }
};

#endif // STREAMCONVERT_H
