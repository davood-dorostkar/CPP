#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <queue>
#include <stack>

using namespace std;


int main()
{
    stack<int> mystask;
    mystask.push(1);
    mystask.push(3);
    mystask.push(6);
    mystask.push(9);
    cout << mystask.top()<<endl;
    cout << mystask.size()<<endl;
    mystask.pop();
    cout << mystask.top()<<endl;
    cout << mystask.size()<<endl;
    return 0;
}
