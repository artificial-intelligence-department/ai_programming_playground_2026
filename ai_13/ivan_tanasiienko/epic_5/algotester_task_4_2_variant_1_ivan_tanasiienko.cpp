/*
    Algotester lab 4v1, Танасієнко Іван, ШІ-13
*/
#include <iostream>

void makeAllNeg1(int arr[], int len = 210)
{
    for(int i = 0; i < len; i++)
    {
        arr[i] = -1;
    }
    return;
}

void printArr(int arr[], int len = 210)
{
    int elements = 0;

    for(int i = 0; i < len; i++)
    {
        if(arr[i] != -1)
        {
            elements++;
        }
    }

    std::cout << elements << std::endl;

    for(int i = 0; i < len; i++)
    {
        if(arr[i] != -1)
        {
            std::cout << arr[i] << ' ';
        }
    }

    std::cout << std::endl << std::endl;
}

void sort(int arr[], int len)
{
    if(len <= 1)
    {
        return;
    }

    int pivot = arr[len - 1];
    int i = -1;

    for(int j = 0; j < len - 1; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            int temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[len - 1];
    arr[len - 1] = temp;

    sort(arr, i + 1);
    sort(arr + i + 2, len - i - 2);
}

void setDifference(int arr1[], int len1, int arr2[], int len2, int result[])
{
    int i = 0, j = 0, k = 0;

    while(i < len1 && j < len2)
    {
        if(arr1[i] < arr2[j])
        {
            result[k++] = arr1[i++];
        }
        else if(arr2[j] < arr1[i])
        {
            j++;
        }
        else
        {
            i++;
            j++;
        }
    }

    while(i < len1)
    {
        result[k++] = arr1[i++];
    }
}

void setIntersection(int arr1[], int len1, int arr2[], int len2, int result[])
{
    int i = 0, j = 0, k = 0;

    while(i < len1 && j < len2)
    {
        if(arr1[i] < arr2[j])
        {
            i++;
        }
        else if(arr2[j] < arr1[i])
        {
            j++;
        }
        else
        {
            result[k++] = arr1[i];
            i++;
            j++;
        }
    }
}

void setUnion(int arr1[], int len1, int arr2[], int len2, int result[])
{
    int i = 0, j = 0, k = 0;

    while(i < len1 && j < len2)
    {
        if(arr1[i] < arr2[j])
        {
            result[k++] = arr1[i++];
        }
        else if(arr2[j] < arr1[i])
        {
            result[k++] = arr2[j++];
        }
        else
        {
            result[k++] = arr1[i];
            i++;
            j++;
        }
    }

    while(i < len1)
    {
        result[k++] = arr1[i++];
    }

    while(j < len2)
    {
        result[k++] = arr2[j++];
    }
}

void setSymetricDifference(int arr1[], int len1, int arr2[], int len2, int result[])
{
    int i = 0, j = 0, k = 0;

    while(i < len1 && j < len2)
    {
        if(arr1[i] < arr2[j])
        {
            result[k++] = arr1[i++];
        }
        else if(arr2[j] < arr1[i])
        {
            result[k++] = arr2[j++];
        }
        else
        {
            i++;
            j++;
        }
    }

    while(i < len1)
    {
        result[k++] = arr1[i++];
    }

    while(j < len2)
    {
        result[k++] = arr2[j++];
    }
}

// It's high time I remembered some discrete mathematics

int main()
{
    int len1, len2;

    std::cin >> len1;
    int arr1[100];

    for(int i = 0; i < len1; i++)
    {
        std::cin >> arr1[i];
    }

    std::cin >> len2;
    int arr2[100];

    for(int i = 0; i < len2; i++)
    {
        std::cin >> arr2[i];
    }

    int result[210];

    sort(arr1, len1);
    sort(arr2, len2);

    makeAllNeg1(result);
    setDifference(arr1, len1, arr2, len2, result);
    printArr(result);

    makeAllNeg1(result);
    setDifference(arr2, len2, arr1, len1, result);
    printArr(result);

    makeAllNeg1(result);
    setIntersection(arr1, len1, arr2, len2, result);
    printArr(result);

    makeAllNeg1(result);
    setUnion(arr1, len1, arr2, len2, result);
    printArr(result);

    makeAllNeg1(result);
    setSymetricDifference(arr1, len1, arr2, len2, result);
    printArr(result);

    return 0;
}