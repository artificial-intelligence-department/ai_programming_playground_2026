/*Алготестер задача 4 варіант 1 (без використання STL)
Максімко Павло - СШІ-13*/

#include <iostream>

using namespace std;

const int MAX = 100;

void memory_clear(int *A);
void merge(int *A, int left, int right, int mid);
void mergeSort(int *A, int left, int right);
int* set_difference(int *A, int N, int *B, int M, int &k);
int* set_intersection(int *A, int N, int *B, int M, int &k);
int* set_union(int *A, int N, int *B, int M, int &k);
int* set_symethric_difference(int *A, int N, int *B, int M, int &n);

int main()
{
    int N, M;
    cin >> N;
    int *A = new int[N];
    for(int i = 0; i < N; i++)
    {
        cin >> *(A + i);
    }
    mergeSort(A, 0, N - 1);
    cin >> M;
    int *B = new int[M];
    for(int i = 0; i < M; i++)
    {
        cin >> *(B + i);
    }
    mergeSort(B, 0, M - 1);

    int k;
    int *res_AB = set_difference(A, N, B, M, k);
    cout << k << endl;
    if(k > 0)
    {
        for(int i = 0; i < k; i++) cout << res_AB[i] << " "; 
        cout << endl;
    }
    cout << endl;
    memory_clear(res_AB);

    res_AB = set_difference(B, M, A, N, k);
    cout << k << endl;
    if(k > 0)
    {
        for(int i = 0; i < k; i++) cout << res_AB[i] << " "; 
        cout << endl;
    }
    cout << endl;
    memory_clear(res_AB);

    res_AB = set_intersection(A, N, B, M, k);
    cout << k << endl;
    if(k > 0)
    {
        for(int i = 0; i < k; i++) cout << res_AB[i] << " "; 
        cout << endl;
    }
    cout << endl;
    memory_clear(res_AB);

    res_AB = set_union(A, N, B, M, k);
    cout << k << endl;
    if(k > 0)
    {
        for(int i = 0; i < k; i++) cout << res_AB[i] << " "; 
        cout << endl;
    }
    cout << endl;
    memory_clear(res_AB);

    res_AB = set_symethric_difference(A, N, B, M, k);
    cout << k << endl;
    if(k > 0)
    {
        for(int i = 0; i < k; i++) cout << res_AB[i] << " "; 
        cout << endl;
    }
    cout << endl;
    memory_clear(res_AB);

    memory_clear(A);
    memory_clear(B);

    return 0;
}

void memory_clear(int *A)
{
    delete[] A;
    A = nullptr;
}

void merge(int *A, int left, int right, int mid)
{
    int i = left;
    int j = mid + 1;
    int k = 0;
    int t[MAX];
    
    while(i <= mid && j <= right)
    {
        if(A[i] <= A[j])
        {
            t[k] = A[i];
            i++; k++;
        }
        else
        {
            t[k] = A[j];
            j++; k++;
        }
    }

    while(i <= mid)
    {
        t[k] = A[i];
        i++; k++;
    }

    while(j <= right)
    {
        t[k] = A[j];
        j++; k++;
    }

    for(int p = 0; p < k; p++)
    {
        A[left + p] = t[p];
    }
}

void mergeSort(int *A, int left, int right)
{
    if(left >= right) return;

    int mid = left + (right - left) / 2;

    mergeSort(A, left, mid);
    mergeSort(A, mid + 1, right);
    merge(A, left, right, mid);
}

int* set_difference(int *A, int N, int *B, int M, int &k)
{
    int *R = new int[N];
    int *A_used = new int[N];
    int *B_used = new int[M];
    for(int i = 0; i < N; i++) A_used[i] = 0;
    for(int i = 0; i < M; i++) B_used[i] = 0;
    k = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(A[i] == B[j] && A_used[i] == 0 && B_used[j] == 0)
            {
                A_used[i] = 1;
                B_used[j] = 1;
                break;
            }
        }
        if(A_used[i] == 0)
        {
            R[k] = A[i];
            k++;
        }
    }
    memory_clear(A_used);
    memory_clear(B_used);
    return R;
}

int* set_intersection(int *A, int N, int *B, int M, int &k)
{
    int *R = new int[N + M];
    int *A_used = new int[N];
    int *B_used = new int[M];
    for(int i = 0; i < N; i++) A_used[i] = 0;
    for(int i = 0; i < M; i++) B_used[i] = 0;
    k = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(A[i] == B[j] && A_used[i] == 0 && B_used[j] == 0)
            {
                R[k] = A[i];
                k++;
                A_used[i] = 1;
                B_used[j] = 1;
            }
        }
    }
    memory_clear(A_used);
    memory_clear(B_used);
    return R;
}

int* set_union(int *A, int N, int *B, int M, int &k)
{
    k = 0;
    int *R = new int[N + M];
    int i = 0, j = 0; 
    while(i < N && j < M)
    {
        if(A[i] < B[j])
        {
            R[k] = A[i];
            i++;
            k++;
        }
        else if(A[i] == B[j])
        {
            R[k] = A[i];
            i++; j++;
            k++;
        }
        else
        {
            R[k] = B[j];
            j++;
            k++;
        }
    }
    
    while(i < N)
    {
        R[k] = A[i];
        i++;
        k++;
    }
    while(j < M)
    {
        R[k] = B[j];
        j++;
        k++;
    }
    return R;
}

int* set_symethric_difference(int *A, int N, int *B, int M, int &n)
{
    int k = 0, p = 0; 
    int *Union = set_union(A, N, B, M, k);
    int *Intersection = set_intersection(A, N, B, M, p);
    n = 0;
    int *Sym_diff = set_difference(Union, k, Intersection, p, n);
    memory_clear(Union);
    memory_clear(Intersection);
    return Sym_diff;
}