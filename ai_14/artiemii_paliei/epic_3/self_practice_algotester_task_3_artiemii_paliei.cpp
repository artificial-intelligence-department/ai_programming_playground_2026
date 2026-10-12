// Веселі каруселі

#include <iostream>

int main()
{
    int k, c, temp;
    bool swapped;
    int n[100];

    int count = 0;

    std::cin >> k >> c;

    for (int i = 0; i < c; i++)
        std::cin >> n[i];
        
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < c-1; j++)
        {
            if (n[j] > n[j+1])
                {
                    temp = n[j];
                    n[j] = n[j+1];
                    n[j+1] = temp;
                }    
        }    
    }

    for (int i = 0; i < c; i++)
    {
        k -= n[i];
        if (k < 0)
            break;
        count++;
    }
    
    std::cout << count << std::endl;

    return 0;
}