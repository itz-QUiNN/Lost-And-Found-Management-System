#include <iostream>
#include "Item.h"
#include "ItemRepository.h"
#include "Menu.h"

int main () {
    ItemRepository repo;
    Menu menu(repo);
    menu.run();

    // std::cout << toLowerCase("WaLlEt") << "\n";

    return 0;
}