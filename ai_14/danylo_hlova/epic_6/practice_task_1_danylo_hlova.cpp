//  Сервісний центр: черга ремонтів
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;


//  Константи
const int LINE_SIZE   = 1024;      
const int MAX_MASTERS = 5;         
const int NAME_SIZE   = 24;        
const int MAX_KOP     = 10000000;  
const int FIRST_ID    = 101;      


//  Переліки
enum class DeviceType { PHONE = 1, LAPTOP, TV };  
enum class Status { WAITING, REPAIR, DONE };      
enum class ActionKind { ADDED, REMOVED };         
enum class DateCheck { OK, BAD_FORMAT, BAD_VALUE };  

//  Структури та об'єднання
struct Money { int hrn; int kop; };               // гривні й копійки (0 <= kop <= 99)
struct Date { int day; int month; int year; };    // дата
struct Client { char name[16]; char phone[11]; }; // клієнт

// Дані пристрою: яке поле заповнене, визначає поле type замовлення
union DeviceInfo {
    int  imei;        // телефон: 6 цифр IMEI
    char serial[12];  // ноутбук: серійний номер (до 11 символів)
    int  inches;      // телевізор: діагональ у дюймах
};

struct Order {
    int        id;               // номер замовлення
    Client     client;           // клієнт
    Date       date;             // дата прийому
    DeviceType type;             // тип пристрою
    DeviceInfo info;             // дані пристрою 
    char       problem[81];      // опис несправності 
    int        priority;         // 1 звичайний, 2 підвищений, 3 терміновий
    Money      price;            // вартість ремонту
    Status     status;           // стан замовлення
    char       master[NAME_SIZE];// ім'я майстра
};

struct OrderNode {               // вузол двозв'язного списку 
    Order      data;
    OrderNode *prev;
    OrderNode *next;
};

struct OrderList {               // журнал замовлень
    OrderNode *head;
    OrderNode *tail;
    int        size;
};

struct QNode {                   
    Order *order;                
    QNode *next;
};

struct Master {                  
    char    name[NAME_SIZE];
    int     done;                
    Money   revenue;             
    Master *next;                
};

struct Action {                  // запис стеку історії дій
    ActionKind kind;            
    Order      order;            
    Action    *next;
};

struct NumNode {                 // вузол стеку чисел для обчислення RPN
    Money    value;
    NumNode *next;
};

// структури даних програми
struct Center {
    OrderList journal;           // журнал замовлень
    QNode    *queue;             // голова пріоритетної черги
    Master   *nextMaster;        // майстер, який отримає наступне замовлення
    Action   *history;           // вершина стеку дій
    int       nextId;            // наступний вільний номер замовлення
};


// допоміжні функції
// Переводить суму в копійки.
int toKop(const Money &m) {
    return m.hrn * 100 + m.kop;
}

// Створює Money з кількості копійок 
Money fromKop(int kop) {
    Money m;
    m.hrn = kop / 100;
    m.kop = kop % 100;
    return m;
}

// Оператор +: сума двох вартостей.
Money operator+(const Money &a, const Money &b) {
    return fromKop(toKop(a) + toKop(b));
}

// Оператор -: різниця a - b
Money operator-(const Money &a, const Money &b) {
    return fromKop(toKop(a) - toKop(b));
}

// Оператор *: вартість помножена на ціле число
Money operator*(const Money &a, int n) {
    return fromKop(toKop(a) * n);
}

// Оператор <
bool operator<(const Money &a, const Money &b) {
    return toKop(a) < toKop(b);
}

// Оператор <<: друкує суму 
ostream &operator<<(ostream &os, const Money &m) {
    char buf[24];
    snprintf(buf, sizeof(buf), "%d.%02d", m.hrn, m.kop);
    return os << buf;
}

//  Назви переліків
// Повертає назву типу пристрою для таблиці
const char *typeName(DeviceType t) {
    switch (t) {
        case DeviceType::PHONE:  return "PHONE";
        case DeviceType::LAPTOP: return "LAPTOP";
        default:                 return "TV";
    }
}

// Повертає назву статусу замовлення
const char *statusName(Status s) {
    switch (s) {
        case Status::WAITING: return "WAITING";
        case Status::REPAIR:  return "REPAIR";
        default:              return "DONE";
    }
}

