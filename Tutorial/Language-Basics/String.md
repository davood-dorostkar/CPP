## Extract parts based on character
```cpp
include<iostream>
include<sstream>
using namespace std;

int main()  {
    string A;
    cin>>A;
    stringstream s(A);
    string token;
    while(getline(s, token, ',')) {
        cout << token << '\n';
    }
    return 0;
}
```