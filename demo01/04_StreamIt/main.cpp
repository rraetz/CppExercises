/*
//
// Author: Patrik Arnold
// Contact: patrik.arnold@bfh.ch
//
*/
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    // Stream Iterator Input
    vector<string> vec4;
    copy(istream_iterator<string>(cin), istream_iterator<string>(),
    back_inserter(vec4));
    // NOTE: use e.g. front_inserter with deque

    // Important: Use CTRL + D to terminate console input!!!

    // Stream Iterator Output
    copy(vec4.begin(), vec4.end(),
    ostream_iterator<string>(cout, " "));
    cout << "\n";

    // Combine both, i.e. cin to cout
//    copy(istream_iterator<string>(cin), istream_iterator<string>(),
//    ostream_iterator<string>(cout, " "));

    return 0;
}
