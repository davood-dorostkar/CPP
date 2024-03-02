#include <iostream>
#include <vector>
using namespace std;

int maxProfit(vector<int> &prices)
{
    int total = 0;
    for (int i = 0; i < prices.size() - 1; i++)
    {
        if (prices[i] < prices[i + 1])
        {
            total += prices[i + 1] - prices[i];
        }
    }
    return total;
}

int main()
{
    // vector<int> priceList1 = {1, 2, 5, 2, 4, 8, 2, 6};
    vector<int> priceList2 = {7, 1, 5, 3, 6, 4};
    vector<int> priceList3 = {1, 2, 3, 4, 5};
    vector<int> priceList4 = {7, 6, 4, 3, 1};
    // cout << maxProfit(priceList1) << endl;
    cout << maxProfit(priceList2) << " must be 7" << endl;
    cout << maxProfit(priceList3) << " must be 4" << endl;
    cout << maxProfit(priceList4) << " must be 0" << endl;
    return 0;
}