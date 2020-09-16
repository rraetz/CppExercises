#include <vector>
#include <numeric>
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>     //stream class to operate on files
#include <algorithm>


int main() 
{

// Ex 2.1
    // Create and fill vector
    std::vector<char> vec1(26);                 
    std::iota(vec1.begin(), vec1.end(), 'a');

    // Print it using ostream iterator and copy
    std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<char>(std::cout, " "));
    // std::ostream_iterator<char> outIter1(std::cout, " ");
    // std::copy(vec1.begin(), vec1.end(), outIter1);
    std::cout  << "\n\n";



// Ex 2.2
    // Create vector and ifstream object
    std::vector<std::string> cars;
    std::ifstream inFile("cars.txt");

    // Fill vector using copy, istream_iterators and back_inserter
    std::copy(std::istream_iterator<std::string>(inFile), std::istream_iterator<std::string>(), std::back_inserter(cars));  

    // Sort vector
    std::sort(cars.begin(), cars.end());

    // Print vector
    std::copy(cars.begin(), cars.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    std::cout  << "\n\n";



// Ex 2.3
    for (auto iter = cars.begin(); iter != cars.end(); ++iter)
    {
        // Check for "A" in first position of string
        if(iter->at(0) == 'A') 
        {
            std::cout << *iter << std::endl;
        }
    }
    std::cout  << "\n";

    for (auto& e:cars)
    {
        // Check for "A" in first position of string
        if(e.at(0) == 'A') 
        {
            std::cout << e << std::endl;
        }
    }
    std::cout  << "\n\n";



// Ex 2.4



    return 0;
}



/*

CODE PROJECT
- Roboter arm representation
- Simple flight/drone
- Path planning for robot
- Simulator for dynamic system




*/