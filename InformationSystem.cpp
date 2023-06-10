#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// Класс продукта
class Product {
public:
    int id; //id блюдв
    string name; //название блюда
    double price; //цена блюда
    int quantity; //кол-во блюд в наличии

    //конструктор продукта
    Product(int _id, const string& _name, int _quantity, double _price) : id(_id), name(_name), quantity(_quantity), price(_price) {} 
};

// Класс ресторан
class Restaurant {
private:
    double balance; //баланс рестика

public:
    Restaurant(double initialBalance) : balance(initialBalance) {} //конструктор рестика

    //функция возвращающая баланс ресторана
    double getBalance() const {
        return balance;
    }

    //функция для пополнения баланса ресторана
    void deposit(double amount) {
        balance += amount; //пополняем баланс
    }

    //функция для списания средств со счета ресторана
    bool withdraw(double amount) {
        if (amount <= balance) { //проверяем, что списываем меньше или сумму баланса рестика
            balance -= amount; //списываем бабки
            return true;  // Успешное списание средств
        }
        return false;  // Недостаточно средств на балансе
    }
};


// Класс меню
class Menu {
private:
    vector<Product> products; //лист блюд для меню

public:
    //функция добавления блюда в меню
    void addToMenu(int id, const string& name, double price, int quantity) {
        products.emplace_back(id, name, price, quantity); //добавление блюда
    }

    //функция проверки доступности блюда для заказа
    bool isAvailable(const string& name, int quantity) {
        for (const auto& product : products) { //циклом проходимся по всем позициям меню
            //проверяем, что конкретное блюдо в количество больше или равно запрашиваемому количеству
            if (product.name == name && product.quantity >= quantity) {
                return true; //возвращаем true если блюдо есть
            }
        }
        return false; //блюд не хватает
    }
    
    //функция  вывода блюд меню
    void GetMenu() {
        for (const auto& product : products) { //цикл проходящий по всем позициям меню
            cout << "ID: " << product.id << " | Блюдо: " << product.name << " Цена: " << product.price << "руб." << endl; //вывод блюда
        }
    }

    //функция возвращающая название блюда
    string getMenuProductNameById(int id) {
        for (const auto& product : products) { //цикл проходящий по всем позициям меню
            if (product.id == id) { //проверка соответствия id искомого блюда с текущим в цикле
                return product.name; //возвращаем название блюда
            }
        }
        return "Блюдо не найдено";  //возвращаем пустую строку, если продукт с указанным id не найден
    }

    //функция возвращающая цену блюда
    double GetPrice(int id) {
        for (const auto& product : products) { //цикл проходящий по всем позициям меню
            if (product.id == id) { //проверка соответствия id искомого блюда с текущим в цикле
                return product.price; //возвращаем цену блюда
            }
        }
        return 0; // Возвращаем 0, если продукт не найден
    }

    //функция возвращающая кол-во конкретного блюда
    int GetQuantity(int id) {
        for (const auto& product : products) { //цикл проходящий по всем позициям меню
            if (product.id == id) { //проверка соответствия id искомого блюда с текущим в цикле
                return product.quantity; //возвращаем кол-во конкретного блюда
            }
        }
        return 0; // Возвращаем 0, если продукт не найден
    }
};

// Класс корзины заказа гостя
class GuestOrderBasket {
private:
    vector<Product> items; //лист с блюдами заказа

public:
    //функция добавления блюда в заказ
    void addItem(int id, string name, double price, int quantity) {
        items.emplace_back(id, name, price, quantity); //добавление блюда
    }

    //вывод корзины в консоль
    void printBasket() const {
        cout << "Ваш заказ: " << endl;
        for (const auto& item : items) { //цикл проходящий по всем позиция корзины
            cout << "Блюдо: " << item.name << ", Количество: " << item.quantity << endl; //вывод каждого блюда
        }
    }

    //функция для подсчета стоимости всего заказа
    double Amount() {
        double amount = 0; //обнуляем стоимость
        for (const auto& item : items) { //проходимся по всем пунктам заказа
            amount += item.price * item.quantity; //прибавляем к итоговой стоимости стоимость блюда умноженного на количество этого блюда
        }
        return amount; //возвращаем стоимость корзины
    }
};

// Класс заказа
class Order {
public:
    string status; //статус заказа

    Order() : status("Новый заказ!") {} //конструктор заказа

    void confirmOrder() {
        status = "Оплачен и передан на кухню";
        cout << status << endl;
    }

    void CookingOrder() {
        status = "В процессе приготовления";
        cout << status << endl;
    }

    void DeliveryOrder() {
        status = "Передан официанту";
        cout << status << endl;
    }

    void CompleteOrder() {
        status = "Выдано";
        cout << status << endl;
    }

    string GetStatus() {
        return status;
    }
};

// Класс сотрудника
class Employee {
public:
    string role;
    string lastName;
    string firstName;
    string patronymic;
    string username;
    string password;

    Employee(
        const string& _role,
        const string& _lastName,
        const string& _firstName,
        const string& _patronymic,
        const string& _username,
        const string& _password)
        : role(_role),
        lastName(_lastName),
        firstName(_firstName),
        patronymic(_patronymic),
        username(_username),
        password(_password) {}
};

// Класс системного администратора
class SystemAdministrator {
public:
    void editMenu() {
        // Логика редактирования меню
    }

    void editProductList(Menu& menu) {
        // Логика редактирования списка продуктов
    }

    void editEmployeeAccounts() {
        // Логика редактирования учетных записей сотрудников
    }
};

// Класс журнала аудита
class AuditLog {
private:
    vector<string> entries;

public:
    void addEntry(const string& entry) {
        entries.push_back(entry);
    }

    void printEntries() const {
        for (const auto& entry : entries) {
            cout << entry << endl;
        }
    }
};

