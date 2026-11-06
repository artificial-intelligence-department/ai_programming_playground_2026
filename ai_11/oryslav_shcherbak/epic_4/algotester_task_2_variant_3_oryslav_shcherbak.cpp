#include <iostream>
#include <string>
using namespace std;

/*
 * Задача: Algotester Lab 2v3
 * Щербак Орислав
 * Група ШІ-11
 */

int main(){
    int N;
    cin >> N;
    int *a = new int[N+1];
    for(int i = 1; i <= N; i++){
        cin >> a[i];
    }
    string result;
    int left = 1;
    int right = N;
    while(true){
        if(left == right){
        result = "Collision";
        break;
    }
        if(left > right){
        result = "Miss";
        break;
    }
        if(right - left == 1){
        result =  "Stopped";
        break;
    }
    int nextleft = left + a[left];
    int nextright = right - a[right];
    left = nextleft;
    right = nextright;
    }
    cout << left << " " << right << endl;
    cout << result;
}