#include <iostream>

void merge(int *array, int start, int mid, int end)
{
    int left_size = mid - start + 1;
    int right_size = end - mid;

    int *left = new int[left_size];
    int *right = new int[right_size];

    for (int i = 0; i < left_size; i++)
        left[i] = array[start+i];

    for (int i = 0; i < right_size; i++)
        right[i] = array[mid+1+i];

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

int main()
{
    int N, m;

    std::cin >> N;

    int *array = new int[N];

    for (int i = 0; i < N; i++)
        std::cin >> array[i];

    mergeSort(array, 0, N-1);

    if (N < 2)
        m = 0;
    else if ((array[N - 2] - array[0]) >= (array[N - 1] - array[1]))
        m = array[N - 1] - array[1];
    else
        m = array[N - 2] - array[0];

    std::cout << m << std::endl;

    delete[] array;
    array = nullptr;
    return 0;
}