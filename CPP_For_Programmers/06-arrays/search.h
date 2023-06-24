#ifndef SEARCH_H
#define SEARCH_H
#include <iostream>

class Search
{
public:
    Search() {}
    void arraySearch()
    {
        int searchArray[10] = {324,4567,6789,5421345,7,65,8965,12,342,485};
        int searchKey=0, location;
        while(true)
        {
            std::scanf("%d", &searchKey);
            if(searchKey==-1) break;
            location=-1;
            int len = sizeof(searchArray)/sizeof(int);
            for(int i=0; i<len; i++)
            {
                if(searchArray[i]==searchKey) location=i;
            }
            if(location != -1)
            {
                std::cout<<searchKey<<" is at location "<<location<<" in the array.\n";
            }
            else
            {
                std::cout<<searchKey<<" is not in the array.\n";
            }
        }
    }
};
#endif // SEARCH_H
