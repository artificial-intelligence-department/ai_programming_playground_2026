#include <iostream>
using namespace std;

int main(){
    int N, i;
    cin >> N;
    int *r = new int[N];
    for(i=0;i<N;i++){
        cin >> r[i];
    }
    int a,b,c, p = 0, s = 0;
    bool a_d = 1, b_d = 1, c_d = 1;
    cin >> a >> b >> c;
    int *t = new int[N];
    for(int i=0;i<N;i++){
        if(r[i] == a && a_d){
            a_d = 0;
            s++;
            continue;
            }
        else if(r[i] == b && b_d){
            b_d = 0;
            s++;
            continue;
            }
        else if(r[i] == c && c_d){
            c_d = 0;
            s++;
            continue;
            }
        t[p] = r[i];
        p++;
    }
    if(p<2) {
        cout << 0;
        return 0;
    }
    int *newr = new int[N-1-s];
    for(i=0;i<(N-1)-s;i++){
        newr[i] = t[i]+t[i+1];
    }
    cout << (N-1)-s << endl;
    for(i=0;i<(N-1)-s;i++){
        cout << newr[i] << " ";
    }
    delete[] t;
    delete[] r;
    delete[] newr;
    return 0;
}