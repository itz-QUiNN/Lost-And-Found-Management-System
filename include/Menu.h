#pragma once
#include <iostream>
#include "ItemRepository.h"
#include "Item.h"

class Menu {
public:
    explicit Menu(ItemRepository& repo);
    void run();

private:
    ItemRepository& repo_;
};