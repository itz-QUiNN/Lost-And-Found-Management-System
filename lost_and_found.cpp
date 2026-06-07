#include<iostream>
#include <ctime>
#include <sstream>
#include <fstream>
using namespace std;
using std::string;
using std::ifstream;


struct Item {
    int    id;
    string user_id;
    string item_name;
    string description;
    string location;
    string status;
    string report_date;
};


struct Claim {
    string claimant_id;
    int    item_id;
    string proof;
    string claim_date;
};


/**
 * @brief  Rewrites the entire CSV file from the current items array.
 *
 * @param  items       Array of Item structs to save.
 * @param  item_count  Number of valid items in the array.
 */
void Save_All_Items_To_CSV(Item items[], int item_count)
{
    ofstream file("lost_items.csv");  // no ios::app — we want to overwrite

    if (!file.is_open())
    {
        cout << "Error: Could not open lost_items.csv for writing." << endl;
        return;
    }

    file << "id,user_id,item_name,description,location,status,report_date\n";

    for (int i = 0; i < item_count; i++)
    {
        file << items[i].id          << ","
             << items[i].user_id     << ","
             << items[i].item_name   << ","
             << items[i].description << ","
             << items[i].location    << ","
             << items[i].status      << ","
             << items[i].report_date << "\n";
    }

    file.close();
}


/**
 * @brief  Reads lost items from a CSV file into an array of Item structs.
 *
 * @param  items      Array of Item structs to populate.
 * @param  item_count Reference to the counter tracking how many items were loaded.
 */
void Load_Items_From_CSV(Item items[], int &item_count)
{
    ifstream file("lost_items.csv");

    if (!file.is_open())
    {
        cout << "Error: Could not open lost_items.csv" << endl;
        return;
    }

    string line;
    getline(file, line);  // skip header row

    while (getline(file, line))
    {
        stringstream ss(line);
        string cell;
        Item new_item;

        getline(ss, cell, ','); new_item.id          = stoi(cell);
        getline(ss, cell, ','); new_item.user_id      = cell;
        getline(ss, cell, ','); new_item.item_name    = cell;
        getline(ss, cell, ','); new_item.description  = cell;
        getline(ss, cell, ','); new_item.location     = cell;
        getline(ss, cell, ','); new_item.status       = cell;
        getline(ss, cell, ','); new_item.report_date  = cell;

        items[item_count] = new_item;
        item_count++;
    }

    file.close();
    cout << item_count << " items loaded successfully." << endl;
}


/**
 * @brief  Appends a single Item to the CSV file.
 *
 * @param  item  The Item struct to save.
 */
void Save_Item_To_CSV(Item item)
{
    ofstream file("lost_items.csv", ios::app);

    if (!file.is_open())
    {
        cout << "Error: Could not open lost_items.csv for writing." << endl;
        return;
    }

    // ensure we start on a fresh line before appending
    file.seekp(0, ios::end);
    if (file.tellp() > 0)
    {
        file.seekp(-1, ios::end);
        char last_char;
        ifstream check("lost_items.csv");
        check.seekg(-1, ios::end);
        check.get(last_char);
        check.close();

        if (last_char != '\n')
            file << "\n";
    }

    file << item.id          << ","
         << item.user_id     << ","
         << item.item_name   << ","
         << item.description << ","
         << item.location    << ","
         << item.status      << ","
         << item.report_date << "\n";

    file.close();
}


/**
 * @brief  Gets and validates a string input from the user.
 *
 * @param  prompt      The message displayed to the user.
 * @param  max_length  The maximum allowed character length.
 * @return A valid string guaranteed to be within max_length.
 */
string Get_Validated_Input(string prompt, int max_length)
{
    string input;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (input.length() <= max_length)
        {
            return input;
        }
        else
        {
            cout << "Invalid input. Must be " << max_length << " characters or fewer." << endl;
        }
    }
}


string Get_Current_Date()
{
    time_t now = time(0);        // get current time
    tm *ltm = localtime(&now);   // break it into day/month/year

    // build the date string manually
    string date = to_string(1900 + ltm->tm_year) + "-" +
                  to_string(1 + ltm->tm_mon)     + "-" +
                  to_string(ltm->tm_mday);

    return date;
}


/**
 * @brief  Presents a numbered menu of locations and validates
 *         the user's selection.
 *
 * @return A string representing the selected location.
 */
