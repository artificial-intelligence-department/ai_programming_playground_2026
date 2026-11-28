#include <iostream>
using namespace std;

void mergeSort(int *a, int *temp, int left, int right)
{
    if (left >= right) return;

    int mid = left + (right - left)/2;
    mergeSort(a, temp, left, mid);
    mergeSort(a, temp, mid+1, right);

    int i = left;
    int j = mid+1;
    int k = left;

    while (i <= mid && j <= right){
        if (a[i] <= a[j]){
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }

    while (i <= mid){
        temp[k++] = a[i++];
    }
    while (j <= right){
        temp[k++] = a[j++];
    }
    for (int i = left; i <= right; i++){
        a[i] = temp[i];
    }
}

void unique(int *&a, int &len, int *temp)
{
    for (int i = 0; i < len; i++){
        temp[i] = 0;
    }
    
    int k = 0;
    int newlen = len+1;
    for (int i = 0; i < len; i++){
        if (a[i-k] == a[i]){
            temp[i-k] = a[i-k];
            k++;
            newlen--;
        } else {
            temp[i] = a[i];
            k = 1;
        }
    }
    
    int *unique_a = new int[newlen]; 
    delete[] a;
    a = unique_a;
    k = 0;
    for (int i = 0; i < len; i++){
        if (temp[i] == 0){
            k++;
        } else {
            a[i-k] = temp[i];
        }
    }

    len = newlen;
}

void rotate(int *a, int rnum, int len,  int *temp)
{
    if (rnum > len){
        rnum %= len;
    } else if (rnum == len){
        return;
    }

    for (int i = 0; i < len; i++){
        temp[i] = 0;
    }
    
    int k = 0;
    for (int i = 0; i < len; i++){
        if (rnum+i < len){
            temp[i] = a[i+rnum];
            k++;
        } else {
            temp[i] = a[i-k];
        }
    }

    for (int i = 0; i < len; i++){
        a[i] = temp[i];
    }
}

int main()
{
    int N;
    cin >> N;
    int rnum;
    cin >> rnum;

    int *a = new int[N];
    for (int i = 0; i < N; i++){
        cin >> a[i];
    }
    int *temp = new int[N];

    int left = 0;
    int right = N-1;

    mergeSort(a, temp, left, right);
    unique(a, N, temp);
    rotate(a, rnum, N, temp);
    delete[] temp;
    cout << N << endl;
    for (int i = 0; i < N; i++){
        cout << a[i] << " ";
    }
    cout << endl;
    delete[] a;
}