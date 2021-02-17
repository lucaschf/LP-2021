#ifndef ESTOQUE_H
#define ESTOQUE_H

#include <vector>
#include "Product.h"

class Stock {
public:

	// Creates a stock of products with an initial size of zero.
	Stock();

	// Creates a stock of products with initial size defined by the size parameter.
	Stock(int size);

	// Add a product to the stock.
	void addProduct(Product p);

	/*Obt�m uma refer�ncia do objeto produto armazenado no array de objetos na posi��o determinada.
		Se uma posi��o para inv�lida retorna um objeto Produto com atributos vazios.*/
	Product& getProduct(int position);

	/*Pesquisa por um nome de produto no estoque.
		Retorna a posi��o do produto no estoque, se o produto n�o estiver cadastrado retorna - 1. */
	int fetchProductPosition(string name);

	/*Exclui um produto do estoque na posi��o atribu�da.Retorna true se o produto foi exclu�do, caso contr�rio retorna false.*/
	bool removeProduct(int position);

	double getTotalValue();

	int getProductCount();

	int countItemsInStock();

private:

	bool isValidPosition(int position);

	// List of products in stock.
	vector<Product> storage;

	// Rela��o de produtos do estoque. vector<Produto> estoque;
	// Quantidade de produtos cadastrados no estoque.
	int productCount;

};
#endif