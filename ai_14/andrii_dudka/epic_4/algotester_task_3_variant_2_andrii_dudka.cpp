// variant 2

#include <iostream>


using namespace std;

int main() {
    int first_number, second_number, unique_count = 0;
    cin >> first_number;
    int* first_turple = new int[first_number];
    for (int i = 0; i < first_number; ++i) {
        cin >> first_turple[i];
    }
    cin >> second_number;
    int* second_turple = new int[second_number];
    for (int i = 0; i < second_number; ++i) {
        cin >> second_turple[i];
    }
    int total = first_number + second_number;
    for (int i = 0; i < first_number; ++i) {
        int temp = first_turple[i];
        for (int j = 0; j < second_number; ++j) {
            if (temp == second_turple[j]) unique_count++;
    }
    }
    cout << unique_count << endl;
    cout << total - unique_count << endl;

    delete[] first_turple;
    delete[] second_turple;
}