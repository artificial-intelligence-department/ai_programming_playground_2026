
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

enum class DeviceType { PHONE = 1, LAPTOP, TV };
enum class Status { WAITING, REPAIR, DONE };
enum class ActionKind { ADD, REMOVE };

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

struct OrderNode {
    Order order;
    OrderNode* prev;
    OrderNode* next;
};

struct OrderList {
    OrderNode* head;
    OrderNode* tail;
    int size;
};

struct QNode {
    Order* order;
    QNode* next;
};

struct Master {
    char name[24];
    int done;
    Money revenue;
    Master* next;
};

struct Action {
    ActionKind kind;
    Order order;
    Action* next;
};

struct NumNode {
    Money value;
    NumNode* next;
};

struct Center {
    OrderList journal;
    QNode* queue;
    Master* cursor;
    Action* actions;
    int nextId;
};

const int LINE = 512;
const long long MAX_KOP = 10000000;

long long toKop(const Money& m) {
    return (long long)m.hrn * 100 + m.kop;
}

Money fromKop(long long k) {
    Money m;
    m.hrn = (int)(k / 100);
    m.kop = (int)(k % 100);
    return m;
}

Money operator+(const Money& a, const Money& b) {
    return fromKop(toKop(a) + toKop(b));
}

Money operator-(const Money& a, const Money& b) {
    return fromKop(toKop(a) - toKop(b));
}

Money operator*(const Money& a, int k) {
    return fromKop(toKop(a) * k);
}

bool operator<(const Money& a, const Money& b) {
    return toKop(a) < toKop(b);
}

void moneyText(const Money& m, char* out, int size) {
    snprintf(out, size, "%d.%02d", m.hrn, m.kop);
}

ostream& operator<<(ostream& os, const Money& m) {
    char buf[32];
    moneyText(m, buf, sizeof(buf));
    return os << buf;
}

const char* statusText(Status s) {
    if (s == Status::WAITING)
        return "WAITING";
    if (s == Status::REPAIR)
        return "REPAIR";
    return "DONE";
}

const char* typeText(DeviceType t) {
    if (t == DeviceType::PHONE)
        return "PHONE";
    if (t == DeviceType::LAPTOP)
        return "LAPTOP";
    return "TV";
}

void detailsText(const Order& o, char* out, int size) {
    if (o.type == DeviceType::PHONE)
        snprintf(out, size, "IMEI %06d", o.info.imei);
    else if (o.type == DeviceType::LAPTOP)
        snprintf(out, size, "SN %s", o.info.serial);
    else
        snprintf(out, size, "%d inch", o.info.inches);
}

ostream& operator<<(ostream& os, const Order& o) {
    char price[32], details[32], row[256];
    moneyText(o.price, price, sizeof(price));
    detailsText(o, details, sizeof(details));
    snprintf(row, sizeof(row),
             "| %-3d | %-15s | %-10s | %02d.%02d.%04d | %-6s | %-14s | %-2d | %-7s | %9s |",
             o.id, o.client.name, o.client.phone,
             o.date.day, o.date.month, o.date.year,
             typeText(o.type), details, o.priority,
             statusText(o.status), price);
    return os << row;
}

bool isDigitChar(char c) {
    return c >= '0' && c <= '9';
}

