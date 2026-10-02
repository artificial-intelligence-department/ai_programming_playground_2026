/*
Зробити паліндром, Танасієнко Іван, ШІ-13
*/
#include<iostream>
#include<string>

int main()
{
    int singleLettersAllowed;
    int letters;
    char letter;
    std::string str;
    std::string types;

    std::cin >> str;

    if(str.size() % 2 == 1)
    {
        singleLettersAllowed = 1;
    }
    else
    {
        singleLettersAllowed = 0;
    }

    for(int i = 0; i < str.size(); i++)
    {
        letter = str[i];

        if(types.find(letter) != std::string::npos)
        {
            continue;
        }
        types += letter;
        letters = 0;
        for(int j = 0; j < str.size(); j++)
        {
            if(str[j] == letter)
            {
                letters++;
            }
        }
        if(letters % 2 == 1)
        {
            singleLettersAllowed--;

            if(singleLettersAllowed < 0)
            {
                std::cout << "NO" << std::endl;
                return 0;
            }
        }
    }
    std::cout << "YES" << std::endl;

    return 0;
}