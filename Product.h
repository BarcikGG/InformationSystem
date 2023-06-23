#pragma once
#include <string>

class Product {
public:
    int id; //id продукта
    std::string name; //название продукта
    int price; //цена продукта (закупочная)

    //конструктор продукта
    Product(int _id, const std::string& _name, int _price);
};

