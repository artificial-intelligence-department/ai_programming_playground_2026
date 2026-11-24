#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;


enum class DeviceType { PHONE = 1, LAPTOP, TV };

enum class Status { WAITING, REPAIR, DONE };

struct Money { int hrn; int kop; };

Money operator+(const Money& a, const Money& b){
    Money tmp{0,0};
    tmp.hrn=b.hrn+a.hrn;
    tmp.kop=b.kop+a.kop;
    if(tmp.kop>=100){
        tmp.hrn++;
        tmp.kop-=100;
    }
    return tmp;
}
Money operator-(const Money& a, const Money& b){
    Money tmp{0,0};
    tmp.hrn=a.hrn-b.hrn;
    tmp.kop=a.kop-b.kop;
    if(tmp.kop < 0){
        tmp.hrn--;
        tmp.kop+=100;
    }
    return tmp;
}

Money operator*(const Money& m, int k){
    Money tmp{0,0};
    tmp.hrn=m.hrn*k;
    tmp.kop=m.kop*k;
    while(tmp.kop>=100){
        tmp.hrn++;
        tmp.kop-=100;
    }
    return tmp;
}

bool operator<(const Money& a, const Money& b){
    if(a.hrn < b.hrn){
        return true;
    }
    if(a.hrn == b.hrn){
        if(a.kop < b.kop){
            return true;
        }
    }
    return false;
}

ostream& operator<<(std::ostream& os, const Money& m){
    char buf[32];
    sprintf(buf, "%d.%02d", m.hrn, m.kop);
    return os << buf;
}


struct Date{
    int day;
    int month;
    int year;
};

struct Client{
    char name[16];
    char phone[11];
};

union DeviceInfo { int imei; char serial[12]; int inches; };


struct Order{
    int id;
    Client client;
    Date date;
    DeviceType type;
    DeviceInfo info;
    Status status;
    char problem[81];
    int priority;
    Money price;
    char master[24];
};
ostream& operator<<(std::ostream& os, const Order& m){
    char order[256];
    char details[32];
    char priceStr[16];
    char typeStr[7];
    char statusStr[8];
    switch(m.type){
        case DeviceType::PHONE:
        sprintf(details, "IMEI %06d", m.info.imei);
        strcpy(typeStr,"PHONE");
        break;
        case DeviceType::LAPTOP:
        sprintf(details, "SN %s", m.info.serial);
        strcpy(typeStr,"LAPTOP");
        break;
        case DeviceType::TV:
        sprintf(details, "%d inch", m.info.inches);
        strcpy(typeStr,"TV");
        break;
    }
    switch(m.status){
        case Status::WAITING:
        strcpy(statusStr, "WAITING");
        break;
        case Status::REPAIR:
        strcpy(statusStr, "REPAIR");
        break;
        case Status::DONE:
        strcpy(statusStr, "DONE");
        break;
    }

    sprintf(priceStr, "%d.%02d", m.price.hrn, m.price.kop);

    sprintf(order, "| %3d | %-15s | %-10s | %02d.%02d.%04d | %-6s | %-14s | %2d | %-7s | %9s |", 
    m.id, m.client.name, m.client.phone, m.date.day, m.date.month, m.date.year, typeStr, details, m.priority, statusStr, priceStr);
    return os << order;
}

struct OrderNode{
    Order data;
    OrderNode* prev;
    OrderNode* next;
};

struct OrderList{
    int size=0;
    OrderNode* head = nullptr;
    OrderNode* tail = nullptr;
};

struct QNode{
    Order* order;
    QNode* next;
};

struct OrderQueue {
    QNode* head = nullptr;
    int size = 0;
};

struct Master{
    char name[24];
    int doneCount;
    Money revenue;
    Master* next;
};

enum class ActionType { ADD, DELETE };

struct Action {
    ActionType type;
    Order order;
    Action* next;
};


OrderNode* appendOrder(OrderList& list, const Order& o){
    if(list.head==nullptr){
        list.head= new OrderNode{o,nullptr,nullptr};
        list.tail=list.head;
    }
    else{
        list.tail= new OrderNode{o, list.tail, nullptr};
        list.tail->prev->next=list.tail;
    }
    list.size++;
    return list.tail;
}

