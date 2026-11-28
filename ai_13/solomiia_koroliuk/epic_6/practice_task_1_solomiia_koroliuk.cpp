/* 
    Epic 6 Practice task: Сервісний центр: черга ремонтів
    Соломія Королюк 
    ШІ-13
*/

#include <iostream>
#include <iomanip>
#include <cstdio> //засоби C вводу і виводу
#include <cstring> //функції C рядків
#include <cctype> //перевірки й перетворення символів

using namespace std;

// ---------- Константи ----------
const int MAX_BUF     = 256;        // розмір буфера для рядка (255 символів + '\0')
const int MAX_NAME    = 24;         // імʼя майстра: 23 символи + '\0'
const int MAX_CLIENT  = 16;         // імʼя клієнта: 15 символів + '\0'
const int MAX_PHONE   = 11;         // телефон: 10 цифр + '\0'
const int MAX_SERIAL  = 12;         // серійний номер: 11 символів + '\0'
const int MAX_PROBLEM = 81;         // опис несправності: 80 байтів + '\0'
const int MAX_KOP     = 10000000;   // 100000.00 грн у копійках
const int FIRST_ID    = 101;        // перший номер замовлення

// Горизонтальна лінія таблиці журналу
const char LINE[] = "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+";

// ---------- Переліки й структури ----------
enum class DeviceType { PHONE = 1, LAPTOP, TV };
enum class Status { WAITING, REPAIR, DONE };
enum class ActionType { ADD, REMOVE };

struct Money  { int hrn; int kop; };
struct Date   { int day; int month; int year; };
struct Client { char name[MAX_CLIENT]; char phone[MAX_PHONE]; };

// яке поле заповнене, визначає поле type замовлення
union DeviceInfo {
    int imei;
    char serial[MAX_SERIAL];
    int inches;
};

struct Order {
    int id;
    Client client;
    Date date;
    DeviceType type;
    DeviceInfo info;
    char problem[MAX_PROBLEM];
    int priority;
    Money price;
    Status status;
    char master[MAX_NAME];
};

// Журнал: двозвʼязний список
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

// Пріоритетна черга: однозвʼязний список вказівників на замовлення журналу
struct QNode {
    Order *order;
    QNode *next;
};

struct PQueue {
    QNode *head;
    int size;
};

// Майстри: кільцевий список
struct Master {
    char name[MAX_NAME];
    int done;
    Money revenue;
    Master *next;
};

// Стек дій для скасування
struct Action {
    ActionType type;
    Order order;       // копія замовлення
    Action *next;
};

// Стек чисел для зворотного польського запису
struct NumNode {
    Money value;
    NumNode *next;
};

struct NumStack {
    NumNode *top;
    int size;
};

// ---------- Прототипи функцій ----------

// ввід і перевірки
bool readLine(const char *prompt, char *buf);
bool parseInt(const char *s, int &value);
bool isValidAlpha(const char *s, int maxLen);
bool isValidPhone(const char *s);
bool parseDateFormat(const char *s, Date &d);
bool isRealDate(const Date &d);
bool isLeapYear(int year);
bool readDeviceInfo(Order &o);

// Money
int toKop(const Money &m);
Money fromKop(int kop);
Money operator+(const Money &a, const Money &b);
Money operator-(const Money &a, const Money &b);
Money operator*(const Money &a, int n);
bool operator<(const Money &a, const Money &b);
ostream &operator<<(ostream &os, const Money &m);
ostream &operator<<(ostream &os, const Order &o);

// стек чисел і вираз
void pushNum(NumStack &st, const Money &m);
bool popNum(NumStack &st, Money &m);
void freeNums(NumStack &st);
bool parseMoney(const char *tok, Money &m);
bool evalRPN(const char *expr, Money &res);

// журнал
OrderNode *appendOrder(OrderList &list, const Order &o);
OrderNode *findById(const OrderList &list, int id);
void removeNode(OrderList &list, OrderNode *node);
void reverseList(OrderList &list);
Money revenue(const OrderNode *p);
void freeJournal(OrderList &list);

// черга
void insertQueue(PQueue &q, Order *o);
Order *popQueue(PQueue &q);
bool removeFromQueue(PQueue &q, const Order *o);
void freeQueue(PQueue &q);

