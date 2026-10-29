/*
    Algotester Lab 3v3, Танасієнко Іван, ШІ-13
*/
#include<iostream>
#include<string>

int main()
{
    std::string str;
    std::cin >> str;
    int el = 0;
    for(int i = 0; i < str.size(); i++)
    {
        if(i + 1 < str.size())
        {
            if(str[i] == str[i + 1])
            {
                int sames = 0;
                for(int j = i; str[j] == str[i]; j++)
                {
                    sames++;
                }
                std::cout << str[i] << sames;
                i += sames - 1;
            }
            else
            {
                std::cout << str[i];
            }
        }
        else
        {
            std::cout << str[i];
        }
    }
    std::cout << std::endl;
    return 0;
}