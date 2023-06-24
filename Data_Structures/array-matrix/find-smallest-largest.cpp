#include <iostream>
#include <vector>
#include <unordered_map>

template <size_t n>
std::pair<int,int> findSmallestLargest(const std::array<int, n>& arr)
{
    int smallest = arr[0];
    int largest = arr[0];
    for(const int& item : arr)
    {
        if(item>largest) largest=item;
        else if(item<smallest) smallest= item;
    }
    //std::pair<int,int> result = {smallest,largest};
    return  std::make_pair(smallest,largest);
}

template <typename type>
void print(const std::pair<type,type> &pair)
{
    std::cout << "smallest: " << pair.first << std::endl;
    std::cout << "largest: " << pair.second << std::endl;
}

int main()
{
    std::array<int,7> arr = {1,2,3,5,3,2,7};
    print(findSmallestLargest(arr));
    return 0;
}
