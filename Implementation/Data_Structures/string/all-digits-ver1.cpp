#include <iostream>
using namespace std;

void checkDigits(string str)
{
    char digits[10] = {'0','1','2','3','4','5','6','7','8','9'};
    for(const char &c : str)
    {
        bool flag = false;
        for(const char& d : digits)
           if(d==c)
           {
               flag = true;
               break;
           }
        if(flag==false)
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
   str = "123f5";
   checkDigits(str);
}
