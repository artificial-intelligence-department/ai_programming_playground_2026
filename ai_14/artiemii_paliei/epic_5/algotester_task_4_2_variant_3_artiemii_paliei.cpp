/*
без STL
algotester task 4_2
*/
#include <iostream>

void printArray(int *array, int n)
{
    for (int i = 0; i < n; i++)
        std::cout << array[i] << " ";
}

void merge(int *array, int start, int mid, int end)
{
    int left_size = mid - start + 1;
    int right_size = end - mid;

    int *left = new int[left_size];
    int *right = new int[right_size];

    for (int i = 0; i < left_size; i++)
        left[i] = array[start + i];

    for (int i = 0; i < right_size; i++)
        right[i] = array[mid + 1 + i];

    int i = 0, j = 0;

    while (left_size > 0 && right_size > 0)
    {
        if (left[i] > right[j])
        {
            array[start] = right[j];
            j++;
            start++;
            right_size--;
        }
        else
        {
            array[start] = left[i];
            i++;
            start++;
            left_size--;
        }
    }

    while (left_size)
    {
        array[start] = left[i];
        i++;
        start++;
        left_size--;
    }

    while (right_size)
    {
        array[start] = right[j];
        j++;
        start++;
        right_size--;
    }

    delete[] left;
    delete[] right;
    left = nullptr;
    right = nullptr;
}

void mergeSort(int *array, int start, int end)
{
    if (start < end)
    {
        int mid = start + (end - start) / 2;
        mergeSort(array, start, mid);
        mergeSort(array, mid + 1, end);
        merge(array, start, mid, end);
    }
}

int makeUnique(int *array, int n)
{
    if (n <= 1)
        return n;
    else
    {
        int unique_count = 1;
        for (int i = 1; i < n; i++)
        {
            if (array[i] != array[i-1])
            {
                array[unique_count] = array[i];
                unique_count++;
            }
        }

        return unique_count;
    }
}

int main()
{
    int N, element, zero = 0, one = 0, two = 0;
    std::cin >> N;

    int *array_zero = new int[N];
    int *array_one = new int[N];
    int *array_two = new int[N];

    for (int i = 0; i < N; i++)
    {
        std::cin >> element;
        switch (element % 3)
        {
        case 0:
            array_zero[zero] = element;
            zero++;
            break;
        case 1:
            array_one[one] = element;
            one++;
            break;
        case 2:
            array_two[two] = element;
            two++;
            break;
        default:
            break;
        }
    }

    mergeSort(array_zero, 0, zero - 1);
    mergeSort(array_one, 0, one - 1);
    mergeSort(array_two, 0, two - 1);

    zero = makeUnique(array_zero, zero);
    one = makeUnique(array_one, one);
    two = makeUnique(array_two, two);

    for (int i = 0; i < one / 2; i++)
    {
        int temp = array_one[i];
        int current = one - 1 - i;
        array_one[i] = array_one[current];
        array_one[current] = temp;
    }

    std::cout << zero + one + two << std::endl;

    printArray(array_zero, zero);
    printArray(array_one, one);
    printArray(array_two, two);

    delete[] array_zero;
    delete[] array_one;
    delete[] array_two;

    return 0;
}