bool isLatinChar(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool allDigits(const char* s) {
    if (s[0] == '\0')
        return false;
    for (int i = 0; s[i]; i++)
        if (!isDigitChar(s[i]))
            return false;
    return true;
}

bool isLatinWord(const char* s, int maxLen) {
    int len = (int)strlen(s);
    if (len < 1 || len > maxLen)
        return false;
    for (int i = 0; i < len; i++)
        if (!isLatinChar(s[i]))
            return false;
    return true;
}

bool parseNumber(const char* s, int& value) {
    if (!allDigits(s) || strlen(s) > 9)
        return false;
    value = 0;
    for (int i = 0; s[i]; i++)
        value = value * 10 + (s[i] - '0');
    return true;
}

void trim(char* s) {
    int len = (int)strlen(s);
    int start = 0;
    while (s[start] && isspace((unsigned char)s[start]))
        start++;
    while (len > start && isspace((unsigned char)s[len - 1]))
        len--;
    memmove(s, s + start, len - start);
    s[len - start] = '\0';
}

bool readLine(const char* prompt, char* buf, int size) {
    cout << prompt;
    cin.getline(buf, size);
    if (cin.fail()) {
        if (cin.eof())
            return false;
        cin.clear();
        cin.ignore(100000, '\n');
    }
    trim(buf);
    return true;
}

void numPush(NumNode*& top, const Money& v) {
    top = new NumNode{v, top};
}

bool numPop(NumNode*& top, Money& v) {
    if (top == nullptr)
        return false;
    NumNode* t = top;
    v = t->value;
    top = t->next;
    delete t;
    return true;
}

int numCount(const NumNode* top) {
    int n = 0;
    for (const NumNode* p = top; p != nullptr; p = p->next)
        n++;
    return n;
}

void numClear(NumNode*& top) {
    while (top != nullptr) {
        NumNode* t = top;
        top = t->next;
        delete t;
    }
}

bool parseMoney(const char* s, Money& m) {
    int i = 0;
    int hrn = 0;
    while (isDigitChar(s[i])) {
        hrn = hrn * 10 + (s[i] - '0');
        i++;
        if (i > 6)
            return false;
    }
    if (i == 0)
        return false;
    int kop = 0;
    if (s[i] == '.') {
        i++;
        int start = i;
        while (isDigitChar(s[i])) {
            kop = kop * 10 + (s[i] - '0');
            i++;
        }
        int digits = i - start;
        if (digits < 1 || digits > 2)
            return false;
        if (digits == 1)
            kop = kop * 10;
    }
    if (s[i] != '\0')
        return false;
    m.hrn = hrn;
    m.kop = kop;
    return true;
}

bool rpnError(NumNode*& st, const char* message) {
    cout << "Помилка у виразі: " << message << endl;
    numClear(st);
    return false;
}

bool evalRPN(const char* expr, Money& res) {
    NumNode* st = nullptr;
    bool any = false;
    char tok[64];
    int i = 0;
    while (expr[i]) {
        while (expr[i] && isspace((unsigned char)expr[i]))
            i++;
        if (!expr[i])
            break;
        int len = 0;
        while (expr[i] && !isspace((unsigned char)expr[i])) {
            if (len < 63)
                tok[len++] = expr[i];
            i++;
        }
        tok[len] = '\0';
        any = true;

        Money value;
        if (len == 1 && (tok[0] == '+' || tok[0] == '-' || tok[0] == '*')) {
            if (st == nullptr || st->next == nullptr) {
                char msg[64];
                snprintf(msg, sizeof(msg), "для операції «%c» бракує чисел.", tok[0]);
                return rpnError(st, msg);
            }
            Money b, a;
            numPop(st, b);
            numPop(st, a);
            Money r;
            if (tok[0] == '+') {
                r = a + b;
            } else if (tok[0] == '-') {
                if (a < b)
                    return rpnError(st, "проміжний результат від'ємний.");
                r = a - b;
            } else {
                if (b.kop != 0 || b.hrn < 1 || b.hrn > 100)
                    return rpnError(st, "множник має бути цілим числом від 1 до 100.");
                r = a * b.hrn;
            }
            if (toKop(r) > MAX_KOP)
                return rpnError(st, "сума перевищує 100000.00 грн.");
            numPush(st, r);
        } else if (parseMoney(tok, value)) {
            if (toKop(value) > MAX_KOP)
                return rpnError(st, "сума перевищує 100000.00 грн.");
            numPush(st, value);
        } else {
            cout << "Помилка у виразі: «" << tok << "» не є числом або операцією." << endl;
            numClear(st);
            return false;
        }
    }
    if (!any)
        return rpnError(st, "порожній вираз.");
    int count = numCount(st);
    if (count != 1) {
        char msg[96];
        snprintf(msg, sizeof(msg), "у стеку залишилось чисел: %d, а має бути одне.", count);
        return rpnError(st, msg);
    }
    numPop(st, res);
    if (toKop(res) == 0) {
        cout << "Помилка у виразі: вартість має бути більшою за 0.00 грн." << endl;
        return false;
    }
    return true;
}

void listInit(OrderList& list) {
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

OrderNode* listPushBack(OrderList& list, const Order& o) {
    OrderNode* n = new OrderNode;
    n->order = o;
    n->prev = list.tail;
    n->next = nullptr;
    if (list.tail != nullptr)
        list.tail->next = n;
    else
        list.head = n;
    list.tail = n;
    list.size++;
    return n;
}

OrderNode* findById(const OrderList& list, int id) {
    for (OrderNode* p = list.head; p != nullptr; p = p->next)
        if (p->order.id == id)
            return p;
    return nullptr;
}

void listRemove(OrderList& list, OrderNode* p) {
    if (p->prev != nullptr)
        p->prev->next = p->next;
    else
        list.head = p->next;
    if (p->next != nullptr)
        p->next->prev = p->prev;
    else
        list.tail = p->prev;
    delete p;
    list.size--;
}

void listReverse(OrderList& list) {
    OrderNode* p = list.head;
    while (p != nullptr) {
        OrderNode* next = p->next;
        p->next = p->prev;
        p->prev = next;
        p = next;
    }
    OrderNode* t = list.head;
    list.head = list.tail;
    list.tail = t;
}

void listClear(OrderList& list) {
    OrderNode* p = list.head;
    while (p != nullptr) {
        OrderNode* next = p->next;
        delete p;
        p = next;
    }
    listInit(list);
}

void queueInsert(QNode*& head, Order* o) {
    QNode* n = new QNode{o, nullptr};
    if (head == nullptr || head->order->priority < o->priority) {
        n->next = head;
        head = n;
        return;
    }
    QNode* cur = head;
    while (cur->next != nullptr && cur->next->order->priority >= o->priority)
        cur = cur->next;
    n->next = cur->next;
    cur->next = n;
}

Order* queuePop(QNode*& head) {
    if (head == nullptr)
        return nullptr;
    QNode* t = head;
    Order* o = t->order;
    head = t->next;
    delete t;
    return o;
}

bool queueRemove(QNode*& head, const Order* o) {
    QNode* prev = nullptr;
    QNode* cur = head;
    while (cur != nullptr && cur->order != o) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == nullptr)
        return false;
    if (prev != nullptr)
        prev->next = cur->next;
    else
        head = cur->next;
    delete cur;
    return true;
}

int queueSize(const QNode* head) {
    int n = 0;
    for (const QNode* p = head; p != nullptr; p = p->next)
        n++;
    return n;
}

void queueClear(QNode*& head) {
    while (head != nullptr) {
        QNode* t = head;
        head = t->next;
        delete t;
    }
}

void pushAction(Action*& top, ActionKind kind, const Order& o) {
    Action* a = new Action;
    a->kind = kind;
    a->order = o;
    a->next = top;
    top = a;
}

bool popAction(Action*& top, ActionKind& kind, Order& o) {
    if (top == nullptr)
        return false;
    Action* t = top;
    kind = t->kind;
    o = t->order;
    top = t->next;
    delete t;
    return true;
}

void actionsClear(Action*& top) {
    while (top != nullptr) {
        Action* t = top;
        top = t->next;
        delete t;
    }
}

Master* findMaster(Master* start, const char* name) {
    Master* p = start;
    do {
        if (strcmp(p->name, name) == 0)
            return p;
        p = p->next;
    } while (p != start);
    return nullptr;
}

void ringClear(Master*& cursor) {
    if (cursor == nullptr)
        return;
    Master* p = cursor->next;
    cursor->next = nullptr;
    while (p != nullptr) {
        Master* next = p->next;
        delete p;
        p = next;
    }
    cursor = nullptr;
}

bool isLeap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
}

