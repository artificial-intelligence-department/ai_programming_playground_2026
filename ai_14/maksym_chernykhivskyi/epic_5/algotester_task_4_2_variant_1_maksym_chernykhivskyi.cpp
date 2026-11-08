/*Epic 5 - lab 4v1_2
Чернихівський Максим
Ші - 14*/

#include <iostream>
#include <algorithm>

using namespace std;

int* setDifference(int* arr1, int N, int* arr2, int M, int* result) {
    int i = 0, j = 0, k = 0;
    while (i < N && j < M) {
        if (arr1[i] < arr2[j]) {
            result[k] = arr1[i];
            i++;
            k++;
        } else if (arr1[i] > arr2[j]) {
            j++;
        } else { 
            i++;            
            j++;
        }
    }
    while (i < N) {
        result[k] = arr1[i];
        i++;
        k++;
    }
    return result + k;
}

int* setIntersection(int* arr1, int N, int* arr2, int M, int* result) {
    int i = 0, j = 0, k = 0;
    while (i < N && j < M) {
        if (arr1[i] == arr2[j]) {
            result[k] = arr1[i];
            i++;
            j++;
            k++;
        } else if (arr1[i] < arr2[j]) {
            i++;
        } else {
            j++;
        }
    }
    return result + k;
}

int* setUnion(int* arr1, int N, int* arr2, int M, int* result) {
    int i = 0, j = 0, k = 0;
    while (i < N && j < M) {
        if (arr1[i] == arr2[j]) {
            result[k] = arr1[i];
            i++;
            j++;
            k++;
        } else if (arr1[i] < arr2[j]) {
            result[k] = arr1[i];
            i++;
            k++;
        } else {
            result[k] = arr2[j];
            j++;
            k++;
        }
    }
    while (i < N) {
        result[k] = arr1[i];
        i++;
        k++;
    }
    while (j < M) {
        result[k] = arr2[j];
        j++;
        k++;
    }
    return result + k;
}

int* setSymmetricDifference(int* arr1, int N, int* arr2, int M, int* result) {
    int i = 0, j = 0, k = 0;
    while (i < N && j < M) {
        if (arr1[i] == arr2[j]) {
            i++;
            j++;
        } else if (arr1[i] < arr2[j]) {
            result[k] = arr1[i];
            i++;
            k++;
        } else {
            result[k] = arr2[j];
            j++;
            k++;
        }
    }
    while (i < N) {
        result[k] = arr1[i];
        i++;
        k++;
    }
    while (j < M) {
        result[k] = arr2[j];
        j++;
        k++;
    } 
    return result + k;
}

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
    end_ptr = setDifference(arr1, N, arr2, M, res_diff_NM);
    printRes(res_diff_NM, end_ptr);
    
    // Різниця M - N
    end_ptr = setDifference(arr2, M, arr1, N, res_diff_MN);
    printRes(res_diff_MN, end_ptr);
    
    // Перетин
    end_ptr = setIntersection(arr1, N, arr2, M, res_intersection);
    printRes(res_intersection, end_ptr);
    
    // Об'єднання
    end_ptr = setUnion(arr1, N, arr2, M, res_union);
    printRes(res_union, end_ptr);
    
    // Сим. різниця
    end_ptr = setSymmetricDifference(arr1, N, arr2, M, res_symm_diff);
    printRes(res_symm_diff, end_ptr);
    
    delete[] res_diff_NM;
    delete[] res_diff_MN;
    delete[] res_intersection;
    delete[] res_union;
    delete[] res_symm_diff;
    
    delete[] arr1;
    delete[] arr2;
}