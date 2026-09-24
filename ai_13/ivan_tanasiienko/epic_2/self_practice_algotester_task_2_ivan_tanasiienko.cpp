/*
Зробити паліндром, Танасієнко Іван, ШІ-13
*/
#include<iostream>
#include<string>
#include<vector>


int main()
{
    std::vector<char> types;
    int singleLettersAllowed, letters;
    char letter, singleLetter;
    std::string str;

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
        letters = 0;
        letter = str[i];
        if(std::find(types.begin(), types.end(), letter) == types.end())
        {
            types.push_back(letter);
        }
        else
        {
            continue;
        }
        for(int j = 0; j < str.size(); j++)
        {
            if(str[j] == letter)
            {
                letters++;
            }
        }
        if(letters % 2 == 1)
        {
            if(singleLettersAllowed == 1 || letter == singleLetter)
            {
                singleLetter = letter;
                singleLettersAllowed--;
            }
            else
            {
                std::cout << "NO" << std::endl;
                return 0;
            }
        }
    }
    std::cout << "YES" << std::endl;
    return 0;
}