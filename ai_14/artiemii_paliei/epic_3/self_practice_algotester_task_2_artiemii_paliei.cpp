// Хелловін

#include <iostream>

int main()
{

    int n, m, a, b;

    int min_a = 1000;
    int min_b = 1000;

    std::cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        std::cin >> a;
        if (a < min_a)
            min_a = a;
        
    }

    for (int i = 0; i < m; i++)
    {
        std::cin >> b;
        if (b < min_b)
            min_b = b;
        
    }
    
    std::cout << min_a + min_b << std::endl;

    return 0;
}