class ProductRequest {
public:
    map<int, int> products; // Ключ - идентификатор продукта, Значение - количество продукта
};

// Класс складского
class Storekeeper {
public:
    ProductRequest createProductRequest(const Menu& menu) {
        ProductRequest request;

        // Логика создания заявки на продукты

        return request;
    }

    void trackInventory(const Menu& menu) {
        // Логика отслеживания количества продуктов на складе
    }
};

// Класс поставщика
class Supplier {
public:
    void processProductRequest(const ProductRequest& request, Menu& menu) {
        // Логика обработки заявки на продукты и отправки продуктов
    }
};

// Класс бухгалтера
class Accountant {
public:
    void viewProductRequests(const vector<ProductRequest>& requests) {
        // Логика просмотра всех отправленных заявок на продукты
    }

    void viewDeliveries(const vector<ProductRequest>& deliveries) {
        // Логика просмотра всех принятых поставок продуктов
    }

    void viewFinancialReports() {
        // Логика просмотра финансовой отчетности
    }
};

class Chef {
public:
    void viewOrders(const vector<Order>& orders) {
        // Логика просмотра всех заказов
    }

    void startPreparation(Order& order) {
        // Логика начала приготовления заказа
    }

    void prepareItem(Order& order, int menuItemIndex, const vector<int>& productNumbers) {
        // Логика приготовления конкретного пункта заказа
    }
};

// Класс официанта
class Waiter {
public:
    void viewAvailableOrders(const vector<Order>& orders) {
        // Логика просмотра доступных для выдачи заказов
    }

    void changeOrderStatus(Order& order, const string& newStatus) {
        order.status = newStatus;
    }
};

//метод для очистки консоли
void clearConsole() {
    system("cls");
}

//метод для работы с гостем
int Guest(bool isLogin, Menu menu, Restaurant restaurant) {
    isLogin = true; //переменная для определения статуса пользователя и управления циклом
    char answer; //ответ гостя по заказа (да/нет)
    char action; //действие гостя (просмотр статуса или смена роли)
    int status = 0; //статус заказа
    double guest_amount; //сумма которую заплатил гость

    unique_ptr<GuestOrderBasket> backet = make_unique<GuestOrderBasket>(); // создание умного указателя корзины
    unique_ptr<Order> order = make_unique<Order>(); // создание умного указателя заказа

    clearConsole();
    menu.GetMenu(); //выводим меню для гостя
    int id = 0; //id для ввода номера заказа

    do {
        try {
            int quantity = 0;
            cout << "Для заказа блюда, введите его номер (0 - завершить): " << endl;
            cin >> id;

            string productName = menu.getMenuProductNameById(id);
            int AvailableQuantity = menu.GetQuantity(id);

            if (menu.isAvailable(productName, quantity)) {
                cout << "Количество: " << endl;
                cin >> quantity;

                if (AvailableQuantity < quantity) cout << "У нас всего: " << AvailableQuantity << "шт. " << productName << endl;
                else backet->addItem(id, productName, menu.GetPrice(id), quantity);
            }
            else cout << productName << endl;
        }
        catch (exception) {}
    } while (id != 0);

    clearConsole();
    backet->printBasket();

    do {
        cout << "Подтвердить заказ? (y/n): ";
        cin >> answer;

        if (answer == 'y') {
            do {
                try {
                    cout << "К оплате: " << backet->Amount() << "\nВаша сумма: ";
                    cin >> guest_amount;

                    if (guest_amount >= backet->Amount()) {
                        clearConsole();
                        restaurant.deposit(guest_amount);
                        cout << "Статус: ";
                        order->confirmOrder();
                        cout << "Спасибо! Ваш заказ передан на кухню." << endl;
                        break;
                    }
                    else cout << "Недостаточно средств" << endl;
                }
                catch (exception) {}

            } while (guest_amount < backet->Amount());
            break;
        }
    } while (answer != 'y' || answer != 'n');

    do {
        cout << "s - статус заказа\nr - смена роли" << endl;
        cin >> action;

        if (action == 's') {
            switch (status)
            {
            case 0:
                clearConsole();
                cout << order->GetStatus() << endl;
                break;
            case 1:
                clearConsole();
                order->CookingOrder();
                break;
            case 2:
                clearConsole();
                order->DeliveryOrder();
                break;
            case 3:
                clearConsole();
                order->CompleteOrder();
                break;
            default:
                clearConsole();
                cout << order->GetStatus() << endl;
                break;
            }

            status++;
        }
    } while (action != 'r');

    clearConsole();
    return 0;
}

int main()
{
    bool isLogin = false;
    setlocale(LC_ALL, "Russian");
    string login;
    string password;

    Restaurant restaurant{1000000};
    Menu menu;

    menu.addToMenu(1, "Бургер", 499, 5);
    menu.addToMenu(2, "Пицца", 1200, 3);
    menu.addToMenu(3, "Салат", 399, 2);
    menu.addToMenu(4, "Суп", 350, 4);
    menu.addToMenu(5, "Стейк", 1200, 6);
    menu.addToMenu(6, "Рыба", 1500, 3);
    menu.addToMenu(7, "Паста", 850, 4);
    menu.addToMenu(8, "Картофель фри", 250, 5);
    menu.addToMenu(9, "Суши", 999, 7);
    menu.addToMenu(10, "Десерт", 450, 3);

    while (!isLogin) {
        cout << "Добро пожаловать в ресторан" << endl;
        cout << "Ваш логин: ";
        cin >> login;
        cout << "Ваш пароль: ";
        cin >> password;

        if (login == "guest" && password == "guest") {
            Guest(isLogin, menu, restaurant);
            main();
        }
        else if (login == "admin" && password == "admin") {
            
        }
    }

    return 0;
}

