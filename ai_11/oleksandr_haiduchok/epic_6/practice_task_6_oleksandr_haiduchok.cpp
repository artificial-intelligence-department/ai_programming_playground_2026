//Олександр Гайдучок ШІ-11
//Сервісний центр: черга ремонтів

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

enum class DeviceType { PHONE = 1, LAPTOP, TV };
enum class Status { WAITING, REPAIR, DONE };

union DeviceInfo {
    int imei;
    char serial[12];
    int inches;
};

struct Device {
    DeviceType type;
    DeviceInfo info;
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

//оголошення функцій, бо вони потрібні одне одному раніше за опис самої функції
bool evalRPN(const char *expr, Money &res);
long moneyToCents(const Money &m);
Money centsToMoney(long c);
//перевантаження операторів
Money operator+(const Money &a, const Money &b){
    return centsToMoney(moneyToCents(a) + moneyToCents(b));
}
Money operator-(const Money &a, const Money &b){
    return centsToMoney(moneyToCents(a) - moneyToCents(b));
}
Money operator*(const Money &a, int n){
    return centsToMoney(moneyToCents(a) * (long)n);
}
bool operator<(const Money &a, const Money &b){
    return moneyToCents(a) < moneyToCents(b);
}
ostream &operator<<(ostream &out, const Money &a){
    char buf[32];
    snprintf(buf, sizeof(buf), "%d.%02d", a.hrn, a.kop);
    out << buf;
    return out;
}

long moneyToCents(const Money &m){
    return (long)m.hrn * 100 + m.kop;
}
Money centsToMoney(long c) {
    Money m;
    m.hrn = (int)(c / 100);
    m.kop = (int)(c % 100);
    return m;
}

struct Order {
    int id;
    Client client;
    Date date;
    Device device;
    char problem[81];
    int priority;
    Money money;
    Status status;
    void *masterPtr;
    // вказівник на Master, якому передано замовлення
};

const char *deviceTypeName(DeviceType t){
    switch (t) {
        case DeviceType::PHONE:  return "PHONE";
        case DeviceType::LAPTOP: return "LAPTOP";
        case DeviceType::TV:     return "TV";
    }
    return "";
}
const char *statusName(Status s){
    switch (s) {
        case Status::WAITING: return "WAITING";
        case Status::REPAIR:  return "REPAIR";
        case Status::DONE:    return "DONE";
    }
    return "";
}

//перевантаження оператора для подальшого виводу нашого списку
ostream &operator<<(ostream &out, const Order &o) {
    char dateBuf[16];
    snprintf(dateBuf, sizeof(dateBuf), "%02d.%02d.%04d", o.date.day, o.date.month, o.date.year);

    char details[24];
    switch (o.device.type) {
        case DeviceType::PHONE: snprintf(details, sizeof(details), "IMEI %06d", o.device.info.imei);
            break;
        case DeviceType::LAPTOP: snprintf(details, sizeof(details), "SN %s", o.device.info.serial);
            break;
        case DeviceType::TV: snprintf(details, sizeof(details), "%d inch", o.device.info.inches);
            break;
    }

    char costBuf[16];
    snprintf(costBuf, sizeof(costBuf), "%d.%02d", o.money.hrn, o.money.kop);

    char line[220];
    snprintf(line, sizeof(line),
             "| %3d | %-15s | %-10s | %-10s | %-6s | %-14s | %2d | %-7s | %9s |", o.id, o.client.name, o.client.phone, dateBuf,
             deviceTypeName(o.device.type), details, o.priority, statusName(o.status), costBuf);
    out << line;
    return out;
}
// Двозвʼязний список
struct OrderNode {
    Order order;
    OrderNode *prev;
    OrderNode *next;
};
struct OrderList {
    OrderNode *head = nullptr;
    OrderNode *tail = nullptr;
    int size = 0;
};
//додавання нового замовлення
void appendOrder(OrderList &list, const Order &o) {
    OrderNode *node = new OrderNode();
    node->order = o;
    node->prev = list.tail;
    node->next = nullptr;
    if (list.tail) list.tail->next = node;
    list.tail = node;
    if (!list.head) list.head = node;
    list.size++;
}
//пошук замовлення по позиції
OrderNode *findById(const OrderList &list, int id) {
    for (OrderNode *p = list.head; p != nullptr; p = p->next) {
        if (p->order.id == id) return p;
    }
    return nullptr;
}

//вилучення замовлення
void removeNode(OrderList &list, OrderNode *node) {
    if (!node) {
        return;
    }
    if (node->prev){
         node->prev->next = node->next;
    }
    else {
        list.head = node->next;
    }
    if (node->next){
        node->next->prev = node->prev;
    }
    else{
        list.tail = node->prev;
    }
    delete node;
    list.size--;
}

// розвертає журнал на місці, міняємо prev/next у кожному вузлі, міняємо голову і хвіст
void reverseList(OrderList &list){
    OrderNode *p = list.head;
    while (p != nullptr) {
        OrderNode *tmp = p->next;
        p->next = p->prev;
        p->prev = tmp;
        p = tmp;
    }
    OrderNode *tmp = list.head;
    list.head = list.tail;
    list.tail = tmp;
}
// звільнення списку
void freeJournal(OrderList &list){
    OrderNode *p = list.head;
    while (p != nullptr){
        OrderNode *next = p->next;
        delete p;
        p = next;
    }
    list.head = list.tail = nullptr;
    list.size = 0;
}

void printJournal(const OrderList &list, int queueCount){
    if (list.size == 0){
        cout << "Журнал порожній.\n";
        return;
    }
    cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+" << "\n";
    cout << "|   № | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  |  Вартість |\n";
    cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+" << "\n";
    for (OrderNode *p = list.head; p != nullptr; p = p->next) {
        cout << p->order << "\n";
    }
    cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+" << "\n";
    cout << "Усього замовлень: " << list.size << ", у черзі на ремонт: " << queueCount << "\n";
}

//рекурсивний підрахунок виручки
Money revenue(const OrderNode *p){
    if (p == nullptr) {
        Money z{0, 0};
        return z;
    }
    Money rest = revenue(p->next);
    if (p->order.status == Status::DONE) {
        return p->order.money + rest;
    }
    return rest;
}

//пріоритетна черга
struct QNode {
    Order *orderPtr;
    QNode *next;
};

//вставка по пріоритету
void pushQueue(QNode *&head, Order *ptr){
    QNode *node = new QNode();
    node->orderPtr = ptr;
    node->next = nullptr;
    if (!head || ptr->priority > head->orderPtr->priority) {
        node->next = head;
        head = node;
        return;
    }
    QNode *p = head;
    while (p->next != nullptr && p->next->orderPtr->priority >= ptr->priority) {
        p = p->next;
    }
    node->next = p->next;
    p->next = node;
}
//беру найперше замовлення
Order *popQueue(QNode *&head){
    if (!head) return nullptr;
    QNode *node = head;
    head = head->next;
    Order *ptr = node->orderPtr;
    delete node;
    return ptr;
}
//вилучення замовлення з черги
void removeFromQueue(QNode *&head, Order *ptr) {
    QNode *p = head, *prev = nullptr;
    while (p != nullptr) {
        if (p->orderPtr == ptr) {
            if (prev) prev->next = p->next;
            else head = p->next;
            delete p;
            return;
        }
        prev = p;
        p = p->next;
    }
}

int queueLength(const QNode *head) {
    int n = 0;
    for (const QNode *p = head; p != nullptr; p = p->next) n++;
    return n;
}

void freeQueue(QNode *&head) {
    QNode *p = head;
    while (p != nullptr) {
        QNode *next = p->next;
        delete p;
        p = next;
    }
    head = nullptr;
}

//кільцевий список
struct Master {
    char name[24];
    int completed;
    Money salary; 
    Master *next;
};

Master *buildMasterround(char names[][24], int n){
    Master *first = nullptr, *last = nullptr;
    for (int i = 0; i < n; i++) {
        Master *m = new Master();
        strcpy(m->name, names[i]);
        m->completed = 0;
        m->salary.hrn = 0;
        m->salary.kop = 0;
        m->next = nullptr;
        if (!first){
            first = m;
        }
        else{
            last->next = m;
        }
        last = m;
    }
    if (last){
        last->next = first;
    }
    return first;
}

void freeMasterround(Master *&head) {
    if (!head){
        return;
    }
    Master *p = head->next;
    while (p != head){ 
        Master *next = p->next;
        delete p;
        p = next;
    }
    delete head;
    head = nullptr;
}

//Стек
enum class Actionkind { ADD, REMOVE };
struct Action {
    Actionkind kind;
    Order copy;
    Action *next;
};

void pushAction(Action *&top, Actionkind kind, const Order &order){
    Action *a = new Action();
    a->kind = kind;
    a->copy = order;
    a->next = top;
    top = a;
}

void freeActionStack(Action *&top) {
    Action *p = top;
    while (p != nullptr) {
        Action *next = p->next;
        delete p;
        p = next;
    }
    top = nullptr;
}

//Польський запис
struct PolNode {
    long kop;
    PolNode *next;
};
void pushPol(PolNode *&top, long kop) {
    PolNode *node = new PolNode();
    node->kop = kop;
    node->next = top;
    top = node;
}
long popPol(PolNode *&top) {
    PolNode *node = top;
    long v = node->kop;
    top = node->next;
    delete node;
    return v;
}
void freePol(PolNode *&top) {
    while (top != nullptr) {
        PolNode *next = top->next;
        delete top;
        top = next;
    }
}

const long MAX_CENTS = 10000000L;
//Перетворення наших чисел в правильний запис
bool parseMoneyToken(const char *tok, long &cents){
    int len = (int)strlen(tok);
    if (len == 0){
        return false;
    }
    int i = 0;
    int intDigits = 0;
    long intPart = 0;
    while (i < len && isdigit((unsigned char)tok[i])){
        intPart = intPart * 10 + (tok[i] - '0');
        intDigits++;
        i++;
        if (intDigits > 6){
            return false;
        }
    }
    if (intDigits == 0){
        return false; 
    }
    int fracDigits = 0;
    long fracPart = 0;
    if (i < len && tok[i] == '.'){
        i++;
        while (i < len && isdigit((unsigned char)tok[i])){
            fracPart = fracPart * 10 + (tok[i] - '0');
            fracDigits++;
            i++;
            if (fracDigits > 2){
                return false;
            }
        }
        if (fracDigits == 0){
            return false;
        }
    }
    if (i != len){
        return false;
    }
    while (fracDigits < 2){ 
    fracPart *= 10; 
    fracDigits++; 
    }
    cents = intPart * 100 + fracPart;
    return true;
}

bool evalRPN(const char *expr, Money &res){
    int len = (int)strlen(expr);
    char copy[256];
    if (len >= (int)sizeof(copy)){
        len = (int)sizeof(copy) - 1;
    }
    strncpy(copy, expr, len);
    copy[len] = '\0';

    PolNode *stack = nullptr;
    int count = 0;
    char *tok = strtok(copy, " ");
    if (tok == nullptr){
        cout << "Помилка у виразі: порожній вираз.\n";
        return false;
    }
    while (tok != nullptr){
        if (strcmp(tok, "+") == 0 || strcmp(tok, "-") == 0 || strcmp(tok, "*") == 0){
            if (count < 2){
                cout << "Помилка у виразі: для операції «" << tok << "» бракує чисел.\n";
                freePol(stack);
                return false;
            }
            long  b = popPol(stack);
            long  a = popPol(stack);
            count -= 2;
            long  result;
            if (tok[0] == '+'){
                result = a + b;
            } else if (tok[0] == '-'){
                result = a - b;
                if (result < 0){
                    cout << "Помилка у виразі: проміжний результат від'ємний.\n";
                    freePol(stack);
                    return false;
                }
            } 
            else{ 
                if (b % 100 != 0 || b / 100 < 1 || b / 100 > 100){
                    cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100.\n";
                    freePol(stack);
                    return false;
                }
                long  qty = b / 100;
                result = a * qty;
            }
            if (result > MAX_CENTS){
                cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                freePol(stack);
                return false;
            }
            pushPol(stack, result);
            count++;
        } else {
            long cents;
            if (!parseMoneyToken(tok, cents)){
                cout << "Помилка у виразі: «" << tok << "» не є числом або операцією.\n";
                freePol(stack);
                return false;
            }
            if (cents > MAX_CENTS){
                cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                freePol(stack);
                return false;
            }
            pushPol(stack, cents);
            count++;
        }
        tok = strtok(nullptr, " ");
    }

    if (count != 1){
        cout << "Помилка у виразі: у стеку залишилось чисел: " << count << ", а має бути одне.\n";
        freePol(stack);
        return false;
    }
    long finalVal = popPol(stack);
    if (finalVal == 0){
        cout << "Помилка у виразі: кінцевий результат не може дорівнювати 0.00 грн.\n";
        return false;
    }
    res = centsToMoney(finalVal);
    return true;
}

//валідація
void chomp(char *s) {
    int len = (int)strlen(s);
    while (len > 0 && (s[len - 1] == '\r' || s[len - 1] == '\n')) {
        s[len - 1] = '\0';
        len--;
    }
}

bool parseIntStrict(const char *s, int &out) {
    int len = (int)strlen(s);
    if (len == 0){
        return false;
    }
    int i = 0;
    bool neg = false;
    if (s[0] == '-'){ 
        neg = true; 
        i = 1; 
    }
    if (i >= len){
        return false;
    }
    long val = 0;
    for (int k = i; k < len; k++) {
        if (!isdigit((unsigned char)s[k])){
            return false;
        }
        val = val * 10 + (s[k] - '0');
        if (val > 2000000000L){
            return false;
        }
    }
    if (neg){
        val = -val;
    }
    out = (int)val;
    return true;
}

bool isAllAlpha(const char *s){
    int len = (int)strlen(s);
    if (len == 0){
        return false;
    }
    for (int i = 0; i < len; i++){
        if (!isalpha((unsigned char)s[i])){
            return false;
        }
    }
    return true;
}

bool isValidName(const char *s){
    int len = (int)strlen(s);
    return len >= 1 && len <= 15 && isAllAlpha(s);
}

bool isValidPhone(const char *s) {
    int len = (int)strlen(s);
    if (len != 10){
        return false;
    }
    if (s[0] != '0'){
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (!isdigit((unsigned char)s[i])){
            return false;
        }
    }
    return true;
}

bool daysInMonthOk(int day, int month, int year) {
    static const int dim[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month < 1 || month > 12){
        return false;
    }
    int maxDay = dim[month - 1];
    bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if (month == 2 && leap){
        maxDay = 29;
    }
    return day >= 1 && day <= maxDay;
}

bool parseDate(const char *s, Date &date) {
    int len = (int)strlen(s);
    if(len != 10) return false;
    for(int i = 0; i < len; i++) {
        if(i == 2 || i == 5) {
            if (s[i] != '.') {
                return false;
            }
        } 
        else if(!isdigit((unsigned char)s[i])){
            return false;
        }
    }
    int day = (s[0] - '0') * 10 + (s[1] - '0');
    int month = (s[3] - '0') * 10 + (s[4] - '0');
    int year = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 + (s[9] - '0');
    if (year < 2000 || year > 2099) return false;
    if (!daysInMonthOk(day, month, year)) return false;
    date.day = day;
    date.month = month;
    date.year = year;
    return true;
}

bool isValidImei(const char *s){
    int len = (int)strlen(s);
    if(len != 6){
        return false;
    }
    for(int i = 0; i < len; i++){
        if(!isdigit((unsigned char)s[i])){
            return false;
        }
    }
    return true;
}

bool isValidSerial(const char *s){
    int len = (int)strlen(s);
    if(len < 1 || len > 11){
        return false;
    }
    for(int i = 0; i < len; i++){
        unsigned char c = (unsigned char)s[i];
        if(!(isupper(c) || isdigit(c))){
            return false;
        }
    }
    return true;
}