OrderNode* findById(const OrderList& list, int id){
    for(OrderNode* i=list.head; i!=nullptr;i=i->next){
        if(i->data.id==id){
            return i;
        }
    }
    return nullptr;
}

void removeNode(OrderList& list, OrderNode* node){
    if(node==nullptr){
        return;
    }
    if( node->prev !=nullptr){
        node->prev->next=node->next;
    }
    else{
        list.head = node->next;
    }
    if(node->next !=nullptr){
        node->next->prev = node->prev;
    }
    else{
        list.tail = node->prev;
    }
    delete node;
    list.size--;
}

void reverseList(OrderList& list){
    for(OrderNode* i = list.head; i!=nullptr; i=i->prev){
        OrderNode* tmp = i->next;
        i->next=i->prev;
        i->prev=tmp;
    }
    OrderNode* tmp=list.head;
    list.head = list.tail;
    list.tail = tmp;
}

void clearList(OrderList& list){
    OrderNode* next;
    for(OrderNode* i = list.head; i!=nullptr; i=next){
        next=i->next;
        delete i;
    }
    list.head=nullptr;
    list.tail=nullptr;
    list.size=0;
}

void enqueue(OrderQueue& q, Order* order) {
    if (q.head == nullptr || order->priority > q.head->order->priority) {
        q.head = new QNode{order, q.head};
        q.size++;
        return;
    }
    QNode* cur = q.head;
    while (cur->next != nullptr && cur->next->order->priority >= order->priority) {
        cur = cur->next;
    }
    cur->next = new QNode{order, cur->next};
    q.size++;
}

