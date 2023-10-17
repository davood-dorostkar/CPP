#include <iostream>
using namespace std;

void checkDigits(string str)
{
    for(const char &c : str)
    {
           if(!isdigit(c))
           {
               cout << "not a digit" << endl;
               return;
           }
    }
    cout << "all characters are digits" << endl;
}

int main()
{
   string str;
//   cin >> str;
   str = "1235";
   checkDigits(str);
}
