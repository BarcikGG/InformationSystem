#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// Класс продукта
class Product {
public:
    int id;
    string name;
    double price;
    int quantity;

    Product(int _id, const string& _name, int _quantity, double _price) : id(_id), name(_name), quantity(_quantity), price(_price) {}
};

// Класс ресторан
class Restaurant {
private:
    double balance;

public:
    Restaurant(double initialBalance) : balance(initialBalance) {}

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;  // Успешное списание средств
        }
        return false;  // Недостаточно средств на балансе
    }
};


// Класс меню
class Menu {
private:
    vector<Product> products;

public:
    void addToMenu(int id, const string& name, double price, int quantity) {
        products.emplace_back(id, name, price, quantity);
    }

    bool isAvailable(const string& name, int quantity) {
        for (const auto& product : products) {
            if (product.name == name && product.quantity >= quantity) {
                return true;
            }
        }
        return false;
    }

    void GetMenu() {
        for (const auto& product : products) {
            cout << "ID: " << product.id << " | Dish: " << product.name << " Цена: " << product.price << "руб." << endl;
        }
    }

    string getMenuProductNameById(int id) {
        for (const auto& product : products) {
            if (product.id == id) {
                return product.name;
            }
        }
        return "Блюдо не найдено";  // Возвращаем пустую строку, если продукт с указанным id не найден
    }

    double GetPrice(int id) {
        for (const auto& product : products) {
            if (product.id == id) {
                return product.price;
            }
        }
        return 0; // Возвращаем 0, если продукт не найден
    }

    int GetQuantity(int id) {
        for (const auto& product : products) {
            if (product.id == id) {
                return product.quantity;
            }
        }
        return 0; // Возвращаем 0, если продукт не найден
    }
};

// Класс корзины заказа гостя
class GuestOrderBasket {
private:
    vector<Product> items;

public:
    void addItem(int id, string name, double price, int quantity) {
        items.emplace_back(id, name, price, quantity);
    }

    void printBasket() const {
        cout << "Ваш заказ: " << endl;
        for (const auto& item : items) {
            cout << "Dish: " << item.name << ", Quantity: " << item.quantity << endl;
        }
    }

    double Amount() {
        double amount = 0;
        for (const auto& item : items) {
            amount += item.price;
        }
        
        return amount;
    }
};

// Класс заказа
class Order {
public:
    string status;

    Order() : status("New order") {}

    void confirmOrder() {
        status = "Оплачен и передан на кухню";
    }

    void updateStatus(const string& newStatus) {
        status = newStatus;
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

void clearConsole() {
    system("cls");
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
            isLogin = true;
            char answer;
            double guest_amount;
            GuestOrderBasket backet;

            clearConsole();
            menu.GetMenu();
            int id = 0;
            do {
                try {
                    int quantity = 0;
                    cout << "Для заказа блюда, введите его номер (0 - exit): " << endl;
                    cin >> id;

                    string productName = menu.getMenuProductNameById(id);
                    int AvailableQuantity = menu.GetQuantity(id);

                    if (menu.isAvailable(productName, quantity)) {
                        cout << "Количество: " << endl;
                        cin >> quantity;

                        if (AvailableQuantity < quantity) cout << "У нас всего: " << AvailableQuantity << "шт. " << productName << endl;
                        else backet.addItem(id, productName, menu.GetPrice(id), quantity);
                    }
                    else cout << productName << endl;
                }
                catch(exception) {}
            } while (id != 0);

            clearConsole();
            backet.printBasket();

            do {
                cout << "Подтвердить заказ? (y/n): ";
                cin >> answer;

                if (answer == 'y') {
                    do {
                        try {
                            cout << "К оплате: " << backet.Amount() << "\nВаша сумма: ";
                            cin >> guest_amount;

                            if (guest_amount >= backet.Amount()) {
                                clearConsole();
                                cout << "Спасибо! Ваш заказ передан на кухню." << endl;
                                break;
                            }
                            else cout << "Недостаточно средств" << endl;
                        }
                        catch(exception) {}

                    } while (guest_amount < backet.Amount());
                }
            } while (answer != 'y' || answer != 'n');
        }
    }

    return 0;
}

