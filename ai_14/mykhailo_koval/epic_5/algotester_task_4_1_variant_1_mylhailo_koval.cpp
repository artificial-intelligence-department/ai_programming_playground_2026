#include <iostream>
#include <algorithm>

void printArr(int *s, int *e){
    for(int *p = s; p != e; p++){
        std::cout << *p << " ";
    }
    std::cout << '\n';
}

int main(){
    int N, M;
    std::cin >> N;
    int *a = new int[N];
    for(int i = 0; i < N; i++){
        std::cin >> a[i];
    }
    std::cin >> M;
    int *b = new int[M];
    for(int i = 0; i < M; i++){
        std::cin >> b[i];
    }
    int min;
    if(N < M){
        min = N;
    } else {
        min = M;
    }
    std::sort(a, a + N);
    std::sort(b, b + M);

    int *r1 = new int[N];
    int *e1 = std::set_difference(a, a + N, b, b + M, r1);

    int *r2 = new int[M];
    int *e2 = std::set_difference(b, b + M, a, a + N, r2);

    int *result_intr = new int[min];
    int *end_intr = std::set_intersection(a, a + N, b, b + M, result_intr);

    int *result_un = new int[N + M];
    int *end_un = std::set_union(a, a + N, b, b + M, result_un);

    int *result_sym = new int[N + M];
    int *end_sym = std::set_symmetric_difference(a, a + N, b, b + M, result_sym);

    std::cout << e1 - r1 << '\n';
    printArr(r1, e1);
    std::cout << e2 - r2 << '\n';
    printArr(r2, e2);
    std::cout << end_intr - result_intr << '\n';
    printArr(result_intr, end_intr);
    std::cout << end_un - result_un << '\n';
    printArr(result_un, end_un);
    std::cout << end_sym - result_sym << '\n';
    printArr(result_sym, end_sym);

    delete[] a;
    a = nullptr;
    delete[] b;
    b = nullptr;
    delete[] result_intr;
    result_intr = nullptr;
    delete[] result_sym;
    result_sym = nullptr;
    delete[] result_un;
    result_un = nullptr;
    delete[] r1;
    r1 = nullptr;
    delete[] r2;
    r2 = nullptr;
    return 0;
}