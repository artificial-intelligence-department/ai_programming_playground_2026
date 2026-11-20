/*Алготестер задача 4 варіант 1 (з використанням STL)
Максімко Павло - СШІ-13*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N, M;
    cin >> N;
    vector<int> A(N);
    for(int i = 0; i < N; i++) cin >> A[i];
    cin >> M;
    vector<int> B(M);
    for(int i = 0; i < M; i++) cin >> B[i];

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    vector<int> operation_AB;

    set_difference(A.begin(), A.end(), B.begin(), B.end(), inserter(operation_AB, operation_AB.begin())); 
    cout << operation_AB.size() << endl;
    if(!operation_AB.empty()) 
    {
        for(int x : operation_AB) cout << x << " ";
        cout << endl;
    }
    cout << endl;
    operation_AB.clear();

    set_difference(B.begin(), B.end(), A.begin(), A.end(), inserter(operation_AB, operation_AB.begin())); 
    cout << operation_AB.size() << endl;
    if(!operation_AB.empty()) 
    {
        for(int x : operation_AB) cout << x << " ";
        cout << endl;
    }
    cout << endl;
    operation_AB.clear();

    set_intersection(A.begin(), A.end(), B.begin(), B.end(), inserter(operation_AB, operation_AB.begin())); 
    cout << operation_AB.size() << endl;
    if(!operation_AB.empty()) 
    {
        for(int x : operation_AB) cout << x << " ";
        cout << endl;
    }
    cout << endl;
    operation_AB.clear();

    set_union(A.begin(), A.end(), B.begin(), B.end(), inserter(operation_AB, operation_AB.begin())); 
    cout << operation_AB.size() << endl;
    if(!operation_AB.empty()) 
    {
        for(int x : operation_AB) cout << x << " ";
        cout << endl;
    }
    cout << endl;
    operation_AB.clear();

    set_symmetric_difference(A.begin(), A.end(), B.begin(), B.end(), inserter(operation_AB, operation_AB.begin())); 
    cout << operation_AB.size() << endl;
    if(!operation_AB.empty()) 
    {
        for(int x : operation_AB) cout << x << " ";
        cout << endl;
    }
    cout << endl;
    operation_AB.clear();

    return 0;
}