int daysInMonth(int m, int y) {
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && isLeap(y))
        return 29;
    return days[m - 1];
}

int checkDate(const char* s, Date& d) {
    if (strlen(s) != 10 || s[2] != '.' || s[5] != '.')
        return 1;
    for (int i = 0; i < 10; i++)
        if (i != 2 && i != 5 && !isDigitChar(s[i]))
            return 1;
    d.day = (s[0] - '0') * 10 + (s[1] - '0');
    d.month = (s[3] - '0') * 10 + (s[4] - '0');
    d.year = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 + (s[9] - '0');
    if (d.year < 2000 || d.year > 2099)
        return 2;
    if (d.month < 1 || d.month > 12)
        return 2;
    if (d.day < 1 || d.day > daysInMonth(d.month, d.year))
        return 2;
    return 0;
}

bool inputName(Order& o) {
    char buf[LINE];
    if (!readLine("Ім'я клієнта: ", buf, LINE))
        return false;
    if (!isLatinWord(buf, 15)) {
        cout << "Помилка: ім'я має містити від 1 до 15 латинських літер." << endl;
        return false;
    }
    strcpy(o.client.name, buf);
    return true;
}

bool inputPhone(Order& o) {
    char buf[LINE];
    if (!readLine("Телефон (10 цифр): ", buf, LINE))
        return false;
    if (strlen(buf) != 10 || !allDigits(buf) || buf[0] != '0') {
        cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0." << endl;
        return false;
    }
    strcpy(o.client.phone, buf);
    return true;
}

