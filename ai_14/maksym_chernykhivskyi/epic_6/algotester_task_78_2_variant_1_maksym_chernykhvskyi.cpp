/*Epic 6 - lab 78v1_2
Чернихівський Максим
Ші - 14*/

#include <iostream>
#include <cstring>

using namespace std;

class DoubleLinkedList {
    private:
        struct Node {
            int value;
            Node *prev;
            Node *next;
            Node(const int &v) : value(v), prev(nullptr), next(nullptr) {}
        };
        
        Node *head;
        Node *tail;
        int count;
        
        // Повертає вузол за індексом, іде з кінця що ближче
        Node *nodeAt(int index) const {
            Node *p;
            if (index < count / 2) {
                p = head;
                for (int i = 0; i < index; i++){
                    p = p -> next;
                }
            } else {
                p = tail;
                for (int i = count - 1; i > index; i--){
                    p = p -> prev;
                }
            }
            return p;
        }
        
        // Вставляє нове значення перед pos, якщо pos = nullptr, додає в кінець
        void insertBefore(Node *pos, const int &value) {
            Node *node = new Node(value);
            node -> next = pos;
            node -> prev = (pos != nullptr) ? pos -> prev : tail;
            
            if (node -> prev != nullptr){
                node -> prev -> next = node;
            } else {
                head = node;
            }
            if (node -> next != nullptr){
                node -> next -> prev = node;
            } else {
                tail = node;
            }
            
            count++;
        }
        
        // Вилучає вузол зі списку
        void unlink(Node *p) {
            if (p -> prev != nullptr){
                p -> prev -> next = p -> next;
            } else {
                head = p -> next;
            }
            if (p -> next != nullptr){
                p -> next -> prev = p -> prev;
            } else {
                tail = p -> prev;
            }
            delete p;
            count--;
        }

public:
    // Конструктор, створює порожній список
    DoubleLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    
    // Деструктор, звільняє всю пам'ять, викликається сам коли об'єкт перестає існувати
    ~DoubleLinkedList() {
        clear();
    }

    // Метод що повертає кількість елементів
    int size() const {
        return count;
    }
    
    // Видаляє всі вузли списку
    void clear() {
        while (head != nullptr){
            Node *next = head -> next;
            delete head;
            head = next;
        }
        tail = nullptr;
        count = 0;
    }
    
    // Вставляє n значень з масиву values починаючи з позиції index
    void insert(int index, const int *values, int n){
        Node *pos = (index < count) ? nodeAt(index) : nullptr;
        for (int i = 0; i < n; i++){
            insertBefore(pos, values[i]);
        }
    }
    
    // Видалення n елементів починаючи з позиції index
    void erase(int index, int n) {
        Node *p = nodeAt(index);
        for (int i = 0; i < n; i++){
            Node *next = p -> next;
            unlink(p);
            p = next;
        }
    }
    
    // Читає значення за індексом
    const int &get(int index) const {  // другий const означає що метод не змінює сам список
        return nodeAt(index) -> value;
    }
    
    // Змінює значення за індексом
    void set(int index, const int value){
        nodeAt(index) -> value = value;
    }
    
    // Вивід списку через пробіл, friend щоб бачив приватні частини head і Node
    friend ostream &operator<<(ostream &os, const DoubleLinkedList &list){
        for (Node *p = list.head; p != nullptr; p = p -> next){
            if (p != list.head){
                os << ' ';
            }
            os << p -> value;
        }
        return os;
    }
};

enum class Command { INSERT, ERASE, SIZE, GET, SET, PRINT, UNKNOWN };

Command parseCommand(const char *word){
    if (strcmp(word, "insert") == 0) return Command::INSERT;
    if (strcmp(word, "erase") == 0) return Command::ERASE;
    if (strcmp(word, "size") == 0) return Command::SIZE;
    if (strcmp(word, "get") == 0) return Command::GET;
    if (strcmp(word, "set") == 0) return Command::SET;
    if (strcmp(word, "print") == 0) return Command::PRINT;
    return Command::UNKNOWN;
}

int main() {
    DoubleLinkedList list;
    int q;
    cin >> q;
    
    for (int i = 0; i < q; i++){
        char word[16];
        cin >> word;
        
        switch (parseCommand(word)) {
            case Command::INSERT: {
                int index, n;
                cin >> index >> n;
                int *values = new int[n > 0 ? n : 1];
                for (int j = 0; j < n; j++){
                    cin >> values[j];
                }
                list.insert(index, values, n);
                delete[] values;
                break;
            }
            case Command::ERASE: {
                int index, n;
                cin >> index >> n;
                list.erase(index, n);
                break;
            }
            case Command::SIZE: {
                cout << list.size() << "\n";    
                break;
            }
            case Command::GET: {
                int index;
                cin >> index;
                cout << list.get(index) << "\n";
                break;
            }
            case Command::SET: {
                int index, value;
                cin >> index >> value;
                list. set(index, value);
                break;
            }
            case Command::PRINT: {
                cout << list << "\n";
                break;
            }
            default: 
                break;
        }
    }
    return 0;
}