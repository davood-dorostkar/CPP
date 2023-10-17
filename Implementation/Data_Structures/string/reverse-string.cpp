#include <iostream>
using namespace std;

string reverseRecursive(string str)
{
     if(str.length() <= 1)
         return str;
     else
         return reverseRecursive(str.substr(1)) + str[0];
}

int main()
{
    string str;
    cout << "enter a string" << endl;
//    getline(cin, str);
    str = "hello world";
    cout << reverseRecursive(str) << endl;
    return 0;
}
