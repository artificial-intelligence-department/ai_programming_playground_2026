/*
Мельник Олександра ШІ-13
Lab 2v2
Обмеження: 1 сек., 256 МіБ

У вас є масив 𝑟 розміром N. Також вам дано 3 цілих числа.
Спочатку ви маєте видалити з масиву ці 3 числа, які вам дані. 
Після цього перетворити цей масив у масив сум, розміром 𝑁𝑛⁢𝑒⁢𝑤 −1 (розмір нового масиву після видалення елементів), який буде відображати суми сусідніх елементів нового масиву.
Далі необхідно вивести масив сум на екран.
*/
#include <iostream>
#include <cmath>
using namespace std;
    int filtered[100005];
    int sum[100005];
    int f[100005];
int main()
{
    int N,size=0;
    int a,b,c;
    cin>>N;
    for (int i=0; i<N; i++){
        cin>>f[i];
    }
    cin>>a>>b>>c;
    for (int i=0; i<N; i++){
        if (f[i]!=a && f[i]!=b && f[i]!=c)
        {
            filtered[size]=f[i];;
            size++;
        }
    }
    if (size<2){
        cout<<0;
        return 0;
    }
    int m=size-1;
    for (int i=0; i<m; i++){
        sum[i]=filtered[i]+filtered[i+1];
    }
    cout<<m<<endl;
    for (int i=0; i<size-1; i++){
        cout<<sum[i]<<" ";
    }
    cout<<endl;
}