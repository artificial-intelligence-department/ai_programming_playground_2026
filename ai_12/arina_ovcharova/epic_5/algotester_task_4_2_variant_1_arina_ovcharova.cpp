// Algotester Lab 4, варіант 1 - версія без STL алгоритмів (своя реалізація)
// сортування можна було не писати, тому беру sort, а операції з множинами роблю сама
#include <iostream>
#include <algorithm>
using namespace std;

// за умовою N, M <= 100, тому результат не більше 200 елементів
const int MAX_SIZE = 200;

// сортую масив; повтори не прибираю - кожен елемент
// враховується стільки разів, скільки зустрічається (так приймає Algotester)
int makeSet(int arr[], int n) {
    sort(arr, arr + n);
    return n;
}

// всі функції нижче - два "вказівники" i та j, які йдуть по двох посортованих масивах

// a - b: те, що є в a, але немає в b
int difference(const int a[], int n, const int b[], int m, int res[]) {
    int i = 0, j = 0, k = 0;
    while (i < n) {
        if (j == m || a[i] < b[j]) {
            res[k++] = a[i++];
        } else if (a[i] > b[j]) {
            j++;
        } else {
            // однакові - пропускаю обидва
            i++;
            j++;
        }
    }
    return k;
}

// перетин: тільки однакові
int intersection(const int a[], int n, const int b[], int m, int res[]) {
    int i = 0, j = 0, k = 0;
    while (i < n && j < m) {
        if (a[i] < b[j]) {
            i++;
        } else if (a[i] > b[j]) {
            j++;
        } else {
            res[k++] = a[i];
            i++;
            j++;
        }
    }
    return k;
}

// об'єднання: беру менший, однакові записую один раз
int unionSets(const int a[], int n, const int b[], int m, int res[]) {
    int i = 0, j = 0, k = 0;
    while (i < n || j < m) {
        if (j == m || (i < n && a[i] < b[j])) {
            res[k++] = a[i++];
        } else if (i == n || a[i] > b[j]) {
            res[k++] = b[j++];
        } else {
            res[k++] = a[i];
            i++;
            j++;
        }
    }
    return k;
}

// симетрична різниця: все, крім однакових
int symmetricDifference(const int a[], int n, const int b[], int m, int res[]) {
    int i = 0, j = 0, k = 0;
    while (i < n || j < m) {
        if (j == m || (i < n && a[i] < b[j])) {
            res[k++] = a[i++];
        } else if (i == n || a[i] > b[j]) {
            res[k++] = b[j++];
        } else {
            i++;
            j++;
        }
    }
    return k;
}

void printSet(const int s[], int size) {
    cout << size << endl;
    for (int i = 0; i < size; i++) {
        if (i > 0) cout << " ";
        cout << s[i];
    }
    cout << endl;
}

int main() {
    int a[MAX_SIZE], b[MAX_SIZE], res[MAX_SIZE];
    int n, m;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    n = makeSet(a, n);
    m = makeSet(b, m);

    int k;
    k = difference(a, n, b, m, res);
    printSet(res, k);
    k = difference(b, m, a, n, res);
    printSet(res, k);
    k = intersection(a, n, b, m, res);
    printSet(res, k);
    k = unionSets(a, n, b, m, res);
    printSet(res, k);
    k = symmetricDifference(a, n, b, m, res);
    printSet(res, k);

    return 0;
}
