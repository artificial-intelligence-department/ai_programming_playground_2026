#include <iostream>

void dronePositions(int *a, int *dron1, int *dron2, int N){
    *dron1 = 0;
    *dron2 = N - 1;
    while((*dron1) + 1 < *dron2){
        (*dron1) += a[*dron1];
        (*dron2) -= a[*dron2];
    }
}

int main(){
    int N;
    std::cin >> N;
    int *a = new int[N];
    for(int i = 0; i < N; i++){
        std::cin >> *(a + i);
    }

    int dron1, dron2;
    dronePositions(a, &dron1, &dron2, N);
    dron1++;
    dron2++;
    
    if(dron1 == dron2){
        std::cout << dron1 << " " << dron2 << std::endl;
        std::cout << "Collision";
    } else if(dron1 > dron2){
        std::cout << dron1 << " " << dron2 << std::endl;
        std::cout << "Miss";
    } else {
        std::cout << dron1 << " " << dron2 << std::endl;
        std::cout << "Stopped";
    }

    delete[] a;
    a = nullptr;

    return 0;
}