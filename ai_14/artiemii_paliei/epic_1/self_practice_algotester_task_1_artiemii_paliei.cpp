#include <iostream>
int main()
{
    int a, b;
    if (a<0 || b<0 || a>100 || b>100)
        return 1;
    std::cin >> a >> b;
    std::cout << a + b << std::endl;
    return 0;
}