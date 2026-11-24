#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
using namespace std;

template<typename T>
struct Stack {
    struct Node {
        T value; 
        Node *next;
        Node (const T& v, Node* n) {
            value = v;
            next = n;
        }
    };
    int count =0;
    Node *top = nullptr;
    void push(T v) {
        top = new Node(v, top);
        count++;
    }
    T pop() {
        Node* tmp = top;
        T v = tmp->value;
        top = tmp->next;
        count --;
        delete tmp;
        return v;
    }
    bool empty() {
        return (top==nullptr);
    }
    int size() {
        return count;
    }
    ~Stack() {
        while(!empty()) {
            pop();
        }
    }
};

template<typename T>
struct CircularLinkedList {
    struct Node {
        T data;
        Node* next = nullptr;
        Node(const T& v) {
            data = v;
        }
    };
    int count = 0;
    Node* head = nullptr;
    Node* current = nullptr;

    bool empty() const {
        return head==nullptr;
    }

    void add(const T& v) {
        Node* temp = new Node(v);
        if(!head) {
            head = temp;
            head->next=head;
            current=temp;
        } else {
            Node * last = head;
            while (last->next!=head) {
                last = last->next;
            }
            last->next=temp;
            temp->next=head;
        }
        count++;
    }

    T* next() {
        if(empty()) {
            return nullptr;
        }
        Node* node = current;
        current = current->next;
        return &node->data;
    }

    void clear() {
        if(!head) return;
        Node* p =head->next;
        while(p!=head) {
            Node* t = p;
            p = p->next;
            delete t;
        }
        delete head;
        head=nullptr;
        current=nullptr;
        count=0;
    }

    ~CircularLinkedList() {
        clear();
    }
};

template<typename T>
struct PriorityQueue {
    struct Node {
        int priority;
        T data;
        Node* next=nullptr;
        Node(int p, const T& d, Node* n) {
            priority = p;
            data = d;
            next=n;
        }
    };

    Node* head = nullptr;
    int count = 0;

    bool empty() const {
        return head==nullptr;
    }

    int size() const {
        return count;
    }

    void add(int pr, T value) {
        Node** cur = &head;
        while(*cur && (*cur)->priority >= pr) {
            cur= &(*cur)->next;
        }
        *cur = new Node (pr, value, *cur);

        count++;

    }

    T pop() {
        Node* tmp = head;
        T val = tmp->data;
        head = head->next;
        count--;
        delete tmp;
        return val;
    }

    bool remove(T target) {
        Node** curr = &head;
        while (*curr) {
            if ((*curr)->data == target) {
                Node* tmp = *curr;
                *curr = tmp->next;
                delete tmp;
                count--;
                return true;
            }
            curr = &(*curr)->next;
        }
        return false;
    }


    void clear() {
        Node *p = head;
        while(p!=nullptr) {
            Node* temp = p;
            p=p->next;
            delete temp;
        }
        head=nullptr;
        count = 0;
    }

    ~PriorityQueue() {
        clear();
    }
};

template<typename T>
struct DoubleLinkedList {
    struct Node {
        T data;
        Node* prev = nullptr;
        Node* next = nullptr;
        Node (const T& v, Node* p, Node* n) {
            data = v;
            prev=p;
            next=n;
        }
    };

    int count =0;
    Node* head = nullptr;
    Node* tail = nullptr;

    int size () const {
        return count;
    }

    bool empty() const{
        return head==nullptr;
    }

    void clear() {
        Node* p = head;
        while(p) {
            Node *tmp = p;
            p=p->next;
            delete tmp;
        }
        count=0;
        head = nullptr;
        tail = nullptr;
    }

    void removeNode(Node* node) {
        if(!node) return;
        Node* p = node->prev;
        Node* n= node->next;
        if(p!=nullptr) {
            p->next = n;
        } else {
            head = n;
        }
        if(n!=nullptr) {
            n->prev  = p;
        } else {
            tail = p;
        }
        delete node;
        count --;
    }

    T* pushBack(const T& v) {
        Node* node = new Node(v, tail, nullptr);
        if(!tail) {
            head=tail=node;
        } else {
            tail->next=node;
            tail = node;
        }
        count ++;
        return &tail->data;
    }

