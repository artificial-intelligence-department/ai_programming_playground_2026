/*
Lab 4v3 (2)
Варіант: 3
Автор: Петро Стецюк
Група: ШІ-12
*/
#include <iostream>
using namespace std;

int tmp[1005];                          

void mergeSortRec(int arr[], int l, int r) {
    if (l >= r) return;

    int m = (l + r) / 2;
    mergeSortRec(arr, l, m);
    mergeSortRec(arr, m + 1, r);

    int i = l;
    int j = m + 1;
    int k = l;

    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) {
            tmp[k] = arr[i];
            i++;
        } else {
            tmp[k] = arr[j];
            j++;
        }
        k++;
    }
    while (i <= m) {
        tmp[k] = arr[i];
        i++;
        k++;
    }
    while (j <= r) {
        tmp[k] = arr[j];
        j++;
        k++;
    }
    for (int t = l; t <= r; t++) {
        arr[t] = tmp[t];
    }
}

void mergeSort(int arr[], int n) {
    mergeSortRec(arr, 0, n - 1);
}

int a[1000],b0[1000],c1[1000],v2[1000];
int main() 
{
    int n,i,bi=0,ci=0,vi=0,flag=0;
    cin>>n;
    for(i=0;i<n;i++)
    {
        cin>>a[i];
    }
    mergeSort(a,n);
    for(i=0;i<n;i++)
    {
            if(n==1)break;
            if(a[i]==a[i+1])a[i]=-1;
    }

    for(i=0;i<n;i++)
    {
        if(a[i]==-1)continue;
        if(a[i]%3==0){b0[bi]=a[i];bi++;}
         else if(a[i]%3==1){c1[ci]=a[i];ci++;}
            else if(a[i]%3==2){v2[vi]=a[i];vi++;}
    }
    if(bi>0)mergeSort(b0,bi);
    if(ci>0)mergeSort(c1,ci);
    if(vi>0)mergeSort(v2,vi);
    for(i=0;i<bi;i++)
    {
        a[i]=b0[i];
    }
    for(i=ci-1;i>=0;i--)
    {
        a[flag+bi]=c1[i];
        flag++;
    }
    flag=0;
    for(i=ci+bi;i<ci+bi+vi;i++)
    {
        a[i]=v2[flag];
        flag++;
    }
    cout<<bi+ci+vi<<endl;
    for(i=0;i<ci+bi+vi;i++)
    cout<<a[i]<<" ";
    
}  