// майстри
bool readMasters(Master *&ring);
Master *findMaster(Master *ring, const char *name);
void freeMasters(Master *&ring);

// стек дій
void pushAction(Action *&top, ActionType type, const Order &o);
Action *popAction(Action *&top);
void freeActions(Action *&top);

// допоміжне для виводу й сортування
const char *statusName(Status s);
const char *typeName(DeviceType t);
bool before(const Order *a, const Order *b);
void sortOrders(Order **arr, int n);

// пункти меню
void addOrder(OrderList &journal, PQueue &q, Action *&actions, int &nextId);
void showJournal(const OrderList &journal, const PQueue &q);
void giveOrder(PQueue &q, Master *&nextMaster);
void finishRepair(const OrderList &journal, Master *masters);
void deleteOrder(OrderList &journal, PQueue &q, Action *&actions);
void undoLast(OrderList &journal, PQueue &q, Action *&actions);
void showReport(const OrderList &journal, Master *nextMaster);
void reverseJournal(OrderList &journal);

int main() {
    Master *masters = nullptr;

    // Спочатку зчитуємо майстрів, і лише потім показуємо меню
    if (!readMasters(masters)) {
        return 1;
    }

    OrderList journal = {nullptr, nullptr, 0};
    PQueue repairQueue = {nullptr, 0};
    Action *actions = nullptr;
    Master *nextMaster = masters;   // той, хто отримає наступне замовлення
    int nextId = FIRST_ID;

    char line[MAX_BUF];
    int choice;

    do {
        printf("\n===== МЕНЮ =====\n");
        printf("1. Додати замовлення\n");
        printf("2. Журнал замовлень\n");
        printf("3. Видати замовлення майстру\n");
        printf("4. Завершити ремонт\n");
        printf("5. Видалити замовлення\n");
        printf("6. Скасувати останню дію\n");
        printf("7. Звіт\n");
        printf("8. Розвернути журнал\n");
        printf("0. Вийти\n");

        if (!readLine("Ваш вибір: ", line)) {   // кінець вводу — виходимо
            choice = 0;
            break;
        }

        // Перевірка на нечисловий ввід
        if (!parseInt(line, choice)) {
            printf("Помилка: введіть номер пункту меню.\n");
            choice = -1;           // щоб цикл не завершився випадково
            continue;
        }

        switch (choice) {
            case 1:
                addOrder(journal, repairQueue, actions, nextId);
                break;
            case 2:
                showJournal(journal, repairQueue);
                break;
            case 3:
                giveOrder(repairQueue, nextMaster);
                break;
            case 4:
                finishRepair(journal, masters);
                break;
            case 5:
                deleteOrder(journal, repairQueue, actions);
                break;
            case 6:
                undoLast(journal, repairQueue, actions);
                break;
            case 7:
                showReport(journal, nextMaster);
                break;
            case 8:
                reverseJournal(journal);
                break;
            case 0:
                printf("Ви здійснили вихід.\n");
                break;
            default:
                printf("Помилка: пункту %d немає в меню.\n", choice);
        }

    } while (choice != 0);

    // звільняємо памʼять перед виходом
    freeQueue(repairQueue);
    freeJournal(journal);
    freeActions(actions);
    freeMasters(masters);

    return 0;
}


// ---------- Допоміжні функції вводу та перевірки ----------

// Читає рядок через cin.getline; false — тільки коли ввід закінчився
bool readLine(const char *prompt, char *buf) {
    printf("%s", prompt);

    cin.getline(buf, MAX_BUF);

    if (cin.fail()) {
        if (cin.eof()) {
            return false;          // кінець вводу
        }
        // рядок задовгий для буфера: скидаємо стан і відкидаємо залишок
        cin.clear();
        cin.ignore(100000, '\n');
        buf[0] = '\0';             // порожній рядок не пройде жодну перевірку
        return true;
    }

    // прибираємо '\r' (на випадок Windows)
    int len = (int)strlen(buf);
    if (len > 0 && buf[len - 1] == '\r') {
        buf[len - 1] = '\0';
    }
    return true;
}

// Перетворює рядок із цифр (до 9) на ціле число
bool parseInt(const char *s, int &value) {
    int len = (int)strlen(s);

    if (len == 0 || len > 9) {
        return false;
    }

    value = 0;
    for (const char *p = s; *p; p++) {
        if (!isdigit((unsigned char)*p)) {
            return false;
        }
        value = value * 10 + (*p - '0');
    }
    return true;
}

