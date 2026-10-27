/*
Помічники Санта Клауса
При підготовці подарунків на Різдво Санта Клаус вишикував усіх своїх ельфів-помічників у ряд,
щоб видати кожному персональне завдання. Але порядок ельфів його не задовольнив, і він вирішив перешикувати їх так,
щоб останній ельф помінявся місцями з першим, другий — з передостаннім і так далі.
Оскільки ельфи — хитруни, Санта Клаус просить вас перевірити, чи ельфи правильно перешикувалися?
*/

#include <iostream>

int main()
{
    int n, temp;
    std::cin >> n;

    int *start_row = new int[n];
    int *santa_row = new int[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> start_row[i];
        santa_row[i] = start_row[i];
    }

    int *elf_row = new int[n];
    for (int i = 0; i < n; i++)
        std::cin >> elf_row[i];

    int i = 0;
    int j = n - 1;
    while (i < j)
    {
        temp = santa_row[i];
        santa_row[i] = santa_row[j];
        santa_row[j] = temp;
        i++;
        j--;
    }
    for (int k = 0; k < n / 2; k++)
    {
        if (elf_row[k] != santa_row[k])
        {
            std::cout << "No" << std::endl;
            for (int i = 0; i < n; i++)
            {
                if (i != n-1)
                    std::cout << santa_row[i] << " ";
                else
                    std::cout << santa_row[i];
            }
            return 0;  
        }
    }
    std::cout << "Yes" << std::endl;

    delete[] santa_row;
    delete[] elf_row;
    delete[] start_row;
    santa_row = nullptr;
    elf_row = nullptr;
    start_row = nullptr;

    return 0;
}