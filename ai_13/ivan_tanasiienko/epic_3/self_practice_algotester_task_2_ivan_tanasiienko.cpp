/*
Складний екзамен, Танасієнко Іван, ШІ-13
*/
#include<iostream>
#include<string>

int main()
{
    int n;

    std::cin >> n;

    std::string num = std::to_string(n);

    for(int i = 0; i < num.length() - 1; i++)
    {
        if(num[i] == '4' && num[i + 1] == '7')
        {
            std::cout << "YES" << std::endl;
            return 0;
        }
    }

    std::cout << "NO" << std::endl;

    return 0;
}