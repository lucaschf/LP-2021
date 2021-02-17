#include "Program.h"
#include <iostream>
#include <iomanip>

using namespace std;

void Program::execute()
{
	int choosen;

	do {
		cout << "Choose an option: \n\n1 - Add a product in stock\n2 - Display the total value of each stock";
		cout << "\n3 - display the quantity of products in each stock\n4 - Fetch product by name "
			<< "\n5 - Generate reports\n6 - Exit: ";

		cin >> choosen;
		cout << endl;

		switch (choosen)
		{
		case 1:
			productRegistration();
			break;
		case 2:
			displayTotalItemsCount(foodStock, ProductType::FOOD);
			displayTotalItemsCount(cleaningMaterialStock, ProductType::CLEANING_MATERIAL);
			displayTotalItemsCount(personalHygieneStock, ProductType::PERSONAL_HIGYENE);
			break;
		case 3:
			displayTotalValue(foodStock, ProductType::FOOD);
			displayTotalValue(cleaningMaterialStock, ProductType::CLEANING_MATERIAL);
			displayTotalValue(personalHygieneStock, ProductType::PERSONAL_HIGYENE);
			break;
		case 4:
			fetchProductByName();
			break;
		case 5:
			generateReport(foodStock, ProductType::FOOD);
			generateReport(cleaningMaterialStock, ProductType::CLEANING_MATERIAL);
			generateReport(personalHygieneStock, ProductType::PERSONAL_HIGYENE);
			break;
		default:
			break;
		}

	} while (choosen != 6);
}

void Program::addProductInStock(Stock& stock)
{
	string name;
	double price;
	int quantity;

	cout << "\nName: ";
	cin >> name;

	cout << "\nQuantity: ";
	cin >> quantity;

	cout << "\nPrice: ";
	cin >> price;

	Product p = Product(name, quantity, price);

	stock.addProduct(p);
	cout << "\nProduct " << p.getName() << " successfully added in stock\n";
}

int Program::readProductType()
{
	int type;

	cout << "\nChoose a product type: \n\n1 - Food \n2 - Cleaning material" <<
		"\n3 - Personal Higyene\n4 - back\n: ";
	cin >> type;

	return type;
}

void Program::productRegistration()
{
	ProductType type = static_cast<ProductType>(readProductType());

	switch (type)
	{
	case ProductType::FOOD:
		addProductInStock(foodStock);
		break;
	case ProductType::CLEANING_MATERIAL:
		addProductInStock(cleaningMaterialStock);
		break;
	case ProductType::PERSONAL_HIGYENE:
		addProductInStock(personalHygieneStock);
		break;
	default:
		break;
	}
}

void Program::generateReport(Stock stock, ProductType type)
{
	const string spaces = "    ";

	cout << "\n- Stock of " << title[static_cast<int>(type) - 1] << endl;

	cout << spaces << setw(21) << left << "Product"
		<< setw(21) << left << "Quantity"
		<< setw(21) << left << "Unitary price"
		<< setw(21) << left << "Total value" << endl;

	for (int i = 0; i < stock.getProductCount(); i++) {
		auto p = stock.getProduct(i);

		auto price = "R$ " + to_string(p.getPriceForQuantity());

		cout << spaces <<  setw(21) << left << p.getName()
			<< setw(21) << left << p.getQuantity()
			<< setw(21) << left << p.getPrice()
			<< setw(21) << left << price << endl;
	}

	cout << spaces << setw(21) << left << "Total of items in stock:"
		<< setw(21) << left << stock.getProductCount()
		<< setw(21) << left << "\t Stock total value: R$ " 
		<< setw(21) << left << stock.getTotalValue() << endl << endl;
}

void Program::fetchProductByName()
{
	ProductType type = static_cast<ProductType>(readProductType());

	switch (type)
	{
	case ProductType::FOOD:
		fecthProduct(foodStock);
		break;
	case ProductType::CLEANING_MATERIAL:
		fecthProduct(cleaningMaterialStock);
		break;
	case ProductType::PERSONAL_HIGYENE:
		fecthProduct(personalHygieneStock);
		break;
	default:
		break;
	}
}

void Program::fecthProduct(Stock stock)
{
	string name;

	cout << "Name: ";
	cin >> name;

	auto p = stock.fetchProductPosition(name);

	if (p == -1)
	{
		cout << "Product not found." << endl;
		return;
	}

	auto product = stock.getProduct(p);
	cout << product.getName() << " \t " << product.getQuantity() << " \t " << product.getPrice()
		<< " \t R$ " << product.getPriceForQuantity() << endl;
}

void Program::displayTotalValue(Stock stock, ProductType type)
{
	cout << ">> Total value of items in " << title[static_cast<int>(type) - 1] << " inventory"
		<< ": R$ " << stock.getTotalValue() << endl << endl;
}

void Program::displayTotalItemsCount(Stock stock, ProductType type)
{
	cout << ">> Total of items in " << title[static_cast<int>(type) - 1] << " inventory"
		<< ": " << stock.countItemsInStock() << endl << endl;
}
