// Плахтина Дмитро
//ШІ-11
// Сервісний центр: черга ремонтів
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;
enum class DeviceType { PHONE = 1, LAPTOP, TV };
enum class Status { WAITING, REPAIR, DONE };
enum class ActionType { ADD, DEL };

// гроші
struct Money {
    int hrn;
    int kop;
};

// дата
struct Date {
    int d;
    int m;
    int y;
};

// клієнт
struct Client {
    char name[16];
    char phone[11];
};

// дані пристрою
union DeviceInfo {
    int imei;
    char serial[12];
    int inches;
};

//замовлення
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

// вузол журналу
struct OrderNode {
    Order data;
    OrderNode *prev;
    OrderNode *next;
};

// журнал
struct OrderList {
    OrderNode *head = nullptr;
    OrderNode *tail = nullptr;
    int size = 0;
};

// вузол черги 
struct QNode {
    Order *order;
    QNode *next;
};

// майстер (вузол кільця)
struct Master {
    char name[24];
    int done;
    Money earned;
    Master *next;
};

// запис у стеку дій
struct Action {
    ActionType type;
    Order copy;
    Action *next;
};

// вузол стеку чисел для виразу вартості
struct NumNode {
    int val;
    NumNode *next;
};

OrderList journal;
QNode *queueHead = nullptr;
Action *actions = nullptr;
Master *masters = nullptr;
Master *curMaster = nullptr;
NumNode *numTop = nullptr;
int nextId = 101;

int toKop(const Money &m) {
    return m.hrn * 100 + m.kop;
}

Money fromKop(int k) {
    Money m;
    m.hrn = k / 100;
    m.kop = k % 100;
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

// друкує суму
ostream &operator<<(ostream &os, const Money &m) {
    os << m.hrn << ".";
    if (m.kop < 10) os << "0";
    os << m.kop;
    return os;
}

// читає рядок. false — якщо ввід закінчився
bool readLine(char *buf, int size) {
    if (cin.getline(buf, size)) {
        return true;
    }
    if (cin.eof()) {
        buf[0] = '\0';
        return false;
    }
    cin.clear();
    cin.ignore(100000, '\n');
    buf[0] = '\0';
    return true;
}

// чи це число (і яке)
bool isNumber(const char *s, int &x) {
    int len = strlen(s);
    if (len == 0 || len > 9) return false;
    x = 0;
    for (int i = 0; i < len; i++) {
        if (!isdigit(s[i])) return false;
        x = x * 10 + (s[i] - '0');
    }
    return true;
}

// чи це слово з латинських літер
bool isLatinWord(const char *s, int maxLen) {
    int len = strlen(s);
    if (len == 0 || len > maxLen) return false;
    for (int i = 0; i < len; i++) {
        bool small = (s[i] >= 'a' && s[i] <= 'z');
        bool big = (s[i] >= 'A' && s[i] <= 'Z');
        if (!small && !big) return false;
    }
    return true;
}

// 10 цифр, перша 0
bool isPhone(const char *s) {
    if (strlen(s) != 10 || s[0] != '0') return false;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

// дата ДД.ММ.РРРР
bool isDate(const char *s, Date &dt) {
    if (strlen(s) != 10 || s[2] != '.' || s[5] != '.') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(s[i])) return false;
    }
    dt.d = (s[0] - '0') * 10 + (s[1] - '0');
    dt.m = (s[3] - '0') * 10 + (s[4] - '0');
    dt.y = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 + (s[9] - '0');
    if (dt.y < 2000 || dt.y > 2099) return false;
    if (dt.m < 1 || dt.m > 12) return false;

    int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (dt.y % 4 == 0) days[2] = 29;   // високосний рік
    if (dt.d < 1 || dt.d > days[dt.m]) return false;
    return true;
}

// рівно 6 цифр
bool isImei(const char *s, int &x) {
    if (strlen(s) != 6) return false;
    return isNumber(s, x);
}

// до 11 великих літер і цифр
bool isSerial(const char *s) {
    int len = strlen(s);
    if (len == 0 || len > 11) return false;
    for (int i = 0; i < len; i++) {
        bool big = (s[i] >= 'A' && s[i] <= 'Z');
        if (!big && !isdigit(s[i])) return false;
    }
    return true;
}