// Слово з латинських літер довжиною від 1 до maxLen
bool isValidAlpha(const char *s, int maxLen) {
    int len = (int)strlen(s);

    if (len == 0 || len > maxLen) {
        return false;
    }

    for (const char *p = s; *p; p++) {
        if (!isalpha((unsigned char)*p)) {   // у локалі "C" кирилиця не літера
            return false;
        }
    }
    return true;
}

// Телефон: рівно 10 цифр, перша — 0
bool isValidPhone(const char *s) {
    if (strlen(s) != 10 || s[0] != '0') {
        return false;
    }
    for (const char *p = s; *p; p++) {
        if (!isdigit((unsigned char)*p)) {
            return false;
        }
    }
    return true;
}

// Формат ДД.ММ.РРРР: цифри й крапки на своїх місцях
bool parseDateFormat(const char *s, Date &d) {
    if (strlen(s) != 10 || s[2] != '.' || s[5] != '.') {
        return false;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit((unsigned char)s[i])) {
            return false;
        }
    }

    d.day   = (s[0] - '0') * 10 + (s[1] - '0');
    d.month = (s[3] - '0') * 10 + (s[4] - '0');
    d.year  = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 + (s[9] - '0');
    return true;
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

// Чи існує така дата (рік 2000..2099)
bool isRealDate(const Date &d) {
    static const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (d.year < 2000 || d.year > 2099 || d.month < 1 || d.month > 12) {
        return false;
    }

    int maxDay = days[d.month - 1];
    if (d.month == 2 && isLeapYear(d.year)) {
        maxDay = 29;
    }
    return d.day >= 1 && d.day <= maxDay;
}

// Зчитує дані пристрою відповідно до типу й записує в потрібне поле union
bool readDeviceInfo(Order &o) {
    char line[MAX_BUF];

    if (o.type == DeviceType::PHONE) {
        if (!readLine("Останні 6 цифр IMEI: ", line)) return false;

        bool ok = (strlen(line) == 6);
        for (const char *p = line; ok && *p; p++) {
            if (!isdigit((unsigned char)*p)) ok = false;
        }
        if (!ok) {
            printf("Помилка: потрібно рівно 6 цифр.\n");
            return false;
        }
        o.info.imei = 0;
        for (const char *p = line; *p; p++) {
            o.info.imei = o.info.imei * 10 + (*p - '0');
        }
    } else if (o.type == DeviceType::LAPTOP) {
        if (!readLine("Серійний номер (до 11 символів): ", line)) return false;

        int len = (int)strlen(line);
        bool ok = (len >= 1 && len <= 11);
        for (const char *p = line; ok && *p; p++) {
            unsigned char ch = (unsigned char)*p;
            if (!(isdigit(ch) || (isalpha(ch) && isupper(ch)))) ok = false;
        }
        if (!ok) {
            printf("Помилка: серійний номер має містити від 1 до 11 великих латинських літер і цифр.\n");
            return false;
        }
        strcpy(o.info.serial, line);
    } else {
        if (!readLine("Діагональ (дюймів): ", line)) return false;

        int v;
        if (!parseInt(line, v) || v < 19 || v > 100) {
            printf("Помилка: діагональ має бути від 19 до 100 дюймів.\n");
            return false;
        }
        o.info.inches = v;
    }
    return true;
}


// ---------- Money: оператори ----------

int toKop(const Money &m) {
    return m.hrn * 100 + m.kop;
}

Money fromKop(int kop) {
    Money m;
    m.hrn = kop / 100;
    m.kop = kop % 100;
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

// Друкує суму з двома знаками копійок
ostream &operator<<(ostream &os, const Money &m) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d.%02d", m.hrn, m.kop);
    return os << buf;
}

