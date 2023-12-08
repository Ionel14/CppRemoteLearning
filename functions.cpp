#include "product.h"

static int GetTotalPrice(std::vector<Product> &products)
{
    int total = 0;
    for (int i = 0; i < products.size(); i++)
    {
        total+= products[i].price_;
    }
    return total;
}
