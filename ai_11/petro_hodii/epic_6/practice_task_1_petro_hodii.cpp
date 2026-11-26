#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

enum class DeviceType { PHONE = 1, LAPTOP, TV };
enum class Status { WAITING, REPAIR, DONE };
enum class ActionType { ADD, DELETE };

struct Money {
    int hrn;
    int kop;
};

Money operator+(const Money &a, const Money &b) {
    int totalKop = a.kop + b.kop;
    return Money{a.hrn + b.hrn + totalKop / 100, totalKop % 100};
}

Money operator-(const Money &a, const Money &b) {
    int totalA = a.hrn * 100 + a.kop;
    int totalB = b.hrn * 100 + b.kop;
    int diff = totalA - totalB;
    if (diff < 0) diff = 0;
    return Money{diff / 100, diff % 100};
}

Money operator*(const Money &m, int count) {
    long long totalKop = (1LL * m.hrn * 100 + m.kop) * count;
    return Money{static_cast<int>(totalKop / 100), static_cast<int>(totalKop % 100)};
}

bool operator<(const Money &a, const Money &b) {
    if (a.hrn != b.hrn) return a.hrn < b.hrn;
    return a.kop < b.kop;
}

ostream &operator<<(ostream &os, const Money &m) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d.%02d", m.hrn, m.kop);
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
    char masterName[24];
};

ostream &operator<<(ostream &os, const Order &o) {
    char priceBuf[32];
    snprintf(priceBuf, sizeof(priceBuf), "%d.%02d", o.price.hrn, o.price.kop);
    char detailBuf[32];
    if (o.type == DeviceType::PHONE) {
        snprintf(detailBuf, sizeof(detailBuf), "IMEI %06d", o.info.imei);
    } else if (o.type == DeviceType::LAPTOP) {
        snprintf(detailBuf, sizeof(detailBuf), "SN %s", o.info.serial);
    } else {
        snprintf(detailBuf, sizeof(detailBuf), "%d inch", o.info.inches);
    }
    const char *typeStr = (o.type == DeviceType::PHONE ? "PHONE" :
                          (o.type == DeviceType::LAPTOP ? "LAPTOP" : "TV"));
    const char *statusStr = (o.status == Status::WAITING ? "WAITING" :
                            (o.status == Status::REPAIR ? "REPAIR" : "DONE"));
    char dateBuf[16];
    snprintf(dateBuf, sizeof(dateBuf), "%02d.%02d.%04d", o.date.day, o.date.month, o.date.year);

    char rowBuf[256];
    snprintf(rowBuf, sizeof(rowBuf),
             "| %3d | %-15s | %-10s | %-10s | %-6s | %-14s | %2d | %-7s | %9s |",
             o.id, o.client.name, o.client.phone, dateBuf,
             typeStr, detailBuf, o.priority, statusStr, priceBuf);
    os << rowBuf;
    return os;
}

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

struct QNode {
    Order *order;
    QNode *next;
};

struct Master {
    char name[24];
    int completedCount;
    Money revenue;
    Master *next;
};

struct Action {
    ActionType type;
    Order order;
    Action *next;
};

struct NumNode {
    Money val;
    NumNode *next;
};

static void clearNumStack(NumNode *&top, int &size) {
    while (top) {
        NumNode *tmp = top;
        top = top->next;
        delete tmp;
    }
    size = 0;
}

static bool parseMoneyToken(const char *token, Money &m) {
    if (!token || !*token) return false;
    int dotPos = -1;
    int len = 0;
    while (token[len]) {
        if (token[len] == '.') {
            if (dotPos != -1) return false;
            dotPos = len;
        } else if (!isdigit(static_cast<unsigned char>(token[len]))) {
            return false;
        }
        len++;
    }
    int intDigits = (dotPos == -1) ? len : dotPos;
    if (intDigits < 1 || intDigits > 6) return false;

    int fracDigits = 0;
    if (dotPos != -1) {
        fracDigits = len - dotPos - 1;
        if (fracDigits < 1 || fracDigits > 2) return false;
    }

    int hrn = 0;
    for (int i = 0; i < intDigits; ++i) {
        hrn = hrn * 10 + (token[i] - '0');
    }

    int kop = 0;
    if (fracDigits == 1) {
        kop = (token[dotPos + 1] - '0') * 10;
    } else if (fracDigits == 2) {
        kop = (token[dotPos + 1] - '0') * 10 + (token[dotPos + 2] - '0');
    }

    m.hrn = hrn;
    m.kop = kop;
    return true;
}

