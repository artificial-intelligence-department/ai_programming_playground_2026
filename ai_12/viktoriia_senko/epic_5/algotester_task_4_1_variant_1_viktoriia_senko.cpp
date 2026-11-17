/*Algotester Task 4 Variant 1 with STL
Автор:Сенько Вікторія
Група: ШІ-12 group3*/
#include <iostream>
#include <algorithm>
using namespace std;
 
const int Max = 100;
 
void PrintSet(int result[], int size){
    cout<<size<<endl;
    for(int i=0; i<size; i++){
        if(i>0) cout << " ";
        cout<<result[i];
    }
    cout << endl;
}
 
int main() {
    int n[Max];
    int m[Max];
    int result[2 * Max];
    int N, M, size;
 
    cin>>N;
    for(int i = 0; i < N; i++){
        cin>> n[i];
    }
    cin >> M;
    for(int i = 0; i < M; i++){
        cin >> m[i];
    }
 
    sort(n, n + N);
    sort(m, m + M);
 
    size=set_difference(n, n + N, m, m + M, result) - result;
    PrintSet(result, size);
    cout<<endl;
 
    size=set_difference(m, m + M, n, n + N, result) - result;
    PrintSet(result, size);
    cout<<endl;
 
    size=set_intersection(n, n + N, m, m + M, result) - result;
    PrintSet(result, size);
    cout<<endl;
 
    size=set_union(n, n + N, m, m + M, result) - result;
    PrintSet(result, size);
    cout<<endl;
 
    size=set_symmetric_difference(n, n + N, m, m + M, result) - result;
    PrintSet(result, size);
 
    return 0;
}