void addMaster(Master*& head, const char* name) {
    Master* node = new Master;
    strcpy(node->name, name);
    node->doneCount = 0;
    node->revenue = {0, 0};

    if (head == nullptr) {
        node->next = node;
        head = node;
        return;
    }

    Master* cur = head;
    while (cur->next != head) {
        cur = cur->next;
    }
    node->next = head;
    cur->next = node;
}
void clearMasters(Master*& head) {
    if (head == nullptr) return;
    Master* cur = head->next;
    while (cur != head) {
        Master* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    delete head;
    head = nullptr;
}
void clearQueue(OrderQueue& q) {
    while (q.head != nullptr) {
        QNode* tmp = q.head;
        q.head = q.head->next;
        delete tmp;
    }
    q.size = 0;
}

void clearHistory(Action*& top) {
    while (top != nullptr) {
        Action* tmp = top;
        top = top->next;
        delete tmp;
    }
}

struct RpnNode {
    Money val;
    RpnNode* next;
};

void freeRpn(RpnNode*& top) {
    while (top != nullptr) {
        RpnNode* tmp = top;
        top = top->next;
        delete tmp;
    }
}

bool evalRPN(const char* expr, Money& res) {
    char buf[256];
    strcpy(buf, expr);

    char* tok = strtok(buf, " ");
    if (tok == nullptr) {
        cout << "Помилка у виразі: порожній вираз.\n";
        return false;
    }

    RpnNode* top = nullptr;
    Money limit{100000, 0};

    while (tok != nullptr) {
        if (strcmp(tok, "+") == 0 || strcmp(tok, "-") == 0 || strcmp(tok, "*") == 0) {
            if (top == nullptr || top->next == nullptr) {
                cout << "Помилка у виразі: для операції «" << tok << "» бракує чисел.\n";
                freeRpn(top);
                return false;
            }
            Money b = top->val;
            RpnNode* tmp = top;
            top = top->next;
            delete tmp;

            Money a = top->val;
            tmp = top;
            top = top->next;
            delete tmp;

            Money r{0, 0};
            if (tok[0] == '+') {
                r = a + b;
                if (limit < r) {
                    cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                    freeRpn(top);
                    return false;
                }
            } else if (tok[0] == '-') {
                if (a < b) {
                    cout << "Помилка у виразі: проміжний результат від'ємний.\n";
                    freeRpn(top);
                    return false;
                }
                r = a - b;
            } else {
                if (b.kop != 0 || b.hrn < 1 || b.hrn > 100) {
                    cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100.\n";
                    freeRpn(top);
                    return false;
                }
                r = a * b.hrn;
                if (limit < r) {
                    cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                    freeRpn(top);
                    return false;
                }
            }
            top = new RpnNode{r, top};
        } else {
            const char* dot = strchr(tok, '.');
            int intLen = (dot == nullptr) ? strlen(tok) : (dot - tok);
            bool numOk = (intLen >= 1 && intLen <= 6);
            for (int i = 0; numOk && i < intLen; i++) {
                if (!isdigit((unsigned char)tok[i])) numOk = false;
            }
            int fracLen = 0;
            if (numOk && dot != nullptr) {
                fracLen = strlen(dot + 1);
                if (fracLen < 1 || fracLen > 2) numOk = false;
                for (int i = 0; numOk && i < fracLen; i++) {
                    if (!isdigit((unsigned char)dot[1 + i])) numOk = false;
                }
            }
            if (!numOk) {
                cout << "Помилка у виразі: «" << tok << "» не є числом або операцією.\n";
                freeRpn(top);
                return false;
            }

            Money val{0, 0};
            for (int i = 0; i < intLen; i++) {
                val.hrn = val.hrn * 10 + (tok[i] - '0');
            }
            if (fracLen == 1) {
                val.kop = (dot[1] - '0') * 10;
            } else if (fracLen == 2) {
                val.kop = (dot[1] - '0') * 10 + (dot[2] - '0');
            }

            if (limit < val) {
                cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                freeRpn(top);
                return false;
            }
            top = new RpnNode{val, top};
        }

        tok = strtok(nullptr, " ");
    }

    int count = 0;
    for (RpnNode* p = top; p != nullptr; p = p->next) count++;
    if (count != 1) {
        cout << "Помилка у виразі: у стеку залишилось чисел: " << count << ", а має бути одне.\n";
        freeRpn(top);
        return false;
    }

    res = top->val;
    delete top;

    if (res.hrn == 0 && res.kop == 0) {
        cout << "Помилка у виразі: вартість не може дорівнювати 0.00 грн.\n";
        return false;
    }
    return true;
}
//пункт 1
void addOrder(OrderList& list, OrderQueue& q, Action*& history, int& nextId) {
    Order o{};
    char buf[256];

    cout << "Ім'я клієнта: ";
    if (!cin.getline(buf, 256)) {
        if (!cin.eof()) { cin.clear(); cin.ignore(10000, '\n'); }
        cout << "Помилка: ім'я має містити від 1 до 15 латинських літер.\n";
        return;
    }
    int len = strlen(buf);
    if (len < 1 || len > 15) {
        cout << "Помилка: ім'я має містити від 1 до 15 латинських літер.\n";
        return;
    }
    for (int i = 0; i < len; i++) {
        char c = buf[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
            cout << "Помилка: ім'я має містити від 1 до 15 латинських літер.\n";
            return;
        }
    }
    strcpy(o.client.name, buf);

    cout << "Телефон (10 цифр): ";
    if (!cin.getline(buf, 256)) {
        if (!cin.eof()) { cin.clear(); cin.ignore(10000, '\n'); }
        cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0.\n";
        return;
    }
    if (strlen(buf) != 10 || buf[0] != '0') {
        cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0.\n";
        return;
    }
    for (int i = 0; i < 10; i++) {
        if (!isdigit((unsigned char)buf[i])) {
            cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0.\n";
            return;
        }
    }
    strcpy(o.client.phone, buf);

    cout << "Дата прийому (ДД.ММ.РРРР): ";
    if (!cin.getline(buf, 256)) {
        if (!cin.eof()) { cin.clear(); cin.ignore(10000, '\n'); }
        cout << "Помилка: некоректна дата.\n";
        return;
    }
    bool dateOk = (strlen(buf) == 10 && buf[2] == '.' && buf[5] == '.');
    for (int i = 0; dateOk && i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit((unsigned char)buf[i])) dateOk = false;
    }
    if (dateOk) {
        sscanf(buf, "%d.%d.%d", &o.date.day, &o.date.month, &o.date.year);
        if (o.date.year < 2000 || o.date.year > 2099 || o.date.month < 1 || o.date.month > 12) {
            dateOk = false;
        } else {
            int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            bool leap = (o.date.year % 4 == 0 && o.date.year % 100 != 0) || (o.date.year % 400 == 0);
            int maxDay = daysInMonth[o.date.month];
            if (o.date.month == 2 && leap) maxDay = 29;
            if (o.date.day < 1 || o.date.day > maxDay) dateOk = false;
        }
    }
    if (!dateOk) {
        cout << "Помилка: некоректна дата.\n";
        return;
    }

    cout << "Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ";
    if (!cin.getline(buf, 256) || strlen(buf) != 1 || buf[0] < '1' || buf[0] > '3') {
        if (!cin.eof() && cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); }
        cout << "Помилка: тип пристрою має бути 1, 2 або 3.\n";
        return;
    }
    o.type = (DeviceType)(buf[0] - '0');

    if (o.type == DeviceType::PHONE) {
        cout << "Останні 6 цифр IMEI: ";
        if (!cin.getline(buf, 256)) {
            if (!cin.eof()) { cin.clear(); cin.ignore(10000, '\n'); }
            cout << "Помилка: потрібно рівно 6 цифр.\n";
            return;
        }
        bool imeiOk = (strlen(buf) == 6);
        for (int i = 0; imeiOk && i < 6; i++) {
            if (!isdigit((unsigned char)buf[i])) imeiOk = false;
        }
        if (!imeiOk) {
            cout << "Помилка: потрібно рівно 6 цифр.\n";
            return;
        }
        sscanf(buf, "%d", &o.info.imei);
    } else if (o.type == DeviceType::LAPTOP) {
        cout << "Серійний номер: ";
        if (!cin.getline(buf, 256)) {
            if (!cin.eof()) { cin.clear(); cin.ignore(10000, '\n'); }
            cout << "Помилка: серійний номер має містити від 1 до 11 великих латинських літер і цифр.\n";
            return;
        }
        int slen = strlen(buf);
        bool snOk = (slen >= 1 && slen <= 11);
        for (int i = 0; snOk && i < slen; i++) {
            char c = buf[i];
            if (!((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) snOk = false;
        }
        if (!snOk) {
            cout << "Помилка: серійний номер має містити від 1 до 11 великих латинських літер і цифр.\n";
            return;
        }
        strcpy(o.info.serial, buf);
    } else {
        cout << "Діагональ (19-100 дюймів): ";
        if (!cin.getline(buf, 256)) {
            if (!cin.eof()) { cin.clear(); cin.ignore(10000, '\n'); }
            cout << "Помилка: діагональ має бути від 19 до 100 дюймів.\n";
            return;
        }
        int dlen = strlen(buf);
        bool dOk = (dlen >= 1 && dlen <= 3);
        for (int i = 0; dOk && i < dlen; i++) {
            if (!isdigit((unsigned char)buf[i])) dOk = false;
        }
        int inches = 0;
        if (dOk) sscanf(buf, "%d", &inches);
        if (!dOk || inches < 19 || inches > 100) {
            cout << "Помилка: діагональ має бути від 19 до 100 дюймів.\n";
            return;
        }
        o.info.inches = inches;
    }

    cout << "Опис несправності: ";
    if (!cin.getline(buf, 256)) {
        if (!cin.eof()) { cin.clear(); cin.ignore(10000, '\n'); }
        cout << "Помилка: опис несправності має містити від 1 до 80 байтів.\n";
        return;
    }
    int plen = strlen(buf);
    if (plen < 1 || plen > 80) {
        cout << "Помилка: опис несправності має містити від 1 до 80 байтів.\n";
        return;
    }
    strcpy(o.problem, buf);

    cout << "Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ";
    if (!cin.getline(buf, 256) || strlen(buf) != 1 || buf[0] < '1' || buf[0] > '3') {
        if (!cin.eof() && cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); }
        cout << "Помилка: пріоритет має бути 1, 2 або 3.\n";
        return;
    }
    o.priority = buf[0] - '0';

    cout << "Вартість (обернений польський запис): ";
    if (!cin.getline(buf, 256)) {
        if (!cin.eof()) { cin.clear(); cin.ignore(10000, '\n'); }
        cout << "Помилка у виразі: порожній вираз.\n";
        return;
    }
    if (!evalRPN(buf, o.price)) {
        return;
    }

    o.id = nextId++;
    o.status = Status::WAITING;
    o.master[0] = '\0';

    OrderNode* added = appendOrder(list, o);
    enqueue(q, &added->data);
    history = new Action{ActionType::ADD, o, history};

    cout << "Замовлення №" << o.id << " додано: вартість " << o.price<< " грн, у черзі на ремонт: " << q.size << ".\n";
}

