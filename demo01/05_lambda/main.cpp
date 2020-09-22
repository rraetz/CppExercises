/*
//
// Author: Patrik Arnold
// Contact: patrik.arnold@bfh.ch
//
*/
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
using namespace std;


// in header
bool isEven(int x);


int main()
{
    vector<int> vec(40, 0);
    iota(vec.begin(), vec.end(),0);
    copy(vec.begin(), vec.end(), ostream_iterator<int>{cout, " "});
    cout << "\n";

    // print even numbers only!
    copy_if(vec.begin(), vec.end(), ostream_iterator<int>{cout, " "}, isEven); // binary predicat function
    cout << "\nWith Lambda \n";

    // using lambda function inplace
    copy_if(vec.begin(), vec.end(), ostream_iterator<int>{cout, " "}, [](int x)
    {
        return (x%2 == 0);
    }); // binary predicat function -> lambda style

    return 0;
}

// in cpp
bool isEven(int x)
{
    return (x%2 == 0);

}
