/* 
Епік 2. lab_1_task_2_variant_11
Авторка: Софія Ліс
Група: ші-11
*/

#include <iostream>

using namespace std;

int main() {
    int n0;
    int m0;
    // введення початкових значень m і n
    cout << "Введіть число n: ";
    cin >> n0; 
    cout << "Введіть число m: ";
    cin >> m0;

    int n = n0;
    int m = m0;

    int res1 = n++ * m;

    n = n0; // повертаємо n до початкового значення, аби для окремого обчислення n не залежала від попереднього

    int res2 = n++ < m;

    n = n0; 

    int res3 = m-- > m;

    cout << "Результат першого обчислення (n++*m): " << res1 << endl;
    cout << "Результат другого обчислення (n++<m): " << res2 << endl;
    cout << "Результат третього обчислення (m-->m): " << res3 << endl;

    return 0;
}