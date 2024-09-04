#include <iostream>
#include "middleware/utils/MySqlModel.hpp"

int main()
{
    MySqlModel model;
    auto result = model.execute_query("SELECT * FROM `order_products`");
    std::cout << result.rows().at(0).at(1) << std::endl;
    return 0;
}