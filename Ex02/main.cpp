#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <list>

using namespace std;

int main() 
{
    
// PHONE BOOK
    // Data as given by the exercise
    vector<pair<string, string>> vec{ 
        make_pair ("Homer", "1111"),
        make_pair ("Marge", "2222"),
        make_pair ("Lisa", "3333"),
        make_pair ("Magy", "4444"),
        make_pair ("Bart", "5555")};

    // Create phoneBook and copy content of vec
    multimap<string, string> phoneBook;
    copy(vec.begin(), vec.end(), inserter(phoneBook, phoneBook.end()));

    // Add additional number for Homer
    phoneBook.emplace(make_pair("Homer", "1234"));
    

    // Get phone numbers
    string inputName;
    while(1)
    {   
        cout << "Enter name (or Exit): ";
        cin >> inputName;

        // Break if "exit" or "Exit"
        if (inputName.compare("Exit") == 0 || inputName.compare("exit") == 0) 
        {
            break;
        }

        // Find name in phone book and print if available
        if (phoneBook.find(inputName) == phoneBook.end())
        {
            cout << "Name not in directory" << endl;
        }
        else
        {
            auto its = phoneBook.equal_range(inputName);
            for (auto it = its.first; it != its.second; it++)
            {
                cout << "Phone number: " << it->second << endl;
            }
        }   
    }



// BILLIONAIRES OF THE WORLD





    return 0;
}