// покласти число
void pushNum(int v) {
    NumNode *n = new NumNode;
    n->val = v;
    n->next = numTop;
    numTop = n;
}

// зняти число
int popNum() {
    NumNode *t = numTop;
    int v = t->val;
    numTop = numTop->next;
    delete t;
    return v;
}

// очистити стек чисел
void freeNums() {
    while (numTop != nullptr) {
        popNum();
    }
}

bool parseMoney(const char *s, int &kop) {
    int i = 0;
    int hrn = 0;
    int digits = 0;
    while (isdigit(s[i])) {
        hrn = hrn * 10 + (s[i] - '0');
        digits++;
        i++;
    }
    if (digits < 1 || digits > 6) return false;
    int k = 0;
    if (s[i] == '.') {
        i++;
        if (!isdigit(s[i])) return false;
        k = (s[i] - '0') * 10;
        i++;
        if (isdigit(s[i])) {
            k = k + (s[i] - '0');
            i++;
        }
    }
    if (s[i] != '\0') return false;
    kop = hrn * 100 + k;
    return true;
}

bool evalRPN(const char *expr, Money &res) {
    const int LIMIT = 10000000;
    char buf[256];
    strcpy(buf, expr);
    int count = 0;

    char *tok = strtok(buf, " ");
    while (tok != nullptr) {
        bool isOp = strlen(tok) == 1 && (tok[0] == '+' || tok[0] == '-' || tok[0] == '*');

        if (isOp) {
            if (count < 2) {
                cout << "Помилка у виразі: для операції «" << tok << "» бракує чисел." << endl;
                freeNums();
                return false;
            }
            int b = popNum();
            int a = popNum();
            count = count - 2;

            int r;
            if (tok[0] == '+') {
                r = a + b;
            } else if (tok[0] == '-') {
                r = a - b;
            } else {
                if (b % 100 != 0 || b / 100 < 1 || b / 100 > 100) {
                    cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100." << endl;
                    freeNums();
                    return false;
                }
                r = a * (b / 100);
            }

            if (r < 0) {
                cout << "Помилка у виразі: проміжний результат від'ємний." << endl;
                freeNums();
                return false;
            }
            if (r > LIMIT) {
                cout << "Помилка у виразі: сума перевищує 100000.00 грн." << endl;
                freeNums();
                return false;
            }
            pushNum(r);
            count++;
        } else {
            int v;
            if (!parseMoney(tok, v)) {
                cout << "Помилка у виразі: «" << tok << "» не є числом або операцією." << endl;
                freeNums();
                return false;
            }
            if (v > LIMIT) {
                cout << "Помилка у виразі: сума перевищує 100000.00 грн." << endl;
                freeNums();
                return false;
            }
            pushNum(v);
            count++;
        }
        tok = strtok(nullptr, " ");
    }
    // перевірки в кінці
    if (count == 0) {
        cout << "Помилка у виразі: порожній вираз." << endl;
        return false;
    }
    if (count > 1) {
        cout << "Помилка у виразі: у стеку залишилось чисел: " << count << ", а має бути одне." << endl;
        freeNums();
        return false;
    }
    int result = popNum();
    if (result == 0) {
        cout << "Помилка у виразі: вартість має бути більшою за 0.00 грн." << endl;
        return false;
    }
    res = fromKop(result);
    return true;
}
// додати майстра в кільце
void addMaster(const char *name) {
    Master *m = new Master;
    strcpy(m->name, name);
    m->done = 0;
    m->earned = Money{0, 0};
    // перший майстер вказує сам на себе
    if (masters == nullptr) {
        masters = m;
        m->next = m;
        return;
    }
    // шукаємо останнього
    Master *p = masters;
    while (p->next != masters) {
        p = p->next;
    }
    p->next = m;
    m->next = masters;
}
// знайти майстра за ім'ям
Master *findMaster(const char *name) {
    Master *p = masters;
    do {
        if (strcmp(p->name, name) == 0) return p;
        p = p->next;
    } while (p != masters);
    return nullptr;
}
// ввід майстрів
bool readMasters() {
    char buf[256];
    int n;
    cout << "Кількість майстрів (від 1 до 5): ";
    readLine(buf, 256);
    if (!isNumber(buf, n) || n < 1 || n > 5) {
        cout << "Помилка: кількість майстрів має бути цілим числом від 1 до 5." << endl;
        return false;
    }

    cout << "Імена майстрів через пробіл: ";
    readLine(buf, 256);

    // ріжемо на слова
    char *words[5];
    int count = 0;
    bool ok = true;
    char *w = strtok(buf, " ");
    while (w != nullptr) {
        if (count >= n || !isLatinWord(w, 23)) {
            ok = false;
            break;
        }
        words[count] = w;
        count++;
        w = strtok(nullptr, " ");
    }
    if (!ok || count != n) {
        cout << "Помилка: кількість імен має дорівнювати " << n
             << ", кожне ім'я з латинських літер, до 23 символів." << endl;
        return false;
    }

    // чи немає повторів
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                cout << "Помилка: імена майстрів не повинні повторюватися." << endl;
                return false;
            }
        }
    }
    // будуємо кільце
    for (int i = 0; i < n; i++) {
        addMaster(words[i]);
    }
    curMaster = masters;
    return true;
}

