#include "Dish.h"

//определение конструктора блюда
Dish::Dish(int _id, const std::string& _name, int _craft, int _time, int _price, int _quantity) : id(_id), name(_name), craft(_craft), time(_time), price(_price), quantity(_quantity) {}
