### Read a file
```cpp
include <fstream>
include <string>
include <iostream>

fstream readingFile("input.txt");
if(readingFIle.is_open())
{

    while( getline(readingFile, line))
    {
        std::cout << line << std::endl;
    }

    readingFile.close();
}

else std::cout << cannot open file << std::endl;
```

### Write to a file
```cpp
fstream writingFile("input.txt", ios::app);

if(writingFile.is_open())
{

    writingFile << "some text";
    writingFile.close();

}

else std::court << cannot open file << std::endl;
```