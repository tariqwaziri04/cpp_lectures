#include <algorithm>
#include <ios>
#include <iostream>
#include <optional>
#include <string>
#include <vector>
using namespace std;

constexpr auto MAX_ITEMS      = 30;
constexpr auto MAX_MODEL_NAME = 70;        // longest model name

// List of items categories stored in the shop.
enum class items
{
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

// Holds the names of the items categories.
constexpr string_view ITEM_NAMES[static_cast<int>(items::Count)] = {
    [static_cast<int>(items::vegetables)]          = "vegetables",
    [static_cast<int>(items::shampoos)]            = "shampoos",
    [static_cast<int>(items::cereals)]             = "cereals",
    [static_cast<int>(items::shoes)]               = "shoes",
    [static_cast<int>(items::savouries)]           = "savouries",
    [static_cast<int>(items::alcohol)]             = "alcohol",
    [static_cast<int>(items::fruits)]              = "fruits",
    [static_cast<int>(items::salads)]              = "salads",
    [static_cast<int>(items::dairy)]               = "dairy",
    [static_cast<int>(items::toiletries)]          = "toiletries",
    [static_cast<int>(items::accessories)]         = "accessories",
    [static_cast<int>(items::frozen_foods)]        = "frozen_foods",
    [static_cast<int>(items::soft_drinks)]         = "soft_drinks",
    [static_cast<int>(items::confectionery)]       = "confectionery",
    [static_cast<int>(items::biscuits)]            = "biscuits",
    [static_cast<int>(items::fresh_meats)]         = "fresh_meats",
    [static_cast<int>(items::pet_care)]            = "pet_care",
    [static_cast<int>(items::canned_goods)]        = "canned_goods",
    [static_cast<int>(items::hot_beverages)]       = "hot_beverages",
    [static_cast<int>(items::household_cleaning)]  = "household_cleaning",
    [static_cast<int>(items::ambient_bakery)]      = "ambient_bakery",
    [static_cast<int>(items::fresh_poultry)]       = "fresh_poultry",
    [static_cast<int>(items::games)]               = "games",
    [static_cast<int>(items::health_care)]         = "health_care",
    [static_cast<int>(items::chilled_convenience)] = "chilled_convenience",
    [static_cast<int>(items::clothings)]           = "clothings",
    [static_cast<int>(items::condiments)]          = "condiments",
    [static_cast<int>(items::books)]               = "books",
    [static_cast<int>(items::postcards)]           = "postcards",
    [static_cast<int>(items::electronics)]         = "electronics",
};

// Checks if the given product is valid.
constexpr auto is_valid_product(items prod) { return prod > items::Invalid && prod < items::Count; }

// Return the name of the given product.
constexpr auto get_product_name(items prod)
{
        if (!is_valid_product(prod)) { return string_view {""}; }

        return ITEM_NAMES[static_cast<int>(prod)];
}

// Prints a list of all the product categories available.
auto list_products()
{
        cout << "Items list: \n";
        for_each_n(begin(ITEM_NAMES), size(ITEM_NAMES), [i = 0](const auto& name) mutable {
                printf("(%d) %s\n", i, name.data());
                i++;
        });
        cout << "==============================" << endl;
}

/// Represents a stocked item corresponding to one of the listed products categories.
struct Item
{
        items  id;            // items category that item falls into
        string name;          // Name of the item
        float  price;         // Price in dollars
        int    nstock;        // No. of units in stock
        string bbd;           // best before date

        Item() = default;

        Item(const items prod, const std::string& name, const float price, const int nstock, string& bbd) :
                id {prod}, name {name}, price {price}, nstock {nstock}, bbd {bbd}
        {}

        auto print() const { printf("%32s%64s%16.2f%8d%12s\n", get_product_name(id).data(), name.c_str(), price, nstock, bbd); }
};
/// Holds the inventory of all the stocked items in the store.
struct Inventory
{
        using SearchPredicate = std::function<bool(const Item&)>;
        using Items           = std::vector<Item>;
        using ItemPtr         = Items::iterator;        // pointer to item type

        Items items;

        Inventory() { items.reserve(MAX_ITEMS); }

        /// @brief Adds the given item to the inventory.
        auto add(const Item& item) { items.emplace_back(item); }

        /// @brief Deletes the given item from the inventory.
        auto remove(ItemPtr pitem) { items.erase(pitem); }

        /// @brief Look for the item for which the given predicate returns true.
        ///
        /// @returns nullptr if item is not found else pointer to item.
        auto search(const SearchPredicate& pred) -> ItemPtr
        {
                auto pitem = std::find_if(items.begin(), items.end(), pred);
                if (pitem != items.end()) { return pitem; }

                return {};
        }

