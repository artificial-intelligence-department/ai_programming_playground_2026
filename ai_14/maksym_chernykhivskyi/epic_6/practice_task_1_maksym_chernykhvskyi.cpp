/*Epic 6 - Сервісний центр: черга ремонтів
Чернихівський Максим
Ші - 14*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_LINE = 256;
const int MAX_MASTERS = 5;
const int FIRST_ORDER_ID = 101;


// Типи техніки та дій, стан ремонту
enum class DeviceType { PHONE = 1, LAPTOP = 2, TV = 3 };
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


// union бо одночасно може бути тільки одне значення
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


// Журнал: двозв'язний список
struct OrderNode {
    Order order;
    OrderNode *prev;
    OrderNode *next;
};


struct OrderList {
    OrderNode *head;
    OrderNode *tail;
    int size;
};


// Пріоритетна черга (однозв'язний масив вказівників)
struct QNode {
    Order *order;
    QNode *next;
};


struct PriorityQueue {
    QNode *head;
    int size;
};


// Майстер: вузол кільцевого списку
struct Master {
    char name [24];
    int done;
    Money revenue;
    Master *next;
};


// Запис стеку дій
struct Action {
    ActionKind kind;
    Order order;                // копія замовлення
    Action *next;
};


// Увесь стан програми
struct Service {
    OrderList journal;
    PriorityQueue queue;
    Master *masters;            // перший введений майстер
    Master *nextMaster;         // майстер який отримає наступне замовлення
    Action *history;            // веришна стеку дій
    int nextId;
    bool eof;                   // ввід закінчився
};


// Оператори
const Money MAX_PRICE = {100000, 0}; // Максимальна вартість

Money operator+(const Money &a, const Money &b) {
    Money r;
    r.hrn = a.hrn + b.hrn;
    r.kop = a.kop + b.kop;

    if (r.kop >= 100) {
        r.kop -= 100;
        r.hrn++;
    }

    return r;
}

Money operator-(const Money &a, const Money &b) {
    Money r;
    r.hrn = a.hrn - b.hrn;
    r.kop = a.kop - b.kop;

    if (r.kop < 0) {
        r.kop += 100;
        r.hrn--;
    }
    return r;
}

Money operator*(const Money &a, int k) {
    Money r;
    r.kop = a.kop * k;
    r.hrn = a.hrn * k + r.kop / 100;
    r.kop = r.kop % 100;

    return r;
}


bool operator<(const Money &a, const Money &b) {
    return a.hrn < b.hrn || (a.hrn == b.hrn && a.kop < b.kop);
}


// Друк у форматі гривні.копійки, копійки завжди двома символами
ostream &operator<<(ostream &os, const Money &m) {
    char oldFill = os.fill(); // Запам'ятовує символ який зараз доповнює поле, пробіл за замовчуванням
    os << m.hrn << "." << setfill('0') << setw(2) << m.kop; // setfill() перетворює цей символ на "0"
    os.fill(oldFill); // Повертає пробіл
    return os;
}


void moneyToString(const Money &m, char *buf, size_t size) {
    snprintf(buf, size, "%d.%02d", m.hrn, m.kop);   // Зберігає форматований результат у buf розміром size
                                                    // snprintf а не sprintf - контроль переповнення буфера
}

// Ввід

// Зчитує рядок, повертає: 1 - ок, 0 - рядок задовгий, -1 - кінець вводу
int readLine(char *buf, int size) {
    cin.getline(buf, size);

    if (cin.fail()) {

        if (cin.eof()) {
            buf[0] = '\0';
            return -1; 
        }
        cin.clear();
        int c;

        while ((c = cin.get()) != '\n' && c != EOF) {}
        cin.clear();

        buf[0] = '\0';
        return 0;
    }
    size_t len = strlen(buf);

    while (len > 0 && buf[len - 1] == '\r') {
        buf[--len] = '\0';
    }
    return 1;
}


// Виводить підказку і зчитує рядок, повертає false якщо ввід закінчися
bool ask(Service &s, const char *prompt, char *buf) {
    cout << prompt;

    if (readLine(buf, MAX_LINE) == -1) {
        s.eof = true;
        return false;
    }
    return true;
}


// Перевірки символів
bool isDigitChar(char c) {
    return c >= '0' && c <= '9';
}

bool isLatinLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isUpperOrDigit(char c) {
    return (c >= 'A' && c <= 'Z') || isDigitChar(c);
}

// Валідація і розбір полів замовлення

// Перевірка і перетворення на додатне ціле число з не більше 9 цифр
bool parseInt(const char *s, int &value) {
    size_t len = strlen(s);

    if (len == 0 || len > 9) {
        return false;
    }
    int v = 0;

    for (size_t i = 0; i < len; i++) {
        if (!isDigitChar(s[i])) {
            return false;
        }
        v = v * 10 + (s[i] - '0'); // (s[i] - '0') Перетворює символ на числове значення
    }
    value = v;
    return true;
}


// Перевірка латинських слів - імен клієнтів і майстрів довжиною від 1 до maxLen
bool isLatinWord(const char *s, size_t maxLen) {
    size_t len = strlen(s);

    if (len == 0 || len > maxLen) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        if (!isLatinLetter(s[i])) {
            return false;
        }
    }
    return true;
}


// Перевірка номеру телефону, 10 цифер, перший нуль
bool isValidPhone(const char *s) {
    if (strlen(s) != 10 || s[0] != '0') {
        return false;
    }

    for (int i = 1; i < 10; i++) {
        if (!isDigitChar(s[i])) {
            return false;
        }
    }
    return true;
}


// Перевірка на високосний рік
bool isLeapYear(int y) {
    return (y % 4 == 0 && y && y % 100 != 0) || y % 400 == 0;
}


// Показує скільки деів у місяці
int daysInMonth(int month, int year) {
    // static щоб масив створювався 1 раз а не при кожному виклику
    static const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return days[month - 1];
}


// Перевіряє форат дати - ДД.ММ.РРРР
bool hasDateFormat(const char *s) {
    if (strlen(s) != 10 || s[2] != '.' || s[5] != '.') {
        return false;
    }

    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5 && !isDigitChar(s[i])) {
            return false;
        }
    }
    return true;
}


// Дата: формат, реальна дата, рік 2000 ... 2099
bool parseDate(const char *s, Date &d) {
    if (!hasDateFormat(s)) {
        return false;
    }
    int day = (s[0] - '0') * 10 + (s[1] - '0');
    int month = (s[3] - '0') * 10 + (s[4] - '0');
    int year = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 + (s[9] - '0');

    if (year < 2000 || year > 2099 || month < 1 || month > 12) {
        return false;
    }

    if (day < 1 || day > daysInMonth(month, year)) {
        return false;
    }
    d.day = day;
    d.month = month;
    d.year = year;
    return true;
}


// Перевіряє ІМЕІ (6 цифр)
bool parseImei(const char *s, int &imei) {
    if (strlen(s) != 6) {
        return false;
    }
    return parseInt(s, imei);
}


// Перевіряє серійний номер (1..11 символів, великі літери або цифри)
bool isValidSerial(const char *s) {
    size_t len = strlen(s);

    if (len == 0 || len > 11) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        if (!isUpperOrDigit(s[i])) {
            return false;
        }
    }
    return true;
}


// Перевіряє діагональ (ціле число від 19 до 100)
bool parseInches(const char *s, int &inches) {
    int v;

    if (!parseInt(s, v) || v < 19 || v > 100) {
        return false;
    }
    inches = v;
    return true;
}


// Перевірка опису несправності (1..80 байтів)
bool isValidProblem(const char *s) {
    size_t len = strlen(s);
    return len >= 1 && len <= 80;
}


// Стек чисел для evalRPN (однозв'язний список)
struct NumNode {
    Money value;
    NumNode *next;
};


// Створює вузол, кладе в нього число, робить його вершиною
void pushNum(NumNode *&top, const Money &value) {
    NumNode *node = new NumNode;
    node -> value = value;
    node -> next = top;
    top = node;
}


// Повертає число з вершини, false якщо стек порожній
bool popNum(NumNode *&top, Money &value) {
    if (top == nullptr) {
        return false;
    }
    NumNode *node = top;
    value = node -> value;
    top = node -> next;

    delete node;
    return true;
}


// Рахує числа в стеку
int countNums(const NumNode *top) {
    int n = 0;

    for (const NumNode *p = top; p != nullptr; p = p -> next) {
        n++;
    }
    return n;
}


// Звільняє весь стек
void freeNums(NumNode *&top) {
    while (top != nullptr) {
        NumNode *next = top -> next;
        delete top;
        top = next;
    }
}

// Обернений польський запис

// Перевіряє чи є токен числом у форматі вартості і розкладає його на гривні і копійки
bool parseMoney(const char *s, Money &out) {
    int i = 0, hrn = 0, digits = 0;

    while(isDigitChar(s[i])) {
        hrn = hrn * 10 + (s[i] - '0');
        i++;
        digits++;
        if (digits > 6) {
            return false;
        }
    }

    if (digits == 0) {
        return false;
    }
    int kop = 0;

    if (s[i] == '.') {
        i++;
        int frac = 0;

        while (isDigitChar(s[i])) {
            kop = kop * 10 + (s[i] - '0');
            i++;
            frac++;

            if (frac > 2) {
                return false;
            }
        }
        if (frac == 0) {
            return false;
        }
        if (frac == 1) {
            kop *= 10;
        }
    }
    if (s[i] != '\0') {
        return false;
    }
    out.hrn = hrn;
    out.kop = kop;
    return true;
}


// Перевіряє чи токен є знаком операції
bool isOperator(const char *tok) {
    if (tok[1] != '\0') {
        return false;
    }
    return tok[0] == '+' || tok[0] == '-' || tok[0] == '*';
}


// Застосовує операцію до двох верхніх чисел стеку, при помилці виводить повідомлення
bool applyOperator(NumNode *&top, char op) {
    Money a, b;

    if (!popNum(top, b) || !popNum(top, a)) {
        cout << "Помилка у виразі: для операції " << op << " бракує чисел.\n";
        return false;
    }
    Money r;
    if (op == '+') {
        r = a + b;
    } else if (op == '-') {
        if (a < b) {
            cout << "Помилка у виразі, проміжний результат від'ємний.\n";
            return false;
        }
        r = a - b;
    } else {
        // Правий операнд - кількість деталей: ціле від 1 до 100
        if (b.kop != 0 || b.hrn < 1 || b.hrn > 100) {
            cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100.\n";
            return false;
        }
        r = a * b.hrn;
    }
    if (MAX_PRICE < r) {
        cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
        return false;
    }
    pushNum(top, r);
    return true;
}


// Обчислює вираз вартості
bool evalRPN(const char *expr, Money &res) {
    char buf[MAX_LINE];
    strncpy(buf, expr, MAX_LINE - 1);
    buf[MAX_LINE - 1] = '\0';

    NumNode *top = nullptr;
    int tokens = 0;
    bool ok = true;

    for(char *tok = strtok(buf, " "); tok != nullptr && ok; tok = strtok(nullptr, " ")) {
        tokens++;

        if (isOperator(tok)) {
            ok = applyOperator(top, tok[0]);
        } else {
            Money m;

            if (!parseMoney(tok, m)) {
                cout << "Помилка у виразі: \"" << tok << "\" не є числом або операцією.\n";
                ok = false;
            } else if (MAX_PRICE < m) {
                cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                ok = false;
            } else {
                pushNum(top, m);
            }
        }
    }
    if (ok && tokens == 0) {
        cout << "Помилка: порожній вираз.\n";
        ok = false;
    }
    if (ok) {
        int left = countNums(top);

        if (left != 1) {
            cout << "Помилка у виразі: у стеку залишилось чисел: " << left << ", а має бути одне.\n";
            ok = false;
        }
    }
    if (ok) {
        Money result;
        popNum(top, result);

        if (result.hrn == 0 && result.kop == 0) {
            cout << "Помилка у виразі: вартість не може дорівнювати 0.00.\n";
            ok = false;
        } else {
            res = result;
        }
    }
    freeNums(top);
    return ok;
}

// Вивід замовлення

// Назва типу пристрою
const char *typeName(DeviceType t) {
    switch (t) {
        case DeviceType::PHONE:
            return "PHONE";
        case DeviceType::LAPTOP:
            return "LAPTOP";
        default:
            return "TV";
    }
}


// Назва статусу замовлення
const char *statusName(Status s) {
    switch (s) {
        case Status::WAITING:
            return "WAITING";
        case Status::REPAIR:
            return "REPAIR";
        default:
            return "DONE";
    }
}


// Формує текст для стовпця Деталі, записує в buf
void detailsToString(const Order &o, char *buf, size_t size) {
    // union зберігає три варіанти в одному місці пам'яті, o.type показує яке чинне
    switch(o.type) {
        case DeviceType::PHONE:
            snprintf(buf, size, "IMEI %06d", o.info.imei);
            break;
        case DeviceType::LAPTOP:
            snprintf(buf, size, "SN %s", o.info.serial);
            break;
        default:
            snprintf(buf, size, "%d inch", o.info.inches);
            break;
    }
}


// Один рядок таблиці фурналу
ostream &operator<<(ostream &os, const Order &o) {
    char details[32], price[16], line[200];

    detailsToString(o, details, sizeof(details));
    moneyToString(o.price, price, sizeof(price));

    snprintf(line, sizeof(line), "| %3d | %-15s | %-10s | %02d.%02d.%04d | %-6s | %-14s | %2d | %-7s | %9s |",
        o.id, o.client.name, o.client.phone, o.date.day, o.date.month, o.date.year, typeName(o.type), details,
        o.priority, statusName(o.status), price);

    return os << line;
}

// Журнал: двозв'язний список

// Ініціалізує список
void initList(OrderList &l) {
    l.head = nullptr;   
    l.tail = nullptr;   
    l.size = 0;
}


// Додає копію замовлення в кінець журналу
OrderNode *appendOrder(OrderList &l, const Order &o) {
    OrderNode *node = new OrderNode;
    node -> order = o;
    node -> prev = l.tail;
    node -> next = nullptr;

    if (l.tail != nullptr) {
        l.tail -> next = node;
    } else {
        l.head = node;
    }
    l.tail = node;
    l.size++;
    return node;
}


// Лінійний пошук замовлення за номером
OrderNode *findById(const OrderList &list, int id) {
    for (OrderNode *p = list.head; p != nullptr; p = p-> next) {

        if (p -> order.id == id) {
            return p;
        }
    }
    return nullptr;
}


// Вилучає вузол з будь - якого мсця журналу
void removeNode(OrderList &l, OrderNode *n) {
    if (n -> prev != nullptr) {
        n -> prev -> next = n -> next;
    } else {
        l.head = n -> next;
    }

    if (n -> next != nullptr) {
        n -> next -> prev = n -> prev;
    } else {
        l.tail = n -> prev;
    }

    delete n;
    l.size--;
}


// Розворот на місці - у кожному вузлі міняє prev і next, а потім head і tail
void reverseList(OrderList &l) {
    OrderNode *p = l.head;

    while (p != nullptr) {
        OrderNode *next = p -> next;
        p -> next = p -> prev;
        p -> prev = next;
        p = next;
    }
    OrderNode *tmp = l.head;
    l.head = l.tail;
    l.tail = tmp;
}


// Знищує список
void freeList(OrderList &l) {
    while (l.head != nullptr) {
        OrderNode *next = l.head -> next;
        delete l.head;
        l.head = next;
    }
    l.tail = nullptr;
    l.size = 0;
}


// Виручка за завершеними ремонтами (рекурсивно)
Money revenue(const OrderNode *p) {
    if (p == nullptr) {
        Money zero = {0, 0};
        return zero;
    }
    Money rest = revenue(p -> next);
    if (p -> order.status == Status::DONE) {
        rest = rest + p -> order.price;
    }
    return rest;
}

// Пріроритетна черга

// Ініціалізація
void initQueue(PriorityQueue &q) {
    q.head = nullptr;
    q.size = 0;
}


// Вставка після всіх замовлень з пріоритетом більшим за новий
void enqueue(PriorityQueue &q, Order *o) {
    QNode *node = new QNode;
    node -> order = o;
    node -> next = nullptr;
    
    // Якщо черга порожня або в нового замовлення вищий пріоритет - вставка на початок
    if (q.head == nullptr || q.head -> order -> priority < o -> priority) {
        node -> next = q.head;
        q.head = node;
    } else {
        QNode *p = q.head;

        // Пропускає всі елементи з вищим і таким самим пріоритетом щоб знайти позицію для вставки
        while (p -> next != nullptr && p -> next -> order -> priority >= o -> priority) {
            p = p -> next;
        }
        node -> next = p -> next;
        p -> next = node;
    }
    q.size++;
}


// Знімає замовлення з голови черги
Order *dequeue(PriorityQueue &q) {
    if (q.head == nullptr) {
        return nullptr;
    }

    QNode *node = q.head;
    Order *o = node -> order;
    q.head = node -> next;
    delete node;
    q.size--;
    return o;
}


// Вилучає з черги конкретне замовлення
bool removeFromQueue(PriorityQueue &q, const Order *o) {
    QNode *prev = nullptr;

    for (QNode *p = q.head; p != nullptr; prev = p, p = p -> next) {

        if (p -> order == o) {

            if (prev != nullptr) {
                prev -> next = p -> next;
            } else {
                q.head = p -> next;
            }
            delete p;
            q.size--;
            return true;
        }
    }
    return false;
}


// Звільняє вузли черги
void freeQueue(PriorityQueue &q) {
    while (q.head != nullptr) {
        QNode *next = q.head -> next;
        delete q.head;
        q.head = next;
    }
    q.size = 0;
}

// Майстри, кільцевий список 

// Створює кільце з n майстрів, повертає першого
Master *createMasters(char names [][24], int n) {
    Master *first = nullptr;
    Master *last = nullptr;

    for (int i = 0; i< n; i++) {
        Master *m = new Master;
        strcpy(m -> name, names[i]);
        m -> done = 0;
        m -> revenue.hrn = 0;
        m -> revenue.kop = 0;
        m -> next = nullptr;

        if (last != nullptr) {
            last -> next = m;
        } else {
            first = m;
        }
        last = m;
    }
    last -> next = first; // Замикаємо кільце
    return first;
} 


// Шукає майстра за іменем
Master *findMaster(Master *first, const char *name) {
    Master *m = first;
    do {
        if (strcmp(m -> name, name) == 0) {
            return m;
        }
        m = m -> next;
    } while (m != first);
    return nullptr;
}


// Звільняє усе кільце майстрів
void freeMasters(Master *&first) {
    if (first == nullptr) {
        return;
    }
    Master *last = first;

    while (last -> next != first) {
        last = last -> next;
    }
    last -> next = nullptr; // Розриваємо кільце

    while (first != nullptr) {
        Master *next = first -> next;
        delete first;
        first = next;
    }
}

// Стек дій

// Кладе запис про дію на вершину стеку для скасування дій
void pushAction(Action *&top, ActionKind kind, const Order &order) {
    Action *a = new Action;
    a -> kind = kind;
    a -> order = order;
    a -> next = top;
    top = a;
}


// Знімає дію з вершини, повертає false якщо стек порожній
bool popAction(Action *&top, ActionKind &kind, Order &order) {
    if (top == nullptr) {
        return false;
    }
    Action *a = top;
    kind = a -> kind;
    order = a -> order;
    top = a -> next;
    delete a;
    return true;
}


// Видалає весь стек дій
void freeActions(Action *&top) {
    while (top != nullptr) {
        Action *next = top -> next;
        delete top;
        top = next;
    }
}


// Готує стан програми
void initService(Service &s) {
        initList(s.journal);
        initQueue(s.queue);

        s.masters = nullptr;
        s.nextMaster = nullptr;
        s.history = nullptr;
        s.nextId = FIRST_ORDER_ID;
        s.eof = false;
}


// Видаляє стан програми
void freeService(Service &s) {
    freeActions(s.history); 
    freeQueue(s.queue);
    freeList(s.journal);
    freeMasters(s.masters);

    s.nextMaster = nullptr;
}


// Зчитує кількість майстрів та їхні імена
bool readMasters(Service &s) {
    char line[MAX_LINE];
    int n;
    
    cout << "Кількість майстрів (від 1 до 5): ";

    if (readLine(line, MAX_LINE) == -1) {
        cout << "Помилка: порожній ввід.\n";
        return false;
    }

    if (!parseInt(line, n) || n < 1 || n > MAX_MASTERS) {
        cout << "Помилка: кількість майстрів має бути від 1 до 5.\n";
        return false;
    }

    cout << "Імена майстрів через пробіл: ";

    if (readLine(line, MAX_LINE) == -1) {
        cout << "Помилка: порожній ввід.\n";
        return false;
    }
    char names[MAX_MASTERS][24];
    int count = 0;
    bool valid = true;

    for (char *tok = strtok(line, " "); tok != nullptr; tok = strtok(nullptr, " ")) {

        if (count >= n || !isLatinWord(tok, 23)) {
            valid = false;
            break;
        }
        strcpy(names[count++], tok);            
    }

    if (!valid || count != n) {
        cout << "Помилка: кількість імен має дорівнювати " << n << ", кожне ім'я до 23 латинських літер.\n";
        return false;
    }

    for (int i = 0; i < n; i++) {

        for (int j = i + 1; j < n; j++) {

            if (strcmp(names[i], names[j]) == 0) {
                cout << "Помилка: імена майстрів не повинні повторюватися.\n";
                return false;
            }
        }
    }
    s.masters = createMasters(names, n);
    s.nextMaster = s.masters;
    return true;
}


// 1. Додати замовлення, Будь - яка помилка скасовує дію
void addOrder(Service &s) {
    Order o;
    memset(&o, 0, sizeof(o)); // Обнуляє всі поля структури та union щоб прибрати сміття з пам'яті
    char line[MAX_LINE];
    int value;

    // Ім'я
    if (!ask(s, "Ім'я клієнта: ", line)) {
        return;
    }
    if (!isLatinWord(line, 15)) {
        cout << "Помилка: ім'я має містити від 1 до 15 латинських літер.\n";
        return;
    }
    strcpy(o.client.name, line);
    
    // Телефон
    if (!ask(s, "Телефон клієнта (10 цифр): ", line)) {
        return;
    }
    if (!isValidPhone(line)) {
        cout << "Помилка: телефон має складатись з 10 цифр і починатись з 0.\n";
        return;
    }
    strcpy(o.client.phone, line);
    // Дата
    if (!ask(s, "Дата прийому (ДД.ММ.РРРР): ", line)) {
        return;
    }
    if (!hasDateFormat(line)) {
        cout << "Помилка: дата має бути у форматі ДД.ММ.РРРР.\n";
        return;
    }
    if (!parseDate(line, o.date)) {
        cout << "Помилка: некоректна дата.\n";
        return;
    }

    // Тип пристрою
    if (!ask(s, "Тип пристрою (1 - телефон, 2 - ноутбук, 3 - телевізор): ", line)) {
        return;
    }
    if (!parseInt(line, value) || value < 1 || value > 3) {
        cout << "Помилка: тип пристрою має бути 1, 2 або 3.\n";
        return;
    }
    o.type = static_cast<DeviceType>(value); // Перетворює введене число 1-3 у відповідний тип пристрою enum

    // Характеристика пристрою за типом
    if (o.type == DeviceType::PHONE) {

        // Телефон - ІМЕІ
        if (!ask(s, "Останні 6 цифр IMEI: ", line)) {
            return;
        }
        if (!parseImei(line, o.info.imei)) {
            cout << "Помилка: потрібно рівно 6 цифр.\n";
            return;
        }
    } else if (o.type == DeviceType::LAPTOP) {
        
        // Ноутбук - серійний номер
        if (!ask(s, "Серійний номер (до 11 великих латинських літер і цифр): ", line)) {
            return;
        }
        if (!isValidSerial(line)) {
            cout << "Помилка: серійний номер має містити від 1 до 11 великих латинських літер і цифр.\n";
            return;
        }
        strcpy(o.info.serial, line);
    } else if (o.type == DeviceType::TV) {

        // Телевізор - діагональ
        if (!ask(s, "Діагональ (дюймів, від 19 до 100): ", line)) {
            return;
        }
        if (!parseInches(line, o.info.inches)) {
            cout << "Помилка: діагональ має бути цілим числом від 19 до 100.\n";
            return;
        }
    }

    // Опис несправності
    if (!ask(s, "Опис несправності: ", line)) {
        return;
    }
    if (!isValidProblem(line)) {
        cout << "Помилка: опис має містити від 1 до 80 байтів.\n";
        return;
    }
    strcpy(o.problem, line);

    // Пріоритет
    if (!ask(s, "Пріоритет (1 - звичайний, 2 - підвищений, 3 - терміновий): ", line)) {
        return;
    }
    if (!parseInt(line, value) || value < 1 || value > 3) {
        cout << "Помилка: пріоритет має бути 1, 2 або 3.\n";
        return;
    }
    o.priority = value;

    // Вартість
    if (!ask(s, "Вартість (обернений польський запис): ", line)) {
        return;
    }
    if (!evalRPN(line, o.price)) {
        // Повідомлення вивела функція 
        return;
    }

    // Усі дані коректні, видаємо номер, статус, додаємо в чергу
    o.id = s.nextId++;
    o.status = Status::WAITING;
    o.master[0] = '\0';

    OrderNode *node = appendOrder(s.journal, o);
    enqueue(s.queue, &node -> order);
    pushAction(s.history, ActionKind::ADD, o);

    cout << "Замовлення №" << o.id << " додано: вартість " << o.price
            << " грн, у черзі на ремонт: " << s.queue.size << ".\n";
} 


// 2. Журнал замовлень
void showJournal(const Service &s) {
    if (s.journal.head == nullptr) {
        cout << "Журнал порожній.\n";
        return;    
    }
    const char *border = "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+";

    cout << border << "\n";
    printf("|  %3s  | %-21s | %-17s | %-14s | %-9s | %-20s | %-4s | %-13s | %17s |\n","№",
             "Клієнт","Телефон", "Дата", "Тип", "Деталі", "Пр", "Статус", "Вартість");
        
    cout << border << "\n";
    
    for (const OrderNode *p = s.journal.head; p != nullptr; p = p -> next) {
        cout << p -> order << "\n";
    }
    
    cout << border << "\n";

    cout << "Усього замовлень: " << s.journal.size << ", у черзі на ремонт: " << s.queue.size << "\n";
}


// 3. Видати замовлення майстру
void assignOrder(Service &s) {
    Order *o = dequeue(s.queue);

    if (o == nullptr) {
        cout << "Черга на ремонт порожня.\n";
        return;    
    }
    Master *m = s.nextMaster;
    s.nextMaster = m -> next;

    o -> status = Status::REPAIR;
    strcpy(o -> master, m -> name);

    cout << "Замовлення №" << o -> id << " (пріоритет "<<o -> priority
                        <<") передано майстру " << m -> name << ".\n";

    cout << "Несправність: " << o -> problem << "\n";
    cout << "У черзі залишилось: " << s.queue.size << "\n";
}


// Зчитує номер замовлення і шукає його в журналі
OrderNode *askOrder(Service &s) {
    char line[MAX_LINE];
    int id;

    if (!ask(s, "Номер замовлення: ", line)) {
        return nullptr;
    }

    if (!parseInt(line, id)) {
        cout << "Помилка: замовлення має бути цілим числом.\n";
        return nullptr;
    }
    OrderNode *node = findById(s.journal, id);

    if (node == nullptr) {
        cout << "Замовлення №" << id << " не знайдено.\n";
    }
    return node;
}


// 4. Завершити ремонт
void finishRepair(Service &s) {
    OrderNode *node = askOrder(s);

    if (node == nullptr) {
        return;
    }
    Order &o = node -> order;

    if (o.status == Status::WAITING) {
        cout << "Замовлення №" << o.id << " ще не передано майстру.\n";
        return;
    }

    if (o.status == Status::DONE) {
        cout << "Замовлення №" << o.id << " вже завершено.\n";
        return;
    }
    o.status = Status::DONE;
    Master *m = findMaster(s.masters, o.master);

    m -> done++;
    m -> revenue = m -> revenue + o.price;

    cout << "Ремонт замовлення №" << o.id << " завершено.\n";
    cout << "Майстер " << m -> name << ": виконано " << m -> done << ", виручка " << m -> revenue << " грн.\n";
}


// 5. Видалити замовлення (лише WAITING)
void deleteOrder(Service &s) {
    OrderNode *node = askOrder(s);

    if (node == nullptr) {
        return;
    }

    if (node -> order.status != Status::WAITING) {
        cout << "Видалити можна лише замовлення, яке очікує в черзі.\n";
        return;
    }
    Order copy = node -> order;

    removeFromQueue(s.queue, &node -> order);
    removeNode(s.journal, node);
    pushAction(s.history, ActionKind::REMOVE, copy);

    cout << "Замовлення №" << copy.id << " видалено. У журналі: " <<
            s.journal.size<< ", у черзі: " << s.queue.size << ".\n";
}


// 6. Скасувати останню дію
void undoLast(Service &s) {
    ActionKind kind;
    Order order;

    if (!popAction(s.history, kind, order)) {
        cout << "Немає дій для скасування.\n";
        return;
    }

    if (kind == ActionKind::ADD) {
        OrderNode *node = findById(s.journal, order.id);

        if (node != nullptr && node -> order.status == Status::WAITING) {
            removeFromQueue(s.queue, &node -> order);
            removeNode(s.journal, node);
            cout << "Скасовано додавання замовлення №" << order.id << ".\n";
        } else {
            cout << "Додавання замовлення №" << order.id << " скасувати неможливо: його вже передано майстру.\n";
        }
    } else {
        OrderNode *node = appendOrder(s.journal, order);
        enqueue(s.queue, &node -> order);
        cout << "Скасовано видалення замовлення №" << order.id << ": його повернуто в кінець журналу і в чергу.\n";
    }
}


// Перевіряє чи повинне замовлення a стояти у звіті раніше за b:
// дорожче - раніше, за рівної вартості - менший номер
bool reportBefore(const Order *a, const Order *b) {
    if (b -> price < a -> price) {
        return true;
    }
    if (a -> price < b -> price) {
        return false;
    }
    return a -> id < b -> id;
}


// Insertion sort масива вказівників
void sortReport(Order **arr, int n) {
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


// 7. Звіт
void showReport(const Service &s) {
    if (s.journal.size == 0) {
        cout << "Журнал порожній.\n";
    } else {
        Order **arr = new Order *[s.journal.size];
        int n = 0;

        for (OrderNode *p = s.journal.head; p != nullptr; p = p -> next) {
            arr[n++] = &p -> order;
        }
        sortReport(arr, n);

        cout << "Замовлення за вартістю:\n";

        for (int i = 0; i < n; i++) {
            char price[16];
            moneyToString(arr[i] -> price, price, sizeof(price));

            char line[96];
            snprintf(line, sizeof(line), " №%d%11s грн  %s", arr[i] -> id, price, statusName(arr[i] -> status));

            cout << line << "\n";
        }
        Money diff = arr[0] -> price - arr [n - 1] -> price;
        cout << "Різниця між найдорожчим і найдешевшим: " << diff << " грн\n";
        delete[] arr;
    }
    cout << "Виручка за завершеними ремонтами: " << revenue(s.journal.head) << " грн\n";

    cout << "Майстри, починаючи з наступного в черзі:\n";
    const Master *m = s.nextMaster;

    do {
        char revenueText[16];
        moneyToString(m -> revenue, revenueText, sizeof(revenueText));

        char line[96];
        snprintf(line, sizeof(line), "  %-12s виконано: %d, виручка: %s грн", m -> name, m -> done, revenueText);

        cout << line << "\n";
        m = m -> next;
    } while (m != s.nextMaster);
}


// 8. Розвернути журнал
void reverseJournal(Service &s) {
    if (s.journal.head == nullptr) {
        cout << "Журнал порожній.\n";
        return;
    }
    reverseList(s.journal);
    cout << "Журнал розвернуто: тепер першим іде замовлення №" << s.journal.head -> order.id
                                    <<", останнім №" << s.journal.tail -> order.id << ".\n";
}


// Друкує розділювач для меню
void printLine() {
    cout << "===============================\n";
}


// Друкує меню
void printMenu() {
    cout << "\n";
    printLine();
    cout << "Меню:\n";
    cout << "1. Додати замовлення\n";
    cout << "2. Журнал замовлень\n";
    cout << "3. Видати замовлення майстру\n";
    cout << "4. Завершити ремонт\n";
    cout << "5. Видалити замовлення\n";
    cout << "6. Скасувати останню дію\n";
    cout << "7. Звіт\n";
    cout << "8. Розвернути журнал\n";
    cout << "0. Вийти\n";
    printLine();
}


int main() {
    Service s;
    initService(s);

    if (!readMasters(s)) {
        return 1;
    }

    char line[MAX_LINE];
    bool run = true;

    while (run && !s.eof) {
        printMenu();

        if (!ask(s, "Ваш вибір: ", line)) {
            break;
        }
        int choice;

        if (!parseInt(line, choice)) {
            cout << "Помилка: введіть номер пункту меню.\n";
            continue;
        }
        printLine();

        switch (choice) {
            case 1:
                addOrder(s);
                break;
            case 2:
                showJournal(s);
                break;
            case 3:
                assignOrder(s);
                break;
            case 4:
                finishRepair(s);
                break;
            case 5:
                deleteOrder(s);
                break;
            case 6:
                undoLast(s);
                break;
            case 7:
                showReport(s);
                break;
            case 8:
                reverseJournal(s);
                break;
            case 0:
                run = false;
                break;
            default:
                cout << "Помилка: пункту " << choice << " немає в меню.\n";
                break;            
        }
    }
    freeService(s);
    return 0;
}