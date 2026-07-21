#include "ItemRepository.h"

std::string toLowerCase(const std::string& text) {
    std::string result = text;
    for (char& c : result) {
        c = std::tolower(c);
    }
    return result;
}

time_t parseDate(const std::string& dateStr) {
    struct tm timeStruct = {};
    sscanf(dateStr.c_str(), "%d-%d-%d", &timeStruct.tm_year, &timeStruct.tm_mon, &timeStruct.tm_mday);
    timeStruct.tm_year -= 1900;
    timeStruct.tm_mon -=1;
    return mktime(&timeStruct);
}

std::string getTodayDate() {
    time_t now = time(nullptr);
    struct tm* localTime =  localtime(&now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);
    return std::string(buffer);
}

int ItemRepository::itemCount () const {
    return items_.size();
}

void ItemRepository::reportItem(Item newItem) {
    newItem.itemId = nextItemId_;
    nextItemId_++;
    newItem.reportDate = getTodayDate();
    items_.push_back(newItem);
}

void ItemRepository::printALL() const {
    for (const Item& item : items_) {
        std::cout<< "ID: " << item.itemId
                << ", Name: " << item.itemName
                << ", Status: "<< item.status << "\n";
    }
}

void ItemRepository::searchByName(const std::string& name) const {
    std::string searchTerm = toLowerCase(name);

    for (const Item& item: items_) {
        if (toLowerCase(item.itemName) == searchTerm && item.status == "unclaimed") {
            std::cout << "ID: " << item.itemId
                    << ", Name: " << item.itemName
                    << ", Description: " << item.description << "\n";
        }
    }
}

void ItemRepository::searchByLocation(int locationId) const {
    for (const Item& item : items_) {
        if ( item.foundLocation == locationId && item.status == "unclaimed") {
            std::cout << "ID: " << item.itemId
                    << ", Name: " << item.itemName
                    << ", Description: " << item.description << "\n";
        }
    }
}

void ItemRepository::searchByDate(const std::string& date) const {
    time_t searchTime = parseDate(date);

    for (const Item& item : items_) {
        time_t itemTime = parseDate(item.reportDate);
        double seconndsDiff = difftime(itemTime, searchTime);
        double daysDiff = seconndsDiff / (60 * 60 * 24);

        if (0 <= daysDiff && daysDiff < 14 && item.status == "unclaimed") {
            std::cout << "ID: " << item.itemId
                    << ", Name: " << item.itemName
                    << ", Description: " << item.description << "\n";
        }
    }
}

void ItemRepository::claimItem(int itemId) {
    for (Item& item : items_) {
        if (item.itemId == itemId && item.status == "unclaimed") {
            item.status = "claimed";
            std::cout << "Item claimed: " << item.itemName << "\n";
            return;
        }
    }
    std::cout << "Item not found or already cliamed.\n";
}

void ItemRepository::save(const std::string& filename) const {
    std::ofstream file(filename);
    for (const Item& item : items_) {
        file << item.itemId << ","
            << item.reporterId << ","
            << item.itemName << ","
            << item.description << ","
            << item.foundLocation << ","
            << item.status << ","
            << item.reportDate << "\n";
    }
}

void ItemRepository::load(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        Item item;

        std::getline(ss, field, ','); item.itemId = std::stoi(field);
        std::getline(ss, field, ','); item.reporterId = std::stoi(field);
        std::getline(ss, field, ','); item.itemName = field;
        std::getline(ss, field, ','); item.description = field;
        std::getline(ss, field, ','); item.foundLocation = std::stoi(field);
        std::getline(ss, field, ','); item.status = field;
        std::getline(ss, item.reportDate, ',');

        items_.push_back(item);

        if (item.itemId >= nextItemId_) {
            nextItemId_ = item.itemId + 1;
        }
    }
}