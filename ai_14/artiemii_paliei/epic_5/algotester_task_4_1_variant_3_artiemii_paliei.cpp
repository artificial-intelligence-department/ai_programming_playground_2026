/*
з STL
algotester task 4_1
*/ 

#include <algorithm>
#include <vector>
#include <iostream>

int main()
{
    int N;
    std::cin >> N;
    std::vector<int> array(N);

    for (int i = 0; i < N; i++)
        std::cin>> array[i];

    auto last0 = std::partition(array.begin(), array.end(), [](int a) {return a%3 == 0;});
    auto last1 = std::partition(last0, array.end(), [](int a) {return a%3 == 1;});
    std::sort(array.begin(), last0);
    std::sort(last0, last1);
    std::reverse(last0, last1);
    std::sort(last1, array.end());
    auto unique_end = std::unique(array.begin(), array.end());
    array.erase(unique_end, array.end());
    
    std::cout << array.size() << std::endl;
    for (int i = 0; i < array.size(); i++)
        std::cout << array[i] << " ";

    return 0;
}