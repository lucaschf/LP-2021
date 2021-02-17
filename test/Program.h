#pragma once
#include "Stock.h"

#include <string>

using namespace std;

enum class ProductType { FOOD = 1, CLEANING_MATERIAL, PERSONAL_HIGYENE };

class Program
{
public:
	
	Program() = default;

	void execute();

private:
	
	Stock foodStock = Stock();
	Stock cleaningMaterialStock = Stock();
	Stock personalHygieneStock = Stock();

	string title[3] = { "food", "cleaning material", "personal higyene" };

	void addProductInStock(Stock& stock);

	int readProductType();

	void productRegistration();

	void generateReport(Stock stock, ProductType type);

	void fetchProductByName();

	void fecthProduct(Stock stock);

	void displayTotalValue(Stock stock, ProductType type);

	void displayTotalItemsCount(Stock stock, ProductType type);
};

