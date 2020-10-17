#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <iterator>
#include <list>
#include <fstream>
#include <istream>
#include <ostream>
#include <ctype.h>
#include <algorithm>

using namespace std;



class Billionaire
{
private:


public:
    string m_name;
    string m_salary;
    string m_country;
    inline friend istream &operator >> (istream &is, Billionaire  &billionaire) 
    {
        if (is.peek() != is.eof())
        {
            getline(is, billionaire.m_name, '\t');
            getline(is, billionaire.m_salary, '\t');
            getline(is, billionaire.m_country, '\n');
        }
        return is;
    }

    inline friend ostream &operator << (ostream &os, const Billionaire  &billionaire) 
    {
        os << "Name: " << billionaire.m_name << " Salary: " << billionaire.m_salary 
            << " Country:" << billionaire.m_country;
        return os;
    }
};



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
    unordered_multimap<string, string> phoneBook;
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


    ifstream stream("Forbes2018.txt");
    if (!stream)
    {
        cout << "WARNING: File not found!" << endl;
    }
   
    vector<Billionaire> billionaires;
    copy(istream_iterator<Billionaire>(stream), istream_iterator<Billionaire>(), back_inserter(billionaires));
    cout << "\n List of billionaires:" << endl;
    copy(billionaires.begin(), billionaires.end(), ostream_iterator<Billionaire>(cout , "\n"));


    // Copy of first billionaire, counter with # of billionaires per country>
    map<string, pair<const Billionaire, size_t>> billiMap;
    for (const auto &e:billionaires)
    {
        // Check if key for e.m_country already exists, if yes, increment counter
        auto check = billiMap.try_emplace(e.m_country, e, 1);
        if (!check.second)
        {
            // dereference iterator, access pair, access counter
            check.first->second.second++; 
        }
    }

    // Print the map
    cout << "\n Billionaires per country:" << endl;
    for (const auto &e:billiMap)
    {
        cout << e.first <<": " << e.second.second << 
        " billionaires.  Richest is " << e.second.first.m_name << 
        " with " << e.second.first.m_salary << "$" << endl;
    }


    // Sort the map
    map<string, pair<const Billionaire, size_t>> billiMapTmp;
    copy(billiMap.begin(), billiMap.end(), inserter(billiMapTmp), )

    return 0;
}