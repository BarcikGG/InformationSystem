#include "Product.h"

//определение конструктора продукта
Product::Product(int _id, const std::string& _name, int _price) : id(_id), name(_name), price(_price) {}