    ~DoubleLinkedList() {
        clear();
    }
};

enum class DeviceType {
    PHONE = 1, 
    LAPTOP,
    TV
};

enum class Status {
    WAITING, 
    REPAIR,
    DONE
};

enum class ActionType {
    ADD,
    REMOVE
};

struct Money {
    int hrn;
    int kop;
};

struct Date {
    int day;
    int month;
    int year;
};

struct Client {
    char name[16]; 
    char phone[11];
};

union DeviceInfo {
    int imei;
    char serial[12];
    int inches;
};

struct Order {
    int id;
    Client client;
    Date date;
    DeviceType type;
    DeviceInfo info;
    char problem[81];
    int priority;
    Money price;
    Status status;
    char master[24];
};

struct Action
{
    ActionType type;
    Order order;
};

struct Master {
    char name[24];
    int completed =0;
    Money revenue = {0, 0};
};

long long toKop(const Money& m) {
    return (long long) m.hrn*100+m.kop;
}

Money fromKop(long long total) {
    Money res;
    res.hrn = (int)(total/100);
    res.kop = (int)(total%100);
    return res;
}

Money operator+(const Money&a, const Money&b) {
    return fromKop(toKop(a) + toKop(b));
}

Money operator-(const Money&a, const Money&b) {
    return fromKop(toKop(a) - toKop(b));
}

Money operator*(const Money&a, int k) {
    return fromKop(toKop(a)* k);
}

bool operator <(const Money&a, const Money&b) {
    return toKop(a) < toKop(b);
}

bool operator >(const Money&a, const Money&b) {
    return toKop(a) > toKop(b);
}

bool operator ==(const Money&a, const Money&b) {
    return toKop(a) == toKop(b);
}

ostream& operator <<(ostream& os, const Money&a) {
    char buff[32];
    sprintf(buff, "%d.%02d", a.hrn, a.kop);
    os << buff;
    return os;
}

void freeWords(char** words, int n) {
    for (int i=0; i<n; i++) {
        delete[] words[i];
    }
    delete[] words;
}

