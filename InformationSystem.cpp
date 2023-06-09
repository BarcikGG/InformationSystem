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
    int quantity;

    Product(int _id, const string& _name, int _quantity) : id(_id), name(_name), quantity(_quantity) {}
};

// Класс меню
class Menu {
private:
    vector<Product> products;

public:
    void addToMenu(int id, const string& name, int quantity) {
        products.emplace_back(id, name, quantity);
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
            cout << "ID: " << product.id << " | Dish: " << product.name << endl;
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
    void addItem(int id, string name, int quantity) {
        items.emplace_back(id, name, quantity);
    }

    void printBasket() const {
        cout << "Ваш заказ: " << endl;
        for (const auto& item : items) {
            cout << "Dish: " << item.name << ", Quantity: " << item.quantity << endl;
        }
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

    Menu menu;

    menu.addToMenu(1, "Бургер", 5);
    menu.addToMenu(2, "Пицца", 3);
    menu.addToMenu(3, "Салат", 2);
    menu.addToMenu(4, "Суп", 4);
    menu.addToMenu(5, "Стейк", 6);
    menu.addToMenu(6, "Рыба", 3);
    menu.addToMenu(7, "Паста", 4);
    menu.addToMenu(8, "Картофель фри", 5);
    menu.addToMenu(9, "Суши", 7);
    menu.addToMenu(10, "Десерт", 3);

    while (!isLogin) {
        cout << "Добро пожаловать в ресторан" << endl;
        cout << "Ваш логин: ";
        cin >> login;
        cout << "Ваш пароль: ";
        cin >> password;

        if (login == "guest" && password == "guest") {
            isLogin = true;
            GuestOrderBasket backet;
            clearConsole();
            menu.GetMenu();
            int id = 0;
            do {
                int quantity = 0;
                cout << "Для заказа блюда, введите его номер: " << endl;
                cin >> id;
                cout << "Количество: " << endl;
                cin >> quantity;

                string productName = menu.getMenuProductNameById(id);
                if (menu.isAvailable(productName, quantity)) backet.addItem(id, productName, quantity);
                else cout << "У нас всего: " << menu.GetQuantity(id) << "шт. " << productName << endl;
            } while (id != 0);

            backet.printBasket();
        }
    }

    return 0;
}

