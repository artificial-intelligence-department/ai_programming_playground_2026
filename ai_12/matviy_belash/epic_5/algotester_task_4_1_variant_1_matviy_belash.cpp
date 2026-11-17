#include <iostream>
#include <algorithm>
using namespace std;

void count_sort(int* a, int n){

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

    int* end = set_difference(n, n + N, m, m + M, res);
    int final_len = end - res;
    cout << final_len << endl;
    vivid(res, final_len);

    end = set_difference(m, m + M, n, n + N, res);
    final_len = end - res;
    cout << final_len << endl;
    vivid(res, final_len);

    end = set_intersection(n, n + N, m, m + M, res);
    final_len = end - res;
    cout << final_len << endl;
    vivid(res, final_len);

    end = set_union(n, n + N, m, m + M, res);
    final_len = end - res;
    cout << final_len << endl;
    vivid(res, final_len);

    end = set_symmetric_difference(n, n + N, m, m + M, res);
    final_len = end - res;
    cout << final_len << endl;
    vivid(res, final_len);

    return 0;
}
