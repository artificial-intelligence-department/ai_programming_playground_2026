/*
    Задача: Листки
    Михайловська Анна
    ШІ-14
*/
#include <iostream>
using namespace std;

struct Rectangle {int x1, y1, x2, y2;};

Rectangle rectangles[500];
int xs[1000], ys[1000];
bool covered[1001][1001];

void swapNumbers(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int sortAndUnique(int a[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (a[i] > a[j])
                swapNumbers(a[i], a[j]);
        }
    }

    int uniqueCount = 0;
    for (int i = 0; i < count; i++) {
        if (uniqueCount == 0 ||
            a[i] != a[uniqueCount - 1]) {

            a[uniqueCount] = a[i];
            uniqueCount++;
        }
    }
    return uniqueCount;
}

int findIndex(int a[], int count, int value) {
    for (int i = 0; i < count; i++) {
        if (a[i] == value)
            return i;
    }
    return -1;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        Rectangle &r = rectangles[i];

        cin >> r.x1 >> r.y1 >> r.x2 >> r.y2;

        if (r.x1 > r.x2)
            swapNumbers(r.x1, r.x2);

        if (r.y1 > r.y2)
            swapNumbers(r.y1, r.y2);

        xs[2 * i] = r.x1;
        xs[2 * i + 1] = r.x2;

        ys[2 * i] = r.y1;
        ys[2 * i + 1] = r.y2;
    }

    int nx = sortAndUnique(xs, 2 * n);
    int ny = sortAndUnique(ys, 2 * n);

    for (int i = 0; i < n; i++) {
        Rectangle r = rectangles[i];

        int left = findIndex(xs, nx, r.x1);
        int right = findIndex(xs, nx, r.x2);
        int bottom = findIndex(ys, ny, r.y1);
        int top = findIndex(ys, ny, r.y2);

        for (int x = left; x < right; x++) {
            for (int y = bottom; y < top; y++) {
                covered[x][y] = true;
            }
        }
    }

    long long answer = 0;
    for (int i = 0; i < nx - 1; i++) {
        for (int j = 0; j < ny - 1; j++) {
            if (covered[i][j] == false)
                continue;

            int width = xs[i + 1] - xs[i];
            int height = ys[j + 1] - ys[j];

            if (i == 0 || covered[i - 1][j] == false)
                answer += height;

            if (i == nx - 2 || covered[i + 1][j] == false)
                answer += height;

            if (j == 0 || covered[i][j - 1] == false)
                answer += width;

            if (j == ny - 2 || covered[i][j + 1] == false)
                answer += width;
        }
    }
    cout << answer << '\n';
    
    return 0;
}