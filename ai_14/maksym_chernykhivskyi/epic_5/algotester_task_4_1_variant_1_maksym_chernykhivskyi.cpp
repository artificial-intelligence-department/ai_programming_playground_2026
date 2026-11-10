/*Epic 5 - lab 4v1_1
Чернихівський Максим
Ші - 14*/

#include <iostream>
#include <algorithm>

using namespace std;

void printRes(int* start, int* end) {
    int size = end - start;
    cout << size << "\n";
    
    for (int* p = start; p != end; ++p) {
        cout << *p << " ";
    }
    cout << "\n\n";
}

int main() {
    int N;
    cin >> N;
    int* arr1 = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> arr1[i];
    }
    
    int M;
    cin >> M;
    int* arr2 = new int[M];
    for (int i = 0; i < M; i++) {
        cin >> arr2[i];
    }
    
    sort(arr1, arr1 + N);
    sort(arr2, arr2 + M);
    
    const int MAX_SIZE = N + M;
    
    int* res_diff_NM = new int[MAX_SIZE];
    int* res_diff_MN = new int[MAX_SIZE];
    int* res_intersection = new int[MAX_SIZE];
    int* res_union = new int[MAX_SIZE];
    int* res_symm_diff = new int[MAX_SIZE];
    
    int* end_ptr;
    
    // Різниця N - M
    end_ptr = set_difference(arr1, arr1 + N, arr2, arr2 + M, res_diff_NM);
    printRes(res_diff_NM, end_ptr);
    
    // Різниця M - N
    end_ptr = set_difference(arr2, arr2 + M, arr1, arr1 + N, res_diff_MN);
    printRes(res_diff_MN, end_ptr);
    
    // Перетин
    end_ptr = set_intersection(arr1, arr1 + N, arr2, arr2 + M, res_intersection);
    printRes(res_intersection, end_ptr);
    
    // Об'єднання
    end_ptr = set_union(arr1, arr1 + N, arr2, arr2 + M, res_union);
    printRes(res_union, end_ptr);
    
    // Сим. різниця
    end_ptr = set_symmetric_difference(arr1, arr1 + N, arr2, arr2 + M, res_symm_diff);
    printRes(res_symm_diff, end_ptr);
    
    delete[] res_diff_NM;
    delete[] res_diff_MN;
    delete[] res_intersection;
    delete[] res_union;
    delete[] res_symm_diff;
    
    delete[] arr1;
    delete[] arr2;
}