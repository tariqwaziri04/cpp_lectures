#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//List of items categories stored in the shop.
enum class items{
    vegetables,
    shampoos, 
    cereals, 
    shoes, 
    savouries,
    alcohol,
    fruits,
    salads,
    dairy,
    toiletries,
    accessories,
    frozen_foods,
    soft_drinks,
    confectionery,
    biscuits,
    fresh_meats,
    pet_care,
    canned_goods,
    hot_beverages,
    household_cleaning,
    ambient_bakery,
    fresh_poultry,
    games,
    health_care,
    chilled_convenience,
    clothings,
    condiments,
    books,
    postcards,
    electronics,
    Count
};

/// @brief Holds the names of the product categories.
constexpr string_view PRODUCT_NAMES[static_cast<int>(items::Count)] = {
    [static_cast<int>(items::vegetables)]    = "vegetables",
    [static_cast<int>(items::shampoos)]      = "shampoos",
    [static_cast<int>(items::cereals)]        = "cereals",
    [static_cast<int>(items::shoes)]  = "shoes",
    [static_cast<int>(items::savouries)]     = "savouries",
    [static_cast<int>(items::alcohol)]     = "alcohol",
    [static_cast<int>(items::fruits)] = "fruits",
    [static_cast<int>(items::salads)]   = "salads",
    [static_cast<int>(items::dairy)]      = "dairy",
    [static_cast<int>(items::toiletries)] = "toiletries",
    [static_cast<int>(items::accessories)] = "accessories",
    [static_cast<int>(items::frozen_foods)] = "frozen_foods",
    [static_cast<int>(items::soft_drinks)] = "soft_drinks",
    [static_cast<int>(items::confectionery)] = "confectionery",
    [static_cast<int>(items::biscuits)] = "biscuits",
    [static_cast<int>(items::fresh_meats)] = "fresh_meats",
    [static_cast<int>(items::pet_care)] = "pet_care",
    [static_cast<int>(items::canned_goods)] = "canned_goods",
    [static_cast<int>(items::hot_beverages)] = "hot_beverages",
    [static_cast<int>(items::household_cleaning)] = "household_cleaning",
    [static_cast<int>(items::ambient_bakery)] = "ambient_bakery",
    [static_cast<int>(items::fresh_poultry)] = "fresh_poultry",
    [static_cast<int>(items::games)] = "games",
    [static_cast<int>(items::health_care)] = "health_care",
    [static_cast<int>(items::chilled_convenience)] = "chilled_convenience",
    [static_cast<int>(items::clothings)] = "clothings",
    [static_cast<int>(items::condiments)] = "condiments",
    [static_cast<int>(items::books)] = "books",
    [static_cast<int>(items::postcards)] = "postcards",
    [static_cast<int>(items::electronics)] = "electronics",
};


int main() {
    cout
    std::cout << "Hello World! \n";
    return 0;
}