/*
//
// Author: Patrik Arnold
// Contact: patrik.arnold@bfh.ch
//
*/
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <fstream>

using namespace std;

int main()
{

    std::ifstream file("cars.txt");

    if (!file)
    {
        cout << "Could not open file ... abort\n";
        return 1;
    }

    vector<string> cars;
    copy(istream_iterator<string>(file),{}, back_inserter(cars));
    cout << "There are " << cars.size() << " brands of cars !" << endl;

    copy(cars.begin(),cars.end(),ostream_iterator<string>(cout," "));
    cout << "\n";

    return 0;

}