//пункт 2
void printJournal(const OrderList& list, const OrderQueue& q) {
    if (list.head == nullptr) {
        cout << "Журнал замовлень порожній.\n";
        return;
    }

    cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n"
         << "|   № | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  |  Вартість |\n"
         << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n";
    for (OrderNode* cur = list.head; cur != nullptr; cur = cur->next) {
        cout << cur->data << "\n";
    }
    cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n";
    cout << "Усього замовлень: " << list.size << ", у черзі на ремонт: " << q.size << "\n";
}
Order* dequeue(OrderQueue& q) {
    if (q.head == nullptr) return nullptr;
    QNode* tmp = q.head;
    Order* res = tmp->order;
    q.head = q.head->next;
    delete tmp;
    q.size--;
    return res;
}

Master* findMaster(Master* start, const char* name) {
    if (start == nullptr) return nullptr;
    Master* cur = start;
    do {
        if (strcmp(cur->name, name) == 0) return cur;
        cur = cur->next;
    } while (cur != start);
    return nullptr;
}

//пункт 3
void assignOrder(OrderQueue& q, Master*& currentMaster) {
    if (q.head == nullptr) {
        cout << "Черга на ремонт порожня.\n";
        return;
    }

    Order* o = dequeue(q);
    o->status = Status::REPAIR;
    strcpy(o->master, currentMaster->name);

    cout << "Замовлення №" << o->id << " (пріоритет " << o->priority<< ") передано майстру " << currentMaster->name;
    cout << "\nНесправність: " << o->problem;
    cout << "\nУ черзі залишилось: " << q.size << "\n";

    currentMaster = currentMaster->next;
}