// видалити майстрів (спершу розриваємо кільце)
void freeMasters() {
    if (masters == nullptr) return;
    Master *p = masters->next;
    masters->next = nullptr;
    while (p != nullptr) {
        Master *t = p;
        p = p->next;
        delete t;
    }
    masters = nullptr;
    curMaster = nullptr;
}

// додати в кінець журналу
OrderNode *pushBack(OrderList &list, const Order &o) {
    OrderNode *n = new OrderNode;
    n->data = o;
    n->next = nullptr;
    n->prev = list.tail;
    if (list.tail != nullptr) list.tail->next = n;
    else list.head = n;         // журнал був порожній
    list.tail = n;
    list.size++;
    return n;
}

// знайти за номером
OrderNode *findById(const OrderList &list, int id) {
    OrderNode *p = list.head;
    while (p != nullptr) {
        if (p->data.id == id) return p;
        p = p->next;
    }
    return nullptr;
}

// видалити вузол з журналу
void removeNode(OrderList &list, OrderNode *p) {
    if (p->prev != nullptr) p->prev->next = p->next;
    else list.head = p->next;       // p був першим
    if (p->next != nullptr) p->next->prev = p->prev;
    else list.tail = p->prev;       // p був останнім
    list.size--;
    delete p;
}

// розвернути журнал
void reverseList(OrderList &list) {
    OrderNode *p = list.head;
    while (p != nullptr) {
        OrderNode *t = p->next;
        p->next = p->prev;
        p->prev = t;
        p = t;                      // далі
    }
    OrderNode *t = list.head;
    list.head = list.tail;
    list.tail = t;
}

// очистити журнал
void freeList(OrderList &list) {
    while (list.head != nullptr) {
        OrderNode *t = list.head;
        list.head = list.head->next;
        delete t;
    }
    list.tail = nullptr;
    list.size = 0;
}

// виручка за завершеними (рекурсія)
Money revenue(const OrderNode *p) {
    if (p == nullptr) return Money{0, 0};
    Money rest = revenue(p->next);
    if (p->data.status == Status::DONE) return rest + p->data.price;
    return rest;
}

// поставити в чергу за пріоритетом
void enqueue(Order *o) {
    QNode *n = new QNode;
    n->order = o;
    n->next = nullptr;
    // на початок
    if (queueHead == nullptr || queueHead->order->priority < o->priority) {
        n->next = queueHead;
        queueHead = n;
        return;
    }
    // за всіма з таким самим або вищим пріоритетом
    QNode *p = queueHead;
    while (p->next != nullptr && p->next->order->priority >= o->priority) {
        p = p->next;
    }
    n->next = p->next;
    p->next = n;
}

// забрати перше з черги
Order *dequeue() {
    if (queueHead == nullptr) return nullptr;
    QNode *t = queueHead;
    Order *o = t->order;
    queueHead = queueHead->next;
    delete t;
    return o;
}

// прибрати замовлення з черги
void removeFromQueue(Order *o) {
    QNode *prev = nullptr;
    QNode *p = queueHead;
    while (p != nullptr && p->order != o) {
        prev = p;
        p = p->next;
    }
    if (p == nullptr) return;
    if (prev == nullptr) queueHead = p->next;
    else prev->next = p->next;
    delete p;
}