// Друкує один рядок таблиці журналу (без переходу на новий рядок)
ostream &operator<<(ostream &os, const Order &o) {
    char details[32];
    char price[32];
    char row[200];

    if (o.type == DeviceType::PHONE) {
        snprintf(details, sizeof(details), "IMEI %06d", o.info.imei);   // з ведучими нулями
    } else if (o.type == DeviceType::LAPTOP) {
        snprintf(details, sizeof(details), "SN %s", o.info.serial);
    } else {
        snprintf(details, sizeof(details), "%d inch", o.info.inches);
    }

    snprintf(price, sizeof(price), "%d.%02d", o.price.hrn, o.price.kop);

    snprintf(row, sizeof(row), "| %3d | %-15s | %-10s | %02d.%02d.%04d | %-6s | %-14s | %2d | %-7s | %9s |",
             o.id, o.client.name, o.client.phone, o.date.day, o.date.month, o.date.year,
             typeName(o.type), details, o.priority, statusName(o.status), price);

    return os << row;
}


// ---------- Стек чисел і обчислення виразу ----------

void pushNum(NumStack &st, const Money &m) {
    NumNode *node = new NumNode;
    node->value = m;
    node->next = st.top;
    st.top = node;
    st.size++;
}

bool popNum(NumStack &st, Money &m) {
    if (st.top == nullptr) {
        return false;
    }
    NumNode *node = st.top;
    m = node->value;
    st.top = node->next;
    delete node;
    st.size--;
    return true;
}

void freeNums(NumStack &st) {
    Money tmp;
    while (popNum(st, tmp)) {
        // просто знімаємо все зі стеку
    }
}

// Число: 1..6 цифр цілої частини і 0..2 цифри після крапки
bool parseMoney(const char *tok, Money &m) {
    int i = 0;
    int intPart = 0, intDigits = 0;

    while (isdigit((unsigned char)tok[i])) {
        intPart = intPart * 10 + (tok[i] - '0');
        intDigits++;
        i++;
        if (intDigits > 6) {
            return false;
        }
    }
    if (intDigits == 0) {
        return false;
    }

    int frac = 0;
    if (tok[i] == '.') {
        i++;
        int fracDigits = 0;
        while (isdigit((unsigned char)tok[i])) {
            frac = frac * 10 + (tok[i] - '0');
            fracDigits++;
            i++;
            if (fracDigits > 2) {
                return false;
            }
        }
        if (fracDigits == 0) {
            return false;
        }
        if (fracDigits == 1) {
            frac *= 10;            // 7.5 це 7 грн 50 коп
        }
    }

    if (tok[i] != '\0') {
        return false;
    }

    m.hrn = intPart;
    m.kop = frac;
    return true;
}

// Обчислює вираз в оберненому польському записі; при помилці друкує причину
bool evalRPN(const char *expr, Money &res) {
    NumStack st = {nullptr, 0};
    char tok[MAX_BUF];
    int tokens = 0;
    const char *p = expr;

    while (true) {
        while (*p && isspace((unsigned char)*p)) p++;
        if (*p == '\0') break;

        int len = 0;
        while (*p && !isspace((unsigned char)*p)) {
            if (len < MAX_BUF - 1) tok[len++] = *p;
            p++;
        }
        tok[len] = '\0';
        tokens++;

        bool isOp = (strcmp(tok, "+") == 0 || strcmp(tok, "-") == 0 || strcmp(tok, "*") == 0);

        if (isOp) {
            Money a, b;

            if (st.size < 2) {
                printf("Помилка у виразі: для операції «%s» бракує чисел.\n", tok);
                freeNums(st);
                return false;
            }
            popNum(st, b);   // правий операнд
            popNum(st, a);   // лівий операнд

            Money r;
            if (tok[0] == '+') {
                r = a + b;
            } else if (tok[0] == '-') {
                if (a < b) {
                    printf("Помилка у виразі: проміжний результат від'ємний.\n");
                    freeNums(st);
                    return false;
                }
                r = a - b;
            } else {
                if (b.kop != 0 || b.hrn < 1 || b.hrn > 100) {
                    printf("Помилка у виразі: множник має бути цілим числом від 1 до 100.\n");
                    freeNums(st);
                    return false;
                }
                r = a * b.hrn;   // a <= 100000.00, множник <= 100: int не переповниться
            }

            // межу перевіряємо після кожного кроку
            if (toKop(r) > MAX_KOP) {
                printf("Помилка у виразі: сума перевищує 100000.00 грн.\n");
                freeNums(st);
                return false;
            }
            pushNum(st, r);
        } else {
            Money m;
            if (!parseMoney(tok, m)) {
                printf("Помилка у виразі: «%s» не є числом або операцією.\n", tok);
                freeNums(st);
                return false;
            }
            if (toKop(m) > MAX_KOP) {
                printf("Помилка у виразі: сума перевищує 100000.00 грн.\n");
                freeNums(st);
                return false;
            }
            pushNum(st, m);
        }
    }

    if (tokens == 0) {
        printf("Помилка у виразі: порожній вираз.\n");
        return false;
    }

    if (st.size != 1) {
        printf("Помилка у виразі: у стеку залишилось чисел: %d, а має бути одне.\n", st.size);
        freeNums(st);
        return false;
    }

    popNum(st, res);

    if (toKop(res) == 0) {
        printf("Помилка у виразі: кінцевий результат не може дорівнювати 0.00.\n");
        return false;
    }
    return true;
}