bool isValidName(char* str) {
    if(strlen(str)==0) {
        return false;
    }
    for(int i=0; i<strlen(str); i++) {
        if (!isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

bool isValidNumber(char* str) {
    if(strlen(str)!=10 or str[0]!='0') {
        return false;
    }
    for(int i=0; i<strlen(str); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool isValidIMEI(char* str) {
    if(strlen(str)!=6) {
        return false;
    }
    for(int i=0; i<strlen(str); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool isValidSerial(char* str) {
    if (strlen(str)==0) {
        return false;
    }
    for(int i=0; i<strlen(str); i++) {
        if (!isdigit(str[i]) && !isupper(str[i])) {
            return false;
        }
    }
    return true;
}

bool isValidNames(const char* names, int n, char**& masters) {
    
    char** words = new char*[n];
    for (int i =0; i<n; i++) {
        words[i]=new char[24];

    }

    int count = 0;
    int len = 0;
    size_t totalLen = strlen(names);

    for(size_t i=0; i<=totalLen; i++) {
        char c = names[i];
        if (c==' ' || c=='\0') {
            if(len>0) {
                words[count][len] = '\0';


                for (int j = 0; j<count; j++) {
                    if (strcmp(words[j], words[count]) == 0) {
                        freeWords(words, n);
                        return false;
                    }
                }

                count++;
                len=0;
            }
        } else {
            if(count >=n || len>=23) {
                freeWords(words, n);
                return false;
            }

            if (!isalpha(c)) {
                freeWords(words, n);
                return false;
            }
            words[count][len] = c;
            len++;
        }
    }
    if(count!=n) {
        freeWords(words, n);
        return false;
    }
    masters= words;
    return count == n;

}

bool isValidDate(char*str) {
    if(strlen(str)!=10) {
        return false;
    }
    for (int i =0; i<strlen(str); i++) {
        if (!isdigit(str[i]) and i!=2 and i!=5) {
            return false;
        }
    }
    if(str[2]!='.' || str[5]!='.') {
        return false;
    }
    int day = (int)(str[0]-'0')*10+(int)(str[1]-'0');
    int month  = (int)(str[3]-'0')*10+(int)(str[4]-'0');
    int year =  (int)(str[6]-'0')*1000+(int)(str[7]-'0')*100+(int)(str[8]-'0')*10+(int)(str[9]-'0');
    if(year <2000 || year>2099) {
        return false;
    }
    if(month < 1 || month > 12) {
        return false;
    }
    int vysok = 0;
    if(year%4==0) {
        vysok++;
    }
    if(day==0) {
        return false;
    }
    bool valid = true;
    switch (month) {
        case 1: {
            valid = (day<=31);
            break;
        }
        case 2: {
            valid = (day<=28+vysok);
            break;
        }
        case 3: {
            valid = (day<=31);
             break;
        }
        case 4: {
            valid = (day<=30);
             break;
        }
        case 5: {
            valid = (day<=31);
             break;
        }
        case 6: {
            valid = (day<=30);
             break;
        }
        case 7: {
            valid = (day<=31);
             break;
        }
        case 8: {
            valid = (day<=31);
             break;
        }
        case 9: {
            valid = (day<=30);
             break;
        }
        case 10: {
            valid = (day<=31);
             break;
        }
        case 11: {
            valid = (day<=30);
             break;
        }
        case 12: {
            valid = (day<=31);
             break;
        }
    }
    return valid;

}

bool parseKop(const char* s, long long& kop) {
    if(!s || s[0]=='\0') return false;
    const char* dot = strchr(s, '.');
    int intLen = dot ? (int)(dot-s) : (int)(strlen(s));
    if(intLen<1 || intLen > 6) return false;
    long long hrn =0, k=0;
    for (int i =0; i<intLen; i++) {
        if(!isdigit(s[i])) return false;
        hrn = hrn*10 + (s[i]-'0');
    }
    if(dot) {
        int fracLen = (int)strlen(dot+1);
        if (fracLen < 1 || fracLen > 2) return false;
        for (int i =1; i<=fracLen; i++) {
            if(!isdigit(dot[i])) return false;
            k=k*10 + (dot[i]-'0');
        }
        if(fracLen == 1) k*=10;
    }
    kop = hrn*100 + k;
    return true;
}

bool evalRPN(const char *expr, Money &res) {
    Stack<long long> st;
    int i =0;
    bool hasTokens = false;
    while(expr[i]!='\0') {
        while (expr[i] == ' ') {
            i++;
        }
        if(expr[i]=='\0') break;

        char tok[64];
        int len =0;
        while(expr[i] != '\0' && expr[i] != ' ') {
            if (len<63) tok[len++] = expr[i];
            i++;
        }

        tok[len] = '\0';
        hasTokens = true;

        if (len == 1 && (tok[0] =='+' || tok[0] == '-' || tok[0] == '*')) {
            if(st.size() < 2) {
                cout << "Помилка у виразі: для операції \"" << tok[0] << "/' бракує чисел."<< endl;
                return false;
            }
        
            long long b = st.pop();
            long long a = st.pop();
            long long step =0;
            if (tok[0] == '+') {
                step = a+b;
            } else if (tok[0]=='-') {
                step = a-b;
                if (step<0) {
                    cout << "Помилка у виразі: проміжний результат від'ємний."<<endl;
                    return false;
                }
            } else {
                if (b%100!=0 || b/100 <1 || b/100>100) {
                    cout << "Помилка: множник має бути цілим числом від 1 до 100."<<endl;
                    return false;
                }
                step = a *(b/100);
            }

            if(step > 10000000) {
                cout << "Помилка у виразі: сума перевищує 100 000 грн." << endl;
                return false;
            }
            st.push(step);
        } else {
            long long value = 0;
            if(!parseKop(tok, value)) {
                cout << "Помилка у виразі: \""<< tok << "\" не є числом або операцією." << endl;
                return false;
            }
            if(value > 10000000) {
                cout << "Помилка у виразі: сума перевищує 100 000 грн." << endl;
                return false;
            }
            st.push(value);
        }
    }
    if(!hasTokens) {
        cout << "Помилка у виразі: порожній вираз." << endl;
        return false;
    }
    if (st.size()!=1) {
        cout << "Помилка у виразі: у стеку залишилось чисел: " << st.size() << endl;
        return false;
    }
    long long total = st.pop();
    if (total == 0) {
        cout << "Помилка у виразі: кінцевий результат не може дорвнювати 0.00 грн."<< endl;
        return false;

    }
    res = fromKop(total);
    return true;
}

void addOrder(DoubleLinkedList<Order> &journal, PriorityQueue<Order*>& queue, Stack<Action>& history, int& nextId) {
    Order order;
    order.id = nextId;
    order.status = Status::WAITING;
    order.master[0] = '\0';

    cout << "Ім'я клієнта: ";
    char name[16];
    cin.clear();
    cin.ignore(10000, '\n');
    cin.getline(name, 16);
    if(cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Некоректний ввід" << endl;
        return;
    }
    if(!isValidName(name)) {
        cout << "Некоректний ввід" << endl;
        return;
    }


    cout << "Телефон (10 цифр): ";
    char telephone[11];
    cin.getline(telephone, 11);
    if(cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Некоректний ввід" << endl;
        return;
    }
    if(!isValidNumber(telephone)) {
        cout << "Некоректний ввід" << endl;
        return;
    }

    
    cout << "Дата прийому (ДД.ММ.РРРР): ";
    char date[11];
    cin.getline(date, 11);
    if(cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Некоректний ввід" << endl;
        return;
    }
    if(!isValidDate(date)) {
        cout << "Некоректний ввід" << endl;
        return;
    }
    int day = (int)(date[0]-'0')*10+(int)(date[1]-'0');
    int month  = (int)(date[3]-'0')*10+(int)(date[4]-'0');
    int year =  (int)(date[6]-'0')*1000+(int)(date[7]-'0')*100+(int)(date[8]-'0')*10+(int)(date[9]-'0');
    strcpy(order.client.name, name);
    strcpy(order.client.phone, telephone);
    order.date = {day, month, year};
    
    cout << "Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ";
    int type;
    cin >> type;
    if(cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Некоректний ввід типу пристрою." << endl;
        return;
    }
    if(type!= 1 && type!=2 && type!=3) {
        cout << "Некоректний ввід типу пристрою." << endl;
        return;
    }
    order.type = (DeviceType)(type);
    switch (type) {
        case 1: {
            cout << "Останні 6 цифр IMEI: ";
            char IMEI[7];
            cin.clear();
            cin.ignore(10000, '\n');
            cin.getline(IMEI, 7);
            if(cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Помилка: потрібно рівно 6 цифр." << endl;
                return;
            }
            if(!isValidIMEI(IMEI)) {
                cout << "Помилка: потрібно рівно 6 цифр." << endl;
                return;
            }
            int imei = 0;
            for (int i =0; i<6; i++) {
                imei = imei*10 + (IMEI[i]-'0');
            }
            order.info.imei=imei;
            break;
        }
        case 2: {
            cout << "Серійний номер: ";
            char Serial[12];
            cin.clear();
            cin.ignore(10000, '\n');
            cin.getline(Serial, 12);
            if(cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Помилка: потрібно 11 символів латинські букви чи цифри." << endl;
                return;
            }
            if(!isValidSerial(Serial)) {
                cout << "Помилка: потрібно 11 символів латинські букви чи цифри." << endl;
                return;
            }
            strcpy(order.info.serial, Serial);
            break;
            
        }
        case 3: {
            cout << "Діагональ (inch): ";
            cin.clear();
            cin.ignore(10000, '\n');
            int inch;
            cin >> inch;
            cin.ignore(10000, '\n');
            if(cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Помилка: діагональ - число від 19 до 100 дюймів." << endl;
                return;
            }
            if (inch<19 || inch>100) {
                cout << "Помилка: діагональ - число від 19 до 100 дюймів." << endl;
                return;
            }
            
            order.info.inches=inch;
            break;
        }
    }

    cout << "Опис несправності: ";
    if(!cin.getline(order.problem, 81)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Некоректний ввід опису несправності." << endl;
        return;
    }
    if(strlen(order.problem) == 0) {
        cout << "Некоректний ввід опису несправності." << endl;
        return;
    }

    cout << "Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ";
    int pr;
    cin >> pr;
    if(cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка: пріоритет - число від 1 до 3." << endl;
        return;
    }
    if(pr!=1 && pr!=2 && pr!=3) {
        cout << "Помилка: пріоритет - число від 1 до 3." << endl;
        return;
    }
    order.priority=pr;

    cout << "Вартість (обернений польський запис): ";
    char pln[256];
    cin.clear();
    cin.ignore(10000, '\n');
    if(!cin.getline(pln, 256)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка: задвогий вираз польського запису." << endl;
        return;
    }
    if(!evalRPN(pln, order.price)) {
        return;
    }
    Order* savedPtr = journal.pushBack(order);
    queue.add(order.priority, savedPtr);
    history.push({ActionType::ADD, order});
    nextId++;

    cout << "Замовлення №" << order.id << " додано: вартість " << order.price << "грн, у черзі на ремонт: "<<queue.size() << "." << endl;
}

void addMasters(CircularLinkedList<Master>& list, char**& master, int n) {
    for (int i =0; i<n; i++) {
        Master m;
        strcpy(m.name, master[i]);
        list.add(m);

    }
}

ostream& operator<<(ostream&os, const Order& o) {
    char dateBuf[16];
    sprintf(dateBuf, "%02d.%02d.%04d", o.date.day, o.date.month, o.date.year);

    const char* typeStr="";
    char detailsBuf[24];
    if(o.type == DeviceType::PHONE) {
        typeStr="PHONE";
        sprintf(detailsBuf, "IMEI %06d", o.info.imei);
    } else if (o.type == DeviceType::LAPTOP) {
        typeStr="LAPTOP";
        sprintf(detailsBuf,"SN %s", o.info.serial);
    } else {
        typeStr="TV";
        sprintf(detailsBuf, "%d inch", o.info.inches);
    }

    const char* statusStr ="";
    if (o.status == Status::WAITING) {
        statusStr="WAITING";
    } else if (o.status == Status::REPAIR) {
        statusStr = "REPAIR";
    } else {
        statusStr = "DONE";
    }

    char priceBuf[24];
    sprintf(priceBuf, "%d.%02d", o.price.hrn, o.price.kop);

    os << "| " << right << setw(3) << o.id << " | " << left << setw(15) << o.client.name
    << " | " << left << setw(10) << o.client.phone << " | "  << left << setw(10) << dateBuf << " | "
    << setw(6) << typeStr << " | " << left << setw(14) << detailsBuf << " | " << right << setw(2) << o.priority <<
    " | " << left << setw(7) << statusStr << " | " << right << setw(9) << priceBuf << " |"<< left;
    return os;
}

void printJournal(const DoubleLinkedList<Order>& journal, const PriorityQueue<Order*>& queue) {
    if(journal.empty()) {
        cout << "Журнал замовлень порожній." << endl;
        return;
    }
    const char* border = "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+";
    cout << border << endl;
    cout << "|   № | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  |  Вартість |" << endl;
    cout << border << endl;

    DoubleLinkedList<Order>::Node* curr = journal.head;
    while(curr != nullptr) {
        cout << curr->data << endl;
        curr = curr->next;
    }
    cout << border << endl;
    cout << "Усього замовлень: " << journal.size() << endl;
    cout << "У черзі на ремонт: " << queue.size() << endl;
}

void assignToMaster(PriorityQueue<Order*>& queue, CircularLinkedList<Master>& masters) {
    if (queue.empty()) {
        cout << "Черга на ремонт порожня. " << endl;
        return;
    }
    Order* order = queue.pop();
    Master* m = masters.next();
    order->status=Status::REPAIR;
    strcpy(order->master, m->name);
    cout << "Замовлення №" << order->id << " (пріоритет "<<order->priority << ") передано майстру "<< order->master << "." << endl;
    printf("Несправність: %s\n", order->problem);
    cout << "У черзі залишилось: "<< queue.size() << endl;
}

DoubleLinkedList<Order>::Node* findById(const DoubleLinkedList<Order>& list, int id) {
    DoubleLinkedList<Order>::Node* tmp = list.head;
    while(tmp) {
        if(tmp->data.id==id) {
            return tmp;
        }
        tmp=tmp->next;
    }
    return nullptr;

}

void finishRepair(const DoubleLinkedList<Order>& list, CircularLinkedList<Master>& masters) {
    cout << "Номер замовлення: ";
    int rep_id;
    cin.ignore(10000, '\n');
    cin >> rep_id;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ви ввели некоректне id." << endl;
        return;
    }
    DoubleLinkedList<Order>::Node* node = findById(list, rep_id);
    if (!node) {
        cout << "Немає такого замовлення." << endl;
        return;
    }
    if(node->data.status == Status::WAITING) {
        cout << "Замовлення №"<<rep_id << " ще не передано майстру."<<endl;
        return;
    } else if(node->data.status == Status::DONE) {
        cout << "Замовлення №"<<rep_id << " уже завершено."<<endl;
        return;
    } else {
        CircularLinkedList<Master>::Node* p = masters.head;
        do {
            if (strcmp(p->data.name, node->data.master)==0) {
                p->data.completed++;
                p->data.revenue = p->data.revenue + node->data.price;
                cout << "Ремонт №" << rep_id << " щойно завершено. Майстер "<<p->data.name << ": виконано " << p->data.completed << ", виручка "<< p->data.revenue << " грн."<< endl;
                break;
            } 
            p=p->next;
        } while (p!=masters.head);
        node->data.status = Status::DONE;
    }

}

void deleteOrder(DoubleLinkedList<Order>& list, PriorityQueue<Order*>& queue, Stack<Action> &history) {
    cout << "Номер замовлення: ";
    int id;
    cin.ignore(10000, '\n');
    cin >> id;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Неправильний номер замовлення. "<< endl;
        return;
    }
    DoubleLinkedList<Order>::Node* node = findById(list, id);
    if(!node) {
        cout << "Замовлення №" << id <<" не знайдено."<<endl;
        return;
    }
    if(node->data.status!=Status::WAITING) {
        cout << "Видалити можна лише замовлення, яке очікує в черзі."<<endl;
        return;
    }
    Order copy = node->data;
    queue.remove(&node->data);
    list.removeNode(node);
    history.push({ActionType::REMOVE, copy});
    cout << "Замовлення №" << copy.id << " видалено. У журналі: " << list.size() << ", у черзі: "<< queue.size() << endl;


}

void UndoAction(DoubleLinkedList<Order>& journal, PriorityQueue<Order*>& queue, Stack<Action>& history) {
    if(history.empty()) {
        cout << "Історія дій пуста. Немає дій для скасування."  << endl;
        return;
    }
    Action action = history.pop();
    if(action.type == ActionType::ADD) {
        DoubleLinkedList<Order>::Node* node = findById(journal, action.order.id);
        if(!node or node->data.status!=Status::WAITING) {
            cout << "Додавання замовлення №"<< action.order.id << "неможливо скасувати: його вже передано майстру." << endl;
            return;
        }
        queue.remove(&node->data);
        journal.removeNode(node);
        cout << "Скасовано додавання замовлення №" << action.order.id<<endl;
        
    } else {
        Order* ord = journal.pushBack(action.order);
        queue.add(action.order.priority, ord);
        cout << "Скасовано видалення замовлення №" << action.order.id << ": повернуто в журнал та чергу." << endl;
    }
}

void revJournal(DoubleLinkedList<Order> &journal) {
    if (journal.empty()) {
        cout << "Неможливо розвернути порожній жжурнал."<<endl;
        return;
    }
    DoubleLinkedList<Order>::Node* temp = journal.head;
    while (temp) {
         DoubleLinkedList<Order>::Node* curr = temp->next;
         temp->next = temp->prev;
         temp->prev = curr;
         temp = curr;
    }
    temp = journal.head;
    journal.head = journal.tail;
    journal.tail = temp;

    cout << "Журнал розвернуто. Тепер першим іде замовлення №" << journal.head->data.id << ", останнім № " << journal.tail->data.id << endl;
}

Money totalRevenue(DoubleLinkedList<Order>::Node*p) {
    if (p==nullptr) {
        return {0, 0};
    }
    Money res = totalRevenue(p->next);
    if(p->data.status == Status::DONE) {
        return p->data.price + res;
    }
    return res;

}

void report (const DoubleLinkedList<Order> &journal, CircularLinkedList<Master>& masters) {
    if(journal.empty()) {
        cout << "Ще немає замовлень для звіту."<<endl;
        return;
    }
    int size = journal.size();
    Order** arr = new Order*[size];
    DoubleLinkedList<Order>::Node* curr  =journal.head;
    for (int i =0; i<size; i++) {
        arr[i] = &curr->data;
        curr = curr->next;
    }

    for (int i =0; i<size; i++) {
        for (int j=0; j<size-i-1; j++) {
            if(arr[j]->price<arr[j+1]->price) {
                Order* tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j]=tmp;
            } else if(arr[j]->price == arr[j+1]->price) {
                if(arr[j]->id>arr[j+1]->id) {
                    Order* tmp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j]=tmp;
                }
            }
        }
    }
    cout << "Замовлення за вартістю:" << endl;
    for (int i =0; i<size; i++) {
        const char* str = "";
        if(arr[i]->status==Status::DONE) {
            str="DONE";
        } else if(arr[i]->status==Status::WAITING) {
            str="WAITING";
        }  else {
            str = "REPAIR";
        }
        cout << " №" << arr[i]->id << "    " << arr[i]->price << "грн. "<<"   "<< str << endl;
    }
        cout << "Різниця між найдорожчим і найдешевшим: " << arr[0]->price - arr[size-1]->price << " грн"<<endl;
        cout << "Виручка за завершеними ремонтами: " << totalRevenue(journal.head)<< "грн. "<<endl;

        cout << "Майстри, починаючи з наступного в черзі:" << endl;
        CircularLinkedList<Master>::Node* m  = masters.current;
        do  {
            cout << " " << left << setw(12) << m->data.name << " виконано: " << m->data.completed << ", виручка: " << m->data.revenue << " грн." << endl;
            m= m->next;
        } while (m!= masters.current);
        
        delete[] arr;

}

int main(){
    int n;
    while(true) {
        cout << "Кількість майстрів (від 1 до 5): ";
        if(!(cin>>n) || n<1 || n>5 || cin.peek() !='\n') {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ви ввели некоректну кількість майстрів. Це повинно бути число від 1 до 5."<< endl;
        } else break;
    }
    cin.ignore(10000, '\n');

    cout << "Імена майстрів через пробіл: ";
    char names[256];
    char** masters  = nullptr;

    cin.getline(names, 256);
    if (cin.fail()) {
        cout << "Рядок занадто довгий!" << endl;
        return  1;
    } else {
        if (!isValidNames(names, n, masters)) {
            cout << "Ви ввели неправильні імена майстрів!" << endl;
            return 1;
        } 
    }
    

    DoubleLinkedList<Order> journal;
    PriorityQueue<Order*> repairQueue;
    Stack<Action> history;
    CircularLinkedList<Master> masterss;
    addMasters(masterss, masters, n);
    freeWords(masters, n);
    int nextId = 101;

    int choice = -1;
    while (choice != 0) {
        cout << "==== -=- MENU -=- ====\n";
        cout << "1 - Додати замовлення\n2 - Журнал замовлень\n3 - Видати замовлення майстру\n4 - Завершити ремонт\n5 - Видалити замовлення\n6 - Скасувати останню дію\n7 - Звіт\n8 - Розвернути журнал\n0 - Вийти\n";
        cout << "Зробіть свій вибір: ";
        if(!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка: введіть номер пункту меню."<<endl;
            continue;
        }
        switch (choice) {
            case 1: {
                addOrder(journal, repairQueue, history, nextId);
                break;
            
            }
            case 2: {
                printJournal(journal, repairQueue);
                break;
            }
            case 3: {
                assignToMaster(repairQueue, masterss);
                break;
            }
            case 4: {
                finishRepair(journal, masterss);
                break;
            }
            case 5: {
                deleteOrder(journal, repairQueue, history);
                break;
            }
            case 6: {
                UndoAction(journal, repairQueue, history);
                break;
            }
            case 7: {
                report(journal, masterss);
                break;
            }
            case 8: {
                revJournal(journal);
                break;
            }
            case 0: {
                
                break;
            }
            default: {
                cout << "Помилка: пункту "<< choice << " немає в меню."<< endl;
                break;
            }
        }

    }
    cout << "Дякуємо за використання нашої програми!" << endl;
    return 0;
    
    


    
}

