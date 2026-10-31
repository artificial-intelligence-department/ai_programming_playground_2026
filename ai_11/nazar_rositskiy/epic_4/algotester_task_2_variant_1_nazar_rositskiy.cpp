#include <iostream>

using namespace std;

int main(){
    //Ввід масиву
    int N;
    cin >> N;
    int r[N];
    for(int i = 0; i < N; i++){
        cin >> r[i];
    }

    //створення масивів без кожного числа по черзі
    int minmax[N];
    for(int i = 0; i < N; i++){
        //cтворення масиву без і
        int r1[N];
        for(int j = 0; j < i; j++){
            r1[j] = r[j];
        }
        for(int j = i; j < N-1; j++){
            r1[j] = r[j+1];
        }
        //обчислення в них максимальних і мінімальних значень та їх різниці, додавання їх в масив
        int max = r1[0];
        int min = r1[0];
        for(int j = 0; j < N-1; j++){
            if (r1[j] < min){
                min = r1[j];
            }
            if (r1[j] > max){
                max = r1[j];
            }
        }
        minmax[i]=max-min;
    }
    //знаходження та вивід мінімального значення в цьому масиві різниць
    int minf = minmax[0];
    for(int i = 0; i < N; i++){
        if (minmax[i] < minf){
                minf = minmax[i];
            }
    }
    cout << minf;





}