string Get_Found_Location()
{
    int location_id;

    while (true)
    {
        cout << "\nSelect the appropriate location:" << endl;
        cout << "\t01. Basement"     << endl;
        cout << "\t02. Ground floor" << endl;
        cout << "\t03. 1st floor"    << endl;
        cout << "\t04. 2nd floor"    << endl;
        cout << "\t05. Elsewhere"    << endl;
        cout << "\nLocation: ";
        cin >> location_id;
        cin.ignore();            // cleans up '\n' right where it's caused

        switch (location_id)
        {
            case 1: return "Basement";
            case 2: return "Ground floor";
            case 3: return "1st floor";
            case 4: return "2nd floor";
            case 5: return "Elsewhere";

            default:
                cout << "Invalid choice, please select a valid location." << endl;
                break;
        }
    }
}


/**
 * @brief  Collects item details from user, assigns an ID and date,
 *         and stores the item in the items array.
 *
 * @param  item_id      Reference to the global item counter, incremented on each report.
 * @param  items        Array of Item structs where the new item will be stored.
 */
void Report_Item(int &item_id, Item items[])
{
    cout << "\t\t                      Reporting a found item.                           " << endl;
    cout << "\t\t______________________________________________________________________" << endl;
    cout << "\nPlease enter following details:" << endl;

    // collect input
    Item new_item;
    new_item.user_id     = Get_Validated_Input("\t01. Your ID (Student/ Lecturer/ Staff): ", 10);
    new_item.item_name   = Get_Validated_Input("\t02. Item Name: ", 30);
    new_item.description = Get_Validated_Input("\t03. Item Description: ", 200);
    new_item.location    = new_item.location = Get_Found_Location();
    new_item.status      = "unclaimed";
    new_item.report_date = Get_Current_Date();

    // assign ID and store
    item_id             += 1;
    new_item.id          = item_id;
    items[item_id - 1]   = new_item;
    Save_Item_To_CSV(new_item);

    // summary
    cout << "\n\t\t--- Item Reported Successfully ---" << endl;
    cout << "\tID        : " << new_item.id          << endl;
    cout << "\tReported by: " << new_item.user_id    << endl;
    cout << "\tItem Name : " << new_item.item_name   << endl;
    cout << "\tDescription: " << new_item.description << endl;
    cout << "\tLocation  : " << new_item.location    << endl;
    cout << "\tStatus    : " << new_item.status      << endl;
    cout << "\tDate      : " << new_item.report_date << endl;
}


string To_Lower(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]);  // lowercase one character at a time
    }
    return str;
}


/**
 * @brief  Searches for items by name using case-insensitive comparison.
 *
 * @param  items       Array of Item structs to search through.
 * @param  item_count  Number of valid items in the array.
 */
void Search_By_Name(Item items[], int item_count)
{
    cout << "\t\t                 Searching for an item - By Name                      " << endl;
    cout << "\t\t______________________________________________________________________" << endl;

    string search_name;
    cout << "\nEnter the name of the item you are looking for: ";
    getline(cin, search_name);
    search_name = To_Lower(search_name);  // convert input to lowercase

    bool found = false;

    for (int i = 0; i < item_count; i++)
    {
        if (To_Lower(items[i].item_name) == search_name)  // compare lowercase versions
        {
            cout << "\n\t\t--- Item Found ---"                    << endl;
            cout << "\tID         : " << items[i].id             << endl;
            cout << "\tReported by: " << items[i].user_id        << endl;
            cout << "\tItem Name  : " << items[i].item_name      << endl;  // original case preserved
            cout << "\tDescription: " << items[i].description    << endl;
            cout << "\tLocation   : " << items[i].location       << endl;
            cout << "\tStatus     : " << items[i].status         << endl;
            cout << "\tDate       : " << items[i].report_date    << endl;
            found = true;
        }
    }

    if (!found)
        cout << "\nSearch complete. No items found matching: " << search_name << endl;
}


/**
 * @brief  Searches for items by location using a predefined location menu.
 *
 * @param  items       Array of Item structs to search through.
 * @param  item_count  Number of valid items in the array.
 */
