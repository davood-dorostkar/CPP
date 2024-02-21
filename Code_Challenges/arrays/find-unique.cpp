#include <iostream>
#include <vector>

int findUnique(std::vector<int> &nums)
{
    int len = nums.size();
    if (len == 0)
        return 0;
    int i = 0;

    for (int j = i + 1; j < len; j++)
    {
        if (nums[j] == nums[i])
            continue;
        else
        {
            nums[i + 1] = nums[j];
            i++;
        }
    }
    return i + 1;
}

int main()
{
    // std::vector<int> example = {1, 2, 2, 2, 3, 3};
    std::vector<int> example = {1, 1, 2};
    int num = findUnique(example);
    std::cout << "# of unique ones:" << num << std::endl;
    return 0;
}