//пункт 4
void completeOrder(OrderList& list, Master* currentMaster) {
    char buf[256];
    cout << "Номер замовлення: ";
    if (!cin.getline(buf, 256)) {
        if (!cin.eof()) { cin.clear(); cin.ignore(10000, '\n'); }
        cout << "Помилка: номер замовлення має бути цілим числом.\n";
        return;
    }

    int len = strlen(buf);
    bool isNum = (len >= 1 && len <= 9);
    int start = (buf[0] == '-') ? 1 : 0;
    if (start == 1 && len == 1) isNum = false;
    for (int i = start; isNum && i < len; i++) {
        if (!isdigit((unsigned char)buf[i])) isNum = false;
    }
    if (!isNum) {
        cout << "Помилка: номер замовлення має бути цілим числом.\n";
        return;
    }

    int id = 0;
    sscanf(buf, "%d", &id);

    OrderNode* node = findById(list, id);
    if (node == nullptr) {
        cout << "Замовлення №" << id << " не знайдено.\n";
        return;
    }
    if (node->data.status == Status::WAITING) {
        cout << "Замовлення №" << id << " ще не передано майстру.\n";
        return;
    }
    if (node->data.status == Status::DONE) {
        cout << "Замовлення №" << id << " уже завершено.\n";
        return;
    }

    node->data.status = Status::DONE;
    Master* m = findMaster(currentMaster, node->data.master);
    if (m != nullptr) {
        m->doneCount++;
        m->revenue = m->revenue + node->data.price;
        cout << "Ремонт замовлення №" << id << " завершено. Майстер " << m->name
             << ": виконано " << m->doneCount << ", виручка " << m->revenue << " грн.\n";
    }
}

void removeFromQueue(OrderQueue& q, int id) {
    if (q.head == nullptr) return;

    if (q.head->order->id == id) {
        QNode* tmp = q.head;
        q.head = q.head->next;
        delete tmp;
        q.size--;
        return;
    }

    QNode* cur = q.head;
    while (cur->next != nullptr && cur->next->order->id != id) {
        cur = cur->next;
    }
    if (cur->next != nullptr) {
        QNode* victim = cur->next;
        cur->next = victim->next;
        delete victim;
        q.size--;
    }
}

