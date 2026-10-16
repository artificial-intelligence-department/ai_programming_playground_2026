/*
Зроби щасливим, Танасієнко Іван, ШІ-13
*/
#include<iostream>
#include<string>

int main()
{
    int a;
    int b = -1;
    std::string sum;
    int nums[] = {4, 7};

    std::cin >> a;

    bool running = true;

    if(a == 0)
    {
        b = 4;
        running = false;
    }
    while(running)
    {
        b++;
        sum = std::to_string(a + b);

        for(int i = 0; i < sum.length(); i++)
        {
            if(sum[i] != '4' && sum[i] != '7')
            {
                running = true;
                break;
            }
            else
            {
                running = false;
            }
        }

    }

    std::cout << b << std::endl;

    return 0;
}