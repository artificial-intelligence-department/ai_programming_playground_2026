/*
Практична задача: Сервісний центр: черга ремонтів
Козій Василь Іванович
група: ШІ-12
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

enum class DeviceType { PHONE = 1, LAPTOP, TV };
enum class Status { WAITING, REPAIR, DONE };
enum class ActionType { ADD, REMOVE };

struct Money {
    int hrn;
    int kop;
};

int toKop(const Money &m) {
    return m.hrn * 100 + m.kop;
}

Money fromKop(int total) {
    Money m;
    m.hrn = total / 100;
    m.kop = total % 100;
    return m;
}

Money operator+(const Money &a, const Money &b) {
    return fromKop(toKop(a) + toKop(b));
}

Money operator-(const Money &a, const Money &b) {
    return fromKop(toKop(a) - toKop(b));
}

Money operator*(const Money &a, int n) {
    return fromKop(toKop(a) * n);
}

bool operator<(const Money &a, const Money &b) {
    return toKop(a) < toKop(b);
}

ostream &operator<<(ostream &os, const Money &m) {
    char buf[24];
    sprintf(buf, "%d.%02d", m.hrn, m.kop);
    os << buf;
    return os;
}

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

const char *typeName(DeviceType t) {
    switch (t) {
        case DeviceType::PHONE:  return "PHONE";
        case DeviceType::LAPTOP: return "LAPTOP";
        case DeviceType::TV:     return "TV";
    }
    return "?";
}

const char *statusName(Status s) {
    switch (s) {
        case Status::WAITING: return "WAITING";
        case Status::REPAIR:  return "REPAIR";
        case Status::DONE:    return "DONE";
    }
    return "?";
}

ostream &operator<<(ostream &os, const Order &o) {
    char dateBuf[16];
    sprintf(dateBuf, "%02d.%02d.%04d", o.date.day, o.date.month, o.date.year);

    char infoBuf[32];
    infoBuf[0] = '\0';
    switch (o.type) {
        case DeviceType::PHONE:
            sprintf(infoBuf, "IMEI %06d", o.info.imei);
            break;
        case DeviceType::LAPTOP:
            sprintf(infoBuf, "SN %s", o.info.serial);
            break;
        case DeviceType::TV:
            sprintf(infoBuf, "%d inch", o.info.inches);
            break;
    }

    char priceBuf[16];
    sprintf(priceBuf, "%d.%02d", o.price.hrn, o.price.kop);

    os << "| " << right << setw(3) << o.id
       << " | " << left << setw(15) << o.client.name
       << " | " << setw(10) << o.client.phone
       << " | " << setw(10) << dateBuf
       << " | " << setw(6) << typeName(o.type)
       << " | " << setw(14) << infoBuf
       << " | " << right << setw(2) << o.priority
       << " | " << left << setw(7) << statusName(o.status)
       << " | " << right << setw(9) << priceBuf
       << " |";
    return os;
}

bool allDigits(const char *s) {
    if (s[0] == '\0') return false;
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isdigit((unsigned char)s[i])) return false;
    }
    return true;
}

bool allLetters(const char *s) {
    if (s[0] == '\0') return false;
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isalpha((unsigned char)s[i])) return false;
    }
    return true;
}

bool parseInt(const char *s, int &value) {
    if (!allDigits(s)) return false;
    if (strlen(s) > 9) return false;
    value = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        value = value * 10 + (s[i] - '0');
    }
    return true;
}

bool isValidClientName(const char *s) {
    int len = strlen(s);
    return len >= 1 && len <= 15 && allLetters(s);
}

bool isValidMasterName(const char *s) {
    int len = strlen(s);
    return len >= 1 && len <= 23 && allLetters(s);
}

bool isValidPhone(const char *s) {
    return strlen(s) == 10 && allDigits(s) && s[0] == '0';
}

bool isValidImei(const char *s) {
    return strlen(s) == 6 && allDigits(s);
}

bool isValidSerial(const char *s) {
    int len = strlen(s);
    if (len < 1 || len > 11) return false;
    for (int i = 0; i < len; i++) {
        if (!isupper((unsigned char)s[i]) && !isdigit((unsigned char)s[i]))
            return false;
    }
    return true;
}

bool isValidProblem(const char *s) {
    int len = strlen(s);
    return len >= 1 && len <= 80;
}

bool isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int daysInMonth(int month, int year) {
    switch (month) {
        case 4: case 6: case 9: case 11: return 30;
        case 2: return isLeap(year) ? 29 : 28;
        default: return 31;
    }
}

bool parseDate(const char *s, Date &d) {
    if (strlen(s) != 10) return false;
    if (s[2] != '.' || s[5] != '.') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit((unsigned char)s[i])) return false;
    }
    int day   = (s[0] - '0') * 10 + (s[1] - '0');
    int month = (s[3] - '0') * 10 + (s[4] - '0');
    int year  = (s[6] - '0') * 1000 + (s[7] - '0') * 100
              + (s[8] - '0') * 10 + (s[9] - '0');

    if (year < 2000 || year > 2099) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth(month, year)) return false;

    d.day = day;
    d.month = month;
    d.year = year;
    return true;
}

struct OrderNode {
    Order data;
    OrderNode *prev;
    OrderNode *next;
};

struct OrderList {
    OrderNode *head;
    OrderNode *tail;
    int size;
};

void initList(OrderList &list) {
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

OrderNode *appendOrder(OrderList &list, const Order &o) {
    OrderNode *node = new OrderNode;
    node->data = o;
    node->next = nullptr;
    node->prev = list.tail;

    if (list.tail != nullptr) {
        list.tail->next = node;
    } else {
        list.head = node;
    }
    list.tail = node;
    list.size++;
    return node;
}

OrderNode *findById(const OrderList &list, int id) {
    OrderNode *cur = list.head;
    while (cur != nullptr) {
        if (cur->data.id == id) return cur;
        cur = cur->next;
    }
    return nullptr;
}

void removeNode(OrderList &list, OrderNode *node) {
    if (node->prev != nullptr) {
        node->prev->next = node->next;
    } else {
        list.head = node->next;
    }

    if (node->next != nullptr) {
        node->next->prev = node->prev;
    } else {
        list.tail = node->prev;
    }

    delete node;
    list.size--;
}

void reverseList(OrderList &list) {
    OrderNode *cur = list.head;
    while (cur != nullptr) {
        OrderNode *nxt = cur->next;
        cur->next = cur->prev;
        cur->prev = nxt;
        cur = nxt;
    }
    OrderNode *tmp = list.head;
    list.head = list.tail;
    list.tail = tmp;
}

void clearList(OrderList &list) {
    OrderNode *cur = list.head;
    while (cur != nullptr) {
        OrderNode *nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

struct QNode {
    Order *order;
    QNode *next;
};

struct PQueue {
    QNode *head;
    int size;
};

void initQueue(PQueue &q) {
    q.head = nullptr;
    q.size = 0;
}

void enqueue(PQueue &q, Order *o) {
    QNode *node = new QNode;
    node->order = o;
    node->next = nullptr;

    if (q.head == nullptr || o->priority > q.head->order->priority) {
        node->next = q.head;
        q.head = node;
    } else {
        QNode *cur = q.head;
        while (cur->next != nullptr &&
               cur->next->order->priority >= o->priority) {
            cur = cur->next;
        }
        node->next = cur->next;
        cur->next = node;
    }
    q.size++;
}

Order *dequeue(PQueue &q) {
    if (q.head == nullptr) return nullptr;
    QNode *t = q.head;
    Order *o = t->order;
    q.head = t->next;
    delete t;
    q.size--;
    return o;
}

bool removeFromQueue(PQueue &q, Order *o) {
    QNode *prev = nullptr;
    QNode *cur = q.head;
    while (cur != nullptr && cur->order != o) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == nullptr) return false;

    if (prev != nullptr) {
        prev->next = cur->next;
    } else {
        q.head = cur->next;
    }
    delete cur;
    q.size--;
    return true;
}

void clearQueue(PQueue &q) {
    QNode *cur = q.head;
    while (cur != nullptr) {
        QNode *nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    q.head = nullptr;
    q.size = 0;
}

struct NumNode {
    Money val;
    NumNode *next;
};

void pushNum(NumNode *&top, const Money &m) {
    NumNode *node = new NumNode;
    node->val = m;
    node->next = top;
    top = node;
}

Money popNum(NumNode *&top) {
    NumNode *t = top;
    Money m = t->val;
    top = t->next;
    delete t;
    return m;
}

void clearNumStack(NumNode *&top) {
    while (top != nullptr) {
        popNum(top);
    }
}

const Money MAX_PRICE = {100000, 0};

bool parseMoney(const char *s, Money &m) {
    int i = 0;
    int intPart = 0, digits = 0;
    while (isdigit((unsigned char)s[i])) {
        if (digits >= 6) return false;
        intPart = intPart * 10 + (s[i] - '0');
        digits++;
        i++;
    }
    if (digits == 0) return false;

    int kop = 0;
    if (s[i] == '.') {
        i++;
        int fd = 0;
        while (isdigit((unsigned char)s[i])) {
            if (fd >= 2) return false;
            kop = kop * 10 + (s[i] - '0');
            fd++;
            i++;
        }
        if (fd == 0) return false;
        if (fd == 1) kop *= 10;
    }
    if (s[i] != '\0') return false;

    m.hrn = intPart;
    m.kop = kop;
    return true;
}

bool rpnError(NumNode *&top) {
    clearNumStack(top);
    return false;
}

bool evalRPN(const char *expr, Money &res) {
    NumNode *top = nullptr;
    int cnt = 0;
    int tokens = 0;
    int i = 0;
    char tok[32];

    while (true) {
        while (expr[i] == ' ' || expr[i] == '\t') i++;
        if (expr[i] == '\0') break;

        int len = 0;
        bool tooLong = false;
        while (expr[i] != '\0' && expr[i] != ' ' && expr[i] != '\t') {
            if (len < 30) tok[len++] = expr[i];
            else tooLong = true;
            i++;
        }
        tok[len] = '\0';
        tokens++;

        bool isOp = !tooLong && len == 1 &&
                    (tok[0] == '+' || tok[0] == '-' || tok[0] == '*');

        if (isOp) {
            if (cnt < 2) {
                cout << "Помилка у виразі: для операції «" << tok[0]
                     << "» бракує чисел." << endl;
                return rpnError(top);
            }
            Money b = popNum(top);
            Money a = popNum(top);
            cnt -= 2;
            Money r;

            if (tok[0] == '+') {
                r = a + b;
            } else if (tok[0] == '-') {
                if (a < b) {
                    cout << "Помилка у виразі: проміжний результат від'ємний." << endl;
                    return rpnError(top);
                }
                r = a - b;
            } else {
                if (b.kop != 0 || b.hrn < 1 || b.hrn > 100) {
                    cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100." << endl;
                    return rpnError(top);
                }
                r = a * b.hrn;
            }

            if (MAX_PRICE < r) {
                cout << "Помилка у виразі: сума перевищує 100000.00 грн." << endl;
                return rpnError(top);
            }
            pushNum(top, r);
            cnt++;
        } else {
            Money m;
            if (tooLong || !parseMoney(tok, m)) {
                cout << "Помилка у виразі: «" << tok
                     << "» не є числом або операцією." << endl;
                return rpnError(top);
            }
            if (MAX_PRICE < m) {
                cout << "Помилка у виразі: сума перевищує 100000.00 грн." << endl;
                return rpnError(top);
            }
            pushNum(top, m);
            cnt++;
        }
    }

    if (tokens == 0) {
        cout << "Помилка у виразі: порожній вираз." << endl;
        return rpnError(top);
    }
    if (cnt != 1) {
        cout << "Помилка у виразі: у стеку залишилось чисел: " << cnt
             << ", а має бути одне." << endl;
        return rpnError(top);
    }

    Money result = popNum(top);
    if (toKop(result) == 0) {
        cout << "Помилка у виразі: вартість не може дорівнювати 0.00 грн." << endl;
        return false;
    }
    res = result;
    return true;
}

struct Master {
    char name[24];
    int done;
    Money revenue;
    Master *next;
};

struct MasterRing {
    Master *tail;
    Master *next;
    int count;
};

void initRing(MasterRing &ring) {
    ring.tail = nullptr;
    ring.next = nullptr;
    ring.count = 0;
}

void addMaster(MasterRing &ring, const char *name) {
    Master *m = new Master;
    strcpy(m->name, name);
    m->done = 0;
    m->revenue = {0, 0};

    if (ring.tail == nullptr) {
        m->next = m;
        ring.tail = m;
        ring.next = m;
    } else {
        m->next = ring.tail->next;
        ring.tail->next = m;
        ring.tail = m;
    }
    ring.count++;
}

Master *takeNextMaster(MasterRing &ring) {
    if (ring.next == nullptr) return nullptr;
    Master *m = ring.next;
    ring.next = m->next;
    return m;
}

void clearRing(MasterRing &ring) {
    if (ring.tail == nullptr) return;
    Master *cur = ring.tail->next;
    ring.tail->next = nullptr;
    while (cur != nullptr) {
        Master *nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    ring.tail = nullptr;
    ring.next = nullptr;
    ring.count = 0;
}

bool parseMasterNames(const char *line, int n, char names[][24]) {
    int cnt = 0;
    int i = 0;
    while (true) {
        while (line[i] == ' ' || line[i] == '\t') i++;
        if (line[i] == '\0') break;

        int start = i;
        while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t') i++;
        int len = i - start;

        if (cnt >= n) return false;
        if (len > 23) return false;

        for (int k = 0; k < len; k++) names[cnt][k] = line[start + k];
        names[cnt][len] = '\0';
        if (!isValidMasterName(names[cnt])) return false;
        cnt++;
    }
    return cnt == n;
}

bool hasDuplicates(char names[][24], int n) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (strcmp(names[i], names[j]) == 0) return true;
    return false;
}

bool readMasters(MasterRing &ring) {
    char line[512];

    cout << "Кількість майстрів (від 1 до 5): ";
    if (!cin.getline(line, sizeof(line))) {
        cout << "Помилка: кількість майстрів має бути цілим числом від 1 до 5." << endl;
        return false;
    }
    int n;
    if (!parseInt(line, n) || n < 1 || n > 5) {
        cout << "Помилка: кількість майстрів має бути цілим числом від 1 до 5." << endl;
        return false;
    }

    cout << "Імена майстрів через пробіл: ";
    char names[5][24];
    if (!cin.getline(line, sizeof(line)) || !parseMasterNames(line, n, names)) {
        cout << "Помилка: кількість імен має дорівнювати " << n
             << ", кожне ім'я з латинських літер, до 23 символів." << endl;
        return false;
    }
    if (hasDuplicates(names, n)) {
        cout << "Помилка: імена майстрів не повинні повторюватися." << endl;
        return false;
    }

    for (int i = 0; i < n; i++) addMaster(ring, names[i]);
    return true;
}

struct Action {
    ActionType type;
    Order order;
    Action *next;
};

void pushAction(Action *&top, ActionType type, const Order &o) {
    Action *a = new Action;
    a->type = type;
    a->order = o;
    a->next = top;
    top = a;
}

bool popAction(Action *&top, Action &out) {
    if (top == nullptr) return false;
    Action *t = top;
    out = *t;
    top = t->next;
    delete t;
    return true;
}

void clearActions(Action *&top) {
    while (top != nullptr) {
        Action *t = top;
        top = t->next;
        delete t;
    }
}

struct Service {
    OrderList journal;
    PQueue queue;
    MasterRing masters;
    Action *actions;
    int nextId;
};

void initService(Service &s) {
    initList(s.journal);
    initQueue(s.queue);
    initRing(s.masters);
    s.actions = nullptr;
    s.nextId = 101;
}

bool readLine(const char *prompt, char *buf, int size) {
    cout << prompt;
    if (!cin.getline(buf, size)) {
        if (cin.eof()) return false;
        cin.clear();
        int c;
        while ((c = cin.get()) != EOF && c != '\n') { }
    }
    int len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\r') buf[len - 1] = '\0';
    return true;
}

bool readDeviceInfo(Order &o) {
    char buf[256];
    int v;
    switch (o.type) {
        case DeviceType::PHONE:
            if (!readLine("Останні 6 цифр IMEI: ", buf, sizeof(buf))) return false;
            if (!isValidImei(buf)) {
                cout << "Помилка: потрібно рівно 6 цифр." << endl;
                return false;
            }
            parseInt(buf, v);
            o.info.imei = v;
            break;
        case DeviceType::LAPTOP:
            if (!readLine("Серійний номер: ", buf, sizeof(buf))) return false;
            if (!isValidSerial(buf)) {
                cout << "Помилка: серійний номер має містити від 1 до 11 великих латинських літер і цифр." << endl;
                return false;
            }
            strcpy(o.info.serial, buf);
            break;
        case DeviceType::TV:
            if (!readLine("Діагональ (дюймів): ", buf, sizeof(buf))) return false;
            if (!parseInt(buf, v) || v < 19 || v > 100) {
                cout << "Помилка: діагональ має бути цілим числом від 19 до 100." << endl;
                return false;
            }
            o.info.inches = v;
            break;
    }
    return true;
}

void addOrderMenu(Service &s) {
    char buf[256];
    int v;
    Order o;
    memset(&o, 0, sizeof(o));

    if (!readLine("Ім'я клієнта: ", buf, sizeof(buf))) return;
    if (!isValidClientName(buf)) {
        cout << "Помилка: ім'я має містити від 1 до 15 латинських літер." << endl;
        return;
    }
    strcpy(o.client.name, buf);

    if (!readLine("Телефон (10 цифр): ", buf, sizeof(buf))) return;
    if (!isValidPhone(buf)) {
        cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0." << endl;
        return;
    }
    strcpy(o.client.phone, buf);

    if (!readLine("Дата прийому (ДД.ММ.РРРР): ", buf, sizeof(buf))) return;
    if (!parseDate(buf, o.date)) {
        cout << "Помилка: некоректна дата." << endl;
        return;
    }

    if (!readLine("Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ", buf, sizeof(buf))) return;
    if (!parseInt(buf, v) || v < 1 || v > 3) {
        cout << "Помилка: тип пристрою має бути 1, 2 або 3." << endl;
        return;
    }
    o.type = (DeviceType)v;

    if (!readDeviceInfo(o)) return;

    if (!readLine("Опис несправності: ", buf, sizeof(buf))) return;
    if (!isValidProblem(buf)) {
        cout << "Помилка: опис має містити від 1 до 80 байтів." << endl;
        return;
    }
    strcpy(o.problem, buf);

    if (!readLine("Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ", buf, sizeof(buf))) return;
    if (!parseInt(buf, v) || v < 1 || v > 3) {
        cout << "Помилка: пріоритет має бути 1, 2 або 3." << endl;
        return;
    }
    o.priority = v;

    if (!readLine("Вартість (обернений польський запис): ", buf, sizeof(buf))) return;
    if (!evalRPN(buf, o.price)) return;

    o.id = s.nextId++;
    o.status = Status::WAITING;
    o.master[0] = '\0';

    OrderNode *node = appendOrder(s.journal, o);
    enqueue(s.queue, &node->data);
    pushAction(s.actions, ActionType::ADD, node->data);

    cout << "Замовлення №" << o.id << " додано: вартість " << o.price
         << " грн, у черзі на ремонт: " << s.queue.size << "." << endl;
}

bool readOrderId(int &id) {
    char buf[256];
    if (!readLine("Номер замовлення: ", buf, sizeof(buf))) return false;
    if (!parseInt(buf, id)) {
        cout << "Помилка: номер замовлення має бути цілим числом." << endl;
        return false;
    }
    return true;
}

Master *findMaster(const MasterRing &ring, const char *name) {
    if (ring.tail == nullptr) return nullptr;
    Master *p = ring.tail->next;
    do {
        if (strcmp(p->name, name) == 0) return p;
        p = p->next;
    } while (p != ring.tail->next);
    return nullptr;
}

void printJournal(const Service &s) {
    if (s.journal.head == nullptr) {
        cout << "Журнал порожній." << endl;
        return;
    }
    const char *line =
        "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+";
    cout << line << endl;
    cout << "|   № | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  |  Вартість |" << endl;
    cout << line << endl;
    for (OrderNode *p = s.journal.head; p != nullptr; p = p->next) {
        cout << p->data << endl;
    }
    cout << line << endl;
    cout << "Усього замовлень: " << s.journal.size
         << ", у черзі на ремонт: " << s.queue.size << endl;
}

void assignMenu(Service &s) {
    Order *o = dequeue(s.queue);
    if (o == nullptr) {
        cout << "Черга на ремонт порожня." << endl;
        return;
    }
    Master *m = takeNextMaster(s.masters);
    o->status = Status::REPAIR;
    strcpy(o->master, m->name);

    cout << "Замовлення №" << o->id << " (пріоритет " << o->priority
         << ") передано майстру " << m->name << "." << endl;
    cout << "Несправність: " << o->problem << endl;
    cout << "У черзі залишилось: " << s.queue.size << endl;
}

void finishMenu(Service &s) {
    int id;
    if (!readOrderId(id)) return;

    OrderNode *node = findById(s.journal, id);
    if (node == nullptr) {
        cout << "Замовлення №" << id << " не знайдено." << endl;
        return;
    }
    Order &o = node->data;
    if (o.status == Status::WAITING) {
        cout << "Замовлення №" << id << " ще не передано майстру." << endl;
        return;
    }
    if (o.status == Status::DONE) {
        cout << "Замовлення №" << id << " уже завершено." << endl;
        return;
    }

    o.status = Status::DONE;
    Master *m = findMaster(s.masters, o.master);
    m->done++;
    m->revenue = m->revenue + o.price;

    cout << "Ремонт замовлення №" << id << " завершено. Майстер " << m->name
         << ": виконано " << m->done << ", виручка " << m->revenue << " грн." << endl;
}

void removeMenu(Service &s) {
    int id;
    if (!readOrderId(id)) return;

    OrderNode *node = findById(s.journal, id);
    if (node == nullptr) {
        cout << "Замовлення №" << id << " не знайдено." << endl;
        return;
    }
    if (node->data.status != Status::WAITING) {
        cout << "Видалити можна лише замовлення, яке очікує в черзі." << endl;
        return;
    }

    pushAction(s.actions, ActionType::REMOVE, node->data);
    removeFromQueue(s.queue, &node->data);
    removeNode(s.journal, node);

    cout << "Замовлення №" << id << " видалено. У журналі: " << s.journal.size
         << ", у черзі: " << s.queue.size << "." << endl;
}

void undoMenu(Service &s) {
    Action a;
    if (!popAction(s.actions, a)) {
        cout << "Немає дій для скасування." << endl;
        return;
    }

    if (a.type == ActionType::ADD) {
        OrderNode *node = findById(s.journal, a.order.id);
        if (node == nullptr || node->data.status != Status::WAITING) {
            cout << "Додавання замовлення №" << a.order.id
                 << " скасувати неможливо: його вже передано майстру." << endl;
            return;
        }
        removeFromQueue(s.queue, &node->data);
        removeNode(s.journal, node);
        cout << "Скасовано додавання замовлення №" << a.order.id
             << ": його вилучено з журналу і з черги." << endl;
    } else {
        OrderNode *node = appendOrder(s.journal, a.order);
        enqueue(s.queue, &node->data);
        cout << "Скасовано видалення замовлення №" << a.order.id
             << ": його повернуто в кінець журналу і в чергу." << endl;
    }
}

void reverseMenu(Service &s) {
    if (s.journal.head == nullptr) {
        cout << "Журнал порожній." << endl;
        return;
    }
    reverseList(s.journal);
    cout << "Журнал розвернуто: тепер першим іде замовлення №"
         << s.journal.head->data.id << ", останнім №"
         << s.journal.tail->data.id << "." << endl;
}

void freeService(Service &s) {
    clearQueue(s.queue);
    clearList(s.journal);
    clearActions(s.actions);
    clearRing(s.masters);
}

void printMenu() {
    cout << endl;
    cout << "Меню:" << endl;
    cout << "1-Додати замовлення" << endl;
    cout << "2-Журнал замовлень" << endl;
    cout << "3-Видати замовлення майстру" << endl;
    cout << "4-Завершити ремонт" << endl;
    cout << "5-Видалити замовлення" << endl;
    cout << "6-Скасувати останню дію" << endl;
    cout << "7-Звіт" << endl;
    cout << "8-Розвернути журнал" << endl;
    cout << "0-Вийти" << endl;
}

Money revenue(const OrderNode *p) {
    if (p == nullptr) {
        Money zero = {0, 0};
        return zero;
    }
    Money rest = revenue(p->next);
    if (p->data.status == Status::DONE) {
        return p->data.price + rest;
    }
    return rest;
}

bool comesBefore(const Order *a, const Order *b) {
    if (b->price < a->price) return true;
    if (a->price < b->price) return false;
    return a->id < b->id;
}

void sortOrders(Order **arr, int n) {
    for (int i = 1; i < n; i++) {
        Order *key = arr[i];
        int j = i - 1;
        while (j >= 0 && comesBefore(key, arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void reportMenu(const Service &s) {
    int n = s.journal.size;
    if (n == 0) {
        cout << "Журнал порожній." << endl;
        return;
    }

    Order **arr = new Order *[n];
    int k = 0;
    for (OrderNode *p = s.journal.head; p != nullptr; p = p->next) {
        arr[k++] = &p->data;
    }

    sortOrders(arr, n);

    cout << "Замовлення за вартістю:" << endl;
    for (int i = 0; i < n; i++) {
        char priceBuf[16];
        sprintf(priceBuf, "%d.%02d", arr[i]->price.hrn, arr[i]->price.kop);
        cout << "  №" << arr[i]->id << ' ' << right << setw(10) << priceBuf
             << " грн  " << statusName(arr[i]->status) << endl;
    }

    Money diff = arr[0]->price - arr[n - 1]->price;
    cout << "Різниця між найдорожчим і найдешевшим: " << diff << " грн" << endl;

    delete[] arr;

    cout << "Виручка за завершеними ремонтами: " << revenue(s.journal.head)
         << " грн" << endl;

    cout << "Майстри, починаючи з наступного в черзі:" << endl;
    Master *m = s.masters.next;
    do {
        cout << "  " << left << setw(12) << m->name << " виконано: " << m->done
             << ", виручка: " << m->revenue << " грн" << endl;
        m = m->next;
    } while (m != s.masters.next);
}

int main() {
    Service s;
    initService(s);

    if (!readMasters(s.masters)) {
        freeService(s);
        return 0;
    }

    char buf[256];
    while (true) {
        printMenu();
        if (!readLine("Ваш вибір: ", buf, sizeof(buf))) break;

        int choice;
        if (!parseInt(buf, choice)) {
            cout << "Помилка: введіть номер пункту меню." << endl;
            continue;
        }
        if (choice == 0) break;

        switch (choice) {
            case 1: addOrderMenu(s);  break;
            case 2: printJournal(s);  break;
            case 3: assignMenu(s);    break;
            case 4: finishMenu(s);    break;
            case 5: removeMenu(s);    break;
            case 6: undoMenu(s);      break;
            case 7: reportMenu(s);    break;
            case 8: reverseMenu(s);   break;
            default:
                cout << "Помилка: пункту " << choice << " немає в меню." << endl;
        }
    }

    freeService(s);
}