// пункт 5
void deleteOrder(OrderList& list, OrderQueue& q, Action*& history) {
    char buf[256];
    cout << "Номер замовлення: ";
    if (!cin.getline(buf, 256)) {
        if (!cin.eof()) { cin.clear(); cin.ignore(10000, '\n'); }
        cout << "Помилка: номер замовлення має бути цілим числом.\n";
        return;
    }

    int len = strlen(buf);
    bool isNum = (len >= 1 && len <= 9);
    int start = (buf[0] == '-') ? 1 : 0;
    if (start == 1 && len == 1) isNum = false;
    for (int i = start; isNum && i < len; i++) {
        if (!isdigit((unsigned char)buf[i])) isNum = false;
    }
    if (!isNum) {
        cout << "Помилка: номер замовлення має бути цілим числом.\n";
        return;
    }

    int id = 0;
    sscanf(buf, "%d", &id);

    OrderNode* node = findById(list, id);
    if (node == nullptr) {
        cout << "Замовлення №" << id << " не знайдено.\n";
        return;
    }
    if (node->data.status != Status::WAITING) {
        cout << "Видалити можна лише замовлення, яке очікує в черзі.\n";
        return;
    }

    history = new Action{ActionType::DELETE, node->data, history};
    removeFromQueue(q, id);
    removeNode(list, node);

    cout << "Замовлення №" << id << " видалено. У журналі: " << list.size
         << ", у черзі: " << q.size << ".\n";
}

// пункт 6
void undoAction(OrderList& list, OrderQueue& q, Action*& history) {
    if (history == nullptr) {
        cout << "Немає дій для скасування.\n";
        return;
    }

    Action* act = history;
    history = history->next;

    if (act->type == ActionType::ADD) {
        OrderNode* node = findById(list, act->order.id);
        if (node == nullptr || node->data.status != Status::WAITING) {
            cout << "Додавання замовлення №" << act->order.id
                 << " скасувати неможливо: його вже передано майстру.\n";
        } else {
            removeFromQueue(q, act->order.id);
            removeNode(list, node);
            cout << "Скасовано додавання замовлення №" << act->order.id
                 << ": його вилучено з журналу і черги.\n";
        }
    } else {
        OrderNode* restored = appendOrder(list, act->order);
        enqueue(q, &restored->data);
        cout << "Скасовано видалення замовлення №" << act->order.id
             << ": його повернуто в кінець журналу і в чергу.\n";
    }

    delete act;
}
Money revenue(const OrderNode* p) {
    if (p == nullptr) return Money{0, 0};
    Money rest = revenue(p->next);
    if (p->data.status == Status::DONE) {
        return p->data.price + rest;
    }
    return rest;
}

