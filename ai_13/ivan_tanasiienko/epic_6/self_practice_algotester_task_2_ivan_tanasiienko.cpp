/*
    Трійки чисел, Танасієнко Іван, ШІ-13
*/
#include<iostream>
//Still no stls? =(

#define int long long

void quickSort(int arr[], int len)
{
    if(len <= 1) return;
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

signed main()
{
    int n;
    std::cin >> n;
    int teams[n];
    for(int i = 0; i < n; i++) std::cin >> teams[i];

    quickSort(teams, n);
    int sums = 0;
    for (int i = 2; i < n; i++)
    {
        int left = 0;
        int right = i - 1;

        while (left < right)
        {
            int sum = teams[left] + teams[right];
            
            if (sum < teams[i]) left++;
            else if (sum > teams[i]) right--;
            else
            {
                if (teams[left] == teams[right])
                {
                    int count = right - left + 1;
                    sums += count * (count - 1) / 2;
                    break;
                }
                int leftValue = teams[left];
                int rightValue = teams[right];
                int countLeft = 0;
                int countRight = 0;
                while (left < right &&teams[left] == leftValue)
                {
                    countLeft++;
                    left++;
                }
                while (left <= right && teams[right] == rightValue)
                {
                    countRight++;
                    right--;
                }
                sums += countLeft * countRight;
            }
        }
    }
    std::cout << sums << '\n';
    return 0;
}