bool inputDate(Order& o) {
    char buf[LINE];
    if (!readLine("Дата прийому (ДД.ММ.РРРР): ", buf, LINE))
        return false;
    int code = checkDate(buf, o.date);
    if (code == 1) {
        cout << "Помилка: дата має бути у форматі ДД.ММ.РРРР." << endl;
        return false;
    }
    if (code == 2) {
        cout << "Помилка: некоректна дата." << endl;
        return false;
    }
    return true;
}

bool inputType(Order& o) {
    char buf[LINE];
    if (!readLine("Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ", buf, LINE))
        return false;
    if (strcmp(buf, "1") != 0 && strcmp(buf, "2") != 0 && strcmp(buf, "3") != 0) {
        cout << "Помилка: тип пристрою має бути 1, 2 або 3." << endl;
        return false;
    }
    o.type = static_cast<DeviceType>(buf[0] - '0');
    return true;
}

bool isSerial(const char* s) {
    int len = (int)strlen(s);
    if (len < 1 || len > 11)
        return false;
    for (int i = 0; i < len; i++)
        if (!isDigitChar(s[i]) && !(s[i] >= 'A' && s[i] <= 'Z'))
            return false;
    return true;
}

bool inputInfo(Order& o) {
    char buf[LINE];
    if (o.type == DeviceType::PHONE) {
        if (!readLine("Останні 6 цифр IMEI: ", buf, LINE))
            return false;
        if (strlen(buf) != 6 || !allDigits(buf)) {
            cout << "Помилка: потрібно рівно 6 цифр." << endl;
            return false;
        }
        int v = 0;
        for (int i = 0; i < 6; i++)
            v = v * 10 + (buf[i] - '0');
        o.info.imei = v;
    } else if (o.type == DeviceType::LAPTOP) {
        if (!readLine("Серійний номер (1-11 великих латинських літер і цифр): ", buf, LINE))
            return false;
        if (!isSerial(buf)) {
            cout << "Помилка: серійний номер має містити від 1 до 11 великих латинських літер і цифр." << endl;
            return false;
        }
        strcpy(o.info.serial, buf);
    } else {
        if (!readLine("Діагональ (19-100 дюймів): ", buf, LINE))
            return false;
        int v;
        if (!parseNumber(buf, v) || v < 19 || v > 100) {
            cout << "Помилка: діагональ має бути цілим числом від 19 до 100." << endl;
            return false;
        }
        o.info.inches = v;
    }
    return true;
}

bool inputProblem(Order& o) {
    char buf[LINE];
    if (!readLine("Опис несправності: ", buf, LINE))
        return false;
    int len = (int)strlen(buf);
    if (len < 1 || len > 80) {
        cout << "Помилка: опис має містити від 1 до 80 байтів." << endl;
        return false;
    }
    strcpy(o.problem, buf);
    return true;
}