void Search_By_Location(Item items[], int item_count)
{
    cout << "\t\t                 Searching for an item - By Location                      " << endl;
    cout << "\t\t______________________________________________________________________" << endl;

    string search_location = Get_Found_Location();

    bool found = false;

    for (int i = 0; i < item_count; i++)
    {
        if (items[i].location == search_location)
        {
            cout << "\n\t\t--- Item Found ---"                 << endl;
            cout << "\tID         : " << items[i].id          << endl;
            cout << "\tReported by: " << items[i].user_id     << endl;
            cout << "\tItem Name  : " << items[i].item_name   << endl;
            cout << "\tDescription: " << items[i].description << endl;
            cout << "\tLocation   : " << items[i].location    << endl;
            cout << "\tStatus     : " << items[i].status      << endl;
            cout << "\tDate       : " << items[i].report_date << endl;
            found = true;
        }
    }

    if (!found)
        cout << "\nSearch complete. No items found at location: " << search_location << endl;
}


/**
 * @brief  Converts a date string in "YYYY-M-D" format to a time_t value.
 *
 * @param  date  The date string to convert.
 * @return A time_t value representing the date.
 */
time_t Date_To_Time(string date)
{
    tm t  = {};
    int year, month, day;

    sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);

    t.tm_year = year - 1900;
    t.tm_mon  = month - 1;
    t.tm_mday = day;

    return mktime(&t);
}

/**
 * @brief  Searches for items found within two weeks of a user-specified lost date.
 *
 * @param  items       Array of Item structs to search through.
 * @param  item_count  Number of valid items in the array.
 */
void Search_By_Date(Item items[], int item_count)
{
    cout << "\t\t                 Searching for an item - By Date                      " << endl;
    cout << "\t\t______________________________________________________________________" << endl;

    string lost_date;
    cout << "\nEnter the date you lost the item (YYYY-MM-DD): ";
    getline(cin, lost_date);

    time_t lost_time           = Date_To_Time(lost_date);
    double seconds_in_two_weeks = 14 * 24 * 60 * 60;

    bool found = false;

    for (int i = 0; i < item_count; i++)
    {
        time_t found_time = Date_To_Time(items[i].report_date);
        double diff       = difftime(found_time, lost_time);

        // item was found between 0 and 14 days after the lost date
        if (diff >= 0 && diff <= seconds_in_two_weeks)
        {
            cout << "\n\t\t--- Item Found ---"                 << endl;
            cout << "\tID         : " << items[i].id          << endl;
            cout << "\tReported by: " << items[i].user_id     << endl;
            cout << "\tItem Name  : " << items[i].item_name   << endl;
            cout << "\tDescription: " << items[i].description << endl;
            cout << "\tLocation   : " << items[i].location    << endl;
            cout << "\tStatus     : " << items[i].status      << endl;
            cout << "\tDate       : " << items[i].report_date << endl;
            found = true;
        }
    }

    if (!found)
        cout << "\nSearch complete. No items found within two weeks of: " << lost_date << endl;
}


void Claim_Item()
{
    bool item_found = false;

    cout<< "\t\t                 Claiming an item                      " << endl;
    cout<< "\t\t______________________________________________________________________" << endl;

    cout<<"\nIs the item you are looking for listed above? (y/n): ";
    char response;
    cin >> response;
    cin.ignore();  // clean up newline

    if (response == 'y' || response == 'Y')
    {
        cout<<"\nPlease enter your ID to verify ownership: ";
        string user_id;
        getline(cin, user_id);
        cout << "\nPlease enter the ID of the item you wish to claim: ";
        int claim_id;
        cin >> claim_id;
        cin.ignore();  // clean up newline

        cout<<"nPlease explain the proof of ownership you can provide: ";
        string proof;
        getline(cin, proof);
    }
}


/**
 * @brief  Appends a new claim to the claims CSV file.
 *
 * @param  claim  The Claim struct to save.
 */
void Save_Claim_To_CSV(Claim claim)
{
    // check if file exists, if not write header first
    ifstream check("claims.csv");
    bool file_exists = check.is_open();
    check.close();

    ofstream file("claims.csv", ios::app);

    if (!file.is_open())
    {
        cout << "Error: Could not open claims.csv for writing." << endl;
        return;
    }

    if (!file_exists)
        file << "claimant_id,item_id,proof,claim_date\n";

    file << claim.claimant_id << ","
         << claim.item_id     << ","
         << claim.proof       << ","
         << claim.claim_date  << "\n";

    file.close();
}


/**
 * @brief  Allows a user to claim an unclaimed item by providing proof of ownership.
 *         Updates the item status to "pending verification" in memory and both CSVs.
 *
 * @param  items       Array of Item structs to search and update.
 * @param  item_count  Number of valid items in the array.
 */
