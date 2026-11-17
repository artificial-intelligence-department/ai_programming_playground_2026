#include <iostream>
using namespace std;

void count_sort(int* a, int n){

    if (n <= 0) return;

    int max = *a, min = *a;
    for(int i = 0; i < n; i++){
        if(*(a + i) > max) max = *(a + i);
        if(*(a + i) < min) min = *(a + i);
    }

    int count[max - min + 1] = {0};
    for(int i = 0; i < n; i++){
        count[*(a + i) - min]++;
    }

    int j = 0;
    for (int i = 0; i < max - min + 1; i++){
        while (count[i] > 0){
            *(a + j) = i + min;
            j++;
            count[i]--;
        }
    }

}
    
void vivid(int a[], int n){

    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl << endl;

}

int* difference(int n[], int N, int m[], int M, int* res){

    int i = 0, j = 0, id = 0;
    while (i < N){
        if (j < M && m[j] < n[i]) j++;
        else if (j < M && m[j] == n[i]) { i++; j++; }
        else res[id++] = n[i++];
    }
    return res + id;

}

int* intersection(int n[], int N, int m[], int M, int* res){

    int i = 0, j = 0, id = 0;
    while (i < N && j < M){
        if (n[i] < m[j]) i++;
        else if (n[i] > m[j]) j++;
        else { res[id++] = n[i]; i++; j++; }   
    }
    return res + id;

}

int* union_m(int n[], int N, int m[], int M, int* res){

    int i = 0, j = 0, id = 0;
    while (i < N && j < M){
        if (n[i] < m[j]) res[id++] = n[i++];
        else if (n[i] > m[j]) res[id++] = m[j++];
        else { res[id++] = n[i]; i++; j++; }  
    }
    while (i < N) res[id++] = n[i++];     
    while (j < M) res[id++] = m[j++];         
    return res + id;

}

int* symmetric_difference(int n[], int N, int m[], int M, int* res){

    int i = 0, j = 0, id = 0;
    while (i < N && j < M){
        if (n[i] < m[j]) res[id++] = n[i++];
        else if (n[i] > m[j]) res[id++] = m[j++];
        else { i++; j++; }                     // рівні: пара скорочується, нічого не пишемо
    }
    while (i < N) res[id++] = n[i++];
    while (j < M) res[id++] = m[j++];
    return res + id;

}

int main(){

    int N=0, M=0;

    cin >> N;
    int n[N];
    for(int i = 0; i <N; i++){
        cin >> n[i];
    }

    cin >> M;
    int m[M];
    for(int i = 0; i <M; i++){
        cin >> m[i];
    }

    count_sort(n, N);
    count_sort(m, M);

    int res[M+N]; 

    int* end = difference(n, N, m, M, res);
    int final_len = end - res;
    cout << final_len << endl;
    vivid(res, final_len);

    end = difference(m, M, n, N, res);
    final_len = end - res;
    cout << final_len << endl;
    vivid(res, final_len);

    end = intersection(n, N, m, M, res);
    final_len = end - res;
    cout << final_len << endl;
    vivid(res, final_len);

    end = union_m(n, N, m, M, res);
    final_len = end - res;
    cout << final_len << endl;
    vivid(res, final_len);

    end = symmetric_difference(n, N, m, M, res);
    final_len = end - res;
    cout << final_len << endl;
    vivid(res, final_len);

    return 0;
}
