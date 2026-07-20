#pragma once
#include <vector>
#include <iostream>
#include <cctype>
#include "Item.h"

std::string toLowerCase(const std::string& text) {
    std::string result = text;
    for (char& c : result) {
        c = std::tolower(c);
    }
    return result;
}

class ItemRepository {
public:
    void reportItem(Item newItem) {
        newItem.itemId = nextItemId_;
        nextItemId_++;
        items_.push_back(newItem);
    }

    int itemCount() const {
        return items_.size();
    }

    void printALL() const {
        for (const Item& item : items_) {
            std::cout<< "ID: " << item.itemId
                    << ", Name: " << item.itemName
                    << ", Status: "<< item.status << "\n";
        }
    }

    void searchByName(const std::string& name) const {
        std::string searchTerm = toLowerCase(name);

        for (const Item& item: items_) {
            if (toLowerCase(item.itemName) == searchTerm && item.status == "unclaimed") {
                std::cout << "ID: " << item.itemId
                        << ", Name: " << item.itemName
                        << ", Description: " << item.description << "\n";
            }
        }
    }

    void searchByLocation(int locationId) const {
        for (const Item& item : items_) {
            if ( item.foundLocation == locationId && item.status == "unclaimed") {
                std::cout << "ID: " << item.itemId
                        << ", Name: " << item.itemName
                        << ", Description: " << item.description << "\n";
            }
        }
    }

    void searchByDate(const std::string& date) const {
        for (const Item& item : items_) {
            if (item.reportDate == date && item.status == "unclaimed") {
                std::cout << "ID: " << item.itemId
                        << ", Name: " << item.itemName
                        << ", Description: " << item.description << "\n";
            }
        }
    }

    void claimItem(int itemId) {
        for (Item& item : items_) {
            if (item.itemId == itemId && item.status == "unclaimed") {
                item.status = "claimed";
                std::cout << "Item claimed: " << item.itemName << "\n";
                return;
            }
        }
        std::cout << "Item not found or already cliamed.\n";
    }

private:
    std::vector<Item> items_;
    int nextItemId_ = 1;
};