   //0 все добре, 1 кількість імен не збігається або є некоректні, 2 імена повторюються 
int parseMasterNames(const char *line, int n, char names[][24]){
    char copy[256];
    int len = (int)strlen(line);
    if (len >= (int)sizeof(copy)){
        len = (int)sizeof(copy) - 1;
    }
    strncpy(copy, line, len);
    copy[len] = '\0';

    int j = 0;
    char *h = strtok(copy, " ");
    while (h != nullptr) {
        if (j >= n){
            j++;
            h = strtok(nullptr, " "); 
            continue; 
        } 
        if(strlen(h) < 1 || strlen(h) > 23 || !isAllAlpha(h)){
            return 1;
        }
        strcpy(names[j], h);
        j++;
        h = strtok(nullptr, " ");
    }
    if (j != n){
        return 1;
    }

    for (int a = 0; a < n; a++){
        for (int b = a + 1; b < n; b++){
            if (strcmp(names[a], names[b]) == 0){
                return 2;
            }
        }
    }
    return 0;
}

struct System{
    OrderList journal;
    QNode *queueHead = nullptr;
    Master *masterHead = nullptr;
    Master *nextMaster = nullptr;
    Action *actionStack = nullptr;
    int nextId = 101;
};


void Punkt1(System &sys){
    char buf[256];

    cout << "Ім'я клієнта: ";
    if (!cin.getline(buf, sizeof(buf))){ 
        cin.clear(); 
        return;
     }
    chomp(buf);
    if (!isValidName(buf)){
        cout << "Помилка: ім'я має містити від 1 до 15 латинських літер.\n";
        return;
    }
    char name[16];
    strcpy(name, buf);

    cout << "Телефон (10 цифр): ";
    if (!cin.getline(buf, sizeof(buf))){ 
        cin.clear(); 
        return; 
    }
    chomp(buf);
    if (!isValidPhone(buf)){
        cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0.\n";
        return;
    }
    char phone[11];
    strcpy(phone, buf);

    cout << "Дата прийому (ДД.ММ.РРРР): ";
    if (!cin.getline(buf, sizeof(buf))){ 
        cin.clear(); 
        return; 
    }
    chomp(buf);
    Date date;
    if (!parseDate(buf, date)){
        cout << "Помилка: некоректна дата.\n";
        return;
    }

    cout << "Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ";
    if (!cin.getline(buf, sizeof(buf))){ 
        cin.clear(); 
        return; 
    }
    chomp(buf);
    int typeNum;
    if (!parseIntStrict(buf, typeNum) || typeNum < 1 || typeNum > 3){
        cout << "Помилка: тип пристрою має бути 1, 2 або 3.\n";
        return;
    }
    DeviceType type = (DeviceType)typeNum;
    DeviceInfo info;
    memset(&info, 0, sizeof(info));

    if (type == DeviceType::PHONE){
        cout << "Останні 6 цифр IMEI: ";
        if (!cin.getline(buf, sizeof(buf))){ 
            cin.clear(); 
            return; 
        }
        chomp(buf);
        if (!isValidImei(buf)){
            cout << "Помилка: потрібно рівно 6 цифр.\n";
            return;
        }
        int v;
        parseIntStrict(buf, v);
        info.imei = v;
    } 
    else if (type == DeviceType::LAPTOP){
        cout << "Серійний номер до 11 символів: ";
        if (!cin.getline(buf, sizeof(buf))){ 
            cin.clear(); 
            return; 
        }
        chomp(buf);
        if (!isValidSerial(buf)){
            cout << "Помилка: серійний номер має складатися з великих латинських літер і цифр, довжиною до 11 символів.\n";
            return;
        }
        strcpy(info.serial, buf);
    } else {
        cout << "Діагональ від 19 до 100 дюймів: ";
        if (!cin.getline(buf, sizeof(buf))){ 
            cin.clear(); 
            return; 
        }
        chomp(buf);
        int inches;
        if (!parseIntStrict(buf, inches) || inches < 19 || inches > 100){
            cout << "Помилка: діагональ має бути від 19 до 100 дюймів.\n";
            return;
        }
        info.inches = inches;
    }

    cout << "Опис несправності: ";
    if (!cin.getline(buf, sizeof(buf))){ 
        cin.clear(); return; 
    }
    chomp(buf);
    int plen = (int)strlen(buf);
    if (plen < 1 || plen > 80){
        cout << "Помилка: опис несправності має містити від 1 до 80 символів.\n";
        return;
    }
    char problem[81];
    strcpy(problem, buf);

    cout << "Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ";
    if (!cin.getline(buf, sizeof(buf))){ 
        cin.clear(); 
        return; 
    }
    chomp(buf);
    int priority;
    if (!parseIntStrict(buf, priority) || priority < 1 || priority > 3){
        cout << "Помилка: пріоритет має бути 1, 2 або 3.\n";
        return;
    }

    cout << "Вартість (обернений польський запис): ";
    if (!cin.getline(buf, sizeof(buf))){ 
        cin.clear(); 
        return; 
    }
    chomp(buf);
    Money money;
    if (!evalRPN(buf, money)){
        return; 
    }

    Order order;
    order.id = sys.nextId++;
    strcpy(order.client.name, name);
    strcpy(order.client.phone, phone);
    order.date = date;
    order.device.type = type;
    order.device.info = info;
    strcpy(order.problem, problem);
    order.priority = priority;
    order.money = money;
    order.status = Status::WAITING;
    order.masterPtr = nullptr;

    appendOrder(sys.journal, order);
    pushQueue(sys.queueHead, &sys.journal.tail->order);
    pushAction(sys.actionStack, Actionkind::ADD, order);

    cout << "Замовлення №" << order.id << " додано: вартість " << order.money << " грн, у черзі на ремонт: " << queueLength(sys.queueHead) << ".\n";
}

void Punkt2(System &sys){
    printJournal(sys.journal, queueLength(sys.queueHead));
}

void Punkt3(System &sys){
    if (!sys.queueHead) {
        cout << "Черга на ремонт порожня.\n";
        return;
    }
    Order *ord = popQueue(sys.queueHead);
    Master *m = sys.nextMaster;
    sys.nextMaster = sys.nextMaster->next;
    ord->status = Status::REPAIR;
    ord->masterPtr = m;

    cout << "Замовлення №" << ord->id << " (пріоритет " << ord->priority << ") передано майстру " << m->name << ".\n";
    cout << "Несправність: " << ord->problem << "\n";
    cout << "У черзі залишилось: " << queueLength(sys.queueHead) << "\n";
}

void Punkt4(System &sys) {
    char buf[64];
    cout << "Номер замовлення: ";
    if (!cin.getline(buf, sizeof(buf))){ 
        cin.clear(); 
        return; 
    }
    chomp(buf);
    int id;
    if (!parseIntStrict(buf, id)){
        cout << "Помилка: номер замовлення має бути цілим числом.\n";
        return;
    }
    OrderNode *node = findById(sys.journal, id);
    if (!node){
        cout << "Замовлення №" << id << " не знайдено.\n";
        return;
    }
    Order &ord = node->order;
    if (ord.status == Status::WAITING){
        cout << "Замовлення №" << id << " ще не передано майстру.\n";
        return;
    }
    if (ord.status == Status::DONE){
        cout << "Замовлення №" << id << " уже завершено.\n";
        return;
    }
    ord.status = Status::DONE;
    Master *m = (Master *)ord.masterPtr;
    m->completed += 1;
    m->salary = m->salary + ord.money;

    cout << "Ремонт замовлення №" << id << " завершено. Майстер " << m->name << ": виконано " << m->completed << ", виручка " << m->salary << " грн.\n";
}

void Punkt5(System &sys) {
    char buf[64];
    cout << "Номер замовлення: ";
    if (!cin.getline(buf, sizeof(buf))){ 
        cin.clear(); 
        return; 
    }
    chomp(buf);
    int id;
    if (!parseIntStrict(buf, id)){
        cout << "Помилка: номер замовлення має бути цілим числом.\n";
        return;
    }
    OrderNode *node = findById(sys.journal, id);
    if (!node){
        cout << "Замовлення №" << id << " не знайдено.\n";
        return;
    }
    if (node->order.status != Status::WAITING){
        cout << "Видалити можна лише замовлення, яке очікує в черзі.\n";
        return;
    }
    Order copy = node->order;
    removeFromQueue(sys.queueHead, &node->order);
    removeNode(sys.journal, node);
    pushAction(sys.actionStack, Actionkind::REMOVE, copy);
    cout << "Замовлення №" << id << " видалено. У журналі: " << sys.journal.size << ", у черзі: " << queueLength(sys.queueHead) << ".\n";
}

void Punkt6(System &sys){
    if (!sys.actionStack){
        cout << "Немає дій для скасування.\n";
        return;
    }
    Action *act = sys.actionStack;
    sys.actionStack = sys.actionStack->next;

    if (act->kind == Actionkind::ADD){
        OrderNode *node = findById(sys.journal, act->copy.id);
        if (node != nullptr && node->order.status == Status::WAITING) {
            removeFromQueue(sys.queueHead, &node->order);
            removeNode(sys.journal, node);
            cout << "Скасовано додавання замовлення №" << act->copy.id << ".\n";
        } 
        else {
            cout << "Додавання замовлення №" << act->copy.id << " скасувати неможливо: його вже передано майстру.\n";
        }
    } 
    else { 
        appendOrder(sys.journal, act->copy);
        pushQueue(sys.queueHead, &sys.journal.tail->order);
        cout << "Скасовано видалення замовлення №" << act->copy.id << ": його повернуто в кінець журналу і в чергу.\n";
    }
    delete act;
}

void Punkt7(System &sys) {
    if (sys.journal.size == 0){
        cout << "Журнал порожній.\n";
        return;
    }
    int n = sys.journal.size;
    Order **arr = new Order *[n];
    int idx = 0;
    for (OrderNode *p = sys.journal.head; p != nullptr; p = p->next){
        arr[idx++] = &p->order;
    }

    for (int i = 0; i < n - 1; i++){
        int best = i;
        for (int j = i + 1; j < n; j++) {
            long  bet1 = moneyToCents(arr[j]->money);
            long  bet2 = moneyToCents(arr[best]->money);
            bool better = (bet1 > bet2) || (bet1 == bet2 && arr[j]->id < arr[best]->id);
            if(better){
                best = j;
            }
        }
        if (best != i){
            Order *tmp = arr[i];
            arr[i] = arr[best];
            arr[best] = tmp;
        }
    }
    cout << "Замовлення за вартістю:\n";
    for (int i = 0; i < n; i++) {
        char amt[16];
        snprintf(amt, sizeof(amt), "%d.%02d", arr[i]->money.hrn, arr[i]->money.kop);
        printf("  №%d%11s грн  %s\n", arr[i]->id, amt, statusName(arr[i]->status));
    }
    Money maxC = arr[0]->money, minC = arr[0]->money;
    for (int i = 1; i < n; i++) {
        if (maxC < arr[i]->money){
            maxC = arr[i]->money;
        }
        if (arr[i]->money < minC){
            minC = arr[i]->money;
        }
    }
    Money diff = maxC - minC;
    cout << "Різниця між найдорожчим і найдешевшим: " << diff << " грн\n";
    Money rev = revenue(sys.journal.head);
    cout << "Виручка за завершеними ремонтами: " << rev << " грн\n";
    delete[] arr;
    
    cout << "Майстри, починаючи з наступного в черзі:\n";
    if (sys.nextMaster != nullptr){
        Master *start = sys.nextMaster;
        Master *cur = start;
        do{
            printf("  %-13sвиконано: %d, виручка: %d.%02d грн\n", cur->name, cur->completed, cur->salary.hrn, cur->salary.kop);
            cur = cur->next;
        } 
        while (cur != start);
    }
}

void Punkt8(System &sys) {
    if (sys.journal.size == 0){
        cout << "Журнал порожній.\n";
        return;
    }
    reverseList(sys.journal);
    cout << "Журнал розвернуто: тепер першим іде замовлення №" << sys.journal.head->order.id << ", останнім №" << sys.journal.tail->order.id << ".\n";
}

int main(){
    char buf[256];
    cout << "Кількість майстрів (від 1 до 5): ";
    if (!cin.getline(buf, sizeof(buf))){
         return 0;
    }
    chomp(buf);
    int n;
    if (!parseIntStrict(buf, n) || n < 1 || n > 5){
        cout << "Помилка: кількість майстрів має бути від 1 до 5.\n";
        return 0;
    }

    cout << "Імена майстрів через пробіл: ";
    if (!cin.getline(buf, sizeof(buf))){
         return 0;
    }
    chomp(buf);

    char names[5][24];
    int rc = parseMasterNames(buf, n, names);
    if (rc == 1){
        cout << "Помилка: кількість імен має дорівнювати " << n << ", кожне ім'я з латинських літер, до 23 символів.\n";
        return 0;
    }
    if (rc == 2){
        cout << "Помилка: імена майстрів не повинні повторюватися.\n";
        return 0;
    }

    System sys;
    sys.masterHead = buildMasterround(names, n);
    sys.nextMaster = sys.masterHead;

    while (true){
        cout << "\n1 - Додати замовлення\n"
            "2 - Журнал замовлень\n"
            "3 - Видати замовлення майстру\n"
            "4 - Завершити ремонт\n"
            "5 - Видалити замовлення\n"
            "6 - Скасувати останню дію\n"
            "7 - Звіт\n"
            "8 - Розвернути журнал\n"
            "0 - Вийти\n";
        cout << "Ваш вибір: ";
        if (!cin.getline(buf, sizeof(buf))){
            break; 
        } 
        chomp(buf);
        int choice;
        if (!parseIntStrict(buf, choice)){
            cout << "Помилка: введіть номер пункту меню.\n";
            continue;
        };
        if (choice == 0){
            break;
        }
        switch (choice){
            case 1: Punkt1(sys); break;
            case 2: Punkt2(sys); break;
            case 3: Punkt3(sys); break;
            case 4: Punkt4(sys); break;
            case 5: Punkt5(sys); break;
            case 6: Punkt6(sys); break;
            case 7: Punkt7(sys); break;
            case 8: Punkt8(sys); break;
            default: cout << "Помилка: пункту " << choice << " немає в меню.\n";
        }
    }
    //звільненння памʼяті
    freeJournal(sys.journal);
    freeQueue(sys.queueHead);
    freeActionStack(sys.actionStack);
    freeMasterround(sys.masterHead);
    return 0;
}
