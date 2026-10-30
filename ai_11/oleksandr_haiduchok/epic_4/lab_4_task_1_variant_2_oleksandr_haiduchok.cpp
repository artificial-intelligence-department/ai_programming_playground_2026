#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
void Delete(int *a, int &N){
int y = 0;
int count = 0;
for(y = 0; y < N; y++){
    if(a[y] == 0){
    for(int i = y; i < N - count - 1; i++){
        a[i] = a[i + 1];
        }
        count++;
        break;
    }
    }
    N = N - count;
    for(int h = 0; h < N; h++){
        cout << a[h] << " ";
    }
}
void Paste(int *a, int N){
    int count2 = 0;
    for(int i = 0; i < N; i++){
        if(a[i]%2 == 0 && i != 0){
            count2++; 
        }
    }
    int b[N + count2];
    int ind = 0;
    for(int k = 0; k < N; k++){
        b[ind] = a[k];
        if(a[k]%2 == 0 && k != 0){
            b[ind + 1] = b[ind - 1] + 2;
            ind++;
        }
        ind++;
    }
    
    for(int k = 0; k < N + count2; k++){
        cout << b[k] << " ";
}
cout << "\n";
}

int main(){
    srand(time(0));
    int N = 0;
    cin >> N;
    int a[N];
    for(int v = 0; v < N; v++){
        a[v] = rand()%10;
        cout << a[v] << "\t ";
    }
    
    cout << "\n";
    Delete(a, N);
    cout << "\n";
    Paste(a, N);
    return 0;
}