void Claim_Item(Item items[], int item_count)
{
    cout << "\n\t\t                 Claiming an item                      " << endl;
    cout << "\t\t______________________________________________________________________" << endl;

    // cout << "\nIs the item you are looking for listed above? (y/n): ";
    // char response;
    // cin >> response;
    // cin.ignore();

    // if (!(response == 'y' || response == 'Y'))
    // {
    //     cout << "Returning to main menu." << endl;
    //     return;
    // }

    // get claimant ID
    string claimant_id = Get_Validated_Input("\nPlease enter your ID to verify ownership: ", 10);
    // cin.ignore();

    // get and validate item ID
    int claim_id;
    bool item_found = false;

    while (!item_found)
    {
        cout << "\nPlease enter the ID of the item you wish to claim (0 to cancel): ";
        cin >> claim_id;
        cin.ignore();

        if (claim_id == 0)
        {
            cout << "Claim cancelled. Returning to main menu." << endl;
            return;
        }

        // search for item
        for (int i = 0; i < item_count; i++)
        {
            if (items[i].id == claim_id)
            {
                item_found = true;

                // check status
                if (items[i].status != "unclaimed")
                {
                    cout << "Sorry, this item is already " << items[i].status << " and cannot be claimed." << endl;
                    item_found = false;  // let them try another ID
                    break;
                }

                // get proof
                string proof = Get_Validated_Input("\nPlease explain the proof of ownership you can provide: ", 200);

                // update status in memory
                items[i].status = "pending verification";

                // save claim to claims.csv
                Claim new_claim;
                new_claim.claimant_id = claimant_id;
                new_claim.item_id     = claim_id;
                new_claim.proof       = proof;
                new_claim.claim_date  = Get_Current_Date();
                Save_Claim_To_CSV(new_claim);

                // rewrite lost_items.csv with updated status
                Save_All_Items_To_CSV(items, item_count);

                cout << "\n\t\t--- Claim Submitted Successfully ---"   << endl;
                cout << "\tItem ID    : " << items[i].id              << endl;
                cout << "\tItem Name  : " << items[i].item_name       << endl;
                cout << "\tYour ID    : " << claimant_id              << endl;
                cout << "\tStatus     : " << items[i].status          << endl;
                cout << "\tClaim Date : " << new_claim.claim_date     << endl;

                return;
            }
        }

        if (!item_found)
            cout << "Item ID " << claim_id << " not found. Please try again." << endl;
    }
}


void Display_Main_Menu()
{
    cout << "\t\t                      Lost and Found System                      " << endl;
    cout << "\t\t______________________________________________________________________" << endl;
    cout << "\nPlease select an option:" << endl;
    cout << "\t01. Report a found item" << endl;
    cout << "\t02. Search for an item" << endl;
    cout << "\t03. Exit" << endl;
    cout << "\nYour choice: ";
}


void Display_Search_Menu()
{
    cout << "\t\t                 Search for an item                      " << endl;
    cout << "\t\t______________________________________________________________________" << endl;
    cout << "\nSearch by:" << endl;
    cout << "\t01. Name" << endl;
    cout << "\t02. Location" << endl;
    cout << "\t03. Date" << endl;
    cout << "\nYour choice: ";
}


int main()
{
    int  item_id = 0;
    Item items[100];

    Load_Items_From_CSV(items, item_id);

    while (true)
    {
        Display_Main_Menu();

        int main_choice;
        cin >> main_choice;
        cin.ignore();

        switch (main_choice)
        {
            case 1:
                Report_Item(item_id, items);
                break;

            case 2:
            {
                Display_Search_Menu();
                int search_choice;
                cin >> search_choice;
                cin.ignore();

                switch (search_choice)
                {
                    case 1: Search_By_Name(items, item_id);     break;
                    case 2: Search_By_Location(items, item_id); break;
                    case 3: Search_By_Date(items, item_id);     break;
                    default:
                        cout << "Invalid search option. Returning to main menu." << endl;
                        break;
                }

                // offer claiming after search
                cout << "\nWould you like to claim an item from these results? (y/n): ";
                char claim_response;
                cin >> claim_response;
                cin.ignore();

                if (claim_response == 'y' || claim_response == 'Y')
                    Claim_Item(items, item_id);

                break;
            }

            case 3:
                cout << "Exiting the system. Goodbye!" << endl;
                return 0;

            default:
                cout << "Invalid option. Please select a valid choice." << endl;
                break;
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    }

    return 0;
}