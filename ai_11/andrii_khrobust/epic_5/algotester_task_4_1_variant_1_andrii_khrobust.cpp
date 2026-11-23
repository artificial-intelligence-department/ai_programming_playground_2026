#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int N,M;
    int n[100];
    int m[100];
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>n[i];
    }
    cin>>M;
    for(int i=0;i<M;i++){
        cin>>m[i];
    }
    sort(n,n+N);
    sort(m,m+M);
    
    int result1[100];
    int* last1 = set_difference(n, n + N, m, m + M, result1);
    cout<<last1-result1<<endl;
    for(int i = 0; i < last1-result1; i++)
    cout << result1[i] << " ";
    cout<<endl;

    int result2[100];
    int* last2 = set_difference(m, m+ M, n, n+N, result2);
    cout<<last2-result2<<endl;
    for(int i = 0; i < last2-result2; i++)
    cout << result2[i] << " ";
    cout<<endl;

     int result3[100];
    int* last3 = set_intersection(m, m+ M, n, n+N, result3);
    cout<<last3-result3<<endl;
    for(int i = 0; i < last3-result3; i++)
    cout << result3[i] << " ";
    cout<<endl;

    int result4[100];
    int* last4 = set_union(m, m+ M, n, n+N, result4);
    cout<<last4-result4<<endl;
    for(int i = 0; i < last4-result4; i++)
    cout << result4[i] << " ";
    cout<<endl;

    int result5[100];
    int* last5=set_symmetric_difference(n,n+N,m,m+M,result5);
    cout<<last5-result5<<endl;
    for(int i=0;i<last5-result5;i++)
    cout<<result5[i]<<" ";

    return 0;
}