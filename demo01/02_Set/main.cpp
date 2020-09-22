/*
//
// Author: Patrik Arnold
// Contact: patrik.arnold@bfh.ch
//
*/
#include <iostream>
#include <set>
#include <iterator>

// Demo for set

using namespace std;

int main()
{
//    multiset<int> myset; // multiple values allowed

    set<int> myset; // std::greater<int> e.g. to change opposite sorting
    myset.insert(12);
    myset.insert(3);
    myset.insert(1);
    myset.insert(7);
//    myset.insert(7); // only unique values are added

    copy(myset.begin(), myset.end(), ostream_iterator<int>{cout, "\n"});
    cout << "\n";


    // Check insertion
//    pair<set<int>::iterator, bool> ret;
    auto ret = myset.insert(3); // No new element inserted

    if (ret.second==false)
        cout << *ret.first << endl;

    copy(myset.begin(), myset.end(), ostream_iterator<int>{cout, "\n"});
    cout << "\n";

    // Note: find function
    set<int>::iterator it;
    it = myset.find(7); // O(log(n)) , it points to 7

    // Insert with hint
    myset.insert(it,8); // O(log(n) -> O(1)

    // Erease
    myset.erase(it);
    myset.erase(12);
    copy(myset.begin(), myset.end(), ostream_iterator<int>{cout, "\n"});
    cout << "\n";

    return 0;
}