        /// @brief Prints a table listing currently stocked items in the inventory.
        auto list()
        {
                std::printf("%32s%64s%16s%8s%15s\n", "Product", "Model Name", "Price (GBP)", "Qty ", "Best Before Date");
                std::for_each(items.begin(), items.end(), [](const auto& item) { item.print(); });
                std::printf("---------------\n");
        }
};

struct InventoryUI
{
        enum class Option
        {
                Invalid      = -1,
                AddItem      = 'a',
                RemoveItem   = 'r',
                EditItem     = 'e',
                SearchItem   = 's',
                ListProducts = 'p',
                ListItems    = 'l',
                Quit         = 'q',
        };

        Inventory inventory;

        auto      user_input_handler() {}

        auto      list_options()
        {
                std::printf("(%c) Add Item\n", static_cast<char>(Option::AddItem));
                std::printf("(%c) Search Item\n", static_cast<char>(Option::SearchItem));
                std::printf("(%c) List Product Categories\n", static_cast<char>(Option::ListProducts));
                std::printf("(%c) List Items in Stock\n", static_cast<char>(Option::ListItems));
                std::printf("(%c) Quit\n", static_cast<char>(Option::Quit));
        }

        auto get_user_action()
        {
                char opt {};
                std::printf("Select operation: ");
                std::scanf(" %c", &opt);
                std::printf("---------------\n");
                return opt;
        }

        /// @brief Adds item to the inventory.
        auto handle_add_option()
        {
                Item item;
                do {
                        list_products();

                        std::printf("Select product category to add: ");
                        int pid {};
                        std::scanf("%d", &item.id);

                        if (!is_valid_product(item.id)) { std::printf("Invalid option selected. Please try again.\n"); }
                        else
                        {
                                // NOTE(CA, 28.03.2022) - Important to note that we need to consume the whitespaces from user input when using getline
                                std::printf("Enter item type: ");
                                std::getline(std::cin >> std::ws, item.name);

                                std::printf("Enter price: ");
                                std::cin >> item.price;

                                std::printf("Enter quantity: ");
                                std::cin >> item.nstock;

                                return item;
                        }

                } while (true);
        }

        /// @brief Search item by name or product category to perform remove or edit operations on the found item.
        auto handle_search_option()
        {
                char opt {};
                std::printf("Search by (n) Name, (p) Product Category: ");
                std::cin >> opt;

                Inventory::ItemPtr pitem;

                if (opt == 'n')
                {
                        // search for item by name
                        std::string name {};
                        std::printf("Enter item name: ");
                        std::getline(std::cin >> std::ws, name);
                        pitem = inventory.search([&](const Item& item) { return item.name == name; });
                }
                else if (opt == 'p')
                {
                        // search for item by product id
                        items prod {items::Invalid};
                        list_products();
                        std::printf("Select product id: ");
                        std::scanf("%d", &prod);
                        std::printf("Selected product category: %s\n", get_product_name(prod).data());

                        pitem = inventory.search([&](const Item& item) { return item.id == prod; });
                }
                else
                {
                        std::printf("Invalid option selected. Please try again.\n");
                        return;
                }

                // if item was found
                if (pitem != Inventory::ItemPtr {})
                {
                        // we ask the user what they'd like to do with this found item
                        do {
                                pitem->print();
                                std::printf("---------------\n");

                                std::printf("(%c) Remove Item\n", static_cast<char>(Option::RemoveItem));
                                std::printf("(%c) Edit Item\n", static_cast<char>(Option::EditItem));
                                std::printf("(%c) Quit\n", static_cast<char>(Option::Quit));
                                const auto opt = get_user_action();

                                if (opt == static_cast<char>(Option::RemoveItem))
                                {
                                        inventory.remove(pitem);
                                        break;
                                }
                                else if (opt == static_cast<char>(Option::EditItem))
                                {
                                        // NOTE(CA, 28.03.2022) - This is cumbersome to use and also inefficient. You should swap in-place or
                                        // just edit a property of interest but that'd be more complicated.
                                        const auto new_item = handle_add_option();
                                        inventory.remove(pitem);
                                        inventory.add(new_item);
                                        break;
                                }
                                else if (opt == static_cast<char>(Option::Quit)) { break; }
                                else { std::printf("Invalid option selected. Please try again.\n"); }
                        } while (true);
                }
                else { std::printf("Item not found. Try adding an item.\n"); }
        }

        auto run()
        {
                std::printf("Amigo Supermarket Inventory System\n");

                do {
                        list_options();
                        const auto opt = get_user_action();
                        if (opt == static_cast<char>(Option::AddItem))
                        {
                                const auto item = handle_add_option();
                                inventory.add(item);
                                std::printf("Added item\n\n");
                        }
                        else if (opt == static_cast<char>(Option::SearchItem)) { handle_search_option(); }
                        else if (opt == static_cast<char>(Option::ListProducts)) { list_products(); }
                        else if (opt == static_cast<char>(Option::ListItems)) { inventory.list(); }
                        else if (opt == static_cast<char>(Option::Quit)) { break; }
                        else { std::printf("Invalid option selected. Please try again.\n"); }
                } while (true);
        }
};

auto main() -> int
{
        InventoryUI ui {};

        ui.run();
}