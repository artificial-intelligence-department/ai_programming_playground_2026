#include <iostream>
using namespace std;

int main(){
    int N;
    cin >> N;

    char field[10][10];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
        cin >> field[i][j];
    }
}
    int Q;
    cin >> Q;
    for(int k = 0; k < Q; k++){
         int x, y;
         cin >> x >> y;
     
        if(field[x - 1][y - 1] != '0'){
            cout << "1" << endl;
            cout << field[x - 1][y - 1] << endl;
            continue;
        }
        bool used[10] = {false};
       
        for(int j = 0; j < N; j++){
            int digit = field[x - 1][j] - '0';
            if(digit >= 1 && digit <= N){
                used[digit] = true;
            }
        }
         for(int i = 0; i < N; i++){
            int digit = field[i][y - 1] - '0';
            if(digit >= 1 && digit <= N){
                used[digit] = true;
            }
        }
        int count = 0;
        for(int i = 1; i <= N; i++){
            if(!used[i]){
                count++;
            }
        }
        
        cout << count << endl;
        for(int i = 1; i <= N; i++){
               if(!used[i]){
                cout << i << " ";
               }
            }
            cout << endl;
        }
    return 0;
}