// пункт 7
void printReport(const OrderList& list, Master* currentMaster) {
    if (list.head == nullptr) {
        cout << "Журнал порожній.\n";
        return;
    }

    Order** arr = new Order*[list.size];
    int idx = 0;
    for (OrderNode* cur = list.head; cur != nullptr; cur = cur->next) {
        arr[idx++] = &cur->data;
    }

    for (int i = 0; i < list.size - 1; i++) {
        for (int j = 0; j < list.size - 1 - i; j++) {
            bool swapNeeded = (arr[j]->price < arr[j + 1]->price) ||
                              (!(arr[j + 1]->price < arr[j]->price) && arr[j]->id > arr[j + 1]->id);
            if (swapNeeded) {
                Order* tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }

    cout << "Замовлення за вартістю:\n";
    for (int i = 0; i < list.size; i++) {
        const char* statusStr = "";
        switch (arr[i]->status) {
            case Status::WAITING: statusStr = "WAITING"; break;
            case Status::REPAIR:  statusStr = "REPAIR";  break;
            case Status::DONE:    statusStr = "DONE";    break;
        }
        char priceStr[16];
        sprintf(priceStr, "%d.%02d", arr[i]->price.hrn, arr[i]->price.kop);

        cout << "  №" << left << setw(4) << arr[i]->id
             << right << setw(10) << priceStr << " грн  " << statusStr << "\n";
    }

    Money diff = arr[0]->price - arr[list.size - 1]->price;
    delete[] arr;

    cout << "Різниця між найдорожчим і найдешевшим: " << diff << " грн\n";
    cout << "Виручка за завершеними ремонтами: " << revenue(list.head) << " грн\n";

    cout << "Майстри, починаючи з наступного в черзі:\n";
    if (currentMaster != nullptr) {
        Master* cur = currentMaster;
        do {
            cout << "  " << left << setw(13) << cur->name
                 << "виконано: " << cur->doneCount
                 << ", виручка: " << cur->revenue << " грн\n";
            cur = cur->next;
        } while (cur != currentMaster);
        cout << right;
    }
}

// пункт8
void reverseJournal(OrderList& list) {
    if (list.head == nullptr) {
        cout << "Журнал порожній.\n";
        return;
    }
    reverseList(list);
    cout << "Журнал розвернуто: тепер першим іде замовлення №"
         << list.head->data.id << ", останнім №" << list.tail->data.id << ".\n";
}


int main(){
    Master* currentMaster = nullptr;
     char line[256];
    cout << "Кількість майстрів (від 1 до 5): ";
    if (!cin.getline(line, 256) || strlen(line) != 1 || line[0] < '1' || line[0] > '5') {
        cout << "Помилка: кількість майстрів має бути цілим числом від 1 до 5.\n";
        return 0;
    }
    int n = line[0] - '0';

    cout << "Імена майстрів через пробіл: ";
    char names[256];
    if (!cin.getline(names, 256)) {
        cout << "Помилка: некоректний ввід імен.\n";
        return 0;
    }

    int count = 0;
    for (char* w = strtok(names, " "); w != nullptr; w = strtok(nullptr, " ")) {
        int len = strlen(w);
        bool ok = (len >= 1 && len <= 23);
        for (int i = 0; ok && i < len; i++) {
            if (!isalpha((unsigned char)w[i])) ok = false;
        }
        if (!ok || count >= n) {
            cout << "Помилка: кількість імен має дорівнювати " << n
                 << ", кожне ім'я з латинських літер, до 23 символів.\n";
            clearMasters(currentMaster);
            return 0;
        }
        if (currentMaster != nullptr) {
            Master* cur = currentMaster;
            do {
                if (strcmp(cur->name, w) == 0) {
                    cout << "Помилка: імена майстрів не повинні повторюватися.\n";
                    clearMasters(currentMaster);
                    return 0;
                }
                cur = cur->next;
            } while (cur != currentMaster);
        }
        addMaster(currentMaster, w);
        count++;
    }

    if (count != n) {
        cout << "Помилка: кількість імен має дорівнювати " << n
             << ", кожне ім'я з латинських літер, до 23 символів.\n";
        clearMasters(currentMaster);
        return 0;
    }

    OrderList list;
    OrderQueue queue;
    Action* history = nullptr;
    int nextId = 101;
    int choice = -1;

    do {
        cout << "\nМеню:\n"
             << "1. Додати замовлення\n"
             << "2. Журнал замовлень\n"
             << "3. Видати замовлення майстру\n"
             << "4. Завершити ремонт\n"
             << "5. Видалити замовлення\n"
             << "6. Скасувати останню дію\n"
             << "7. Звіт\n"
             << "8. Розвернути журнал\n"
             << "0. Вийти\n"
             << "Ваш вибір: ";

        if (!cin.getline(line, 256)) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка: введіть номер пункту меню.\n";
            choice = -1;
            continue;
        }

        int len = strlen(line);
        bool isNum = (len >= 1 && len <= 9);
        int start = (line[0] == '-') ? 1 : 0;
        if (start == 1 && len == 1) isNum = false;
        for (int i = start; isNum && i < len; i++) {
            if (!isdigit((unsigned char)line[i])) isNum = false;
        }
        if (!isNum) {
            cout << "Помилка: введіть номер пункту меню.\n";
            choice = -1;
            continue;
        }
        sscanf(line, "%d", &choice);

        switch (choice) {
            case 1: addOrder(list, queue, history, nextId); break;
            case 2: printJournal(list, queue); break;
            case 3: assignOrder(queue, currentMaster); break;
            case 4: completeOrder(list, currentMaster); break;
            case 5: deleteOrder(list, queue, history); break;
            case 6: undoAction(list, queue, history); break;
            case 7: printReport(list, currentMaster); break;
            case 8: reverseJournal(list); break;
            case 0: break;
            default:
                cout << "Помилка: пункту " << choice << " немає в меню.\n";
                break;
        }
    } while (choice != 0);

    clearHistory(history);
    clearQueue(queue);
    clearList(list);
    clearMasters(currentMaster);
    return 0;
}