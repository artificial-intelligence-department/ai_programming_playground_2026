#include <iostream>

using namespace std;

bool comp(int a, int b){
    
    //Остача
    int a0 = a%3;
    int b0 = b%3;

    //Який елемент стоїть раніше
    if(a0 != b0){
        return (a0 < b0);
    }
    if(a0 == 0 || a0 == 2){
        return (a < b);
    } else {
        return (b < a);
    }


}

void sort(int arr[], int start, int end){

    //Поки більше одного елемента
    if(start < end){
        //вибрати ведучий елемент
        int pivot = arr[end];

        //ліміт лівої зони
        int i = start - 1;


        for(int j = start; j < end; j++){
            if(comp(arr[j], pivot)){
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        //Встановлюємо pivot на своє місце між зонами
        int temp = arr[i + 1];
        arr[i + 1] = arr[end];
        arr[end] = temp;
        //Рекурсивний виклик функції для лівої правої частини
        sort(arr, start, i);
        sort(arr, i + 2, end);
    }


}

int main(){
    const int max = 1000;

    int a[max];

    //Від кількості елементів і елементів масиву
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    //Сортування
    sort(a, 0, n - 1);

    //Видаляємо дублікати
    int uniqueCount = 0;
    if (n > 0) {
        uniqueCount = 1;
        for (int i = 1; i < n; i++) {
            if (a[i] != a[i - 1]) {
                a[uniqueCount++] = a[i];
            }
        }
    }

    //виводимо результат
    cout << uniqueCount << endl;
    for (int i = 0; i < uniqueCount; i++) {
        cout << a[i];
        if(!(i+1 == uniqueCount)){
            cout << " ";
        }
    }

}
