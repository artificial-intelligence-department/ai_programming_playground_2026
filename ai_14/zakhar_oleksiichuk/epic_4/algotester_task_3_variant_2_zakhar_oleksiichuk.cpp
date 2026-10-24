#include <iostream>

using namespace std;

void getSameElementsCount(int arr1[], int l1, int arr2[], int l2, int &count)
{
    for (int i = 0; i < l1; i++)
    {
        for (int j = 0; j < l2; j++)
        {
            if (arr1[i] == arr2[j])
                count++;
        }
    }
}

void getEniqueElementsCount(int arr1[], int l1, int arr2[], int l2, int &count)
{
    count = l1+l2;
    for (int i = 0; i < l1; i++)
    {
        for (int j = 0; j < l2; j++)
        {
            if (arr1[i] == arr2[j])
            {
                count--;
                break;
            }
        }
    }
}

int main()
{
    int N;
    cin >> N;
    int arr1[N];
    for (int i = 0; i < N; i++)
    {
        cin >> arr1[i];
    }

    int M;
    cin >> M;
    int arr2[M];
    for (int i = 0; i < M; i++)
    {
        cin >> arr2[i];
    }

    int sameElementsCount = 0;
    getSameElementsCount(arr1, N, arr2, M, sameElementsCount);

    int uniqueElementsCount = 0;
    getEniqueElementsCount(arr1, N, arr2, M, uniqueElementsCount);

    cout << sameElementsCount << endl;
    cout << uniqueElementsCount << endl;
}