#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int N;
    cin >> N;

    int *N_arr = new int[N];

    for (int i = 0; i < N; i++) {
        cin >> N_arr[i];
    }

    int M;
    cin >> M;

    int *M_arr = new int[M];

    for (int i = 0; i < M; i++) {
        cin >> M_arr[i];
    }

    int mx = max(N, M);

    sort(N_arr, N_arr + N);
    sort(M_arr, M_arr + M);

    int *result = new int[mx];


    int *end_ptr = set_difference(
        N_arr, N_arr + N,
        M_arr, M_arr + M,
        result
    );
    int count = 0;
    for (int* ptr = result; ptr != end_ptr; ptr++) {
        count++;
    }
    cout<<count<<endl;
    for (int* ptr = result; ptr != end_ptr; ptr++) {
        cout << *ptr << ' ';
    }
    cout<<endl;
    cout<<endl;
    delete[] result;


    result = new int[mx];


    end_ptr = set_difference(
        M_arr, M_arr + M,
        N_arr, N_arr + N,
        result
    );
    count = 0;
    for (int* ptr = result; ptr != end_ptr; ptr++) {
        count++;
    }
    cout<<count<<endl;
    for (int* ptr = result; ptr != end_ptr; ptr++) {
        cout << *ptr << ' ';
    }
    cout<<endl;
    cout<<endl;
    delete[] result;

    result = new int[mx];


    end_ptr = set_intersection(
        M_arr, M_arr + M,
        N_arr, N_arr + N,
        result
    );
    count = 0;
    for (int* ptr = result; ptr != end_ptr; ptr++) {
        count++;
    }
    cout<<count<<endl;
    for (int* ptr = result; ptr != end_ptr; ptr++) {
        cout << *ptr << ' ';
    }
    cout<<endl;
    cout<<endl;
    delete[] result;

    result = new int[mx*2];


    end_ptr = set_union(
        M_arr, M_arr + M,
        N_arr, N_arr + N,
        result
    );
    count = 0;
    for (int* ptr = result; ptr != end_ptr; ptr++) {
        count++;
    }
    cout<<count<<endl;
    for (int* ptr = result; ptr != end_ptr; ptr++) {
        cout << *ptr << ' ';
    }
    cout<<endl;
    cout<<endl;
    delete[] result;

    result = new int[mx*2];


    end_ptr = set_symmetric_difference(
        M_arr, M_arr + M,
        N_arr, N_arr + N,
        result
    );
    count = 0;
    for (int* ptr = result; ptr != end_ptr; ptr++) {
        count++;
    }
    cout<<count<<endl;
    for (int* ptr = result; ptr != end_ptr; ptr++) {
        cout << *ptr << ' ';
    }
    delete[] result;



    delete[] N_arr;
    delete[] M_arr;

    return 0;
}