bool inputPriority(Order& o) {
    char buf[LINE];
    if (!readLine("Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ", buf, LINE))
        return false;
    if (strcmp(buf, "1") != 0 && strcmp(buf, "2") != 0 && strcmp(buf, "3") != 0) {
        cout << "Помилка: пріоритет має бути 1, 2 або 3." << endl;
        return false;
    }
    o.priority = buf[0] - '0';
    return true;
}

bool inputPrice(Order& o) {
    char buf[LINE];
    if (!readLine("Вартість (обернений польський запис): ", buf, LINE))
        return false;
    return evalRPN(buf, o.price);
}

bool readOrderId(int& id, char* text) {
    if (!readLine("Номер замовлення: ", text, LINE))
        return false;
    if (!allDigits(text)) {
        cout << "Помилка: номер замовлення має бути цілим числом." << endl;
        return false;
    }
    if (!parseNumber(text, id))
        id = -1;
    return true;
}

void menuAdd(Center& c) {
    Order o;
    memset(&o, 0, sizeof(o));
    if (!inputName(o)) return;
    if (!inputPhone(o)) return;
    if (!inputDate(o)) return;
    if (!inputType(o)) return;
    if (!inputInfo(o)) return;
    if (!inputProblem(o)) return;
    if (!inputPriority(o)) return;
    if (!inputPrice(o)) return;

    o.id = c.nextId;
    c.nextId++;
    o.status = Status::WAITING;

    OrderNode* node = listPushBack(c.journal, o);
    queueInsert(c.queue, &node->order);
    pushAction(c.actions, ActionKind::ADD, o);

    cout << "Замовлення №" << o.id << " додано: вартість " << o.price
         << " грн, у черзі на ремонт: " << queueSize(c.queue) << "." << endl;
}

int utf8len(const char* s) {
    int n = 0;
    for (; *s; s++)
        if (((unsigned char)*s & 0xC0) != 0x80)
            n++;
    return n;
}

void headerCell(const char* text, int width) {
    cout << "| " << text << setw(width - utf8len(text)) << "" << " ";
}

void printSeparator() {
    cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+" << endl;
}

void printHeader() {
    printSeparator();
    headerCell("№", 3);
    headerCell("Клієнт", 15);
    headerCell("Телефон", 10);
    headerCell("Дата", 10);
    headerCell("Тип", 6);
    headerCell("Деталі", 14);
    headerCell("Пр", 2);
    headerCell("Статус", 7);
    headerCell("Вартість", 9);
    cout << "|" << endl;
    printSeparator();
}

void menuJournal(const Center& c) {
    if (c.journal.head == nullptr) {
        cout << "Журнал порожній." << endl;
        return;
    }
    printHeader();
    for (const OrderNode* p = c.journal.head; p != nullptr; p = p->next)
        cout << p->order << endl;
    printSeparator();
    cout << "Усього замовлень: " << c.journal.size
         << ", у черзі на ремонт: " << queueSize(c.queue) << endl;
}

void menuAssign(Center& c) {
    Order* o = queuePop(c.queue);
    if (o == nullptr) {
        cout << "Черга на ремонт порожня." << endl;
        return;
    }
    Master* m = c.cursor;
    c.cursor = c.cursor->next;
    o->status = Status::REPAIR;
    strcpy(o->master, m->name);
    cout << "Замовлення №" << o->id << " (пріоритет " << o->priority
         << ") передано майстру " << m->name << "." << endl;
    cout << "Несправність: " << o->problem << endl;
    cout << "У черзі залишилось: " << queueSize(c.queue) << endl;
}

