#include <QCoreApplication>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int givenInt;
    float givenFloat;
    double givenDouble;
    char givenChar;
    std::string givenString;

    std::cout<<"integer = \n";
    std::cin>>givenInt;
    std::cout<<"float = \n";
    std::cin>>givenFloat;
    std::cout<<"double = \n";
    std::cin>>givenDouble;

//    std::cin.ignore();
    std::cout<<"character = \n";
    std::cin>>givenChar;

    std::cout<<"string = \n";
    std::cin.ignore();
    std::getline (std::cin,givenString);


    //The value stored in the data
    std::cout<<"integer = "<<givenInt<<"\n";
    std::cout<<"float = "<<givenFloat<<"\n";
    std::cout<<"double = "<<givenDouble<<"\n";
    std::cout<<"string = "<<givenString<<"\n";
    std::cout<<"character = "<<givenChar<<"\n\n";

    //The address of the data - use pointers
    std::cout<<"address integer = "<<&givenInt<<"\n";
    std::cout<<"address float = "<<&givenFloat<<"\n";
    std::cout<<"address double = "<<&givenDouble<<"\n";
    std::cout<<"address string = "<<&givenString<<"\n";
    std::cout<< "address character = " << (void *) &givenChar<<"\n";

    return a.exec();
}
