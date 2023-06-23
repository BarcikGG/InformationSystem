#pragma once
#include <string>

class Dish {
public:
    int id; //id �����
    std::string name; //�������� �����
    int craft; //������
    int time; //����� �������
    int price; //���� �����
    int quantity; //���-�� ���� � �������

    //����������� �����
    Dish(int _id, const std::string& _name, int _craft, int _time, int _price, int _quantity);
};