void menuFinish(Center& c) {
    char text[LINE];
    int id;
    if (!readOrderId(id, text))
        return;
    OrderNode* n = findById(c.journal, id);
    if (n == nullptr) {
        cout << "Замовлення №" << text << " не знайдено." << endl;
        return;
    }
    if (n->order.status == Status::WAITING) {
        cout << "Замовлення №" << id << " ще не передано майстру." << endl;
        return;
    }
    if (n->order.status == Status::DONE) {
        cout << "Замовлення №" << id << " уже завершено." << endl;
        return;
    }
    n->order.status = Status::DONE;
    Master* m = findMaster(c.cursor, n->order.master);
    m->done++;
    m->revenue = m->revenue + n->order.price;
    cout << "Ремонт замовлення №" << id << " завершено. Майстер " << m->name
         << ": виконано " << m->done << ", виручка " << m->revenue << " грн." << endl;
}

void menuDelete(Center& c) {
    char text[LINE];
    int id;
    if (!readOrderId(id, text))
        return;
    OrderNode* n = findById(c.journal, id);
    if (n == nullptr) {
        cout << "Замовлення №" << text << " не знайдено." << endl;
        return;
    }
    if (n->order.status != Status::WAITING) {
        cout << "Видалити можна лише замовлення, яке очікує в черзі." << endl;
        return;
    }
    pushAction(c.actions, ActionKind::REMOVE, n->order);
    queueRemove(c.queue, &n->order);
    listRemove(c.journal, n);
    cout << "Замовлення №" << id << " видалено. У журналі: " << c.journal.size
         << ", у черзі: " << queueSize(c.queue) << "." << endl;
}

void menuUndo(Center& c) {
    ActionKind kind;
    Order o;
    if (!popAction(c.actions, kind, o)) {
        cout << "Немає дій для скасування." << endl;
        return;
    }
    if (kind == ActionKind::ADD) {
        OrderNode* n = findById(c.journal, o.id);
        if (n == nullptr || n->order.status != Status::WAITING) {
            cout << "Додавання замовлення №" << o.id
                 << " скасувати неможливо: його вже передано майстру." << endl;
            return;
        }
        queueRemove(c.queue, &n->order);
        listRemove(c.journal, n);
        cout << "Скасовано додавання замовлення №" << o.id
             << ": його вилучено з журналу і з черги." << endl;
    } else {
        OrderNode* n = listPushBack(c.journal, o);
        queueInsert(c.queue, &n->order);
        cout << "Скасовано видалення замовлення №" << o.id
             << ": його повернуто в кінець журналу і в чергу." << endl;
    }
}

bool goesBefore(const Order* a, const Order* b) {
    if (b->price < a->price)
        return true;
    if (a->price < b->price)
        return false;
    return a->id < b->id;
}

