/*
    Algotester lab 4v1, Танасієнко Іван, ШІ-13
*/
#include<iostream>
#include<algorithm>

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
    for(int i = 0; (i < len); i++)
    {
        if(arr[i] != -1)
        {
            elements++;
        }
    }
    std::cout << elements << std::endl;
    for(int i = 0; (i < len); i++)
    {
        if(arr[i] != -1)
        {
            std::cout << arr[i] << ' ';
        }
    }
    std::cout << std::endl << std::endl;
}

int main()
{

    int len1, len2;
    std::cin >> len1;
    int arr1[len1];
    for(int i = 0; i < len1; i++)
    {
        std::cin >> arr1[i];
    }
    std::cin >> len2;
    int arr2[len2];
    for(int i = 0; i < len2; i++)
    {
        std::cin >> arr2[i];
    }

    int result[210];

    makeAllNeg1(result);
    std::sort(arr1, arr1 + len1);
    std::sort(arr2, arr2 + len2);
    std::set_difference(arr1, arr1+len1, arr2, arr2 + len2, result);
    std::sort(result, result + 210);
    printArr(result);

    makeAllNeg1(result);
    std::sort(arr1, arr1 + len1);
    std::sort(arr2, arr2 + len2);
    std::set_difference(arr2, arr2 + len2, arr1, arr1+len1, result);
    std::sort(result, result + 210);
    printArr(result);

    makeAllNeg1(result);
    std::sort(arr1, arr1 + len1);
    std::sort(arr2, arr2 + len2);
    std::set_intersection(arr1, arr1+len1, arr2, arr2 + len2, result);
    std::sort(result, result + 210);
    printArr(result);

    makeAllNeg1(result);
    std::sort(arr1, arr1 + len1);
    std::sort(arr2, arr2 + len2);
    std::set_union(arr1, arr1+len1, arr2, arr2 + len2, result);
    std::sort(result, result + 210);
    printArr(result);

    makeAllNeg1(result);
    std::sort(arr1, arr1 + len1);
    std::sort(arr2, arr2 + len2);
    std::set_symmetric_difference(arr1, arr1+len1, arr2, arr2 + len2, result);
    std::sort(result, result + 210);
    printArr(result);

    return 0;
}