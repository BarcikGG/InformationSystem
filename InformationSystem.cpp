#include <iostream>
#include <string>
#include <map>
#include <vector>

// Класс продукта
class Product {
public:
    std::string name;
    int quantity;

    Product(const std::string& _name, int _quantity) : name(_name), quantity(_quantity) {}
};

// Класс меню
class Menu {
private:
    std::vector<Product> products;

public:
    void addToMenu(const std::string& name, int quantity) {
        products.emplace_back(name, quantity);
    }

    bool isAvailable(const std::string& name, int quantity) {
        for (const auto& product : products) {
            if (product.name == name && product.quantity >= quantity) {
                return true;
            }
        }
        return false;
    }
};

// Класс корзины заказа гостя
class GuestOrderBasket {
private:
    std::vector<Product> items;

public:
    void addItem(const std::string& name, int quantity) {
        items.emplace_back(name, quantity);
    }

    void printBasket() const {
        for (const auto& item : items) {
            std::cout << "Product: " << item.name << ", Quantity: " << item.quantity << std::endl;
        }
    }
};

// Класс заказа
class Order {
public:
    std::string status;

    Order() : status("Новый заказ") {}

    void confirmOrder() {
        status = "Оплачен и передан на кухню";
    }

    void updateStatus(const std::string& newStatus) {
        status = newStatus;
    }
};

// Класс сотрудника
class Employee {
public:
    std::string role;
    std::string lastName;
    std::string firstName;
    std::string patronymic;
    std::string username;
    std::string password;

    Employee(
        const std::string& _role,
        const std::string& _lastName,
        const std::string& _firstName,
        const std::string& _patronymic,
        const std::string& _username,
        const std::string& _password)
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
    std::vector<std::string> entries;

public:
    void addEntry(const std::string& entry) {
        entries.push_back(entry);
    }

    void printEntries() const {
        for (const auto& entry : entries) {
            std::cout << entry << std::endl;
        }
    }
};

class ProductRequest {
public:
    std::map<int, int> products; // Ключ - идентификатор продукта, Значение - количество продукта
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
    void viewProductRequests(const std::vector<ProductRequest>& requests) {
        // Логика просмотра всех отправленных заявок на продукты
    }

    void viewDeliveries(const std::vector<ProductRequest>& deliveries) {
        // Логика просмотра всех принятых поставок продуктов
    }

    void viewFinancialReports() {
        // Логика просмотра финансовой отчетности
    }
};

class Chef {
public:
    void viewOrders(const std::vector<Order>& orders) {
        // Логика просмотра всех заказов
    }

    void startPreparation(Order& order) {
        // Логика начала приготовления заказа
    }

    void prepareItem(Order& order, int menuItemIndex, const std::vector<int>& productNumbers) {
        // Логика приготовления конкретного пункта заказа
    }
};

// Класс официанта
class Waiter {
public:
    void viewAvailableOrders(const std::vector<Order>& orders) {
        // Логика просмотра доступных для выдачи заказов
    }

    void changeOrderStatus(Order& order, const std::string& newStatus) {
        order.status = newStatus;
    }
};

int main()
{
    

    return 0;
}

