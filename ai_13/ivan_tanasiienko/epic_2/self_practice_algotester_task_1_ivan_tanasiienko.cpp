/*
Коля, Вася і Теніс, Танасієнко Іван, ШІ-13
*/
#include<iostream>
#include<string>


int main()
{
    long games;
    std::string score;

    std::cin >> games;

    std::cin >> score;
    int scoreK = 0;
    int scoreV = 0;
    int winsK = 0;
    int winsV = 0;
    bool finished;
    for(char i : score)
    {
        switch (i)
        {
            case 'K':
                scoreK++;
                break;
            case 'V':
                scoreV++;
                break;
        }
        if(scoreK >= 11 && scoreK - scoreV >= 2)
        {
            winsK++;
            scoreK = 0;
            scoreV = 0;
            finished = true;
        }
        else if(scoreV >= 11 && scoreV - scoreK >= 2)
        {
            winsV++;
            scoreK = 0;
            scoreV = 0;
            finished = true;
        }
        else
        {
            finished = false;
        }
    }
    std::cout << winsK << ':' << winsV << std::endl;
    if(!finished)
    {
        std::cout << scoreK << ':' << scoreV << std::endl;
    }
    return 0;
}