//  Order: оператор виводу рядка журналу
ostream &operator<<(ostream &os, const Order &o) {
    ios::fmtflags oldFlags = os.flags();
    char oldFill = os.fill();

    char details[32], dateBuf[16], priceBuf[24];
    switch (o.type) {
        case DeviceType::PHONE:
            snprintf(details, sizeof(details), "IMEI %06d", o.info.imei);
            break;
        case DeviceType::LAPTOP:
            snprintf(details, sizeof(details), "SN %s", o.info.serial);
            break;
        default:
            snprintf(details, sizeof(details), "%d inch", o.info.inches);
            break;
    }
    snprintf(dateBuf, sizeof(dateBuf), "%02d.%02d.%04d", o.date.day, o.date.month, o.date.year);
    snprintf(priceBuf, sizeof(priceBuf), "%d.%02d", o.price.hrn, o.price.kop);

    os << "| " << right << setw(3) << o.id
       << " | " << left << setw(15) << o.client.name
       << " | " << setw(10) << o.client.phone
       << " | " << dateBuf
       << " | " << setw(6) << typeName(o.type)
       << " | " << setw(14) << details
       << " | " << setw(2) << o.priority
       << " | " << setw(7) << statusName(o.status)
       << " | " << right << setw(9) << priceBuf << " |";

    os.flags(oldFlags);
    os.fill(oldFill);
    return os;
}

//  Ввід: допоміжні функції
bool readLine(char *buf, int size) {
    cin.getline(buf, size);
    if (cin.fail()) {
        if (cin.gcount() == 0) {        // кінець вводу
            buf[0] = '\0';
            return false;
        }
        cin.clear();                   
        int ch;
        while ((ch = cin.get()) != EOF && ch != '\n') {
        }
    }
    int len = (int)strlen(buf);
    if (len > 0 && buf[len - 1] == '\r')
        buf[len - 1] = '\0';
    return true;
}

// Виводить підказку й зчитує рядок
bool ask(const char *prompt, char *buf) {
    cout << prompt;
    return readLine(buf, LINE_SIZE);
}

// Видаляє пробіли 
void trimInPlace(char *s) {
    int len = (int)strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1]))
        s[--len] = '\0';
    int start = 0;
    while (s[start] != '\0' && isspace((unsigned char)s[start]))
        start++;
    if (start > 0)
        memmove(s, s + start, strlen(s + start) + 1);
}

// Чи складається рядок лише з цифр
bool isDigits(const char *s) {
    if (*s == '\0')
        return false;
    for (; *s; s++)
        if (!isdigit((unsigned char)*s))
            return false;
    return true;
}

// Перетворює рядок із цифр
bool parseUInt(const char *s, int &value) {
    if (!isDigits(s) || strlen(s) > 9)
        return false;
    value = 0;
    for (; *s; s++)
        value = value * 10 + (*s - '0');
    return true;
}


//  Валідація полів замовлення
// Ім'я клієнта: від 1 до 15 латинських літер.
bool isValidName(const char *s) {
    int len = (int)strlen(s);
    if (len < 1 || len > 15)
        return false;
    for (int i = 0; i < len; i++)
        if (!isalpha((unsigned char)s[i]))
            return false;
    return true;
}

// Телефон: рівно 10 цифр, перша цифра 0
bool isValidPhone(const char *s) {
    return strlen(s) == 10 && isDigits(s) && s[0] == '0';
}

// Чи є рік високосним
bool isLeapYear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
}

// Кількість днів у місяці m року y
int daysInMonth(int m, int y) {
    static const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && isLeapYear(y))
        return 29;
    return days[m - 1];
}

// Розбирає дату у форматі ДД.ММ.РРРР
DateCheck parseDate(const char *s, Date &d) {
    if (strlen(s) != 10 || s[2] != '.' || s[5] != '.')
        return DateCheck::BAD_FORMAT;
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5)
            continue;
        if (!isdigit((unsigned char)s[i]))
            return DateCheck::BAD_FORMAT;
    }
    int day   = (s[0] - '0') * 10 + (s[1] - '0');
    int month = (s[3] - '0') * 10 + (s[4] - '0');
    int year  = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 + (s[9] - '0');
    if (year < 2000 || year > 2099 || month < 1 || month > 12)
        return DateCheck::BAD_VALUE;
    if (day < 1 || day > daysInMonth(month, year))
        return DateCheck::BAD_VALUE;
    d.day = day;
    d.month = month;
    d.year = year;
    return DateCheck::OK;
}

