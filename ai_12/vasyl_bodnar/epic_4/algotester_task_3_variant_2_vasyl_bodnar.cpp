#include <iostream>
using namespace std;

int main(){
    int N, M;
    char i, j;
    cin >> N;
    int *a = new int[N];
    for(i=0;i<N;i++){
        cin >> a[i];
    }
    cin >> M;
    int *b = new int[M];
    for(i=0;i<M;i++){
        cin >> b[i];
    }
    int sim = 0;
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            if(a[i] == b[j]){
                sim += 1;
            }
        }
    }
    cout << sim << endl;
    int dif = (N + M) - sim;
    cout << dif << endl;
    delete[] a;
    delete[] b;
    return 0;
}