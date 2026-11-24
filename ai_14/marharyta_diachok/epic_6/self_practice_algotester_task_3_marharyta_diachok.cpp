/*  
Задача: Self-practice. Завдання №3.
Автор: Дячок Маргарита. 
Група: ШІ-14 
*/

#include <iostream>

using namespace std;

struct Node {
    char bracket;
    Node* next;
};

struct Stack {
Node* top = nullptr;
int size = 0;

void push(char c) {
    top = new Node{c, top};
    size++;}

void pop() {
    if (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
        size--;}}

bool empty() {
    return top == nullptr;}

void clear() {
    while (!empty()) {
        pop();}}};

const int MAXN = 5005;
char s[MAXN];
int first_part[MAXN];
bool ok[MAXN];
int suff_min_bal[MAXN];

int main() {
if (!(cin >> s)) {
    return 0;}

int n = 0; //рахуємо довжину вхідного рядка
while (s[n] != '\0') {
    n++;}

if (n % 2 != 0) {//якщо довжина непарна, коректну послідовність утворити неможливо
    cout << "impossible\n";
    return 0;}

Stack st;
bool already_valid = true;
for (int i = 0; i < n; ++i) {
    if (s[i] == '(') {
        st.push('(');} 
        
    else {
        if (st.empty()) {
            already_valid = false;
            break;}

        st.pop();}}

if (already_valid && st.empty()) {
    cout << "possible\n";
    return 0;}

st.clear();

    first_part[0] = 0;
    ok[0] = true;

    for (int i = 0; i < n; ++i) {
        int delta;
        if (s[i] == '(') {
            delta = 1;
        } else {
            delta = -1;
        }

        first_part[i + 1] = first_part[i] + delta;

        if (ok[i] == true && first_part[i + 1] >= 0) {
            ok[i + 1] = true;
        } else {
            ok[i + 1] = false;
        }
    }

    // Рахуємо мінімальний префіксний баланс на кожному суфіксі
    suff_min_bal[n] = first_part[n];
    for (int i = n - 1; i >= 0; --i) {
        if (first_part[i] < suff_min_bal[i + 1]) {
            suff_min_bal[i] = first_part[i];} 
            
        else {
            suff_min_bal[i] = suff_min_bal[i + 1];}}

for (int l = 0; l < n; ++l) { //перебираємо всі можливі відрізки
    if (!ok[l]) break;

        int cur_bal = first_part[l];
        for (int r = l; r < n; ++r) {
            int inv_delta;
            if (s[r] == '(') {
                inv_delta = -1; //після інверсії '(' стане ')'
            } else {
                inv_delta = 1;  //після інверсії ')' стане '('
            }

cur_bal += inv_delta;

if (cur_bal < 0) break;
            
int shift = cur_bal - first_part[r + 1]; //наскільки змінився баланс на відрізку після інверсії

if (first_part[n] + shift == 0 && suff_min_bal[r + 1] + shift >= 0) {
    cout << "possible\n";
    return 0;}}}

    cout << "impossible\n";
    return 0;
}
