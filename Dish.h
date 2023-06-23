#pragma once
#include <string>

class Dish {
public:
    int id; //id блюда
    std::string name; //название блюда
    int craft; //рецепт
    int time; //время готовки
    int price; //цена блюда
    int quantity; //кол-во блюд в наличии

    //конструктор блюда
    Dish(int _id, const std::string& _name, int _craft, int _time, int _price, int _quantity);
};


