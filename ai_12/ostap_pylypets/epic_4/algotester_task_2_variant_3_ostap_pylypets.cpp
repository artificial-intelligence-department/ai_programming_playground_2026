/*лабораторна робота з алготестеру #2 v3*/

#include <iostream>
using namespace std;
void resultCheck(int droneOnePos, int droneTwoPos, int n, int a[]){
    switch (droneOnePos - droneTwoPos){
        case -1:
            cout <<"Stopped";
            break;
        case 0:
            cout << "Collision";
            break;
        default:
            cout <<"Miss";
            break;
    }
}
void posChange(int& droneOnePos, int& droneTwoPos, int n, int a[]){
    int diff = droneOnePos-droneTwoPos;
    while(diff < -1){
        droneOnePos += a[droneOnePos];
        droneTwoPos -= a[droneTwoPos];
        diff = droneOnePos-droneTwoPos;
    }
}
int main(){
    int n, a[1000], droneOnePos = 0, droneTwoPos = 0;
    cin >> n;
    for(int i = 0; i< n; i++){
        cin >> a[i];
    }
    droneOnePos = 0;
    droneTwoPos = n-1;
    posChange(droneOnePos, droneTwoPos, n, a);
    cout << droneOnePos +1<< " " << droneTwoPos +1<< endl;
    resultCheck(droneOnePos, droneTwoPos, n, a);
    return 0;
}