// Серійний номер ноутбука
bool isValidSerial(const char *s) {
    int len = (int)strlen(s);
    if (len < 1 || len > 11)
        return false;
    for (int i = 0; i < len; i++) {
        bool upper = (s[i] >= 'A' && s[i] <= 'Z');
        if (!upper && !isdigit((unsigned char)s[i]))
            return false;
    }
    return true;
}


//  Стек чисел для оберненого польського запису
// Кладе число на вершину стеку
void pushNum(NumNode *&top, const Money &value) {
    NumNode *n = new NumNode;
    n->value = value;
    n->next = top;
    top = n;
}

// Знімає число з вершини стеку й повертає його 
Money popNum(NumNode *&top) {
    NumNode *n = top;
    Money v = n->value;
    top = n->next;
    delete n;
    return v;
}

// Кількість чисел у стеку
int countNums(const NumNode *top) {
    int n = 0;
    for (; top != nullptr; top = top->next)
        n++;
    return n;
}

// Звільняє весь стек чисел
void clearNums(NumNode *&top) {
    while (top != nullptr)
        popNum(top);
}

// Розбирає токен як число
bool parseNumber(const char *tok, Money &value, bool &over) {
    int i = 0, intDigits = 0, hrn = 0, kop = 0;
    while (isdigit((unsigned char)tok[i])) {
        intDigits++;
        if (intDigits <= 6)            
            hrn = hrn * 10 + (tok[i] - '0');
        i++;
    }
    if (intDigits == 0)
        return false;
    if (tok[i] == '.') {
        i++;
        int fracDigits = 0;
        while (isdigit((unsigned char)tok[i])) {
            fracDigits++;
            if (fracDigits > 2)
                return false;
            kop = kop * 10 + (tok[i] - '0');
            i++;
        }
        if (fracDigits == 0)
            return false;
        if (fracDigits == 1)           
            kop *= 10;
    }
    if (tok[i] != '\0')
        return false;
    over = (intDigits > 6) || (hrn * 100 + kop > MAX_KOP);
    value.hrn = over ? 0 : hrn;
    value.kop = over ? 0 : kop;
    return true;
}

// Чи перевищує сума 100000.00 грн
bool exceedsLimit(const Money &m) {
    return toKop(m) > MAX_KOP;
}

// Обчислює вираз вартості в оберненому польському записі за допомогою стеку чисел
bool evalRPN(const char *expr, Money &res) {
    NumNode *top = nullptr;
    int tokens = 0;
    const char *p = expr;

    while (true) {
        while (*p != '\0' && isspace((unsigned char)*p))
            p++;
        if (*p == '\0')
            break;

        char tok[32];
        int len = 0;
        while (*p != '\0' && !isspace((unsigned char)*p)) {
            if (len < 31)
                tok[len++] = *p;
            p++;
        }
        tok[len] = '\0';
        tokens++;

        if (len == 1 && (tok[0] == '+' || tok[0] == '-' || tok[0] == '*')) {
            char op = tok[0];
            if (top == nullptr || top->next == nullptr) {
                cout << "Помилка у виразі: для операції «" << op << "» бракує чисел." << endl;
                clearNums(top);
                return false;
            }
            Money b = popNum(top);
            Money a = popNum(top);
            Money r;
            if (op == '+') {
                r = a + b;
                if (exceedsLimit(r)) {
                    cout << "Помилка у виразі: сума перевищує 100000.00 грн." << endl;
                    clearNums(top);
                    return false;
                }
            } else if (op == '-') {
                if (a < b) {
                    cout << "Помилка у виразі: проміжний результат від'ємний." << endl;
                    clearNums(top);
                    return false;
                }
                r = a - b;
            } else {
                if (b.kop != 0 || b.hrn < 1 || b.hrn > 100) {
                    cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100." << endl;
                    clearNums(top);
                    return false;
                }
                r = a * b.hrn;
                if (exceedsLimit(r)) {
                    cout << "Помилка у виразі: сума перевищує 100000.00 грн." << endl;
                    clearNums(top);
                    return false;
                }
            }
            pushNum(top, r);
        } else {
            Money v;
            bool over = false;
            if (!parseNumber(tok, v, over)) {
                cout << "Помилка у виразі: «" << tok << "» не є числом або операцією." << endl;
                clearNums(top);
                return false;
            }
            if (over) {
                cout << "Помилка у виразі: сума перевищує 100000.00 грн." << endl;
                clearNums(top);
                return false;
            }
            pushNum(top, v);
        }
    }

    if (tokens == 0) {
        cout << "Помилка у виразі: порожній вираз." << endl;
        return false;
    }
    int count = countNums(top);
    if (count != 1) {
        cout << "Помилка у виразі: у стеку залишилось чисел: " << count
             << ", а має бути одне." << endl;
        clearNums(top);
        return false;
    }
    Money result = popNum(top);
    if (toKop(result) == 0) {
        cout << "Помилка у виразі: вартість не може дорівнювати 0.00 грн." << endl;
        return false;
    }
    res = result;
    return true;
}

