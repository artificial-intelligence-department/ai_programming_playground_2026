#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comparator(int a, int b){
    
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

int main(){
    //введення кількості чисел
    int n;
    cin >> n;

    //оголошення масиву і Введення самих чисел
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    //Сортування функцією сорт
    sort(a.begin(), a.end(), comparator);

    //видаляємо однакові
    a.erase(unique(a.begin(), a.end()), a.end());

    //Виведення розміру
    cout << a.size() << endl;

    //виведи елементів з пробілами
    for (int i = 0; i < a.size(); ++i) {
        cout << a[i];
        if(!(i+1 == a.size())){
            cout << " ";
        }
    }
}
