/*Epic 4 - lab 3v2
Чернихівський Максим
Ші - 14*/

#include <iostream>

using namespace std;

int main() {
    int N = 0;
    int M = 0;
    
    cin >> N;
    int n[N];
    for(int i = 0; i < N; i++){
        cin >> n[i];
    }    
    cin >> M;
    int m[M];
    for(int i = 0; i < M; i++){
        cin >> m[i];
    }   
    int both = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if (n[i] == m[j]){
                both++;
            }
        }
    }
    
    int all = N + M;
    int unique = all - both;
    
    cout << both << endl;
    cout << unique << endl;
}