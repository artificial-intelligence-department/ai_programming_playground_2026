//Проскурня Дмитро ШІ-13
//Сервісний центр: черга ремонтів

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>

const int MAX_PRICE = 10000000;          // 100000.00 грн у копійках

enum class DeviceType { PHONE = 1, LAPTOP, TV };
enum class Status { WAITING, REPAIR, DONE };
enum class ActionType { ADD, REMOVE };

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
    Order data;
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

struct PriorityQueue {
    QNode* head;
    int size;
};

struct Master {
    char name[24];
    int done;
    Money revenue;
    Master* next;
};

struct Action {
    ActionType type;
    Order order;
    Action* next;
};

struct NumNode {
    int kop;
    NumNode* next;
};

Money operator+(const Money& a, const Money& b);
Money operator-(const Money& a, const Money& b);
Money operator*(const Money& a, int k);
bool operator<(const Money& a, const Money& b);
std::ostream& operator<<(std::ostream& os, const Money& m);
std::ostream& operator<<(std::ostream& os, const Order& o);

int toKop(const Money& m);
Money fromKop(int kop);
void moneyToStr(const Money& m, char* buf);
const char* typeName(DeviceType type);
const char* statusName(Status status);

void listPushBack(OrderList& list, const Order& order);
OrderNode* findById(const OrderList& list, int id);
void listUnlink(OrderList& list, OrderNode* node);
void listReverse(OrderList& list);
void listFree(OrderList& list);

void queuePush(PriorityQueue& queue, Order* order);
Order* queuePop(PriorityQueue& queue);
void queueRemove(PriorityQueue& queue, const Order* order);
void queueFree(PriorityQueue& queue);

void actionPush(Action*& top, ActionType type, const Order& order);
void actionsFree(Action*& top);

void masterAdd(Master*& first, Master*& last, const char* name);
Master* findMaster(Master* ring, const char* name);
void mastersFree(Master*& ring);

void numPush(NumNode*& top, int kop);
int numPop(NumNode*& top);
void numFree(NumNode*& top);
bool parseNumber(const char* tok, int& kop);
bool evalRPN(const char* expr, Money& res);

Money revenue(const OrderNode* p);
void sortOrders(Order** arr, int n);
void removeOrder(OrderList& list, PriorityQueue& queue, OrderNode* node);

int readLine(char* buf, int size);
bool parseInt(const char* s, int& value);
bool isLatinWord(const char* s, int maxLen);
bool isValidPhone(const char* s);
bool parseDate(const char* s, Date& date, bool& formatOk);
bool readMasters(Master*& ring);
int readMenuChoice();
int readOrderId(int& id);

void addOrder(OrderList& list, PriorityQueue& queue, Action*& actions, int& nextId);
void showJournal(const OrderList& list, const PriorityQueue& queue);
void assignOrder(PriorityQueue& queue, Master*& current);
void finishRepair(OrderList& list, Master* ring);
void deleteOrder(OrderList& list, PriorityQueue& queue, Action*& actions);
void undoAction(OrderList& list, PriorityQueue& queue, Action*& actions);
void showReport(const OrderList& list, Master* current);
void reverseJournal(OrderList& list);

// Головна функція: зчитує майстрів, у циклі показує меню та викликає потрібний пункт.
// При виході (пункт 0 або кінець вводу) звільняє журнал, чергу, стек дій і кільце майстрів
int main() {
    Master* current = nullptr;
    if (!readMasters(current)) {
        return 1;
    }

    OrderList list = {nullptr, nullptr, 0};
    PriorityQueue queue = {nullptr, 0};
    Action* actions = nullptr;
    int nextId = 101;

    do {
        printf("\n1 Додати замовлення\n");
        printf("2 Журнал замовлень\n");
        printf("3 Видати замовлення майстру\n");
        printf("4 Завершити ремонт\n");
        printf("5 Видалити замовлення\n");
        printf("6 Скасувати останню дію\n");
        printf("7 Звіт\n");
        printf("8 Розвернути журнал\n");
        printf("0 Вийти\n");

        int action;
        while (true) {
            printf("Ваш вибір: ");
            action = readMenuChoice();
            if (action == -2) {
                action = 0;              // кінець вводу
                break;
            }
            if (action == -1) {
                printf("Помилка: введіть номер пункту меню.\n");
            } else if (action > 8) {
                printf("Помилка: пункту %d немає в меню.\n", action);
            } else {
                break;
            }
        }
        printf("\n");

        switch (action)
        {
        case 1:
            addOrder(list, queue, actions, nextId);
            break;

        case 2:
            showJournal(list, queue);
            break;

        case 3:
            assignOrder(queue, current);
            break;

        case 4:
            finishRepair(list, current);
            break;

        case 5:
            deleteOrder(list, queue, actions);
            break;

        case 6:
            undoAction(list, queue, actions);
            break;

        case 7:
            showReport(list, current);
            break;

        case 8:
            reverseJournal(list);
            break;

        case 0:
            queueFree(queue);
            listFree(list);
            actionsFree(actions);
            mastersFree(current);
            printf("Роботу завершено\n");
            return 0;
        }
    } while (true);
}