// розмір черги
int queueSize() {
    int count = 0;
    QNode *p = queueHead;
    while (p != nullptr) {
        count++;
        p = p->next;
    }
    return count;
}

// очистити чергу
void freeQueue() {
    while (queueHead != nullptr) {
        dequeue();
    }
}

//записати дію
void pushAction(ActionType type, const Order &o) {
    Action *a = new Action;
    a->type = type;
    a->copy = o;
    a->next = actions;
    actions = a;
}

//очистити стек дій
void freeActions() {
    while (actions != nullptr) {
        Action *t = actions;
        actions = actions->next;
        delete t;
    }
}

const char *typeName(DeviceType t) {
    if (t == DeviceType::PHONE) return "PHONE";
    if (t == DeviceType::LAPTOP) return "LAPTOP";
    return "TV";
}

const char *statusName(Status s) {
    if (s == Status::WAITING) return "WAITING";
    if (s == Status::REPAIR) return "REPAIR";
    return "DONE";
}

//рядок таблиці журналу
ostream &operator<<(ostream &os, const Order &o) {
    char date[11];
    sprintf(date, "%02d.%02d.%04d", o.date.d, o.date.m, o.date.y);

    char details[20];
    if (o.type == DeviceType::PHONE) sprintf(details, "IMEI %06d", o.info.imei);
    else if (o.type == DeviceType::LAPTOP) sprintf(details, "SN %s", o.info.serial);
    else sprintf(details, "%d inch", o.info.inches);

    char price[16];
    sprintf(price, "%d.%02d", o.price.hrn, o.price.kop);

    return os << "| " << right << setw(3) << o.id << " | " << left << setw(15) << o.client.name<< " | " << o.client.phone<< " | " << date<< " | " << left << setw(6) << typeName(o.type)<< " | " << left << setw(14) << details<< " | " << right << setw(2) << o.priority<< " | " << left << setw(7) << statusName(o.status) << " | " << right << setw(9) << price << " |";
}

//додати замовлення
void menuAdd() {
    char buf[256];
    Order o;

    cout << "Ім'я клієнта: ";
    if (!readLine(buf, 256)) return;
    if (!isLatinWord(buf, 15)) {
        cout << "Помилка: ім'я має містити від 1 до 15 латинських літер." << endl;
        return;
    }
    strcpy(o.client.name, buf);

    cout << "Телефон (10 цифр): ";
    if (!readLine(buf, 256)) return;
    if (!isPhone(buf)) {
        cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0." << endl;
        return;
    }
    strcpy(o.client.phone, buf);

    cout << "Дата прийому (ДД.ММ.РРРР): ";
    if (!readLine(buf, 256)) return;
    if (!isDate(buf, o.date)) {
        cout << "Помилка: некоректна дата." << endl;
        return;
    }
    cout << "Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ";
    if (!readLine(buf, 256)) return;
    int type;
    if (!isNumber(buf, type) || type < 1 || type > 3) {
        cout << "Помилка: тип пристрою має бути 1, 2 або 3." << endl;
        return;
    }
    o.type = (DeviceType)type;

    if (o.type == DeviceType::PHONE) {
        cout << "Останні 6 цифр IMEI: ";
        if (!readLine(buf, 256)) return;
        if (!isImei(buf, o.info.imei)) {
            cout << "Помилка: потрібно рівно 6 цифр." << endl;
            return;
        }
    } else if (o.type == DeviceType::LAPTOP) {
        cout << "Серійний номер (до 11 великих латинських літер і цифр): ";
        if (!readLine(buf, 256)) return;
        if (!isSerial(buf)) {
            cout << "Помилка: серійний номер має містити від 1 до 11 великих латинських літер і цифр." << endl;
            return;
        }
        strcpy(o.info.serial, buf);
    } else {
        cout << "Діагональ (від 19 до 100 дюймів): ";
        if (!readLine(buf, 256)) return;
        if (!isNumber(buf, o.info.inches) || o.info.inches < 19 || o.info.inches > 100) {
            cout << "Помилка: діагональ має бути цілим числом від 19 до 100." << endl;
            return;
        }
    }
    cout << "Опис несправності: ";
    if (!readLine(buf, 256)) return;
    int len = strlen(buf);
    if (len < 1 || len > 80) {
        cout << "Помилка: опис має містити від 1 до 80 байтів." << endl;
        return;
    }
    strcpy(o.problem, buf);
    cout << "Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ";
    if (!readLine(buf, 256)) return;
    if (!isNumber(buf, o.priority) || o.priority < 1 || o.priority > 3) {
        cout << "Помилка: пріоритет має бути 1, 2 або 3." << endl;
        return;
    }

    cout<< "Вартість (обернений польський запис): ";
    if (!readLine(buf, 256)) return;
    if (!evalRPN(buf, o.price)) {
        return;
    }
    // усе добре, додаємо
    o.id = nextId;
    nextId++;
    o.status = Status::WAITING;
    o.master[0] = '\0';

    OrderNode *node = pushBack(journal, o);
    enqueue(&node->data);
    pushAction(ActionType::ADD, o);

    cout << "Замовлення №" << o.id << " додано: вартість " << o.price
         << " грн, у черзі на ремонт: " << queueSize() << "." << endl;
}

