#include "Product.h"

Product::Product()
{
    setName("");
    setQuantity(0);
    setPrice(0);
}

Product::Product(string name, int quantity, double price)
{
    setName(name);
    setQuantity(quantity);
    setPrice(price);
}

void Product::setName(string name)
{
    this->name = name;
}

void Product::setQuantity(int quantity)
{
    this->quantity = quantity;
}

void Product::setPrice(double price)
{
    this->price = price;
}

string Product::getName()
{
    return this->name;
}

int Product::getQuantity()
{
    return this->quantity;
}

double Product::getPrice()
{
    return this->price;
}

double Product::getPriceForQuantity()
{
    return getPrice() * getQuantity();
}
