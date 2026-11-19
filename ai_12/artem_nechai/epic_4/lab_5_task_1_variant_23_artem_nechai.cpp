#include <iostream>

using namespace std;

void input_again(int &a) {
	cin.clear();
	cin.ignore(256, '\n');
	cout << "Неправильний ввід, спробуйте ще раз: ";
	cin >> a;
}

void fill_2d_array(int* arr1, int* arr2, int &N) {
    for (int i = 0; i < N; ++i) {
        arr2[i * N] = (N % 2 == 0) ? arr1[i] + 1 : arr1[i];
        for (int j = 1; j < N; ++j) {
            arr2[i * N + j] = (j % 2 == 0) ? 1 : -1;
        }
    }
}

int main() {
	cout << "Введіть кількість елементів масиву: ";
    int N;
    cin >> N;

	cout << "Введіть елементи масиву: ";
    int* arr1 = new int[N];

    for (int i = 0; i < N; ++i) {
        cin >> arr1[i];
        
        while (cin.fail()) {
            input_again(arr1[i]);
        }
    }

    int* arr2 = new int[N * N];
    fill_2d_array(arr1, arr2, N);

    cout << "Отриманий двовимірний масив:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << arr2[i * N + j] << " ";
        }
        cout << endl;
    }

    delete[] arr1;
    delete[] arr2;

    return 0;
}