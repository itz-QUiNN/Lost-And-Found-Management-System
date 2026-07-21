#pragma once
#include <vector>
#include <iostream>
#include <cctype>
#include <ctime>
#include <fstream>
#include <sstream>
#include "Item.h"

std::string toLowerCase(const std::string& text);
time_t parseDate(const std::string& dateStr);
std::string getTodayDate();

class ItemRepository {
public:
    void reportItem(Item newItem);
    int itemCount() const;
    void printALL() const;
    void searchByName(const std::string& name) const;
    void searchByLocation(int locationId) const;
    void searchByDate(const std::string& date) const;
    void claimItem(int itemId);
    void save(const std::string& filename) const;
    void load(const std::string& filename);

private:
    std::vector<Item> items_;
    int nextItemId_ = 1;
};