/*
Числа для малят, Танасієнко Іван, ШІ-13
*/
#include<iostream>
#include<string>

int main()
{
    long n;

    std::cin >> n;

    std::string num = std::to_string(n);

    std::string min = num;
    std::string max = num;


    char buff;

    for(int i = 0; i < num.length(); i ++)
    {
        for(int j = 0; j < num.length() - i; j++)
        {
            if(int(max[j]) < int(max[j + 1]))
            {
                buff = max[j + 1];
                max[j + 1] = max[j];
                max[j] = buff;
            }
        }
    }
    for(int i = 0; i < num.length(); i ++)
    {
        for(int j = num.length() - 1; j > 0; j--)
        {
            if(int(min[j]) < int(min[j - 1]))
            {
                buff = min[j - 1];
                min[j - 1] = min[j];
                min[j] = buff;
            }
        }
    }
    if(min[0] == '0')
    {
        int i = 1;
        while(min[0] == '0')
        {
            if(min[0] != min[i])
            {
                min[0] = min[i];
                min[i] = '0';
            }
            i++;
        }
    }
    std::cout << min << ' ' << max << std::endl;

    return 0;
}