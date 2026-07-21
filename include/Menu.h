#pragma once
#include <iostream>
#include "ItemRepository.h"
#include "Item.h"

class Menu {
public:
    explicit Menu(ItemRepository& repo) : repo_(repo) {}

    void run() {
        int mode = -1;

        while (mode != 0) {
            std::cout << "Enter;\n";
            std::cout << "01. Report lost item.\n";
            std::cout << "02. Claim a found item.\n";
            std::cout << "00. Exit.\n";

            std::cin >> mode;

            if (mode == 1) {
                std::cout << "Reporting a lost item.\n";

                Item newItem;

                std::cout << "Reporter ID: ";
                std::cin >> newItem.reporterId;
                std::cin.ignore(1000, '\n');

                std::cout << "Item name: ";
                std::getline(std::cin, newItem.itemName);

                std::cout << "Description: ";
                std::getline(std::cin, newItem.description);

                std::cout << "Founded location (1-5): ";
                std::cin >> newItem.foundLocation;

                repo_.reportItem(newItem);

                std::cout << "Item reported successfully.\n";

            } else if ( mode == 2) {
                std::cout << "Claiming a found item.\n";
                std::cout << "Search by: 1.Name 2.Date 3.Location\n";

                int searchMode;
                std::cin >> searchMode;

                if (searchMode == 1) {
                    std::cout << "Search by name.\n";
                    std::cout << "Item name: ";
                    std::string name;
                    std::cin >> name;
                    repo_.searchByName(name);

                } else if ( searchMode == 2) {
                    std::cout << "Search by date.\n";
                    std::cout << "Date (YYYY-MM-DD): ";
                    std::string date;
                    std::cin >> date;
                    repo_.searchByDate(date);

                } else if ( searchMode == 3) {
                    std::cout << "Search by location.\n";
                    std::cout << "Location ID (1-5): ";
                    int locationId;
                    std::cin >> locationId;
                    repo_.searchByLocation(locationId);

                } else {
                    std::cout << "Invalid search mode.\n";
                }

                std::cout << "Enter item ID to claim (or 0 to cancel): ";
                int itemIdToClaim;
                std::cin >> itemIdToClaim;

                if (itemIdToClaim != 0) {
                    repo_.claimItem(itemIdToClaim);
                }

            } else if (mode == 0) {
                repo_.save("items.csv");
                std::cout << "Good Bye...!\n";
            } else {
                std::cout << "Invalid choice.\n";
            }
        }
    }

private:
    ItemRepository& repo_;
};