#include <iostream>

void ring(int *a, int N, int K){
    int x = (K - 1) % N;
    for(int i = 0; i < N; i++){
        std::cout << *(a + (x + i) % N) << " ";  
    }
    std::cout << '\n';
}

void bubbleSort(int *a, int N){
    for(int i = 0; i < N - 1; i++){
        for(int j = 0; j < N - i - 1; j++){
            if((*(a + j)) > (*(a + j + 1))){
                int temp = *(a + j);
                *(a + j) = *(a + j + 1);
                *(a + j + 1) = temp;
            }
        }
    }
}

void eraseEven(int *a, int *N){
    int k = 0;
    for(int i = 0; i < *N; i++){
        if(*(a + i) % 2 != 0){
            *(a + k) = *(a + i);
            k++;
        }
    }
    *N = k;
}


int main(){
    int N, K;
    std::cin >> N >> K;
    int *a = new int[N];
    for(int i = 0; i < N; i++){
        std::cin >> *(a + i);
    }    

    ring(a, N, K);
    bubbleSort(a, N);
    eraseEven(a, &N);
    if(N == 0){
        delete[] a;
        a = nullptr;
        return 0;
    }
    ring(a, N, K);

    delete[] a;
    a = nullptr;
    return 0;
}