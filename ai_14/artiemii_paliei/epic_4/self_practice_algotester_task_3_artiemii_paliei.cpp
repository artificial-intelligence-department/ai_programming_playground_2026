/*
Непарний масив
Зеник і Марічка мають масив з 𝑛 цілих чисел 𝑎𝑖. 
Вони хочуть перевпорядкувати елементи масиву так, щоб сума будь-яких двох послідовних елементів була непарною.
Будь ласка, допоможіть їм зробити це або скажіть, що це неможливо.
*/

#include <iostream>

int main()
{
    int n, even = 0, odd = 0, dif;

    std::cin >> n;

    int *array = new int[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> array[i];
        if (array[i] % 2 == 0)
            even++;
        else
            odd++;
    }

    even > odd ? dif = even - odd : dif = odd - even;

    if (dif <= 1)
    {
        int *even_nums = new int[even];
        int even_index = 0;
        int *odd_nums = new int[odd];
        int odd_index = 0;
        for (int i = 0; i < n; i++)
        {
            if (array[i] % 2 == 0)
            {
                even_nums[even_index] = array[i];
                even_index++;
            }
            else
            {
                odd_nums[odd_index] = array[i];
                odd_index++;
            }
        }
        if (even > odd)
        {
            for (int i = 0; i < even; i++)
            {
                if (i < odd)
                    std::cout << even_nums[i] << " " << odd_nums[i] << " ";
                else
                    std::cout << even_nums[i];
            }
        }
        else if (odd > even)
        {
            for (int i = 0; i < odd; i++)
            {
                if (i < even)
                    std::cout << odd_nums[i] << " " << even_nums[i] << " ";
                else
                    std::cout << odd_nums[i];
            }
        }
        else
        {
            for (int i = 0; i < odd; i++)
                std::cout << odd_nums[i] << " " << even_nums[i] << " ";
        }
        delete[] even_nums;
        delete[] odd_nums;
    }
    else
        std::cout << -1;

    delete[] array;

    return 0;
}