//журнал
void menuJournal() {
    if (journal.size == 0) {
        cout << "Журнал порожній." << endl;
        return;
    }
    const char *line = "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+";
    cout << line << endl;
    cout << "|   № | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  |  Вартість |" << endl;
    cout << line << endl;

    OrderNode *p = journal.head;
    while (p != nullptr) {
        cout << p->data << endl;
        p = p->next;
    }
    cout << line << endl;
    cout << "Усього замовлень: " << journal.size << ", у черзі на ремонт: " << queueSize() << endl;
}

//видати майстру
void menuGive() {
    Order *o = dequeue();
    if (o == nullptr) {
        cout << "Черга на ремонт порожня." << endl;
        return;
    }
    o->status = Status::REPAIR;
    strcpy(o->master, curMaster->name);

    cout << "Замовлення №" << o->id << " (пріоритет " << o->priority << ") передано майстру " << curMaster->name << "." << endl;
    cout << "Несправність: " << o->problem << endl;
    cout << "У черзі залишилось: " << queueSize() << endl;

    curMaster = curMaster->next;
}

// ввести номер і знайти замовлення
OrderNode *readOrderId() {
    char buf[256];
    cout << "Номер замовлення: ";
    if(!readLine(buf, 256)) return nullptr;
    int id;
    if( !isNumber(buf, id)){
        cout << "Помилка: номер замовлення має бути цілим числом." << endl;
        return nullptr;
    }
    OrderNode *node = findById(journal, id);
    if (node == nullptr) {
        cout << "Замовлення №" << id << " не знайдено." << endl;
    }
    return node;
}
void menuFinish() {
    OrderNode *node = readOrderId();
    if (node == nullptr) return;
    Order &o = node->data;

    if (o.status ==Status::WAITING){
        cout << "Замовлення №" << o.id << " ще не передано майстру." << endl;
        return;
    }
    if(o.status== Status::DONE) {
        cout << "Замовлення №" << o.id << " уже завершено." << endl;
        return;
    }

    o.status = Status::DONE;
    Master *m = findMaster(o.master);
    m->done++;
    m->earned = m->earned + o.price;

    cout << "Ремонт замовлення №" << o.id << " завершено. Майстер " << m->name
         << ": виконано " << m->done << ", виручка " << m->earned << " грн." << endl;
}

// видалити замовлення
void menuDelete() {
    OrderNode *node = readOrderId();
    if(node == nullptr) return;

    if(node->data.status != Status::WAITING) {
        cout << "Видалити можна лише замовлення, яке очікує в черзі." << endl;
        return;
    }
    int id = node->data.id;
    pushAction(ActionType::DEL, node->data);
    removeFromQueue(&node->data);
    removeNode(journal, node);

    cout<< "Замовлення №" << id << " видалено. У журналі: " << journal.size
         << ", у черзі: " << queueSize() << "." << endl;
}

