#include <iostream>

int main()
{
    const int MAX_SIZE = 100000;
    char S[MAX_SIZE + 1] = "";
    char S_compressed[MAX_SIZE + 1] = "";
    
    int quantity[MAX_SIZE] = {};
    int index = 0;
    int count = 1;

    std::cin >> S;

    for (int i = 0; i < MAX_SIZE + 1; i++)
    {
        if (S[i] == '\0')
            break;
        else
        {
            if (S[i] == S[i + 1])
            {
                count++;
                continue;
            }
            else
            {
                S_compressed[index] = S[i];
                quantity[index] = count;
                index++;

                count = 1;
            }
        }
    }

    S_compressed[index] = '\0';

    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (S_compressed[i] == '\0')
            break;
        if (quantity[i] == 1)
            std::cout << S_compressed[i];
        else
            std::cout << S_compressed[i] << quantity[i];
    }

    return 0;
}