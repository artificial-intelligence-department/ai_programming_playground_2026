/*
Найбільша пара
Зеник і Марічка мають набір із 𝑛 цілих чисел, причому 𝑛 — парне.
Допоки набір не пустий, вони послідовно вибирають із нього найменше і найбільше число,
після чого записують їх суму на листочку і видаляють числа з набору.
Якщо найбільших або найменших чисел декілька, вони вибирають довільне із них.
Ваше завдання — знайти найбільше число, записане на листочку після опрацювання усіх чисел із набору.
*/

#include <iostream>

int main()
{
    int n, max=-1;
    std::cin >> n;

    int *array = new int[n];

    for (int i = 0; i < n; i++)
        std::cin >> array[i];

    for (int i = 1; i < n; i++)
    {
        int j = i;
        while (j > 0 && array[j - 1] > array[j])
        {
            int temp = array[j];
            array[j] = array[j - 1];
            array[j - 1] = temp;
            j--;
        }
    }

    int i = 0;
    int j = n-1;

    while(i < j)
    {
        if (array[i] + array[j] > max)
            max = array[i] + array[j];
        array[i] = 0;
        array[j] = 0;
        i++;
        j--;
    }

    std::cout << max << std::endl;

    delete[] array;
    array = nullptr;

    return 0;
}