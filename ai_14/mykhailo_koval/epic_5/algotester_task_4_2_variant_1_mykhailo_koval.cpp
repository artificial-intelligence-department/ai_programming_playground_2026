#include <iostream>

void printArr(int *s, int *e){
    for(int *p = s; p != e; p++){
        std::cout << *p << " ";
    }
    std::cout << '\n';
}

void bubble(int *a, int *end){
    int k = end - a; 
    for(int i = 0; i < k - 1; i++){
        for(int j = 0; j < k - i - 1; j++){
            if(a[j] > a[j + 1]){
                int temp = a [j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int diff(int *b, int *diffN, int M, int end){
    int k = end;
    for(int j = 0; j < M; j++){
        for(int i = 0; i < k; i++){
            if(diffN[i] == b[j]){
                for(int t = i; t < k - 1; t++){
                    diffN[t] = diffN[t + 1];
                }
                k--;
                break;
            }
        }
    }
    return k;
}

void intrs(int *a, int *b, int *intr, int N, int M, int &index){
    index = 0;
    int i = 0, j = 0;
    while(i < N && j < M){
        if(a[i] < b[j]){
            i++;
        } else if(a[i] > b[j]){
            j++;
        } else {
            intr[index] = a[i];
            index++;
            i++;
            j++;
        }
    }
}

void unite(int *a, int *b, int *united, int N, int M, int &index){
    index = 0;
    int i = 0, j = 0;
    while(i < N && j < M){
        if(a[i] < b[j]){
            united[index] = a[i];
            index++;
            i++;
        } else if(a[i] > b[j]){
            united[index] = b[j];
            index++;
            j++;
        } else {
            united[index] = a[i];
            index++;
            i++;
            j++;
        }
    }
    while(i < N){
        united[index] = a[i];
        index++;
        i++;
    }
    while(j < M){
        united[index] = b[j];
        index++;
        j++;
    }
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

    bubble(a, a + N);
    bubble(b, b + M);

    int *r1 = new int[N];
    for(int i = 0; i < N; i++){
        r1[i] = a[i];
    }
    int k1 = diff(b, r1, M, N);

    int *r2 = new int[M];
    for(int i = 0; i < M; i++){
        r2[i] = b[i];
    }
    int k2 = diff(a, r2, N, M);

    int *intr = new int[N + M];
    int index = 0;
    intrs(a, b, intr, N, M, index);

    int *united = new int[N + M];
    int k = 0;
    unite(a, b, united, N, M, k);

    int *sym = new int[k1 + k2 + 1];
    for(int i = 0; i < k1; i++){
        sym[i] = r1[i];
    }
    for(int i = 0; i < k2; i++){
        sym[k1 + i] = r2[i];
    }
    int kSym = k1 + k2;
    bubble(sym, sym + kSym);

    std::cout << k1 << '\n';
    printArr(r1, r1 + k1);
    std::cout << k2 << '\n';
    printArr(r2, r2 + k2);
    std::cout << index << '\n';
    printArr(intr, intr + index);
    std::cout << k << '\n';
    printArr(united, united + k);
    std::cout << kSym << '\n';
    printArr(sym, sym + kSym);

    delete[] a;
    delete[] b;
    delete[] r1;
    delete[] r2;
    delete[] intr;
    delete[] united;
    delete[] sym;
    return 0;
}