#ifndef FILEIO_H
#define FILEIO_H
#include <iostream>
#include <fstream>
#include <string>

class FileIO
{
public:
    FileIO() {
    }
    void MakeNewFileAndReadIt()
    {
        std::ofstream file("file.txt", std::ios::trunc);
        //    std::fstream file("file.txt",std::fstream::out | std::ios::trunc); // another way
        //    std::fstream file("file.txt",std::ios::app);
        if(file.is_open())
        {
            file << "here is a new line!" << std::endl;
            file.close();
        }
        else std::cout << "cannot open new file";

        std::fstream reading("file.txt");
        if(reading.is_open())
        {
            std::string line;
            while (std::getline(reading, line))
            {
                std::cout << line << std::endl;
            }
            reading.close();

        }
        else std::cout << "cannot open file to read!";
    }
};

#endif // FILEIO_H
