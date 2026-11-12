#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
    char text[256];
    printf("Введіть текст (до 255 символів, крапка в кінці): \n");
    if (fgets(text, 256, stdin) == NULL)
    {
        printf("Помилка зчитування тексту.\n");
        return 1;
    }
    int len = strlen(text);

    if (len > 0 && text[len - 1] != '\n')
    {
        int c = getchar();

        if (c != '\n')
        {
            printf("Помилка! Текст перевищує 255 символів.\n");
            return 1;
        }
    }
    if (len > 0 && text[len - 1] == '\n')
    {
        text[len - 1] = '\0';
        len--;
    }
    if (len == 0)
    {
        printf("Помилка! Текст не може бути порожнім. \n");
        return 1;
    }
    if (text[len - 1] != '.')
    {
        printf("Помилка! Текст має закінчуватися крапкою. \n");
        return 1;
    }

    for (int i = 0; i < len - 1; i++)
    {
        if (!((text[i] >= 'a' && text[i] <= 'z') ||
              (text[i] >= 'A' && text[i] <= 'Z') ||
              (text[i] >= '0' && text[i] <= '9') ||
              text[i] == ' '))
        {
            printf("Помилка! Недопустимий символ. \n");
            return 1;
        }
    }

    char copy[256];
    strcpy(copy, text);

    char result[256] = "";
    char *word = strtok(copy, " .");
    while (word != NULL)
    {

        bool onlyDigits = true;

        for (int i = 0; i < strlen(word); i++)
        {
            if (word[i] < '0' || word[i] > '9')
            {
                onlyDigits = false;
                break;
            }
        }
        if (!onlyDigits)
        {
            int extra = 0;

            if (strlen(result) > 0)
            {
                extra++;
            }

            if (word[0] >= '0' && word[0] <= '9')
            {
                extra++;
            }

            if (strlen(result) + strlen(word) + extra + 1 > 255)
            {
                printf("Помилка! Результат перевищує 255 символів.\n");
                return 1;
            }

            if (strlen(result) > 0)
            {
                strcat(result, " ");
            }

            if (word[0] >= '0' && word[0] <= '9')
            {
                strcat(result, "_");
            }

            strcat(result, word);
        }

        word = strtok(NULL, " .");
    }

    strcat(result, ".");

    printf("Початковий текст: %s\n", text);
    printf("Перетворений текст: %s\n", result);

    return 0;
}