bool evalRPN(const char *expr, Money &res) {
    if (!expr) {
        cout << "Помилка у виразі: порожній вираз.\n";
        return false;
    }

    const char *scan = expr;
    while (*scan && isspace(static_cast<unsigned char>(*scan))) scan++;
    if (!*scan) {
        cout << "Помилка у виразі: порожній вираз.\n";
        return false;
    }

    NumNode *stack = nullptr;
    int stackSize = 0;

    const char *p = expr;
    while (*p) {
        while (*p && isspace(static_cast<unsigned char>(*p))) p++;
        if (!*p) break;

        char token[128];
        int tLen = 0;
        while (*p && !isspace(static_cast<unsigned char>(*p))) {
            if (tLen < 127) {
                token[tLen++] = *p;
            }
            p++;
        }
        token[tLen] = '\0';

        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0) {
            if (stackSize < 2) {
                cout << "Помилка у виразі: для операції «" << token << "» бракує чисел.\n";
                clearNumStack(stack, stackSize);
                return false;
            }

            Money b = stack->val;
            NumNode *tmpB = stack;
            stack = stack->next;
            delete tmpB;

            Money a = stack->val;
            NumNode *tmpA = stack;
            stack = stack->next;
            delete tmpA;
            stackSize -= 2;

            if (strcmp(token, "+") == 0) {
                Money c = a + b;
                if (c.hrn > 100000 || (c.hrn == 100000 && c.kop > 0)) {
                    cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                    clearNumStack(stack, stackSize);
                    return false;
                }
                stack = new NumNode{c, stack};
                stackSize++;
            } else if (strcmp(token, "-") == 0) {
                if (a < b) {
                    cout << "Помилка у виразі: проміжний результат від'ємний.\n";
                    clearNumStack(stack, stackSize);
                    return false;
                }
                Money c = a - b;
                stack = new NumNode{c, stack};
                stackSize++;
            } else {
                if (b.kop != 0 || b.hrn < 1 || b.hrn > 100) {
                    cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100.\n";
                    clearNumStack(stack, stackSize);
                    return false;
                }
                long long totalKop = (1LL * a.hrn * 100 + a.kop) * b.hrn;
                if (totalKop > 10000000LL) {
                    cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                    clearNumStack(stack, stackSize);
                    return false;
                }
                Money c = a * b.hrn;
                stack = new NumNode{c, stack};
                stackSize++;
            }
        } else {
            Money m;
            if (!parseMoneyToken(token, m)) {
                cout << "Помилка у виразі: «" << token << "» не є числом або операцією.\n";
                clearNumStack(stack, stackSize);
                return false;
            }
            if (m.hrn > 100000 || (m.hrn == 100000 && m.kop > 0)) {
                cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                clearNumStack(stack, stackSize);
                return false;
            }
            stack = new NumNode{m, stack};
            stackSize++;
        }
    }

    if (stackSize > 1) {
        cout << "Помилка у виразі: у стеку залишилось чисел: " << stackSize << ", а має бути одне.\n";
        clearNumStack(stack, stackSize);
        return false;
    }

    if (stackSize == 1) {
        Money finalVal = stack->val;
        clearNumStack(stack, stackSize);
        if (finalVal.hrn == 0 && finalVal.kop == 0) {
            cout << "Помилка у виразі: кінцевий результат не може бути 0.00 грн.\n";
            return false;
        }
        res = finalVal;
        return true;
    }

    cout << "Помилка у виразі: порожній вираз.\n";
    return false;
}

