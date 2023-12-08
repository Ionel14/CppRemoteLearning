#include <iostream>
#include "functions.cpp"
int main()
{
    srand(time(0));
    std::vector<Product> products;
    for (int i = 0; i < 10; i++)
    {
        products.push_back(Product());
    }
    
    std::cout<<"Your total is: "<<GetTotalPrice(products)<< std::endl;
    return 0;
}