// ---------- Журнал: двозвʼязний список ----------

// Додає копію замовлення в кінець журналу
OrderNode *appendOrder(OrderList &list, const Order &o) {
    OrderNode *node = new OrderNode;
    node->data = o;
    node->next = nullptr;
    node->prev = list.tail;

    if (list.tail != nullptr) {
        list.tail->next = node;
    } else {
        list.head = node;          // журнал був порожній
    }
    list.tail = node;
    list.size++;
    return node;
}

// Пошук за номером від head до tail
OrderNode *findById(const OrderList &list, int id) {
    for (OrderNode *p = list.head; p != nullptr; p = p->next) {
        if (p->data.id == id) {
            return p;
        }
    }
    return nullptr;
}

// Вилучає вузол з будь-якого місця журналу й звільняє його
void removeNode(OrderList &list, OrderNode *node) {
    if (node->prev != nullptr) {
        node->prev->next = node->next;
    } else {
        list.head = node->next;    // видаляємо голову
    }

    if (node->next != nullptr) {
        node->next->prev = node->prev;
    } else {
        list.tail = node->prev;    // видаляємо хвіст
    }

    delete node;
    list.size--;
}

// Розворот на місці: міняємо prev і next у кожному вузлі, потім head і tail
void reverseList(OrderList &list) {
    OrderNode *cur = list.head;

    while (cur != nullptr) {
        OrderNode *nxt = cur->next;   // запамʼятовуємо до обміну
        cur->next = cur->prev;
        cur->prev = nxt;
        cur = nxt;
    }

    OrderNode *tmp = list.head;
    list.head = list.tail;
    list.tail = tmp;
}

// Рекурсивно рахує виручку за завершеними ремонтами
Money revenue(const OrderNode *p) {
    if (p == nullptr) {
        return fromKop(0);
    }
    Money rest = revenue(p->next);
    if (p->data.status == Status::DONE) {
        rest = rest + p->data.price;
    }
    return rest;
}

void freeJournal(OrderList &list) {
    while (list.head != nullptr) {
        OrderNode *next = list.head->next;
        delete list.head;
        list.head = next;
    }
    list.tail = nullptr;
    list.size = 0;
}


// ---------- Пріоритетна черга ----------

// Вставляє після всіх елементів з таким самим або вищим пріоритетом
void insertQueue(PQueue &q, Order *o) {
    QNode *node = new QNode;
    node->order = o;
    node->next = nullptr;

    if (q.head == nullptr || q.head->order->priority < o->priority) {
        node->next = q.head;
        q.head = node;
    } else {
        QNode *cur = q.head;
        while (cur->next != nullptr && cur->next->order->priority >= o->priority) {
            cur = cur->next;
        }
        node->next = cur->next;
        cur->next = node;
    }
    q.size++;
}

// Забирає голову черги (nullptr, якщо черга порожня)
Order *popQueue(PQueue &q) {
    if (q.head == nullptr) {
        return nullptr;
    }
    QNode *node = q.head;
    Order *o = node->order;
    q.head = node->next;
    delete node;
    q.size--;
    return o;
}

// Вилучає конкретне замовлення з будь-якого місця черги
bool removeFromQueue(PQueue &q, const Order *o) {
    QNode *prev = nullptr;

    for (QNode *cur = q.head; cur != nullptr; prev = cur, cur = cur->next) {
        if (cur->order == o) {
            if (prev != nullptr) {
                prev->next = cur->next;
            } else {
                q.head = cur->next;
            }
            delete cur;
            q.size--;
            return true;
        }
    }
    return false;
}

