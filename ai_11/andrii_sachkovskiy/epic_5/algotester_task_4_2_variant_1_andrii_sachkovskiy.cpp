/*
 * Задача: algotester_task_4_2_variant_1 з стл
 * Автор: Сачковський Андрій
 * Група: AI-11
*/
#include <iostream>
#include <algorithm>

using namespace std;

//функція яка виводить: кількість, потім числа
void vyvid(int a[], int k)
{
    cout << k << endl;
    for (int i = 0; i < k; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl << endl;
}

int main (){
//користувач вводить свої дані
    int N[100], M[100];
    int n, m;
    cin>>n;
    for (int i = 0 ; i < n ; i++){
        cin>>N[i];
    }

    cin>>m;
    for (int i = 0 ; i < m ; i++){
        cin>>M[i];
    }

    //функції STL працюють тільки з відсортованими масивами
    sort(N, N + n);
    sort(M, M + m);

    int R[200];     //масив для результату
    int k;          

    //різниця N-M
    k = set_difference(N, N + n, M, M + m, R) - R;
    vyvid(R, k);

    //різниця M-N
    k = set_difference(M, M + m, N, N + n, R) - R;
    vyvid(R, k);

    //перетин
    k = set_intersection(N, N + n, M, M + m, R) - R;
    vyvid(R, k);

    //обєднання
    k = set_union(N, N + n, M, M + m, R) - R;
    vyvid(R, k);

    //симетрична різниця
    k = set_symmetric_difference(N, N + n, M, M + m, R) - R;
    vyvid(R, k);

    return 0;
}