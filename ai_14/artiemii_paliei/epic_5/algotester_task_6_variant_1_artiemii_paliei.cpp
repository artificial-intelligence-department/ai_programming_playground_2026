#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    int N, K, counter = 0;
    const int ALPHABET_QUANTITY = 26;

    std::cin >> N >> K;

    std::string *words = new std::string[N];
    std::string word;

    int *counts = new int[N];
    for (int i = 0; i < N; i++)
        counts[i] = 1;
    int *ptr = counts;

    bool alphabet[ALPHABET_QUANTITY] = {};

    for (int i = 0; i < N; i++)
    {
        std::cin >> word;
        for (int j = 0; j < word.length(); j++)
        {
            if (word[j] >= 'A' && word[j] <= 'Z')
                word[j] += 32;
        }
        words[i] = word;
    }

    std::sort(words, words + N);

    for (int i = 1; i < N; i++)
    {
        if (words[i] == words[i - 1])
            (*ptr)++;
        else
            ptr = counts + i;
    }

    for (int i = 0; i < N; i++)
    {
        if (counts[i] >= K)
        {
            for (int j = 0; j < words[i].length(); j++)
            {
                alphabet[words[i][j] - 'a'] = true;
            }
        }
    }

    for (int i = 0; i < ALPHABET_QUANTITY; i++)
        if (alphabet[i])
            counter++;

    if (counter != 0)
    {
        std::cout << counter << std::endl;
        for (int i = 25; i >= 0; i--)
            if (alphabet[i])
                std::cout << char(i + 'a') << " ";
    }
    else
        std::cout << "Empty!" << std::endl;

    delete[] counts;
    delete[] words;
    return 0;
}