#include <algorithm>
#include <ios>
#include <string>
#include <vector>
#include <iostream>
#include <optional>
using namespace std;

constexpr auto MAX_ITEMS      = 30;
constexpr auto MAX_MODEL_NAME = 70;        // longest model name

//List of items categories stored in the shop.
enum class items{
    Invalid = -1,
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

// Holds the names of the product categories.
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

// Checks if the given product is valid.
constexpr auto is_valid_product(items prod) { return prod > items::Invalid && prod < items::Count; }

// Return the name of the given product.
constexpr auto get_product_name(items prod)
{
        if (!is_valid_product(prod)) { return string_view {""}; }

        return PRODUCT_NAMES[static_cast<int>(prod)];
}

// Prints a list of all the product categories available.
auto list_products()
{
        cout << "Items list: \n";
        for_each_n(begin(PRODUCT_NAMES), size(PRODUCT_NAMES), [i = 0](const auto& name) mutable {
                cout << "%s\n", i , name.data();
                i++;
        });
        cout << "==============================" << endl;
}

/// Represents a stocked item corresponding to one of the listed products categories.
struct item
{
    items     id;            // items category that item falls into
    string name;          // Name of the item 
    float       price;         // Price in GBP
    int         nstock;        // No. of units in stock
    int   bbd; // best before date

        item() = default;

        item(const items prod, const std::string& name, const float price, const int nstock) :
                id {prod}, name {name}, price {price}, nstock {nstock}, bbd {bbd}
            {}

        auto print() const { printf("%32s%64s%16.2f%8d\n", get_product_name(id).data(), name.c_str(), price, nstock); }
};
// Holds the inventory of all the stocked items in the store.
struct Inventory
{
        using SearchPredicate = function<bool(const item&)>;
        using Items           = vector<item>;
        using ItemPtr         = Items::iterator;        // pointer to item type

        Items items;

        Inventory() { items.reserve(MAX_ITEMS); }

        // Add the given items to the inventory.
        auto add(const Items& item) { items.emplace_back(item); }

        // Deletes the given item from the inventory.
        auto remove(ItemPtr pitem) { items.erase(pitem); }

        // Look for the item for which the given predicate returns true.
        // nullptr if item is not found else pointer to item.
        auto search(const SearchPredicate& pred) -> ItemPtr
        {
                auto pitem = std::find_if(items.begin(), items.end(), pred);
                if (pitem != items.end()) { return pitem; }
                return {};
        
        }

        // Prints a table listing currently stocked items in the inventory.
        auto list()
        {
            printf("%32s%64s%16s%8s\n", "Product", "Model Name", "Price (GBP)", "Qty.");
            for_each(items.begin(), items.end(), [](const auto& item) { item.print(); });
            cout << "========================" << endl;
        }
};

struct InventoryUI{
    enum class Options
    {
        Invalid      = -1,
        Add_Items      = 'a',
        Remove_Items   = 'r',
        Edit_Items     = 'e',
        Search_Items   = 's',
        List_Products = 'p',
        List_Items    = 'l',
        Quit         = 'q',
    };

    Inventory inventory;

    auto user_input_handlers() {}

    auto list_options()
    {
        printf("(%c) Add Item\n", static_cast<char>(Options::Add_Items));
        printf("(%c) Search Item\n", static_cast<char>(Options::Search_Items));
        printf("(%c) List Product Categories\n", static_cast<char>(Options::List_Products));
        printf("(%c) List Items in Stock\n", static_cast<char>(Options::List_Items));
        printf("(%c) Quit\n", static_cast<char>(Options::Quit));
    }
        // get the user from the inventory management systems
    auto get_user_actions()
    {
        char oprt {};
        cout << "Select operation: ";
        cin >> oprt;
        cout << "============================" << endl;
        return oprt;
    }

        /// Adds item to the inventory.
    auto handle_add_options()
    {
        items Items;
        do {
                list_products();
                cout << "Select product category to add: ";
                int pid {};
                cin >> &Items.id;
                if (!is_valid_product(Items.id)) { cout << "Invalid option selected. Please try again.\n"; }
                else
                {
                cout << "Enter model name: ";
                getline(cin >> ws, Items.name);
                cout << "Enter price: ";
                cin >> Items.price;
                cout << "Enter quantity: ";
                cin >> Items.nstock;
                cout << " Best Before Date: ";
                cin >> Items.bbd;
                return Items;
                }

            } while (true);
    }

    // Search item by name or product category to perform remove or edit operations on the found item.
    auto handle_search_options()
    {
        char opt {};
        cout << "Search by (n) Name, (p) Product Category: ";
        std::cin >> opt;

        Inventory::ItemPtr pitem;

            if (opt == 'n')
            {
                // search for item by name
                string name {};
                cout << "Enter Model Name: ";
                getline(cin >> ws, name);
                pitem = inventory.search([&](const item& item) { return item.name == name; });
            }
            else if (opt == 'p')
                {
                    items prods {items::Invalid};
                    list_products();
                    cout >> "Select item id: ";
                    cin << &prods;
                    cout >> "Selected items category: " prods, get_product_name(prod).data();   
                    pitem = inventory.search([&](const items& item) { return items.id == prods;});
                }
            else
                {
                        cout << "The option selected is invalid. " << endl << "Please try again";
                        return;
                }

                // if item was found
            if (pitem != Inventory::ItemPtr {})
                {
                        // we ask the user what they would like to do with this found item
                        do {
                                pitem->print()
                                cout << "==========================" << endl;

                                std::printf("(%c) Remove Item\n", static_cast<char>(Options::Remove_Items));
                                std::printf("(%c) Edit Item\n", static_cast<char>(Options::Edit_Items));
                                std::printf("(%c) Quit\n", static_cast<char>(Options::Quit));
                                const auto opt = get_user_actions();

                                if (opt == static_cast<char>(Options::Remove_Items))
                                {
                                        inventory.remove(pitem);
                                        break;
                                }
                                else if (opt == static_cast<char>(Options::Edit_Items))
                                {
                                        /* NOTE(CA, 28.03.2022) - This is cumbersome to use and also inefficient. You should swap in-place or
                                        just edit a property of interest but that would be more complicated.*/
                                        const auto new_item = handle_add_options();
                                        inventory.remove(pitem);
                                        inventory.add(new_item);
                                        break;
                                }
                                else if (opt == static_cast<char>(Options::Quit)) { break; }
                                else { cout << "Invalid option selected. Please try again " << endl;}
                        } while (true);
                }
                else { cout << "Item not found. Try adding an item " <<  endl;}
    }

        auto run()
        {
                cout << "Shop Inventory managemnt System" << endl;

                do {
                        list_options();
                        const auto opt = get_user_actions();
                        if (opt == static_cast<char>(Options::Add_Items))
                        {
                                const auto item = handle_add_options();
                                inventory.add(item);
                                cout << "Added item " << endl;
                        }
                        else if (opt == static_cast<char>(Options::Search_Items)) { handle_search_options(); }
                        else if (opt == static_cast<char>(Options::List_Products)) { list_products(); }
                        else if (opt == static_cast<char>(Options::List_Items)) { inventory.list(); }
                        else if (opt == static_cast<char>(Options::Quit)) { break; }
                        else { printf("Invalid option selected. Please try again.\n"); }
                } while (true);
        }
};

int main() {
    InventoryUI ui {};
   
    ui.run();
};