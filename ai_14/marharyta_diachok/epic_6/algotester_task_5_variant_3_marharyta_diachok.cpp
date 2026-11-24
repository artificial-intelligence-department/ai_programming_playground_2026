/*  
Задача: Algotester Lab №5. Варіант №3.  
Автор: Дячок Маргарита. 
Група: ШІ-14 
*/ 

#include <iostream>
using namespace std;

struct Mountain {int x; int y;};

void paint(Mountain peak, int **m, int N, int M) {
int *q = new int[N * M]; //черга клітинок (номер = i * M + j)
int head = 0, tail = 0;

m[peak.x][peak.y] = 0; //відстань піку до себе
q[tail++] = peak.x * M + peak.y;

int maxDist = 0;

while (head < tail) {
int cur = q[head++];
int i = cur / M;
int j = cur % M;

if (m[i][j] > maxDist) maxDist = m[i][j];

//вправо
if (j + 1 < M && m[i][j + 1] == -1) {
    m[i][j + 1] = m[i][j] + 1;
    q[tail++] = i * M + (j + 1);}


//вниз
if (i + 1 < N && m[i + 1][j] == -1) {
    m[i + 1][j] = m[i][j] + 1;
    q[tail++] = (i + 1) * M + j;}


//вліво
if (j - 1 >= 0 && m[i][j - 1] == -1) {
    m[i][j - 1] = m[i][j] + 1;
    q[tail++] = i * M + (j - 1);}


//вгору
if (i - 1 >= 0 && m[i - 1][j] == -1) {
    m[i - 1][j] = m[i][j] + 1;
    q[tail++] = (i - 1) * M + j;}
}


    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            m[i][j] = maxDist - m[i][j];

    delete[] q;
}

int main() {
    int N, M;
    cin >> N >> M;
    Mountain peak;
    cin >> peak.x >> peak.y;
    peak.x--;
    peak.y--;

int **m = new int*[N];
for (int i = 0; i < N; i++) {
    m[i] = new int[M];
        for (int j = 0; j < M; j++) m[i][j] = -1;}

paint(peak, m, N, M);

for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
        if (j > 0) cout << ' ';
        cout << m[i][j];}
        cout << '\n';}

for (int i = 0; i < N; i++) delete[] m[i];
delete[] m;
    return 0;
}