void initOrderList(OrderList &list) {
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

OrderNode *findById(const OrderList &list, int id) {
    OrderNode *curr = list.head;
    while (curr) {
        if (curr->order.id == id) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

void addOrderLast(OrderList &list, const Order &order) {
    OrderNode *newNode = new OrderNode{order, list.tail, nullptr};
    if (list.tail) {
        list.tail->next = newNode;
    } else {
        list.head = newNode;
    }
    list.tail = newNode;
    list.size++;
}

void removeOrderNode(OrderList &list, OrderNode *node) {
    if (!node) return;
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        list.head = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    } else {
        list.tail = node->prev;
    }
    list.size--;
    delete node;
}

void freeOrderList(OrderList &list) {
    OrderNode *curr = list.head;
    while (curr) {
        OrderNode *nxt = curr->next;
        delete curr;
        curr = nxt;
    }
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

void pushQueue(QNode *&qHead, int &qSize, Order *order) {
    QNode *newNode = new QNode{order, nullptr};
    qSize++;
    if (!qHead) {
        qHead = newNode;
        return;
    }
    if (qHead->order->priority < order->priority) {
        newNode->next = qHead;
        qHead = newNode;
        return;
    }
    QNode *curr = qHead;
    while (curr->next && curr->next->order->priority >= order->priority) {
        curr = curr->next;
    }
    newNode->next = curr->next;
    curr->next = newNode;
}

Order *popQueue(QNode *&qHead, int &qSize) {
    if (!qHead) return nullptr;
    QNode *tmp = qHead;
    Order *ord = tmp->order;
    qHead = qHead->next;
    delete tmp;
    qSize--;
    return ord;
}

bool removeFromQueue(QNode *&qHead, int &qSize, int id) {
    if (!qHead) return false;
    if (qHead->order->id == id) {
        QNode *tmp = qHead;
        qHead = qHead->next;
        delete tmp;
        qSize--;
        return true;
    }
    QNode *curr = qHead;
    while (curr->next && curr->next->order->id != id) {
        curr = curr->next;
    }
    if (curr->next) {
        QNode *tmp = curr->next;
        curr->next = tmp->next;
        delete tmp;
        qSize--;
        return true;
    }
    return false;
}

void freeQueue(QNode *&qHead, int &qSize) {
    QNode *curr = qHead;
    while (curr) {
        QNode *nxt = curr->next;
        delete curr;
        curr = nxt;
    }
    qHead = nullptr;
    qSize = 0;
}

void pushAction(Action *&top, ActionType type, const Order &order) {
    Action *newNode = new Action{type, order, top};
    top = newNode;
}

void freeActionStack(Action *&top) {
    Action *curr = top;
    while (curr) {
        Action *nxt = curr->next;
        delete curr;
        curr = nxt;
    }
    top = nullptr;
}

Master *findMaster(Master *head, const char *name) {
    if (!head || !name) return nullptr;
    Master *curr = head;
    do {
        if (strcmp(curr->name, name) == 0) {
            return curr;
        }
        curr = curr->next;
    } while (curr != head);
    return nullptr;
}

void freeMasters(Master *&head) {
    if (!head) return;
    Master *p = head;
    while (p->next && p->next != head) {
        p = p->next;
    }
    p->next = nullptr;
    Master *curr = head;
    while (curr) {
        Master *nxt = curr->next;
        delete curr;
        curr = nxt;
    }
    head = nullptr;
}

Money revenue(const OrderNode *p) {
    if (!p) {
        return Money{0, 0};
    }
    Money rest = revenue(p->next);
    if (p->order.status == Status::DONE) {
        return p->order.price + rest;
    }
    return rest;
}

bool readLine(char *buf, int maxLen) {
    if (!cin.getline(buf, maxLen)) {
        return false;
    }
    int len = strlen(buf);
    while (len > 0 && (buf[len - 1] == '\r' || buf[len - 1] == '\n')) {
        buf[--len] = '\0';
    }
    return true;
}

void trimWhitespace(char *str) {
    if (!str) return;
    int start = 0;
    while (str[start] && isspace(static_cast<unsigned char>(str[start]))) start++;
    int end = strlen(str) - 1;
    while (end >= start && isspace(static_cast<unsigned char>(str[end]))) end--;
    int i = 0;
    for (int j = start; j <= end; ++j) {
        str[i++] = str[j];
    }
    str[i] = '\0';
}

bool isAllLatin(const char *str) {
    if (!str || !*str) return false;
    for (int i = 0; str[i]; ++i) {
        char c = str[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            return false;
        }
    }
    return true;
}

bool isAllDigits(const char *str) {
    if (!str || !*str) return false;
    for (int i = 0; str[i]; ++i) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    return true;
}

bool isValidClientName(const char *str) {
    int len = strlen(str);
    if (len < 1 || len > 15) return false;
    return isAllLatin(str);
}

bool isValidPhone(const char *str) {
    if (strlen(str) != 10) return false;
    if (str[0] != '0') return false;
    for (int i = 0; i < 10; ++i) {
        if (str[i] < '0' || str[i] > '9') return false;
    }
    return true;
}

bool isValidDate(const char *str, Date &d) {
    if (strlen(str) != 10) return false;
    if (str[2] != '.' || str[5] != '.') return false;
    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) continue;
        if (str[i] < '0' || str[i] > '9') return false;
    }
    int day = (str[0] - '0') * 10 + (str[1] - '0');
    int month = (str[3] - '0') * 10 + (str[4] - '0');
    int year = (str[6] - '0') * 1000 + (str[7] - '0') * 100 + (str[8] - '0') * 10 + (str[9] - '0');

    if (year < 2000 || year > 2099) return false;
    if (month < 1 || month > 12) return false;

    bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    int daysInMonth[] = {0, 31, isLeap ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day < 1 || day > daysInMonth[month]) return false;

    d.day = day;
    d.month = month;
    d.year = year;
    return true;
}

bool isValidSerial(const char *str) {
    int len = strlen(str);
    if (len < 1 || len > 11) return false;
    for (int i = 0; i < len; ++i) {
        char c = str[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) {
            return false;
        }
    }
    return true;
}

void handleAddOrder(OrderList &list, QNode *&qHead, int &qSize, Action *&actionTop, int &nextOrderId) {
    char nameBuf[128];
    cout << "Ім'я клієнта: ";
    if (!readLine(nameBuf, sizeof(nameBuf))) return;
    trimWhitespace(nameBuf);
    if (!isValidClientName(nameBuf)) {
        cout << "Помилка: ім'я має містити від 1 до 15 латинських літер.\n";
        return;
    }

    char phoneBuf[128];
    cout << "Телефон (10 цифр): ";
    if (!readLine(phoneBuf, sizeof(phoneBuf))) return;
    trimWhitespace(phoneBuf);
    if (!isValidPhone(phoneBuf)) {
        cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0.\n";
        return;
    }

    char dateBuf[128];
    Date date;
    cout << "Дата прийому (ДД.ММ.РРРР): ";
    if (!readLine(dateBuf, sizeof(dateBuf))) return;
    trimWhitespace(dateBuf);
    if (!isValidDate(dateBuf, date)) {
        cout << "Помилка: некоректна дата.\n";
        return;
    }

    char typeBuf[128];
    cout << "Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ";
    if (!readLine(typeBuf, sizeof(typeBuf))) return;
    trimWhitespace(typeBuf);
    if (strcmp(typeBuf, "1") != 0 && strcmp(typeBuf, "2") != 0 && strcmp(typeBuf, "3") != 0) {
        cout << "Помилка: тип пристрою має бути 1, 2 або 3.\n";
        return;
    }
    DeviceType type = static_cast<DeviceType>(typeBuf[0] - '0');

    DeviceInfo info;
    memset(&info, 0, sizeof(info));
    if (type == DeviceType::PHONE) {
        char imeiBuf[128];
        cout << "Останні 6 цифр IMEI: ";
        if (!readLine(imeiBuf, sizeof(imeiBuf))) return;
        trimWhitespace(imeiBuf);
        if (strlen(imeiBuf) != 6 || !isAllDigits(imeiBuf)) {
            cout << "Помилка: потрібно рівно 6 цифр.\n";
            return;
        }
        int imeiVal = 0;
        for (int i = 0; i < 6; ++i) {
            imeiVal = imeiVal * 10 + (imeiBuf[i] - '0');
        }
        info.imei = imeiVal;
    } else if (type == DeviceType::LAPTOP) {
        char snBuf[128];
        cout << "Серійний номер: ";
        if (!readLine(snBuf, sizeof(snBuf))) return;
        trimWhitespace(snBuf);
        if (!isValidSerial(snBuf)) {
            cout << "Помилка: серійний номер має містити від 1 до 11 великих латинських літер і цифр.\n";
            return;
        }
        strncpy(info.serial, snBuf, sizeof(info.serial) - 1);
        info.serial[sizeof(info.serial) - 1] = '\0';
    } else {
        char inchBuf[128];
        cout << "Діагональ (від 19 до 100 дюймів): ";
        if (!readLine(inchBuf, sizeof(inchBuf))) return;
        trimWhitespace(inchBuf);
        if (!isAllDigits(inchBuf)) {
            cout << "Помилка: діагональ має бути цілим числом від 19 до 100.\n";
            return;
        }
        int val = 0;
        for (int i = 0; inchBuf[i]; ++i) {
            val = val * 10 + (inchBuf[i] - '0');
        }
        if (val < 19 || val > 100) {
            cout << "Помилка: діагональ має бути цілим числом від 19 до 100.\n";
            return;
        }
        info.inches = val;
    }

    char probBuf[256];
    cout << "Опис несправності: ";
    if (!readLine(probBuf, sizeof(probBuf))) return;
    int probLen = strlen(probBuf);
    if (probLen < 1 || probLen > 80) {
        cout << "Помилка: опис несправності має містити від 1 до 80 байтів.\n";
        return;
    }

    char prioBuf[128];
    cout << "Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ";
    if (!readLine(prioBuf, sizeof(prioBuf))) return;
    trimWhitespace(prioBuf);
    if (strcmp(prioBuf, "1") != 0 && strcmp(prioBuf, "2") != 0 && strcmp(prioBuf, "3") != 0) {
        cout << "Помилка: пріоритет має бути 1, 2 або 3.\n";
        return;
    }
    int priority = prioBuf[0] - '0';

    char rpnBuf[512];
    cout << "Вартість (обернений польський запис): ";
    if (!readLine(rpnBuf, sizeof(rpnBuf))) return;
    Money price;
    if (!evalRPN(rpnBuf, price)) {
        return;
    }

    Order newOrder;
    newOrder.id = nextOrderId++;
    strncpy(newOrder.client.name, nameBuf, sizeof(newOrder.client.name) - 1);
    newOrder.client.name[sizeof(newOrder.client.name) - 1] = '\0';
    strncpy(newOrder.client.phone, phoneBuf, sizeof(newOrder.client.phone) - 1);
    newOrder.client.phone[sizeof(newOrder.client.phone) - 1] = '\0';
    newOrder.date = date;
    newOrder.type = type;
    newOrder.info = info;
    strncpy(newOrder.problem, probBuf, sizeof(newOrder.problem) - 1);
    newOrder.problem[sizeof(newOrder.problem) - 1] = '\0';
    newOrder.priority = priority;
    newOrder.price = price;
    newOrder.status = Status::WAITING;
    newOrder.masterName[0] = '\0';

    addOrderLast(list, newOrder);
    pushQueue(qHead, qSize, &list.tail->order);
    pushAction(actionTop, ActionType::ADD, newOrder);

    cout << "Замовлення №" << newOrder.id << " додано: вартість " << newOrder.price
         << " грн, у черзі на ремонт: " << qSize << ".\n";
}

void handleShowJournal(const OrderList &list, int qSize) {
    if (list.size == 0) {
        cout << "Журнал порожній.\n";
        return;
    }
    cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n";
    cout << "|   № | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  |  Вартість |\n";
    cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n";
    OrderNode *curr = list.head;
    while (curr) {
        cout << curr->order << "\n";
        curr = curr->next;
    }
    cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n";
    cout << "Усього замовлень: " << list.size << ", у черзі на ремонт: " << qSize << "\n";
}

void handleAssignToMaster(QNode *&qHead, int &qSize, Master *&currentMaster) {
    if (!qHead) {
        cout << "Черга на ремонт порожня.\n";
        return;
    }
    Order *ord = popQueue(qHead, qSize);
    ord->status = Status::REPAIR;
    strncpy(ord->masterName, currentMaster->name, sizeof(ord->masterName) - 1);
    ord->masterName[sizeof(ord->masterName) - 1] = '\0';

    cout << "Замовлення №" << ord->id << " (пріоритет " << ord->priority
         << ") передано майстру " << currentMaster->name << ".\n";
    cout << "Несправність: " << ord->problem << "\n";
    cout << "У черзі залишилось: " << qSize << "\n";

    currentMaster = currentMaster->next;
}

void handleCompleteRepair(const OrderList &list, Master *mastersHead) {
    char buf[128];
    cout << "Номер замовлення: ";
    if (!readLine(buf, sizeof(buf))) return;
    trimWhitespace(buf);
    if (!isAllDigits(buf)) {
        cout << "Помилка: номер замовлення має бути цілим числом.\n";
        return;
    }
    int id = 0;
    for (int i = 0; buf[i]; ++i) {
        id = id * 10 + (buf[i] - '0');
    }

    OrderNode *node = findById(list, id);
    if (!node) {
        cout << "Замовлення №" << id << " не знайдено.\n";
        return;
    }
    if (node->order.status == Status::WAITING) {
        cout << "Замовлення №" << id << " ще не передано майстру.\n";
        return;
    }
    if (node->order.status == Status::DONE) {
        cout << "Замовлення №" << id << " уже завершено.\n";
        return;
    }

    node->order.status = Status::DONE;
    Master *m = findMaster(mastersHead, node->order.masterName);
    if (m) {
        m->completedCount++;
        m->revenue = m->revenue + node->order.price;
        cout << "Ремонт замовлення №" << id << " завершено. Майстер " << m->name
             << ": виконано " << m->completedCount << ", виручка " << m->revenue << " грн.\n";
    }
}

void handleDeleteOrder(OrderList &list, QNode *&qHead, int &qSize, Action *&actionTop) {
    char buf[128];
    cout << "Номер замовлення: ";
    if (!readLine(buf, sizeof(buf))) return;
    trimWhitespace(buf);
    if (!isAllDigits(buf)) {
        cout << "Помилка: номер замовлення має бути цілим числом.\n";
        return;
    }
    int id = 0;
    for (int i = 0; buf[i]; ++i) {
        id = id * 10 + (buf[i] - '0');
    }

    OrderNode *node = findById(list, id);
    if (!node) {
        cout << "Замовлення №" << id << " не знайдено.\n";
        return;
    }
    if (node->order.status != Status::WAITING) {
        cout << "Видалити можна лише замовлення, яке очікує в черзі.\n";
        return;
    }

    Order copy = node->order;
    pushAction(actionTop, ActionType::DELETE, copy);
    removeFromQueue(qHead, qSize, id);
    removeOrderNode(list, node);

    cout << "Замовлення №" << id << " видалено. У журналі: " << list.size
         << ", у черзі: " << qSize << ".\n";
}

void handleUndoAction(OrderList &list, QNode *&qHead, int &qSize, Action *&actionTop) {
    if (!actionTop) {
        cout << "Немає дій для скасування.\n";
        return;
    }

    Action *act = actionTop;
    actionTop = actionTop->next;
    ActionType type = act->type;
    Order savedOrder = act->order;
    delete act;

    if (type == ActionType::ADD) {
        OrderNode *node = findById(list, savedOrder.id);
        if (!node || node->order.status != Status::WAITING) {
            cout << "Додавання замовлення №" << savedOrder.id
                 << " скасувати неможливо: його вже передано майстру.\n";
            return;
        }
        removeFromQueue(qHead, qSize, savedOrder.id);
        removeOrderNode(list, node);
        cout << "Скасовано додавання замовлення №" << savedOrder.id
             << ": його вилучено з журналу і черги.\n";
    } else {
        addOrderLast(list, savedOrder);
        pushQueue(qHead, qSize, &list.tail->order);
        cout << "Скасовано видалення замовлення №" << savedOrder.id
             << ": його повернуто в кінець журналу і в чергу.\n";
    }
}

void handleReport(const OrderList &list, Master *currentMaster) {
    if (list.size == 0) {
        cout << "Журнал порожній.\n";
        cout << "Виручка за завершеними ремонтами: 0.00 грн\n";
        cout << "Майстри, починаючи з наступного в черзі:\n";
        if (currentMaster) {
            Master *p = currentMaster;
            do {
                cout << "  " << left << setw(13) << p->name
                     << "виконано: " << p->completedCount
                     << ", виручка: " << p->revenue << " грн\n";
                p = p->next;
            } while (p != currentMaster);
        }
        return;
    }

    Order **arr = new Order*[list.size];
    OrderNode *curr = list.head;
    for (int i = 0; i < list.size; ++i) {
        arr[i] = &curr->order;
        curr = curr->next;
    }

    for (int i = 0; i < list.size - 1; ++i) {
        int bestIdx = i;
        for (int j = i + 1; j < list.size; ++j) {
            if (arr[bestIdx]->price < arr[j]->price) {
                bestIdx = j;
            } else if (!(arr[j]->price < arr[bestIdx]->price) && arr[j]->id < arr[bestIdx]->id) {
                bestIdx = j;
            }
        }
        if (bestIdx != i) {
            Order *tmp = arr[i];
            arr[i] = arr[bestIdx];
            arr[bestIdx] = tmp;
        }
    }

    cout << "Замовлення за вартістю:\n";
    for (int i = 0; i < list.size; ++i) {
        const Order *o = arr[i];
        char priceBuf[32];
        snprintf(priceBuf, sizeof(priceBuf), "%d.%02d", o->price.hrn, o->price.kop);
        const char *statusStr = (o->status == Status::WAITING ? "WAITING" :
                                (o->status == Status::REPAIR ? "REPAIR" : "DONE"));
        cout << "  №" << o->id
             << setw(11) << right << priceBuf << " грн  "
             << statusStr << "\n";
    }

    Money diff = arr[0]->price - arr[list.size - 1]->price;
    cout << "Різниця між найдорожчим і найдешевшим: " << diff << " грн\n";

    delete[] arr;

    Money rev = revenue(list.head);
    cout << "Виручка за завершеними ремонтами: " << rev << " грн\n";

    cout << "Майстри, починаючи з наступного в черзі:\n";
    if (currentMaster) {
        Master *p = currentMaster;
        do {
            cout << "  " << left << setw(13) << p->name
                 << "виконано: " << p->completedCount
                 << ", виручка: " << p->revenue << " грн\n";
            p = p->next;
        } while (p != currentMaster);
    }
}

void handleReverseJournal(OrderList &list) {
    if (list.size == 0) {
        cout << "Журнал порожній.\n";
        return;
    }
    OrderNode *curr = list.head;
    while (curr) {
        OrderNode *tmp = curr->prev;
        curr->prev = curr->next;
        curr->next = tmp;
        curr = curr->prev;
    }
    OrderNode *tmp = list.head;
    list.head = list.tail;
    list.tail = tmp;

    cout << "Журнал розвернуто: тепер першим іде замовлення №"
         << list.head->order.id << ", останнім №"
         << list.tail->order.id << ".\n";
}

void showMenu() {
    cout << "\nМеню:\n"
         << "1. Додати замовлення\n"
         << "2. Журнал замовлень\n"
         << "3. Видати замовлення майстру\n"
         << "4. Завершити ремонт\n"
         << "5. Видалити замовлення\n"
         << "6. Скасувати останню дію\n"
         << "7. Звіт\n"
         << "8. Розвернути журнал\n"
         << "0. Вийти\n";
}

int main() {
    char countBuf[128];
    cout << "Кількість майстрів (від 1 до 5): ";
    if (!readLine(countBuf, sizeof(countBuf))) {
        return 0;
    }
    trimWhitespace(countBuf);
    if (!isAllDigits(countBuf)) {
        cout << "Помилка: кількість майстрів має бути цілим числом від 1 до 5.\n";
        return 0;
    }
    int numMasters = 0;
    for (int i = 0; countBuf[i]; ++i) {
        numMasters = numMasters * 10 + (countBuf[i] - '0');
    }
    if (numMasters < 1 || numMasters > 5) {
        cout << "Помилка: кількість майстрів має бути цілим числом від 1 до 5.\n";
        return 0;
    }

    char namesLine[256];
    cout << "Імена майстрів через пробіл: ";
    if (!readLine(namesLine, sizeof(namesLine))) {
        return 0;
    }

    char names[5][32];
    int parsedCount = 0;
    bool namesValid = true;

    const char *np = namesLine;
    while (*np) {
        while (*np && isspace(static_cast<unsigned char>(*np))) np++;
        if (!*np) break;

        char singleName[64];
        int wLen = 0;
        while (*np && !isspace(static_cast<unsigned char>(*np))) {
            if (wLen < 63) {
                singleName[wLen++] = *np;
            }
            np++;
        }
        singleName[wLen] = '\0';

        if (wLen < 1 || wLen > 23 || !isAllLatin(singleName)) {
            namesValid = false;
            break;
        }

        if (parsedCount < numMasters) {
            strncpy(names[parsedCount], singleName, sizeof(names[parsedCount]) - 1);
            names[parsedCount][sizeof(names[parsedCount]) - 1] = '\0';
        }
        parsedCount++;
    }

    if (!namesValid || parsedCount != numMasters) {
        cout << "Помилка: кількість імен має дорівнювати " << numMasters
             << ", кожне ім'я з латинських літер, до 23 символів.\n";
        return 0;
    }

    for (int i = 0; i < numMasters; ++i) {
        for (int j = i + 1; j < numMasters; ++j) {
            if (strcmp(names[i], names[j]) == 0) {
                cout << "Помилка: імена майстрів не повинні повторюватися.\n";
                return 0;
            }
        }
    }

    Master *mastersHead = nullptr;
    Master *lastMaster = nullptr;
    for (int i = 0; i < numMasters; ++i) {
        Master *m = new Master;
        strncpy(m->name, names[i], sizeof(m->name) - 1);
        m->name[sizeof(m->name) - 1] = '\0';
        m->completedCount = 0;
        m->revenue = Money{0, 0};
        m->next = nullptr;
        if (!mastersHead) {
            mastersHead = m;
            lastMaster = m;
        } else {
            lastMaster->next = m;
            lastMaster = m;
        }
    }
    lastMaster->next = mastersHead;
    Master *currentMaster = mastersHead;

    OrderList orderList;
    initOrderList(orderList);

    QNode *qHead = nullptr;
    int qSize = 0;

    Action *actionTop = nullptr;
    int nextOrderId = 101;

    while (true) {
        showMenu();
        cout << "Ваш вибір: ";
        char choiceBuf[128];
        if (!readLine(choiceBuf, sizeof(choiceBuf))) {
            break;
        }
        trimWhitespace(choiceBuf);
        if (!isAllDigits(choiceBuf)) {
            cout << "Помилка: введіть номер пункту меню.\n";
            continue;
        }
        int choice = 0;
        for (int i = 0; choiceBuf[i]; ++i) {
            choice = choice * 10 + (choiceBuf[i] - '0');
        }
        if (choice < 0 || choice > 8) {
            cout << "Помилка: пункту " << choice << " немає в меню.\n";
            continue;
        }

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1:
                handleAddOrder(orderList, qHead, qSize, actionTop, nextOrderId);
                break;
            case 2:
                handleShowJournal(orderList, qSize);
                break;
            case 3:
                handleAssignToMaster(qHead, qSize, currentMaster);
                break;
            case 4:
                handleCompleteRepair(orderList, mastersHead);
                break;
            case 5:
                handleDeleteOrder(orderList, qHead, qSize, actionTop);
                break;
            case 6:
                handleUndoAction(orderList, qHead, qSize, actionTop);
                break;
            case 7:
                handleReport(orderList, currentMaster);
                break;
            case 8:
                handleReverseJournal(orderList);
                break;
            default:
                break;
        }
    }

    freeOrderList(orderList);
    freeQueue(qHead, qSize);
    freeActionStack(actionTop);
    freeMasters(mastersHead);
    return 0;
}