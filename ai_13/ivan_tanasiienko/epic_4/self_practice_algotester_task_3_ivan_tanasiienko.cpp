/*
    Повторювані числа в матриці, Танасієнко Іван, ШІ-13
*/
#include<iostream>

// Поки робив цю задачу навчився реалізовувати алгоритм сортування Quick Sort
void quickSort(int arr[], int len)
{
    if(len <= 1)
    {
        return;
    }
    int pivot = arr[len - 1];
    int i = -1;
    int j = 0;
    while(j < len - 1)
    {
        if(arr[j] < pivot)
        {
            i++;
            int temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
        j++;
    }
    arr[len - 1] = arr[i + 1];
    arr[i + 1] = pivot;
    quickSort(arr, i + 1);
    quickSort(arr + i + 2, len - i - 2);
    return;
}
int main()
{
    int rows, cols;
    std::cin >> rows >> cols;
    int len = rows*cols;
    int matrix[len];
    int duplicates[len];
    int dups = 0;
    for(int i = 0; i < len; i++)
    {
        std::cin >> matrix[i];
    }
    quickSort(matrix, len);
    for(int i = 0; i < len; i++)
    {
        if(matrix[i] == matrix[i + 1])
        {
            duplicates[dups] = matrix[i];
            dups++;
        }
    }
    std::cout << dups << std::endl;
    for(int i = 0; i < dups; i++)
    {
        std::cout << duplicates[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}