void sortOrders(Order** arr, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (goesBefore(arr[j + 1], arr[j])) {
                Order* t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
}

Money revenue(const OrderNode* p) {
    Money zero = {0, 0};
    if (p == nullptr)
        return zero;
    Money rest = revenue(p->next);
    if (p->order.status == Status::DONE)
        return p->order.price + rest;
    return rest;
}

void menuReport(const Center& c) {
    int n = c.journal.size;
    if (n == 0) {
        cout << "Журнал порожній." << endl;
        return;
    }
    Order** arr = new Order*[n];
    int i = 0;
    for (OrderNode* p = c.journal.head; p != nullptr; p = p->next)
        arr[i++] = &p->order;
    sortOrders(arr, n);

    cout << "Замовлення за вартістю:" << endl;
    for (int k = 0; k < n; k++)
        cout << "№" << arr[k]->id << " " << arr[k]->price << " грн "
             << statusText(arr[k]->status) << endl;
    cout << "Різниця між найдорожчим і найдешевшим: "
         << arr[0]->price - arr[n - 1]->price << " грн" << endl;
    delete[] arr;

    cout << "Виручка за завершеними ремонтами: " << revenue(c.journal.head) << " грн" << endl;
    cout << "Майстри, починаючи з наступного в черзі:" << endl;
    const Master* m = c.cursor;
    do {
        cout << m->name << " виконано: " << m->done
             << ", виручка: " << m->revenue << " грн" << endl;
        m = m->next;
    } while (m != c.cursor);
}

void menuReverse(Center& c) {
    if (c.journal.head == nullptr) {
        cout << "Журнал порожній." << endl;
        return;
    }
    listReverse(c.journal);
    cout << "Журнал розвернуто: тепер першим іде замовлення №" << c.journal.head->order.id
         << ", останнім №" << c.journal.tail->order.id << "." << endl;
}

bool readMasters(Center& c) {
    char buf[LINE];
    int n;
    if (!readLine("Кількість майстрів (від 1 до 5): ", buf, LINE))
        return false;
    if (!parseNumber(buf, n) || n < 1 || n > 5) {
        cout << "Помилка: кількість майстрів має бути цілим числом від 1 до 5." << endl;
        return false;
    }
    if (!readLine("Імена майстрів через пробіл: ", buf, LINE))
        return false;

    char names[5][24];
    int count = 0;
    bool bad = false;
    int i = 0;
    while (buf[i]) {
        while (buf[i] && isspace((unsigned char)buf[i]))
            i++;
        if (!buf[i])
            break;
        char word[LINE];
        int len = 0;
        while (buf[i] && !isspace((unsigned char)buf[i])) {
            word[len++] = buf[i];
            i++;
        }
        word[len] = '\0';
        if (!isLatinWord(word, 23))
            bad = true;
        else if (count < 5)
            strcpy(names[count], word);
        count++;
    }
    if (bad || count != n) {
        cout << "Помилка: кількість імен має дорівнювати " << n
             << ", кожне ім'я з латинських літер, до 23 символів." << endl;
        return false;
    }
    for (int a = 0; a < n; a++)
        for (int b = a + 1; b < n; b++)
            if (strcmp(names[a], names[b]) == 0) {
                cout << "Помилка: імена майстрів не повинні повторюватися." << endl;
                return false;
            }

    Master* first = nullptr;
    Master* last = nullptr;
    for (int k = 0; k < n; k++) {
        Master* m = new Master;
        strcpy(m->name, names[k]);
        m->done = 0;
        m->revenue.hrn = 0;
        m->revenue.kop = 0;
        m->next = nullptr;
        if (last != nullptr)
            last->next = m;
        else
            first = m;
        last = m;
    }
    last->next = first;
    c.cursor = first;
    return true;
}

void printMenu() {
    cout << endl;
    cout << "===== Сервісний центр =====" << endl;
    cout << "1. Додати замовлення" << endl;
    cout << "2. Журнал замовлень" << endl;
    cout << "3. Видати замовлення майстру" << endl;
    cout << "4. Завершити ремонт" << endl;
    cout << "5. Видалити замовлення" << endl;
    cout << "6. Скасувати останню дію" << endl;
    cout << "7. Звіт" << endl;
    cout << "8. Розвернути журнал" << endl;
    cout << "0. Вийти" << endl;
}

void runMenu(Center& c) {
    char buf[LINE];
    while (true) {
        printMenu();
        if (!readLine("Ваш вибір: ", buf, LINE))
            break;
        if (!allDigits(buf)) {
            cout << "Помилка: введіть номер пункту меню." << endl;
            continue;
        }
        int choice;
        if (!parseNumber(buf, choice) || choice > 8) {
            cout << "Помилка: пункту " << buf << " немає в меню." << endl;
            continue;
        }
        if (choice == 0)
            break;
        switch (choice) {
            case 1: menuAdd(c); break;
            case 2: menuJournal(c); break;
            case 3: menuAssign(c); break;
            case 4: menuFinish(c); break;
            case 5: menuDelete(c); break;
            case 6: menuUndo(c); break;
            case 7: menuReport(c); break;
            case 8: menuReverse(c); break;
        }
    }
}

void freeAll(Center& c) {
    listClear(c.journal);
    queueClear(c.queue);
    actionsClear(c.actions);
    ringClear(c.cursor);
}

int main() {
    Center c;
    listInit(c.journal);
    c.queue = nullptr;
    c.cursor = nullptr;
    c.actions = nullptr;
    c.nextId = 101;

    if (!readMasters(c))
        return 1;
    runMenu(c);
    freeAll(c);
    return 0;
}