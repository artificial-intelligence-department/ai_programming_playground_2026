#include <iostream>

int main(){

    int n;
    std::cin >> n;
    int arr[100];

    int pumpkins = 0;
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
        if (arr[i] <= 2) {
            pumpkins++;
        }
        else if (arr[i] >= 3 && arr[i]<=7) {
            pumpkins+=2;
        }
        else if (arr[i] >= 8 && arr[i]<=47) {
            pumpkins+=3;
        }
        else if (arr[i] > 47) {
            pumpkins+=4;
        }
    }
    std::cout << pumpkins;
    return 0;
}