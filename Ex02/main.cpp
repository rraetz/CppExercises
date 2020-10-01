#include <iostream>
#include <vector>
#include <unordered_map>
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
    string m_name;
    string m_salary;
    string m_country;

public:
    friend istream &operator >> (istream &is, Billionaire  &billionaire) 
    {
        string tmp;
        getline(is, tmp);
        if (!tmp.empty())
        {
            // Find start & end of name, salary and country
            auto startSalary = tmp.find_first_of("0123456789");
            auto endName = startSalary - 1;
            auto endSalary = tmp.find_last_of("0123456789");
            auto startCountry = tmp.find_last_of("\t") + 1;

            // Store in member variables
            billionaire.m_name = tmp.substr(0, endName);
            billionaire.m_salary = tmp.substr(startSalary, endSalary-startSalary+1);
            billionaire.m_country = tmp.substr(startCountry, tmp.length()-startCountry+1);
        }
        return is;
    }

    friend ostream &operator << (ostream &os, const Billionaire  &billionaire) 
    {
        os << "Name: " << billionaire.m_name << "\nSalary: " << billionaire.m_salary 
            << "\nCountry:" << billionaire.m_country;
        return os;
    }
};



int main() 
{
    
// PHONE BOOK
    // // Data as given by the exercise
    // vector<pair<string, string>> vec{ 
    //     make_pair ("Homer", "1111"),
    //     make_pair ("Marge", "2222"),
    //     make_pair ("Lisa", "3333"),
    //     make_pair ("Magy", "4444"),
    //     make_pair ("Bart", "5555")};

    // // Create phoneBook and copy content of vec
    // unordered_multimap<string, string> phoneBook;
    // copy(vec.begin(), vec.end(), inserter(phoneBook, phoneBook.end()));

    // // Add additional number for Homer
    // phoneBook.emplace(make_pair("Homer", "1234"));
    

    // // Get phone numbers
    // string inputName;
    // while(1)
    // {   
    //     cout << "Enter name (or Exit): ";
    //     cin >> inputName;

    //     // Break if "exit" or "Exit"
    //     if (inputName.compare("Exit") == 0 || inputName.compare("exit") == 0) 
    //     {
    //         break;
    //     }

    //     // Find name in phone book and print if available
    //     if (phoneBook.find(inputName) == phoneBook.end())
    //     {
    //         cout << "Name not in directory" << endl;
    //     }
    //     else
    //     {
    //         auto its = phoneBook.equal_range(inputName);
    //         for (auto it = its.first; it != its.second; it++)
    //         {
    //             cout << "Phone number: " << it->second << endl;
    //         }
    //     }   
    // }





// BILLIONAIRES OF THE WORLD


    ifstream stream("Forbes2018.txt");
    if (!stream)
    {
        cout << "WARNING: File not found!" << endl;
    }
   
    vector<Billionaire> billionaires;
    copy(istream_iterator<Billionaire>(stream), istream_iterator<Billionaire>(), back_inserter(billionaires));
    copy(billionaires.begin(), billionaires.end(), ostream_iterator<Billionaire>(cout , "\n"));


    return 0;
}