// ---------- оператори для Money та Order ----------

// Переводить суму в копійки, щоб з нею було зручно рахувати
int toKop(const Money& m) {
    return m.hrn * 100 + m.kop;
}

// Розкладає кількість копійок на гривні й копійки
Money fromKop(int kop) {
    Money m;
    m.hrn = kop / 100;
    m.kop = kop % 100;
    return m;
}

// Додає дві суми
Money operator+(const Money& a, const Money& b) {
    return fromKop(toKop(a) + toKop(b));
}

// Віднімає від першої суми другу
Money operator-(const Money& a, const Money& b) {
    return fromKop(toKop(a) - toKop(b));
}

// Множить суму на ціле число (кількість однакових деталей)
Money operator*(const Money& a, int k) {
    return fromKop(toKop(a) * k);
}

// Порівнює дві суми: true, якщо перша менша
bool operator<(const Money& a, const Money& b) {
    return toKop(a) < toKop(b);
}

// Записує суму в рядок у вигляді 820.00
void moneyToStr(const Money& m, char* buf) {
    sprintf(buf, "%d.%02d", m.hrn, m.kop);
}

// Друкує суму з двома знаками копійок
std::ostream& operator<<(std::ostream& os, const Money& m) {
    char buf[16];
    moneyToStr(m, buf);
    os << buf;
    return os;
}

// Повертає назву типу пристрою для таблиці
const char* typeName(DeviceType type) {
    switch (type) {
    case DeviceType::PHONE:  return "PHONE";
    case DeviceType::LAPTOP: return "LAPTOP";
    default:                 return "TV";
    }
}

// Повертає назву статусу замовлення
const char* statusName(Status status) {
    switch (status) {
    case Status::WAITING: return "WAITING";
    case Status::REPAIR:  return "REPAIR";
    default:              return "DONE";
    }
}

// Друкує один рядок таблиці журналу. Стовпець «Деталі» залежить від типу пристрою:
// IMEI з ведучими нулями, серійний номер або діагональ. Вартість вирівнюється праворуч
std::ostream& operator<<(std::ostream& os, const Order& o) {
    char date[16], details[24], price[16];
    sprintf(date, "%02d.%02d.%04d", o.date.day, o.date.month, o.date.year);

    if (o.type == DeviceType::PHONE) {
        sprintf(details, "IMEI %06d", o.info.imei);
    } else if (o.type == DeviceType::LAPTOP) {
        sprintf(details, "SN %s", o.info.serial);
    } else {
        sprintf(details, "%d inch", o.info.inches);
    }
    moneyToStr(o.price, price);

    os << "| " << std::right << std::setw(3) << o.id
       << " | " << std::left << std::setw(15) << o.client.name
       << " | " << std::setw(10) << o.client.phone
       << " | " << date
       << " | " << std::setw(6) << typeName(o.type)
       << " | " << std::setw(14) << details
       << " | " << std::right << std::setw(2) << o.priority
       << " | " << std::left << std::setw(7) << statusName(o.status)
       << " | " << std::right << std::setw(9) << price
       << " |";
    return os;
}

// ---------- журнал (двозв'язний список) ----------

// Створює вузол з копією замовлення і додає його в кінець журналу
void listPushBack(OrderList& list, const Order& order) {
    OrderNode* node = new OrderNode;
    node->data = order;
    node->next = nullptr;
    node->prev = list.tail;

    if (list.tail != nullptr) {
        list.tail->next = node;
    } else {
        list.head = node;
    }
    list.tail = node;
    list.size++;
}

