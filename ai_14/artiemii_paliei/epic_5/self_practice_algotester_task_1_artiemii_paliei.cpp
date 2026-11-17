// Снігурочка

#include <iostream>
#include <string.h>
#include <stdio.h>

int main()
{
    int score = 0;
    const int BUFFER_SIZE = 8192;
    char verse[BUFFER_SIZE + 1] = "";

    while (fgets(verse, BUFFER_SIZE + 1, stdin) != NULL)
    {
        char *token = strtok(verse, " \n");
        while (token != NULL)
        {
            bool is_palindrome = true;
            for (int i = 0; i < strlen(token) / 2; i++)
            {
                int last_letter = strlen(token) - 1 - i;
                if (token[last_letter] != token[i] && (abs(token[last_letter] - token[i]) != 32))
                {
                    is_palindrome = false;
                    break;
                }
            }
            if (is_palindrome)
                score++;
            token = strtok(NULL, " \n");
        }
    }
    std::cout << score << std::endl;

    return 0;
}