//  Журнал: двозв'язний список
// Ініціалізує порожній журнал
void initList(OrderList &list) {
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

// Додає копію замовлення в кінець журналу. Повертає новий вузол
OrderNode *appendOrder(OrderList &list, const Order &o) {
    OrderNode *n = new OrderNode;
    n->data = o;
    n->next = nullptr;
    n->prev = list.tail;
    if (list.tail != nullptr)
        list.tail->next = n;
    else
        list.head = n;
    list.tail = n;
    list.size++;
    return n;
}

// Шукає замовлення за номером
OrderNode *findById(const OrderList &list, int id) {
    for (OrderNode *p = list.head; p != nullptr; p = p->next)
        if (p->data.id == id)
            return p;
    return nullptr;
}

// Вилучає вузол із будь-якого місця журналу 
// оновлює prev, next, head, tail, size і звільняє пам'ять вузла
void removeNode(OrderList &list, OrderNode *node) {
    if (node->prev != nullptr)
        node->prev->next = node->next;
    else
        list.head = node->next;
    if (node->next != nullptr)
        node->next->prev = node->prev;
    else
        list.tail = node->prev;
    delete node;
    list.size--;
}

// Розвертає журнал на місці: у кожному вузлі міняє prev і next, потім head і tail
void reverseList(OrderList &list) {
    OrderNode *cur = list.head;
    while (cur != nullptr) {
        OrderNode *oldNext = cur->next;
        cur->next = cur->prev;
        cur->prev = oldNext;
        cur = oldNext;
    }
    OrderNode *tmp = list.head;
    list.head = list.tail;
    list.tail = tmp;
}

// Рекурсивно обчислює виручку за завершеними ремонтами від вузла p до кінця списку
Money revenue(const OrderNode *p) {
    if (p == nullptr) {
        Money zero = {0, 0};
        return zero;
    }
    Money rest = revenue(p->next);
    if (p->data.status == Status::DONE)
        rest = rest + p->data.price;
    return rest;
}

// Звільняє всі вузли журналу
void clearList(OrderList &list) {
    while (list.head != nullptr)
        removeNode(list, list.head);
}

//  Пріоритетна черга: однозв'язний список вказівників на замовлення
void pushQueue(QNode *&head, Order *o) {
    QNode *n = new QNode;
    n->order = o;
    if (head == nullptr || head->order->priority < o->priority) {
        n->next = head;
        head = n;
        return;
    }
    QNode *p = head;
    while (p->next != nullptr && p->next->order->priority >= o->priority)
        p = p->next;
    n->next = p->next;
    p->next = n;
}

// Забирає з голови черги замовлення з найвищим пріоритетом
Order *popQueue(QNode *&head) {
    if (head == nullptr)
        return nullptr;
    QNode *n = head;
    Order *o = n->order;
    head = n->next;
    delete n;
    return o;
}

// Вилучає із черги вузол, що вказує на замовлення o
bool removeFromQueue(QNode *&head, const Order *o) {
    QNode *prev = nullptr;
    for (QNode *p = head; p != nullptr; prev = p, p = p->next) {
        if (p->order == o) {
            if (prev != nullptr)
                prev->next = p->next;
            else
                head = p->next;
            delete p;
            return true;
        }
    }
    return false;
}

// Кількість замовлень у черзі
int queueSize(const QNode *head) {
    int n = 0;
    for (; head != nullptr; head = head->next)
        n++;
    return n;
}

// Звільняє всю чергу
void clearQueue(QNode *&head) {
    while (head != nullptr)
        popQueue(head);
}


//  Майстри: кільцевий список
Master *buildRing(char names[][NAME_SIZE], int n) {
    Master *first = nullptr, *last = nullptr;
    for (int i = 0; i < n; i++) {
        Master *m = new Master;
        strcpy(m->name, names[i]);
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
    if (last != nullptr)
        last->next = first;
    return first;
}

// Видає наступного майстра в кільці й пересуває вказівник на того, хто за ним
Master *takeNextMaster(Master *&next) {
    Master *m = next;
    next = next->next;
    return m;
}

// Шукає майстра за іменем
Master *findMaster(Master *start, const char *name) {
    if (start == nullptr)
        return nullptr;
    Master *p = start;
    do {
        if (strcmp(p->name, name) == 0)
            return p;
        p = p->next;
    } while (p != start);
    return nullptr;
}

// Звільняє кільце
void clearRing(Master *&start) {
    if (start == nullptr)
        return;
    Master *p = start->next;
    start->next = nullptr;
    while (p != nullptr) {
        Master *nxt = p->next;
        delete p;
        p = nxt;
    }
    start = nullptr;
}


//  Історія дій: стек
// Кладе дію на вершину стеку історії
void pushAction(Action *&top, ActionKind kind, const Order &o) {
    Action *a = new Action;
    a->kind = kind;
    a->order = o;
    a->next = top;
    top = a;
}

// Знімає дію з вершини стеку
bool popAction(Action *&top, ActionKind &kind, Order &o) {
    if (top == nullptr)
        return false;
    Action *a = top;
    kind = a->kind;
    o = a->order;
    top = a->next;
    delete a;
    return true;
}

// Звільняє весь стек історії
void clearHistory(Action *&top) {
    ActionKind k;
    Order o;
    while (popAction(top, k, o)) {
    }
}

//  Центр: ініціалізація й звільнення
// Ініціалізує порожній стан центру
void initCenter(Center &c) {
    initList(c.journal);
    c.queue = nullptr;
    c.nextMaster = nullptr;
    c.history = nullptr;
    c.nextId = FIRST_ID;
}

// Звільняє журнал, чергу, стек дій і кільце майстрів
void freeCenter(Center &c) {
    clearQueue(c.queue);
    clearList(c.journal);
    clearHistory(c.history);
    clearRing(c.nextMaster);
}


//  Ввід майстрів
bool readMasters(Master *&ring) {
    char line[LINE_SIZE];
    if (!ask("Кількість майстрів (від 1 до 5): ", line))
        return false;
    trimInPlace(line);
    int n = 0;
    if (!parseUInt(line, n) || n < 1 || n > MAX_MASTERS) {
        cout << "Помилка: кількість майстрів має бути цілим числом від 1 до 5." << endl;
        return false;
    }

    if (!ask("Імена майстрів через пробіл: ", line))
        return false;

    char names[MAX_MASTERS][NAME_SIZE];
    int count = 0;
    bool ok = true;
    const char *p = line;
    while (true) {
        while (*p != '\0' && isspace((unsigned char)*p))
            p++;
        if (*p == '\0')
            break;
        const char *start = p;
        while (*p != '\0' && !isspace((unsigned char)*p))
            p++;
        int len = (int)(p - start);
        count++;
        bool letters = true;
        for (int i = 0; i < len; i++)
            if (!isalpha((unsigned char)start[i]))
                letters = false;
        if (len > NAME_SIZE - 1 || !letters)
            ok = false;
        else if (count <= MAX_MASTERS) {
            memcpy(names[count - 1], start, len);
            names[count - 1][len] = '\0';
        }
    }
    if (!ok || count != n) {
        cout << "Помилка: кількість імен має дорівнювати " << n
             << ", кожне ім'я з латинських літер, до 23 символів." << endl;
        return false;
    }
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (strcmp(names[i], names[j]) == 0) {
                cout << "Помилка: імена майстрів не повинні повторюватися." << endl;
                return false;
            }
    ring = buildRing(names, n);
    return true;
}

//  Ввід замовлення (пункт 1)
bool readClient(Client &cl) {
    char line[LINE_SIZE];
    if (!ask("Ім'я клієнта: ", line))
        return false;
    if (!isValidName(line)) {
        cout << "Помилка: ім'я має містити від 1 до 15 латинських літер." << endl;
        return false;
    }
    strcpy(cl.name, line);

    if (!ask("Телефон (10 цифр): ", line))
        return false;
    if (!isValidPhone(line)) {
        cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0." << endl;
        return false;
    }
    strcpy(cl.phone, line);
    return true;
}

// Зчитує й перевіряє дату прийому у форматі ДД.ММ.РРРР.
bool readDate(Date &d) {
    char line[LINE_SIZE];
    if (!ask("Дата прийому (ДД.ММ.РРРР): ", line))
        return false;
    DateCheck r = parseDate(line, d);
    if (r == DateCheck::BAD_FORMAT) {
        cout << "Помилка: дата має бути у форматі ДД.ММ.РРРР." << endl;
        return false;
    }
    if (r == DateCheck::BAD_VALUE) {
        cout << "Помилка: некоректна дата." << endl;
        return false;
    }
    return true;
}

// Зчитує тип пристрою
bool readDevice(DeviceType &type, DeviceInfo &info) {
    char line[LINE_SIZE];
    if (!ask("Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ", line))
        return false;
    if (strcmp(line, "1") == 0)
        type = DeviceType::PHONE;
    else if (strcmp(line, "2") == 0)
        type = DeviceType::LAPTOP;
    else if (strcmp(line, "3") == 0)
        type = DeviceType::TV;
    else {
        cout << "Помилка: тип пристрою має бути 1, 2 або 3." << endl;
        return false;
    }

    if (type == DeviceType::PHONE) {
        if (!ask("Останні 6 цифр IMEI: ", line))
            return false;
        if (strlen(line) != 6 || !isDigits(line)) {
            cout << "Помилка: потрібно рівно 6 цифр." << endl;
            return false;
        }
        parseUInt(line, info.imei);
    } else if (type == DeviceType::LAPTOP) {
        if (!ask("Серійний номер (до 11 великих латинських літер і цифр): ", line))
            return false;
        if (!isValidSerial(line)) {
            cout << "Помилка: серійний номер має містити від 1 до 11 великих латинських літер і цифр." << endl;
            return false;
        }
        strcpy(info.serial, line);
    } else {
        if (!ask("Діагональ у дюймах (від 19 до 100): ", line))
            return false;
        int inches = 0;
        if (!parseUInt(line, inches) || inches < 19 || inches > 100) {
            cout << "Помилка: діагональ має бути цілим числом від 19 до 100." << endl;
            return false;
        }
        info.inches = inches;
    }
    return true;
}

// Зчитує вартість. вираз в оберненому польському записі
bool readPrice(Money &price) {
    char line[LINE_SIZE];
    if (!ask("Вартість (обернений польський запис): ", line))
        return false;
    if (strlen(line) >= (size_t)(LINE_SIZE - 1)) {
        cout << "Помилка у виразі: вираз задовгий." << endl;
        return false;
    }
    return evalRPN(line, price);
}

// Зчитує всі поля нового замовлення в порядку з таблиці вхідних даних.
bool inputOrder(Order &o) {
    char line[LINE_SIZE];
    memset(&o, 0, sizeof(o));

    if (!readClient(o.client))
        return false;
    if (!readDate(o.date))
        return false;
    if (!readDevice(o.type, o.info))
        return false;

    if (!ask("Опис несправності: ", line))
        return false;
    size_t len = strlen(line);
    if (len < 1 || len > 80) {
        cout << "Помилка: опис має містити від 1 до 80 байтів." << endl;
        return false;
    }
    strcpy(o.problem, line);

    if (!ask("Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ", line))
        return false;
    if (strlen(line) != 1 || line[0] < '1' || line[0] > '3') {
        cout << "Помилка: пріоритет має бути 1, 2 або 3." << endl;
        return false;
    }
    o.priority = line[0] - '0';

    return readPrice(o.price);
}

// Зчитує номер замовлення й перевіряє його
bool readOrderId(int &id) {
    char line[LINE_SIZE];
    if (!ask("Номер замовлення: ", line))
        return false;
    trimInPlace(line);
    bool negative = (line[0] == '-');
    const char *digits = negative ? line + 1 : line;
    if (!isDigits(digits)) {
        cout << "Помилка: номер замовлення має бути цілим числом." << endl;
        return false;
    }
    if (negative || strlen(digits) > 9) {      // такого номера бути не може
        cout << "Замовлення №" << line << " не знайдено." << endl;
        return false;
    }
    parseUInt(digits, id);
    return true;
}

//  Пункти меню
void menuAddOrder(Center &c) {
    Order o;
    if (!inputOrder(o))
        return;
    o.id = c.nextId++;
    o.status = Status::WAITING;
    o.master[0] = '\0';

    OrderNode *node = appendOrder(c.journal, o);
    pushQueue(c.queue, &node->data);
    pushAction(c.history, ActionKind::ADDED, node->data);

    cout << "Замовлення №" << o.id << " додано: вартість " << o.price
         << " грн, у черзі на ремонт: " << queueSize(c.queue) << "." << endl;
}

void printSeparator() {
    cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+" << endl;
}

// Друкує одну клітинку заголовка таблиці
void printHeaderCell(const char *text, int width) {
    int chars = 0;
    for (const char *p = text; *p; p++)
        if (((unsigned char)*p & 0xC0) != 0x80)
            chars++;
    cout << ' ' << text;
    for (int i = chars; i < width; i++)
        cout << ' ';
    cout << " |";
}

// Друкує рядок із назвами стовпців таблиці журналу.
void printHeader() {
    cout << "|";
    printHeaderCell("№", 3);
    printHeaderCell("Клієнт", 15);
    printHeaderCell("Телефон", 10);
    printHeaderCell("Дата", 10);
    printHeaderCell("Тип", 6);
    printHeaderCell("Деталі", 14);
    printHeaderCell("Пр", 2);
    printHeaderCell("Статус", 7);
    printHeaderCell("Вартість", 9);
    cout << endl;
}

// Пункт 2. Журнал замовлень
void menuShowJournal(Center &c) {
    if (c.journal.size == 0) {
        cout << "Журнал порожній." << endl;
        return;
    }
    printSeparator();
    printHeader();
    printSeparator();
    for (const OrderNode *p = c.journal.head; p != nullptr; p = p->next)
        cout << p->data << endl;
    printSeparator();
    cout << "Усього замовлень: " << c.journal.size
         << ", у черзі на ремонт: " << queueSize(c.queue) << endl;
}

// Пункт 3. Видати замовлення майстру
void menuAssignOrder(Center &c) {
    Order *o = popQueue(c.queue);
    if (o == nullptr) {
        cout << "Черга на ремонт порожня." << endl;
        return;
    }
    Master *m = takeNextMaster(c.nextMaster);
    o->status = Status::REPAIR;
    strcpy(o->master, m->name);

    cout << "Замовлення №" << o->id << " (пріоритет " << o->priority
         << ") передано майстру " << m->name << "." << endl;
    cout << "Несправність: " << o->problem << endl;
    cout << "У черзі залишилось: " << queueSize(c.queue) << endl;
}

// Пункт 4. Завершити ремонт
void menuFinishRepair(Center &c) {
    int id;
    if (!readOrderId(id))
        return;
    OrderNode *node = findById(c.journal, id);
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
    Master *m = findMaster(c.nextMaster, o.master);
    o.status = Status::DONE;
    m->done++;
    m->revenue = m->revenue + o.price;

    cout << "Ремонт замовлення №" << id << " завершено. Майстер " << m->name
         << ": виконано " << m->done << ", виручка " << m->revenue << " грн." << endl;
}

// Пункт 5. Видалити замовлення
void menuDeleteOrder(Center &c) {
    int id;
    if (!readOrderId(id))
        return;
    OrderNode *node = findById(c.journal, id);
    if (node == nullptr) {
        cout << "Замовлення №" << id << " не знайдено." << endl;
        return;
    }
    if (node->data.status != Status::WAITING) {
        cout << "Видалити можна лише замовлення, яке очікує в черзі." << endl;
        return;
    }
    pushAction(c.history, ActionKind::REMOVED, node->data);
    removeFromQueue(c.queue, &node->data);
    removeNode(c.journal, node);

    cout << "Замовлення №" << id << " видалено. У журналі: " << c.journal.size
         << ", у черзі: " << queueSize(c.queue) << "." << endl;
}

// Пункт 6. Скасувати останню дію
void menuUndo(Center &c) {
    ActionKind kind;
    Order saved;
    if (!popAction(c.history, kind, saved)) {
        cout << "Немає дій для скасування." << endl;
        return;
    }
    if (kind == ActionKind::ADDED) {
        OrderNode *node = findById(c.journal, saved.id);
        if (node == nullptr) {
            cout << "Замовлення №" << saved.id << " уже немає в журналі." << endl;
            return;
        }
        if (node->data.status != Status::WAITING) {
            cout << "Додавання замовлення №" << saved.id
                 << " скасувати неможливо: його вже передано майстру." << endl;
            return;
        }
        removeFromQueue(c.queue, &node->data);
        removeNode(c.journal, node);
        cout << "Скасовано додавання замовлення №" << saved.id
             << ": його вилучено з журналу і з черги." << endl;
    } else {
        OrderNode *node = appendOrder(c.journal, saved);
        pushQueue(c.queue, &node->data);
        cout << "Скасовано видалення замовлення №" << saved.id
             << ": його повернуто в кінець журналу і в чергу." << endl;
    }
}

// Критерій сортування звіту
bool reportBefore(const Order *a, const Order *b) {
    if (a->price < b->price)      
        return false;
    if (b->price < a->price)     
        return true;
    return a->id < b->id;         
}

// Сортує масив вказівників на замовлення сортуванням вставками 
void sortOrders(Order **arr, int n) {
    for (int i = 1; i < n; i++) {
        Order *key = arr[i];
        int j = i - 1;
        while (j >= 0 && reportBefore(key, arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Друкує майстрів по колу
void printMasters(const Center &c) {
    cout << "Майстри, починаючи з наступного в черзі:" << endl;
    const Master *p = c.nextMaster;
    do {
        cout << p->name << " виконано: " << p->done
             << ", виручка: " << p->revenue << " грн" << endl;
        p = p->next;
    } while (p != c.nextMaster);
}

// Пункт 7. Звіт
void menuReport(Center &c) {
    int n = c.journal.size;
    if (n == 0) {
        cout << "Журнал порожній." << endl;
        return;
    }
    Order **arr = new Order *[n];
    int i = 0;
    for (OrderNode *p = c.journal.head; p != nullptr; p = p->next)
        arr[i++] = &p->data;
    sortOrders(arr, n);

    cout << "Замовлення за вартістю:" << endl;
    for (i = 0; i < n; i++)
        cout << "№" << arr[i]->id << " " << arr[i]->price << " грн "
             << statusName(arr[i]->status) << endl;
    Money diff = arr[0]->price - arr[n - 1]->price;
    cout << "Різниця між найдорожчим і найдешевшим: " << diff << " грн" << endl;
    delete[] arr;

    cout << "Виручка за завершеними ремонтами: " << revenue(c.journal.head) << " грн" << endl;
    printMasters(c);
}

// Пункт 8. Розвернути журнал на місці й повідомити номери першого й останнього замовлення
void menuReverse(Center &c) {
    if (c.journal.size == 0) {
        cout << "Журнал порожній." << endl;
        return;
    }
    reverseList(c.journal);
    cout << "Журнал розвернуто: тепер першим іде замовлення №" << c.journal.head->data.id
         << ", останнім №" << c.journal.tail->data.id << "." << endl;
}

// Друкує меню програми
void printMenu() {
    cout << endl;
    cout << "Меню:" << endl;
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

// Зчитує й перевіряє вибір пункту меню
bool readChoice(int &choice) {
    char line[LINE_SIZE];
    if (!ask("Ваш вибір: ", line)) {
        choice = 0;
        return true;
    }
    trimInPlace(line);
    if (!isDigits(line)) {
        cout << "Помилка: введіть номер пункту меню." << endl;
        return false;
    }
    int value = 0;
    if (!parseUInt(line, value) || value > 8) {
        cout << "Помилка: пункту " << line << " немає в меню." << endl;
        return false;
    }
    choice = value;
    return true;
}

int main() {
    Center center;
    initCenter(center);

    if (!readMasters(center.nextMaster))
        return 1;

    int choice = -1;
    while (choice != 0) {
        printMenu();
        if (!readChoice(choice)) {
            choice = -1;
            continue;
        }
        switch (choice) {
            case 1: menuAddOrder(center);     break;
            case 2: menuShowJournal(center);  break;
            case 3: menuAssignOrder(center);  break;
            case 4: menuFinishRepair(center); break;
            case 5: menuDeleteOrder(center);  break;
            case 6: menuUndo(center);         break;
            case 7: menuReport(center);       break;
            case 8: menuReverse(center);      break;
            default: break;                   // 0 - вихід
        }
    }

    freeCenter(center);
    return 0;
}