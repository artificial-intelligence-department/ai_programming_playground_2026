
#include <iostream>

using namespace std;

int main(){
    int N,K,tmp;
    int count = 0;
    bool inMas = false;
    cin >> N >> K;

    int *mas = new int[N]{-1};

    for(int i = 0; i < N; i++){
        cin >> tmp;
        for(int j = 0; j < i; j++){
            if(mas[j] == tmp){
                inMas = true;
                break;
            }
        }
        if(!inMas){
            mas[count] = tmp;
            count++;
        }
        else{
            inMas = false;
        }
    }

    for(int i = 0; i < count; i++){
        int min = mas[i];
        int minInd = i; 
        for(int j = i; j < count; j++){
            if(mas[j] < min){
                minInd = j;
                min = mas[j];
            }
        }
        int temp = mas[i];
        mas[i] = mas[minInd];
        mas[minInd] = temp;
    }

    K = K % count;

    cout << count << endl;
    for(int i = 0; i < count; i++){
        cout << mas[(i+K)%count] << " ";
    }

    delete[] mas;
    return 0;
}