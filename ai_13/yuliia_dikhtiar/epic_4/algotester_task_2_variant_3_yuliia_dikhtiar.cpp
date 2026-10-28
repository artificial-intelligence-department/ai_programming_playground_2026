/*
Назва задачі: Lab 2v3
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>

using namespace std;

const int Max = 1000;

int main() {

int a[Max + 1] = {};
int N = 0;

cin >> N;
if (N < 0 || N > 1000) {
    return 1;
}

for (int i = 0; i < N; i++) {
    cin >> a[i + 1];
    if (a[i + 1] > 5 || a[i + 1] < 1) {
        return 1;
    }
}

int droneX = 1;
int droneY = N;

if (N == 1) {
    cout << droneX << " " << droneY << endl;
    cout << "Collision";
    return 0;
}

for (int i = 1; i < N; i++) {

    if (droneX == droneY) {
        cout << droneX << " " << droneY << endl;
        cout << "Collision";
        return 0;
    }

    if (droneX > droneY) {
        cout << droneX << " " << droneY << endl;
        cout << "Miss";
        return 0;
    }

    if (droneX == droneY - 1) {
        cout << droneX << " " << droneY << endl;
        cout << "Stopped";
        return 0;
    }

droneX += a[droneX];
droneY -= a[droneY];

}

cout << endl;

return 0;

}