// скасувати
void menuUndo() {
    if (actions == nullptr) {
        cout << "Немає дій для скасування." << endl;
        return;
    }
    Action *a = actions;
    actions = actions->next;
    if (a->type == ActionType::ADD) {
        OrderNode *node = findById(journal, a->copy.id);
        if (node == nullptr || node->data.status != Status::WAITING) {
            cout << "Додавання замовлення №" << a->copy.id
                 << " скасувати неможливо: його вже передано майстру." << endl;
        } else {
            removeFromQueue(&node->data);
            removeNode(journal, node);
            cout << "Скасовано додавання замовлення №" << a->copy.id
                 << ": його вилучено з журналу і черги." << endl;
        }
    } else {
        OrderNode *node = pushBack(journal, a->copy);
        enqueue(&node->data);
        cout << "Скасовано видалення замовлення №" << a->copy.id
             << ": його повернуто в кінець журналу і в чергу." << endl;
    }
    delete a;
}
void menuReport() {
    if (journal.size == 0){
        cout << "Журнал порожній." << endl;
        return;
    }
    // масив адрес
    int n = journal.size;
    Order **arr = new Order*[n];
    OrderNode *p = journal.head;
    for (int i = 0; i < n; i++) {
        arr[i] = &p->data;
        p = p->next;
    }
    // бульбашка
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            bool cheaper = arr[j]->price < arr[j + 1]->price;
            bool samePrice = !(arr[j]->price < arr[j + 1]->price) && !(arr[j + 1]->price < arr[j]->price);
            if (cheaper || (samePrice && arr[j]->id > arr[j + 1]->id)) {
                Order *t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
    cout << "Замовлення за вартістю:" << endl;
    for (int i = 0; i < n; i++) {
        char price[16];
        sprintf(price, "%d.%02d", arr[i]->price.hrn, arr[i]->price.kop);
        cout << "  №" << arr[i]->id << right << setw(11) << price << " грн  "
             << statusName(arr[i]->status) << endl;
    }
    cout<< "Різниця між найдорожчим і найдешевшим: " << arr[0]->price - arr[n - 1]->price << " грн" << endl;
    delete[] arr;

    cout << "Виручка за завершеними ремонтами: " << revenue(journal.head) << " грн" << endl;

    // майстри по колу
    cout << "Майстри, починаючи з наступного в черзі:" << endl;
    Master *m = curMaster;
    do {
        cout << "  " << left << setw(12) << m->name << " виконано: " << m->done
             << ", виручка: " << m->earned << " грн" << endl;
        m = m->next;
    } while (m != curMaster);
}
//розвернути журнал
void menuReverse(){
    if (journal.size == 0) {
        cout << "Журнал порожній." << endl;
        return;
    }
    reverseList(journal);
    cout << "Журнал розвернуто: тепер першим іде замовлення №" << journal.head->data.id
         << ", останнім №" << journal.tail->data.id << "." << endl;
}

// звільнити всю пам'ять
void freeAll(){
    freeQueue();
    freeList(journal);
    freeActions();
    freeMasters();
}
// меню
void printMenu() {
    cout << endl;
    cout<< "1. Додати замовлення" << endl;
    cout << "2. Журнал замовлень" << endl;
    cout<< "3. Видати замовлення майстру" << endl;
    cout << "4. Завершити ремонт" << endl;
    cout<< "5. Видалити замовлення" << endl;
    cout<< "6. Скасувати останню дію" << endl;
    cout<< "7. Звіт" << endl;
    cout << "8. Розвернути журнал" << endl;
    cout << "0. Вийти" << endl;
}
int main() {
    // спершу майстри
    if (!readMasters()) {
        return 0;
    }
    // меню до виходу
    char buf[256];
    while (true){
        printMenu();
        cout << "Ваш вибір: ";
        if (!readLine(buf, 256)){
            break;
        }
        int choice;
        if (!isNumber(buf, choice)) {
            cout << "Помилка: введіть номер пункту меню." << endl;
            continue;
        }
        if (choice == 0) break;
        else if (choice == 1) menuAdd();
        else if(choice == 2) menuJournal();
        else if(choice == 3) menuGive();
        else if (choice == 4) menuFinish();
        else if(choice == 5) menuDelete();
        else if (choice == 6) menuUndo();
        else if(choice == 7) menuReport();
        else if (choice == 8) menuReverse();
        else cout << "Помилка: пункту " << choice << " немає в меню." << endl;
    }
    freeAll();
    return 0;
}