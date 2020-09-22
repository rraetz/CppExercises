/*
//
// Author: Patrik Arnold
// Contact: patrik.arnold@bfh.ch
//
*/
#include <iostream>
#include <string>
#include <map>

// Note: These sample require the c++17 feature structured bindings

using namespace std;

int main()
{

    map<char, string> m;
    m.insert(make_pair('S', "Sunday"));
    m.insert(make_pair('M', "Monday"));
    m.insert({'W', "Wednesday"});
    auto [itr, success] = m.try_emplace('M', "Tuesday"); // Try emplay (C++ 17 feature ) does not construct element, when not iserted! Performance boost
//    auto [itr, success] = m.emplace('M', "Tuesday"); // C++ 11, does create object, althoug not inserted

    if(!success)
    {
        cout << " No element for " << (*itr).first << " inserted\n";
    }

    for(const auto& elem : m)
    {
        cout << elem.first << " => " << elem.second << endl;
    }


    cout << "\nHint for exercise 2-2 - The power of maps\n";
    map<string , pair< string , size_t >> m2;
    m2.insert(make_pair("USA", make_pair("150", 1)));
    m2.insert({"UE", {"350", 1}}); // using C++11 Brace-Initialization

    auto[itr2, success2] = m2.try_emplace("USA", "70", 1); // C++17
    if(!success)
    {
        (*itr2).second.second++;
    }

    for(const auto& elem : m2)
    {
        cout << elem.first << " => " << elem.second.first << "$ with count: " << elem.second.second << endl;
    }

    // Note: Structured bindings (C++17)
    for(const auto&[key, value] : m2)
    {
        auto &[dollars, count] = value;
        cout << key << " Money: " << dollars << " with count: " << count << endl;
    }
    //  Note that both the insert and emplace functions of std::map
    //  work exactly the same way. A crucial difference is that
    //  try_emplace will not construct the object associated with the
    //  key if the key already exists























                //    // Structured bindings on custom types, i.e. structs
                //    struct employee
                //    {
                //        unsigned id;
                //        std::string name;
                //        std::string role;
                //        unsigned salary;
                //     };

                //     std::vector<employee> employess;
                //     employess.push_back({1, "Peter", "CTO", 150000});
                //     employess.push_back({2, "Tom", "Programmer", 300000});

                //     for(const auto&[id, name, job, dollars] : employess)
                //     {
                //         cout << name << "(" << id << ")"
                //              <<" is " << job << " and earns " << dollars << "$!"
                //             << endl;
                //     }

                return 0;
    }