void freeQueue(PQueue &q) {
    while (popQueue(q) != nullptr) {
        // самі замовлення належать журналу, тут видаляються лише вузли черги
    }
}


// ---------- Майстри: кільцевий список ----------

// Зчитує кількість і імена майстрів, будує кільце
bool readMasters(Master *&ring) {
    char line[MAX_BUF];
    int n;

    if (!readLine("Кількість майстрів (від 1 до 5): ", line)) {
        return false;
    }
    if (!parseInt(line, n) || n < 1 || n > 5) {
        printf("Помилка: кількість майстрів має бути цілим числом від 1 до 5.\n");
        return false;
    }

    if (!readLine("Імена майстрів через пробіл: ", line)) {
        return false;
    }

    char names[5][MAX_NAME];
    int count = 0;
    bool ok = true;

    for (char *t = strtok(line, " \t"); t != nullptr; t = strtok(nullptr, " \t")) {
        if (count >= n || !isValidAlpha(t, 23)) {
            ok = false;
            break;
        }
        strcpy(names[count], t);
        count++;
    }

    if (!ok || count != n) {
        printf("Помилка: кількість імен має дорівнювати %d, кожне імʼя з латинських літер, до 23 символів.\n", n);
        return false;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(names[i], names[j]) == 0) {
                printf("Помилка: імена майстрів не повинні повторюватися.\n");
                return false;
            }
        }
    }

    // будуємо кільце: останній вказує на першого
    Master *last = nullptr;
    for (int i = 0; i < n; i++) {
        Master *m = new Master;
        strcpy(m->name, names[i]);
        m->done = 0;
        m->revenue = fromKop(0);
        m->next = nullptr;

        if (last == nullptr) {
            ring = m;
        } else {
            last->next = m;
        }
        last = m;
    }
    last->next = ring;

    return true;
}

// Шукає майстра за імʼям, обходячи кільце циклом do while
Master *findMaster(Master *ring, const char *name) {
    if (ring == nullptr) {
        return nullptr;
    }

    Master *p = ring;
    do {
        if (strcmp(p->name, name) == 0) {
            return p;
        }
        p = p->next;
    } while (p != ring);

    return nullptr;
}

// Розриваємо кільце й видаляємо вузли
void freeMasters(Master *&ring) {
    if (ring == nullptr) {
        return;
    }

    Master *p = ring->next;
    ring->next = nullptr;          // розірвали кільце

    while (p != nullptr) {
        Master *next = p->next;
        delete p;
        p = next;
    }
    ring = nullptr;
}


// ---------- Стек дій ----------

void pushAction(Action *&top, ActionType type, const Order &o) {
    Action *a = new Action;
    a->type = type;
    a->order = o;
    a->next = top;
    top = a;
}

// Знімає дію з вершини; видаляти її має той, хто викликав
Action *popAction(Action *&top) {
    Action *a = top;
    if (a != nullptr) {
        top = a->next;
        a->next = nullptr;
    }
    return a;
}

void freeActions(Action *&top) {
    while (top != nullptr) {
        Action *a = popAction(top);
        delete a;
    }
}


// ---------- Вивід і сортування ----------

const char *statusName(Status s) {
    if (s == Status::WAITING) return "WAITING";
    if (s == Status::REPAIR)  return "REPAIR";
    return "DONE";
}

const char *typeName(DeviceType t) {
    if (t == DeviceType::PHONE)  return "PHONE";
    if (t == DeviceType::LAPTOP) return "LAPTOP";
    return "TV";
}

// Чи має a стояти перед b: дорожчі першими, за рівної вартості менший номер
bool before(const Order *a, const Order *b) {
    if (b->price < a->price) return true;
    if (a->price < b->price) return false;
    return a->id < b->id;
}