// Шукає замовлення за номером, проходячи журнал від head. Повертає вузол або nullptr
OrderNode* findById(const OrderList& list, int id) {
    for (OrderNode* p = list.head; p != nullptr; p = p->next) {
        if (p->data.id == id) {
            return p;
        }
    }
    return nullptr;
}

// Вилучає вузол з будь-якого місця журналу (голова, середина, хвіст)
// з правильним оновленням prev, next, head і tail. Сам вузол не звільняє
void listUnlink(OrderList& list, OrderNode* node) {
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
    list.size--;
}

// Розвертає журнал на місці: у кожному вузлі міняє prev і next,
// а потім міняє місцями head і tail. Нові вузли не створюються
void listReverse(OrderList& list) {
    OrderNode* p = list.head;
    while (p != nullptr) {
        OrderNode* next = p->next;
        p->next = p->prev;
        p->prev = next;
        p = next;
    }
    OrderNode* tmp = list.head;
    list.head = list.tail;
    list.tail = tmp;
}

// Звільняє всі вузли журналу
void listFree(OrderList& list) {
    OrderNode* p = list.head;
    while (p != nullptr) {
        OrderNode* next = p->next;
        delete p;
        p = next;
    }
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

// ---------- пріоритетна черга ----------

// Ставить замовлення в чергу за пріоритетом: після всіх замовлень з таким самим
// або вищим пріоритетом, тому рівні пріоритети обслуговуються в порядку надходження
void queuePush(PriorityQueue& queue, Order* order) {
    QNode* node = new QNode;
    node->order = order;

    if (queue.head == nullptr || queue.head->order->priority < order->priority) {
        node->next = queue.head;
        queue.head = node;
    } else {
        QNode* p = queue.head;
        while (p->next != nullptr && p->next->order->priority >= order->priority) {
            p = p->next;
        }
        node->next = p->next;
        p->next = node;
    }
    queue.size++;
}

// Знімає замовлення з голови черги (найвищий пріоритет). Повертає nullptr, якщо черга порожня
Order* queuePop(PriorityQueue& queue) {
    if (queue.head == nullptr) {
        return nullptr;
    }
    QNode* node = queue.head;
    Order* order = node->order;
    queue.head = node->next;
    delete node;
    queue.size--;
    return order;
}

// Вилучає з черги вузол, що вказує на задане замовлення
void queueRemove(PriorityQueue& queue, const Order* order) {
    QNode* prev = nullptr;
    for (QNode* p = queue.head; p != nullptr; prev = p, p = p->next) {
        if (p->order == order) {
            if (prev != nullptr) {
                prev->next = p->next;
            } else {
                queue.head = p->next;
            }
            delete p;
            queue.size--;
            return;
        }
    }
}

// Звільняє всі вузли черги (самі замовлення належать журналу)
void queueFree(PriorityQueue& queue) {
    while (queue.head != nullptr) {
        queuePop(queue);
    }
}

// ---------- стек дій ----------

// Кладе на вершину стеку дію разом з копією замовлення
void actionPush(Action*& top, ActionType type, const Order& order) {
    Action* a = new Action;
    a->type = type;
    a->order = order;
    a->next = top;
    top = a;
}

// Звільняє весь стек дій
void actionsFree(Action*& top) {
    while (top != nullptr) {
        Action* next = top->next;
        delete top;
        top = next;
    }
}

// ---------- кільце майстрів ----------

// Додає майстра в кінець ланцюжка. Кільце замикається після додавання всіх майстрів
void masterAdd(Master*& first, Master*& last, const char* name) {
    Master* m = new Master;
    strcpy(m->name, name);
    m->done = 0;
    m->revenue = {0, 0};
    m->next = nullptr;

    if (first == nullptr) {
        first = m;
    } else {
        last->next = m;
    }
    last = m;
}

// Шукає майстра за ім'ям, обходячи кільце циклом do while
Master* findMaster(Master* ring, const char* name) {
    if (ring == nullptr) {
        return nullptr;
    }
    Master* p = ring;
    do {
        if (strcmp(p->name, name) == 0) {
            return p;
        }
        p = p->next;
    } while (p != ring);
    return nullptr;
}

// Звільняє кільце майстрів: обходить його до повернення на початок
void mastersFree(Master*& ring) {
    if (ring == nullptr) {
        return;
    }
    Master* p = ring->next;
    while (p != ring) {
        Master* next = p->next;
        delete p;
        p = next;
    }
    delete ring;
    ring = nullptr;
}

// ---------- обчислення виразу в оберненому польському записі ----------

// Кладе число (у копійках) на вершину стеку чисел
void numPush(NumNode*& top, int kop) {
    NumNode* node = new NumNode;
    node->kop = kop;
    node->next = top;
    top = node;
}

// Знімає число з вершини стеку чисел
int numPop(NumNode*& top) {
    NumNode* node = top;
    int kop = node->kop;
    top = node->next;
    delete node;
    return kop;
}

// Звільняє стек чисел
void numFree(NumNode*& top) {
    while (top != nullptr) {
        numPop(top);
    }
}

// Розбирає число: до 6 цифр цілої частини і до 2 цифр після крапки.
// Результат повертає в копійках через kop
bool parseNumber(const char* tok, int& kop) {
    int whole = 0, frac = 0, wholeDigits = 0, fracDigits = 0;
    const char* p = tok;

    while (isdigit((unsigned char)*p)) {
        whole = whole * 10 + (*p - '0');
        wholeDigits++;
        p++;
    }
    if (wholeDigits == 0 || wholeDigits > 6) {
        return false;
    }

    if (*p == '.') {
        p++;
        while (isdigit((unsigned char)*p)) {
            frac = frac * 10 + (*p - '0');
            fracDigits++;
            p++;
        }
        if (fracDigits == 0 || fracDigits > 2) {
            return false;
        }
        if (fracDigits == 1) {
            frac *= 10;
        }
    }

    if (*p != '\0') {
        return false;
    }
    kop = whole * 100 + frac;
    return true;
}

// Обчислює вираз в оберненому польському записі за допомогою стеку чисел.
// Межу 100000.00 грн перевіряє після кожного кроку, щоб не було переповнення int.
// При помилці виводить повідомлення, звільняє стек і повертає false
bool evalRPN(const char* expr, Money& res) {
    char copy[256];
    strcpy(copy, expr);

    NumNode* stack = nullptr;
    int count = 0;
    bool hasTokens = false;

    for (char* tok = strtok(copy, " "); tok != nullptr; tok = strtok(nullptr, " ")) {
        hasTokens = true;
        bool isOp = (strcmp(tok, "+") == 0 || strcmp(tok, "-") == 0 || strcmp(tok, "*") == 0);

        if (!isOp) {
            int kop;
            if (!parseNumber(tok, kop)) {
                printf("Помилка у виразі: «%s» не є числом або операцією.\n", tok);
                numFree(stack);
                return false;
            }
            if (kop > MAX_PRICE) {
                printf("Помилка у виразі: сума перевищує 100000.00 грн.\n");
                numFree(stack);
                return false;
            }
            numPush(stack, kop);
            count++;
            continue;
        }

        if (count < 2) {
            printf("Помилка у виразі: для операції «%s» бракує чисел.\n", tok);
            numFree(stack);
            return false;
        }
        int b = numPop(stack);
        int a = numPop(stack);
        count -= 2;

        int result;
        if (tok[0] == '+') {
            result = a + b;
        } else if (tok[0] == '-') {
            result = a - b;
            if (result < 0) {
                printf("Помилка у виразі: проміжний результат від'ємний.\n");
                numFree(stack);
                return false;
            }
        } else {
            if (b % 100 != 0 || b / 100 < 1 || b / 100 > 100) {
                printf("Помилка у виразі: множник має бути цілим числом від 1 до 100.\n");
                numFree(stack);
                return false;
            }
            result = a * (b / 100);
        }

        if (result > MAX_PRICE) {
            printf("Помилка у виразі: сума перевищує 100000.00 грн.\n");
            numFree(stack);
            return false;
        }
        numPush(stack, result);
        count++;
    }

    if (!hasTokens) {
        printf("Помилка у виразі: порожній вираз.\n");
        return false;
    }
    if (count != 1) {
        printf("Помилка у виразі: у стеку залишилось чисел: %d, а має бути одне.\n", count);
        numFree(stack);
        return false;
    }

    int total = numPop(stack);
    if (total == 0) {
        printf("Помилка у виразі: вартість має бути більшою за 0.00 грн.\n");
        return false;
    }
    res = fromKop(total);
    return true;
}

// ---------- алгоритми обробки ----------

// Рекурсивно рахує виручку за завершеними ремонтами, починаючи з вузла p
Money revenue(const OrderNode* p) {
    if (p == nullptr) {
        return {0, 0};
    }
    Money rest = revenue(p->next);
    if (p->data.status == Status::DONE) {
        return p->data.price + rest;
    }
    return rest;
}

// Сортує масив вказівників на замовлення за спаданням вартості,
// а за рівної вартості за зростанням номера
void sortOrders(Order** arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            bool swapNeeded = arr[i]->price < arr[j]->price ||
                (!(arr[j]->price < arr[i]->price) && arr[j]->id < arr[i]->id);
            if (swapNeeded) {
                Order* tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

// Вилучає замовлення з черги та журналу і звільняє його вузол
void removeOrder(OrderList& list, PriorityQueue& queue, OrderNode* node) {
    queueRemove(queue, &node->data);
    listUnlink(list, node);
    delete node;
}

// ---------- допоміжні функції вводу ----------

// Зчитує рядок через cin.getline. Повертає 1, якщо рядок прочитано, 0 при кінці вводу
// і -1, якщо рядок задовгий (тоді залишок рядка відкидається, а buf стає порожнім)
int readLine(char* buf, int size) {
    std::cin.getline(buf, size);
    if (std::cin.fail()) {
        if (std::cin.eof()) {
            buf[0] = '\0';
            return 0;
        }
        std::cin.clear();
        std::cin.ignore(100000, '\n');
        buf[0] = '\0';
        return -1;
    }

    int len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\r') {
        buf[len - 1] = '\0';
    }
    return 1;
}

// Розбирає невід'ємне ціле число, записане лише цифрами.
// Повертає false, якщо рядок порожній, містить інші символи або число завелике
bool parseInt(const char* s, int& value) {
    if (*s == '\0') {
        return false;
    }
    int result = 0;
    for (const char* p = s; *p != '\0'; p++) {
        if (!isdigit((unsigned char)*p)) {
            return false;
        }
        if (result > 100000000) {
            return false;
        }
        result = result * 10 + (*p - '0');
    }
    value = result;
    return true;
}

// Перевіряє, що рядок складається з 1..maxLen латинських літер
bool isLatinWord(const char* s, int maxLen) {
    int len = strlen(s);
    if (len < 1 || len > maxLen) {
        return false;
    }
    for (const char* p = s; *p != '\0'; p++) {
        if (!isalpha((unsigned char)*p)) {
            return false;
        }
    }
    return true;
}

// Перевіряє телефон: рівно 10 цифр, перша цифра 0
bool isValidPhone(const char* s) {
    if (strlen(s) != 10 || s[0] != '0') {
        return false;
    }
    for (const char* p = s; *p != '\0'; p++) {
        if (!isdigit((unsigned char)*p)) {
            return false;
        }
    }
    return true;
}

// Розбирає дату у форматі ДД.ММ.РРРР. Через formatOk повідомляє, чи правильний формат,
// а повертає true лише для реальної дати з роком від 2000 до 2099
bool parseDate(const char* s, Date& date, bool& formatOk) {
    formatOk = false;
    if (strlen(s) != 10 || s[2] != '.' || s[5] != '.') {
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5 && !isdigit((unsigned char)s[i])) {
            return false;
        }
    }
    formatOk = true;

    date.day = (s[0] - '0') * 10 + (s[1] - '0');
    date.month = (s[3] - '0') * 10 + (s[4] - '0');
    date.year = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 + (s[9] - '0');

    if (date.year < 2000 || date.year > 2099 || date.month < 1 || date.month > 12) {
        return false;
    }
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leap = (date.year % 4 == 0 && date.year % 100 != 0) || date.year % 400 == 0;
    if (leap) {
        daysInMonth[1] = 29;
    }
    return date.day >= 1 && date.day <= daysInMonth[date.month - 1];
}

// Зчитує кількість і імена майстрів та будує з них кільце.
// При некоректних даних виводить повідомлення й повертає false
bool readMasters(Master*& ring) {
    char line[256];
    int n;

    printf("Кількість майстрів (від 1 до 5): ");
    if (readLine(line, sizeof(line)) != 1 || !parseInt(line, n) || n < 1 || n > 5) {
        printf("Помилка: кількість майстрів має бути цілим числом від 1 до 5.\n");
        return false;
    }

    printf("Імена майстрів через пробіл: ");
    int r = readLine(line, sizeof(line));

    char names[5][24];
    int count = 0;
    bool ok = (r == 1);
    for (char* tok = strtok(line, " "); ok && tok != nullptr; tok = strtok(nullptr, " ")) {
        if (count == n || !isLatinWord(tok, 23)) {
            ok = false;
        } else {
            strcpy(names[count++], tok);
        }
    }
    if (!ok || count != n) {
        printf("Помилка: кількість імен має дорівнювати %d, кожне ім'я з латинських літер, до 23 символів.\n", n);
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

    Master* first = nullptr;
    Master* last = nullptr;
    for (int i = 0; i < n; i++) {
        masterAdd(first, last, names[i]);
    }
    last->next = first;                  // замикаємо кільце
    ring = first;
    return true;
}

// Зчитує вибір меню. Повертає номер пункту, -1 якщо введено не число,
// і -2 при кінці вводу
int readMenuChoice() {
    char line[64];
    int r = readLine(line, sizeof(line));
    if (r == 0) {
        return -2;
    }
    int value;
    if (r == -1 || !parseInt(line, value)) {
        return -1;
    }
    return value;
}

// Зчитує номер замовлення. Повертає 1 при успіху, 0 при кінці вводу
// і -1, якщо введено не ціле число (тоді виводить повідомлення)
int readOrderId(int& id) {
    char line[64];
    printf("Номер замовлення: ");
    int r = readLine(line, sizeof(line));
    if (r == 0) {
        return 0;
    }
    if (r == -1 || !parseInt(line, id)) {
        printf("Помилка: номер замовлення має бути цілим числом.\n");
        return -1;
    }
    return 1;
}

// ---------- пункти меню ----------

// Пункт 1: зчитує й перевіряє всі поля замовлення. Дані пристрою записуються у потрібне
// поле union. Коректне замовлення отримує статус WAITING, додається в кінець журналу
// і в чергу, а в стек дій записується дія «додавання». При помилці нічого не змінюється
void addOrder(OrderList& list, PriorityQueue& queue, Action*& actions, int& nextId) {
    Order o = {};
    char line[256];
    int value;

    printf("Ім'я клієнта: ");
    if (readLine(line, sizeof(line)) == 0) return;
    if (!isLatinWord(line, 15)) {
        printf("Помилка: ім'я має містити від 1 до 15 латинських літер.\n");
        return;
    }
    strcpy(o.client.name, line);

    printf("Телефон (10 цифр): ");
    if (readLine(line, sizeof(line)) == 0) return;
    if (!isValidPhone(line)) {
        printf("Помилка: телефон має складатися з 10 цифр і починатися з 0.\n");
        return;
    }
    strcpy(o.client.phone, line);

    printf("Дата прийому (ДД.ММ.РРРР): ");
    if (readLine(line, sizeof(line)) == 0) return;
    bool formatOk;
    if (!parseDate(line, o.date, formatOk)) {
        if (formatOk) {
            printf("Помилка: некоректна дата.\n");
        } else {
            printf("Помилка: дата має бути у форматі ДД.ММ.РРРР.\n");
        }
        return;
    }

    printf("Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ");
    if (readLine(line, sizeof(line)) == 0) return;
    if (!parseInt(line, value) || value < 1 || value > 3) {
        printf("Помилка: тип пристрою має бути 1, 2 або 3.\n");
        return;
    }
    o.type = (DeviceType)value;

    if (o.type == DeviceType::PHONE) {
        printf("Останні 6 цифр IMEI: ");
        if (readLine(line, sizeof(line)) == 0) return;
        if (strlen(line) != 6 || !parseInt(line, value)) {
            printf("Помилка: потрібно рівно 6 цифр.\n");
            return;
        }
        o.info.imei = value;
    } else if (o.type == DeviceType::LAPTOP) {
        printf("Серійний номер: ");
        if (readLine(line, sizeof(line)) == 0) return;
        int len = strlen(line);
        bool ok = (len >= 1 && len <= 11);
        for (int i = 0; ok && i < len; i++) {
            if (!isdigit((unsigned char)line[i]) && !(line[i] >= 'A' && line[i] <= 'Z')) {
                ok = false;
            }
        }
        if (!ok) {
            printf("Помилка: серійний номер має містити від 1 до 11 великих латинських літер і цифр.\n");
            return;
        }
        strcpy(o.info.serial, line);
    } else {
        printf("Діагональ (дюймів): ");
        if (readLine(line, sizeof(line)) == 0) return;
        if (!parseInt(line, value) || value < 19 || value > 100) {
            printf("Помилка: діагональ має бути цілим числом від 19 до 100 дюймів.\n");
            return;
        }
        o.info.inches = value;
    }

    printf("Опис несправності: ");
    if (readLine(line, sizeof(line)) == 0) return;
    int len = strlen(line);
    if (len < 1 || len > 80) {
        printf("Помилка: опис має містити від 1 до 80 байтів (до 80 латинських або 40 кириличних літер).\n");
        return;
    }
    strcpy(o.problem, line);

    printf("Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ");
    if (readLine(line, sizeof(line)) == 0) return;
    if (!parseInt(line, value) || value < 1 || value > 3) {
        printf("Помилка: пріоритет має бути 1, 2 або 3.\n");
        return;
    }
    o.priority = value;

    printf("Вартість (обернений польський запис): ");
    int r = readLine(line, sizeof(line));
    if (r == 0) return;
    if (r == -1) {
        printf("Помилка у виразі: вираз задовгий.\n");
        return;
    }
    if (!evalRPN(line, o.price)) {
        return;
    }

    o.id = nextId++;
    o.status = Status::WAITING;
    o.master[0] = '\0';

    listPushBack(list, o);
    queuePush(queue, &list.tail->data);
    actionPush(actions, ActionType::ADD, o);

    std::cout << "Замовлення №" << o.id << " додано: вартість " << o.price
              << " грн, у черзі на ремонт: " << queue.size << ".\n";
}

// Пункт 2: виводить журнал таблицею від head до tail, кожен рядок друкує оператор <<
// для Order. Під таблицею кількість замовлень у журналі та в черзі
void showJournal(const OrderList& list, const PriorityQueue& queue) {
    if (list.head == nullptr) {
        printf("Журнал порожній.\n");
        return;
    }

    const char* border = "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+";
    printf("%s\n", border);
    printf("|   № | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  |  Вартість |\n");
    printf("%s\n", border);
    for (OrderNode* p = list.head; p != nullptr; p = p->next) {
        std::cout << p->data << "\n";
    }
    printf("%s\n", border);
    printf("Усього замовлень: %d, у черзі на ремонт: %d\n", list.size, queue.size);
}

// Пункт 3: бере з голови черги замовлення з найвищим пріоритетом і віддає його
// наступному майстру в кільці. Статус стає REPAIR, ім'я майстра записується в замовлення
void assignOrder(PriorityQueue& queue, Master*& current) {
    Order* o = queuePop(queue);
    if (o == nullptr) {
        printf("Черга на ремонт порожня.\n");
        return;
    }

    o->status = Status::REPAIR;
    strcpy(o->master, current->name);
    printf("Замовлення №%d (пріоритет %d) передано майстру %s.\n", o->id, o->priority, current->name);
    printf("Несправність: %s\n", o->problem);
    printf("У черзі залишилось: %d\n", queue.size);

    current = current->next;
}

// Пункт 4: завершує ремонт замовлення зі статусом REPAIR. Статус стає DONE,
// у майстра збільшується кількість виконаних ремонтів і виручка (оператор +)
void finishRepair(OrderList& list, Master* ring) {
    int id;
    if (readOrderId(id) != 1) return;

    OrderNode* node = findById(list, id);
    if (node == nullptr) {
        printf("Замовлення №%d не знайдено.\n", id);
        return;
    }
    Order& o = node->data;
    if (o.status == Status::WAITING) {
        printf("Замовлення №%d ще не передано майстру.\n", id);
        return;
    }
    if (o.status == Status::DONE) {
        printf("Замовлення №%d уже завершено.\n", id);
        return;
    }

    Master* m = findMaster(ring, o.master);
    o.status = Status::DONE;
    m->done++;
    m->revenue = m->revenue + o.price;

    std::cout << "Ремонт замовлення №" << id << " завершено. Майстер " << m->name
              << ": виконано " << m->done << ", виручка " << m->revenue << " грн.\n";
}

// Пункт 5: видаляє замовлення зі статусом WAITING з будь-якого місця журналу та з черги,
// а його копію записує в стек дій як дію «видалення»
void deleteOrder(OrderList& list, PriorityQueue& queue, Action*& actions) {
    int id;
    if (readOrderId(id) != 1) return;

    OrderNode* node = findById(list, id);
    if (node == nullptr) {
        printf("Замовлення №%d не знайдено.\n", id);
        return;
    }
    if (node->data.status != Status::WAITING) {
        printf("Видалити можна лише замовлення, яке очікує в черзі.\n");
        return;
    }

    actionPush(actions, ActionType::REMOVE, node->data);
    removeOrder(list, queue, node);
    printf("Замовлення №%d видалено. У журналі: %d, у черзі: %d.\n", id, list.size, queue.size);
}

// Пункт 6: знімає з вершини стеку останню дію і скасовує її. Додавання скасовується,
// лише якщо замовлення ще очікує; видалення повертає замовлення в кінець журналу і в чергу
void undoAction(OrderList& list, PriorityQueue& queue, Action*& actions) {
    if (actions == nullptr) {
        printf("Немає дій для скасування.\n");
        return;
    }

    Action* a = actions;
    actions = a->next;
    int id = a->order.id;

    if (a->type == ActionType::ADD) {
        OrderNode* node = findById(list, id);
        if (node == nullptr) {
            printf("Замовлення №%d уже немає в журналі.\n", id);
        } else if (node->data.status != Status::WAITING) {
            printf("Додавання замовлення №%d скасувати неможливо: його вже передано майстру.\n", id);
        } else {
            removeOrder(list, queue, node);
            printf("Скасовано додавання замовлення №%d: його вилучено з журналу і черги.\n", id);
        }
    } else {
        listPushBack(list, a->order);
        queuePush(queue, &list.tail->data);
        printf("Скасовано видалення замовлення №%d: його повернуто в кінець журналу і в чергу.\n", id);
    }

    delete a;
}

// Пункт 7: виводить замовлення, відсортовані за спаданням вартості (через динамічний
// масив вказівників), різницю між найдорожчим і найдешевшим, виручку за завершеними
// ремонтами (рекурсивно) і майстрів по колу, починаючи з наступного в черзі
void showReport(const OrderList& list, Master* current) {
    if (list.head == nullptr) {
        printf("Журнал порожній.\n");
    } else {
        Order** arr = new Order*[list.size];
        int i = 0;
        for (OrderNode* p = list.head; p != nullptr; p = p->next) {
            arr[i++] = &p->data;
        }
        sortOrders(arr, list.size);

        printf("Замовлення за вартістю:\n");
        for (i = 0; i < list.size; i++) {
            char price[16];
            moneyToStr(arr[i]->price, price);
            printf("№%d%11s грн  %s\n", arr[i]->id, price, statusName(arr[i]->status));
        }

        Money diff = arr[0]->price - arr[list.size - 1]->price;
        delete[] arr;

        std::cout << "Різниця між найдорожчим і найдешевшим: " << diff << " грн\n";
        std::cout << "Виручка за завершеними ремонтами: " << revenue(list.head) << " грн\n";
    }

    printf("Майстри, починаючи з наступного в черзі:\n");
    Master* m = current;
    do {
        printf("%-12s виконано: %d, виручка: ", m->name, m->done);
        std::cout << m->revenue << " грн\n";
        m = m->next;
    } while (m != current);
}

// Пункт 8: розвертає журнал на місці й виводить номери першого та останнього замовлення
void reverseJournal(OrderList& list) {
    if (list.head == nullptr) {
        printf("Журнал порожній.\n");
        return;
    }
    listReverse(list);
    printf("Журнал розвернуто: тепер першим іде замовлення №%d, останнім №%d.\n",
           list.head->data.id, list.tail->data.id);
}
