#include <iostream>
#include <algorithm>

using namespace std;

// Прототипи функцій
void print_result(const int arr[], int size);
int get_difference(const int a[], int n, const int b[], int m, int res[]);
int get_intersection(const int a[], int n, const int b[], int m, int res[]);
int get_union(const int a[], int n, const int b[], int m, int res[]);
int get_symmetric_difference(const int a[], int n, const int b[], int m, int res[]);

int main()
{
    int len1;
    cin >> len1;
    int arr1[100];
    
    for (int i = 0; i < len1; i++)
    {
        cin >> arr1[i];
    }

    int len2;
    cin >> len2;
    int arr2[100];
    
    for (int i = 0; i < len2; i++)
    {
        cin >> arr2[i];
    }

    // Сортуємо вхідні масиви за допомогою стандартної функції sort
    if (len1 > 0) sort(arr1, arr1 + len1);
    if (len2 > 0) sort(arr2, arr2 + len2);

    int result[210];
    int res_size = 0;

    // Визначаємо різницю першої та другої множини
    res_size = get_difference(arr1, len1, arr2, len2, result);
    print_result(result, res_size);

    // Визначаємо різницю другої та першої множини
    res_size = get_difference(arr2, len2, arr1, len1, result);
    print_result(result, res_size);

    // Визначаємо перетин множин
    res_size = get_intersection(arr1, len1, arr2, len2, result);
    print_result(result, res_size);

    // Визначаємо об'єднання множин
    res_size = get_union(arr1, len1, arr2, len2, result);
    print_result(result, res_size);

    // Визначаємо симетричну різницю множин
    res_size = get_symmetric_difference(arr1, len1, arr2, len2, result);
    print_result(result, res_size);

    return 0;
}

// Функція виводить кількість елементів та елементи масиву через пробіл
void print_result(const int arr[], int size)
{
    cout << size << "\n";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << (i + 1 == size ? "" : " ");
    }
    cout << "\n\n";
}

// Обчислення різниці множин A та B
int get_difference(const int a[], int n, const int b[], int m, int res[])
{
    int i = 0, j = 0, k = 0;
    while (i < n && j < m)
    {
        if (a[i] < b[j])
        {
            res[k++] = a[i++];
        }
        else if (b[j] < a[i])
        {
            j++;
        }
        else
        {
            i++;
            j++;
        }
    }
    while (i < n)
    {
        res[k++] = a[i++];
    }
    return k;
}

// Обчислення перетину множин A та B
int get_intersection(const int a[], int n, const int b[], int m, int res[])
{
    int i = 0, j = 0, k = 0;
    while (i < n && j < m)
    {
        if (a[i] < b[j])
        {
            i++;
        }
        else if (b[j] < a[i])
        {
            j++;
        }
        else
        {
            res[k++] = a[i];
            i++;
            j++;
        }
    }
    return k;
}

// Обчислення об'єднання множин A та B
int get_union(const int a[], int n, const int b[], int m, int res[])
{
    int i = 0, j = 0, k = 0;
    while (i < n && j < m)
    {
        if (a[i] < b[j])
        {
            res[k++] = a[i++];
        }
        else if (b[j] < a[i])
        {
            res[k++] = b[j++];
        }
        else
        {
            res[k++] = a[i];
            i++;
            j++;
        }
    }
    while (i < n) res[k++] = a[i++];
    while (j < m) res[k++] = b[j++];
    return k;
}

// Обчислення симетричної різниці множин A та B
int get_symmetric_difference(const int a[], int n, const int b[], int m, int res[])
{
    int i = 0, j = 0, k = 0;
    while (i < n && j < m)
    {
        if (a[i] < b[j])
        {
            res[k++] = a[i++];
        }
        else if (b[j] < a[i])
        {
            res[k++] = b[j++];
        }
        else
        {
            i++;
            j++;
        }
    }
    while (i < n) res[k++] = a[i++];
    while (j < m) res[k++] = b[j++];
    return k;
}
