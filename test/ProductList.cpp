#include "ProductList.h"
#include <iostream>
#include <algorithm>    // std::find_if

void ProductList::insertAtStart(const Product& product)
{
    items.insert(items.begin(), product);
}

void ProductList::insertAtEnd(const Product& product)
{
    items.emplace_back(product);
}

bool ProductList::removeAtStart(Product& product)
{
    if (isEmpty())
        return false;

    product = items.front();
    items.erase(items.begin());

    return true;
}

bool ProductList::removeAtEnd(Product& product)
{
    if (isEmpty())
        return false;

    product = items.back();
    items.pop_back();
    return true;
}

Product& ProductList::fetch(string name)
{
    auto it = find_if(
        items.begin(),
        items.end(),
        [&](Product& p) {return p.getName() == name; });

    return *it._Unwrapped();
}

bool ProductList::isEmpty()
{
    return items.empty();
}

bool ProductList::show()
{
    if(isEmpty())
        return false;

    cout << "Product \t Quantity \t Unitary price \t Total value" << endl;
    for (auto p : items) {
        cout << p.getName() << " \t " << p.getQuantity() << " \t "
            << p.getPrice() << " \t R$ " << p.getPriceForQuantity() << endl;
    }

    return true;
}

int ProductList::size()
{
    return items.size();
}
