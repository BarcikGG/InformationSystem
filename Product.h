#pragma once
#include <string>

class Product {
public:
    int id; //id ��������
    std::string name; //�������� ��������
    int price; //���� �������� (����������)

    //����������� ��������
    Product(int _id, const std::string& _name, int _price);
};

