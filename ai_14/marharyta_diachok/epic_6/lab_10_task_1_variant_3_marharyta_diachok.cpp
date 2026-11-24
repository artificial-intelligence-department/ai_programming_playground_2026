/*  
Задача: Lab 10. Варіант №3.  
Автор: Дячок Маргарита. 
Група: ШІ-14 
*/ 

#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* next;};

Node* createList(int n) {
    Node* head = nullptr;
    Node* tail = nullptr;

for (int i = 0; i < n; i++) {
    Node* newNode = new Node;
    cout << "Введіть значення " << i + 1 << "-го елемента: ";
    cin >> newNode->key;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = tail = newNode;} 
    else {
        tail->next = newNode;
        tail = newNode;}}

    return head;}

void printList(Node* head) {
    if (head == nullptr) {
        cout << "Список порожній." << endl;
        return;}

Node* cur = head;
while (cur != nullptr) {
    cout << cur->key << " ";
    cur = cur->next;}
    cout << endl;}

Node* deleteKElements(Node* head, int start_pos, int k) {
    if (head == nullptr || start_pos < 1 || k <= 0) {
        cout << "Некоректні параметри або список порожній." << endl;
        return head;}

Node* current = head;
Node* prev = nullptr;

for (int i = 1; i < start_pos && current != nullptr; i++) {
        prev = current;
        current = current->next;}

if (current == nullptr) {
    cout << "Початковий номер перевищує розмір списку." << endl;
    return head;}

for (int i = 0; i < k && current != nullptr; i++) {
    Node* temp = current;
    current = current->next;
    delete temp;}

if (prev == nullptr) { // Відновлення зв'язків
    head = current;} 
    else prev->next = current;

    return head;}

Node* insertBeforeKey(Node* head, int target_key, int new_value) {
if (head == nullptr) {
    cout << "Список порожній. Елемент з ключем " << target_key << " не знайдено." << endl;
    return nullptr;}

Node* newNode = new Node;
    newNode->key = new_value;

if (head->key == target_key) {
    newNode->next = head;
    return newNode;}

Node* current = head;
while (current->next != nullptr && current->next->key != target_key) current = current->next;

if (current->next == nullptr) {
    cout << "Елемент із ключем " << target_key << " не знайдено." << endl;
    delete newNode;} 
    
else {
    newNode->next = current->next;
    current->next = newNode;}
    return head;}

Node* destroyList(Node* head) {
Node* current = head;
while (current != nullptr) {
    Node* next = current->next;
    delete current;
    current = next;}
    
cout << "Список повністю знищено." << endl;
return nullptr;}

int main() {
int n;
int start_pos;
int k; 
int target_key;
int new_value;

cout << "Введіть кількість елементів списку: ";
cin >> n;
Node* head = createList(n);

cout << "Початковий список: ";
printList(head);


cout << "\nВведіть номер початкового елемента (від 1) та кількість елементів K для видалення: ";
cin >> start_pos >> k;
head = deleteKElements(head, start_pos, k);

cout << "Список після видалення: ";
printList(head);

cout << "\nВведіть ключ, перед яким вставити елемент, та значення нового елемента: ";
cin >> target_key >> new_value;

head = insertBeforeKey(head, target_key, new_value);

cout << "Список після вставки: ";
printList(head);
cout << endl;

head = destroyList(head);
printList(head);

    return 0;
}
