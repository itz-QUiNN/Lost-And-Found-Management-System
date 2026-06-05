#include<iostream>
#include <ctime>
using namespace std;


struct Item {
    int    id;
    string user_id;
    string item_name;
    string description;
    string location;
    string status;
    string report_date;
};


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



int main()
{
    int  item_id = 0;
    Item items[100];  // storage for up to 100 items

    Report_Item(item_id, items);

    return 0;
}