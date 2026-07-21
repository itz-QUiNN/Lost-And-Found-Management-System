#include <iostream>
#include "Item.h"
#include "ItemRepository.h"
#include "Menu.h"

int main () {
    ItemRepository repo;
    repo.load("items.csv");
    
    Menu menu(repo);
    menu.run();

    return 0;
}