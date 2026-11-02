#include <iostream>
using namespace std;


int main(){

    int N = 0;
    cin >> N;

    int r[N];
    for(int i =0; i <N; i++){
        cin >> r[i];
    }

    bool may_to_delete[N];
    for(int i =0; i <N; i++){
        may_to_delete[i] = true;
    }

    for(int i =0; i <N; i++){ 
        if(!(may_to_delete[i])) continue; 
        for(int j =1; j <(N-i); j++){
            if(r[i] == r[i+j]){
                may_to_delete[i] = false;
                may_to_delete[i+j] = false;
            }
        }
    }


    int max = r[0], min = r[0];
    for(int i =0; i <N; i++){
        if(r[i] > max) max = r[i];
        if(r[i] < min) min = r[i];
    }
    int diff = max - min;

    
    for(int i =0; i <N; i++){
        if(!(may_to_delete[i])) continue;
        if(i != 1){
            max = r[1]; min = r[1];
        }else{
            max = r[0]; min = r[0];
        } 
        for(int j =0; j <N; j++){
            if(j == i) continue;
            if(r[j] >= max) max = r[j];
            if(r[j] <= min) min = r[j];
        }
        if(max - min < diff) diff = max - min;
    }

    cout << diff;

    return 0;
}