// Сортування вставками масиву вказівників
void sortOrders(Order **arr, int n) {
    for (int i = 1; i < n; i++) {
        Order *key = arr[i];
        int j = i - 1;

        while (j >= 0 && before(key, arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


// ---------- Пункти меню ----------

// Пункт 1: додати замовлення
void addOrder(OrderList &journal, PQueue &q, Action *&actions, int &nextId) {
    Order o;
    memset(&o, 0, sizeof(o));
    char line[MAX_BUF];
    int v;

    if (!readLine("Ім'я клієнта: ", line)) return;
    if (!isValidAlpha(line, 15)) {
        printf("Помилка: ім'я має містити від 1 до 15 латинських літер.\n");
        return;
    }
    strcpy(o.client.name, line);

    if (!readLine("Телефон (10 цифр): ", line)) return;
    if (!isValidPhone(line)) {
        printf("Помилка: телефон має складатися з 10 цифр і починатися з 0.\n");
        return;
    }
    strcpy(o.client.phone, line);

    if (!readLine("Дата прийому (ДД.ММ.РРРР): ", line)) return;
    if (!parseDateFormat(line, o.date)) {
        printf("Помилка: дата має бути у форматі ДД.ММ.РРРР.\n");
        return;
    }
    if (!isRealDate(o.date)) {
        printf("Помилка: некоректна дата.\n");
        return;
    }

    if (!readLine("Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ", line)) return;
    if (!parseInt(line, v) || v < 1 || v > 3) {
        printf("Помилка: тип пристрою має бути 1, 2 або 3.\n");
        return;
    }
    o.type = (DeviceType)v;

    if (!readDeviceInfo(o)) return;

    if (!readLine("Опис несправності: ", line)) return;
    if (strlen(line) < 1 || strlen(line) > 80) {
        printf("Помилка: опис має містити від 1 до 80 байтів.\n");
        return;
    }
    strcpy(o.problem, line);

    if (!readLine("Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ", line)) return;
    if (!parseInt(line, v) || v < 1 || v > 3) {
        printf("Помилка: пріоритет має бути 1, 2 або 3.\n");
        return;
    }
    o.priority = v;

    if (!readLine("Вартість (обернений польський запис): ", line)) return;
    if (!evalRPN(line, o.price)) {
        return;                    // причину вже виведено
    }

    // усе коректно: номер видаємо лише тепер, тому він не губиться при помилках
    o.id = nextId++;
    o.status = Status::WAITING;
    o.master[0] = '\0';

    OrderNode *node = appendOrder(journal, o);
    insertQueue(q, &node->data);
    pushAction(actions, ActionType::ADD, o);

    printf("Замовлення №%d додано: вартість ", o.id);
    cout << o.price;
    printf(" грн, у черзі на ремонт: %d.\n", q.size);
}

// Пункт 2: журнал замовлень
void showJournal(const OrderList &journal, const PQueue &q) {
    if (journal.head == nullptr) {
        printf("Журнал порожній.\n");
        return;
    }

    printf("%s\n", LINE);
    printf("| №   | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  |  Вартість |\n");
    printf("%s\n", LINE);

    for (const OrderNode *p = journal.head; p != nullptr; p = p->next) {
        cout << p->data << "\n";   // один вираз на рядок таблиці
    }

    printf("%s\n", LINE);
    printf("Усього замовлень: %d, у черзі на ремонт: %d\n", journal.size, q.size);
}

// Пункт 3: видати замовлення майстру
void giveOrder(PQueue &q, Master *&nextMaster) {
    Order *o = popQueue(q);

    if (o == nullptr) {
        printf("Черга на ремонт порожня.\n");
        return;
    }

    o->status = Status::REPAIR;
    strcpy(o->master, nextMaster->name);
    nextMaster = nextMaster->next;   // по колу

    printf("Замовлення №%d (пріоритет %d) передано майстру %s.\n", o->id, o->priority, o->master);
    printf("Несправність: %s\n", o->problem);
    printf("У черзі залишилось: %d\n", q.size);
}

// Пункт 4: завершити ремонт
void finishRepair(const OrderList &journal, Master *masters) {
    char line[MAX_BUF];
    int id;

    if (!readLine("Номер замовлення: ", line)) return;
    if (!parseInt(line, id)) {
        printf("Помилка: номер замовлення має бути цілим числом.\n");
        return;
    }

    OrderNode *node = findById(journal, id);

    if (node == nullptr) {
        printf("Замовлення №%d не знайдено.\n", id);
        return;
    }
    if (node->data.status == Status::WAITING) {
        printf("Замовлення №%d ще не передано майстру.\n", id);
        return;
    }
    if (node->data.status == Status::DONE) {
        printf("Замовлення №%d уже завершено.\n", id);
        return;
    }

    Master *m = findMaster(masters, node->data.master);

    node->data.status = Status::DONE;
    m->done++;
    m->revenue = m->revenue + node->data.price;

    printf("Ремонт замовлення №%d завершено. Майстер %s: виконано %d, виручка ", id, m->name, m->done);
    cout << m->revenue;
    printf(" грн.\n");
}

// Пункт 5: видалити замовлення
void deleteOrder(OrderList &journal, PQueue &q, Action *&actions) {
    char line[MAX_BUF];
    int id;

    if (!readLine("Номер замовлення: ", line)) return;
    if (!parseInt(line, id)) {
        printf("Помилка: номер замовлення має бути цілим числом.\n");
        return;
    }

    OrderNode *node = findById(journal, id);

    if (node == nullptr) {
        printf("Замовлення №%d не знайдено.\n", id);
        return;
    }
    if (node->data.status != Status::WAITING) {
        printf("Видалити можна лише замовлення, яке очікує в черзі.\n");
        return;
    }

    pushAction(actions, ActionType::REMOVE, node->data);   // копія для скасування
    removeFromQueue(q, &node->data);
    removeNode(journal, node);

    printf("Замовлення №%d видалено. У журналі: %d, у черзі: %d.\n", id, journal.size, q.size);
}

// Пункт 6: скасувати останню дію
void undoLast(OrderList &journal, PQueue &q, Action *&actions) {
    Action *a = popAction(actions);

    if (a == nullptr) {
        printf("Немає дій для скасування.\n");
        return;
    }

    int id = a->order.id;

    if (a->type == ActionType::ADD) {
        OrderNode *node = findById(journal, id);

        if (node != nullptr && node->data.status == Status::WAITING) {
            removeFromQueue(q, &node->data);
            removeNode(journal, node);
            printf("Додавання замовлення №%d скасовано: його вилучено з журналу і черги.\n", id);
        } else {
            printf("Додавання замовлення №%d скасувати неможливо: його вже передано майстру.\n", id);
        }
    } else {
        // повертаємо в кінець журналу й у чергу за пріоритетом
        OrderNode *node = appendOrder(journal, a->order);
        insertQueue(q, &node->data);
        printf("Скасовано видалення замовлення №%d: його повернуто в кінець журналу і в чергу.\n", id);
    }

    delete a;
}

// Пункт 7: звіт
void showReport(const OrderList &journal, Master *nextMaster) {
    if (journal.head == nullptr) {
        printf("Журнал порожній.\n");
        return;
    }

    // динамічний масив вказівників; сам журнал не змінюємо
    int n = journal.size;
    Order **arr = new Order*[n];
    int i = 0;
    for (OrderNode *p = journal.head; p != nullptr; p = p->next) {
        arr[i++] = &p->data;
    }

    sortOrders(arr, n);

    printf("Замовлення за вартістю:\n");
    for (int k = 0; k < n; k++) {
        printf("№%d ", arr[k]->id);
        cout << arr[k]->price;
        printf(" грн %s\n", statusName(arr[k]->status));
    }

    Money diff = arr[0]->price - arr[n - 1]->price;
    printf("Різниця між найдорожчим і найдешевшим: ");
    cout << diff;
    printf(" грн\n");

    printf("Виручка за завершеними ремонтами: ");
    cout << revenue(journal.head);
    printf(" грн\n");

    delete[] arr;
    arr = nullptr;

    // майстри по колу, починаючи з того, хто отримає наступне замовлення
    printf("Майстри, починаючи з наступного в черзі:\n");
    Master *m = nextMaster;
    do {
        cout << left << setw(10) << m->name << right;
        printf(" виконано: %d, виручка: ", m->done);
        cout << m->revenue;
        printf(" грн\n");
        m = m->next;
    } while (m != nextMaster);
}

// Пункт 8: розвернути журнал
void reverseJournal(OrderList &journal) {
    if (journal.head == nullptr) {
        printf("Журнал порожній.\n");
        return;
    }

    reverseList(journal);

    printf("Журнал розвернуто: тепер першим іде замовлення №%d, останнім №%d.\n",
           journal.head->data.id, journal.tail->data.id);
}
