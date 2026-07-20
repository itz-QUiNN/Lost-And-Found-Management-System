#pragma once
#include <string>

struct Item {
    int itemId;
    int reporterId;
    std::string itemName;
    std::string description;
    int foundLocation;
    std::string status = "unclaimed";
    std::string reportDate;
};