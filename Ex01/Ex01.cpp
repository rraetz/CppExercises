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
    // Create and fill char vector
    std::vector<char> vec1(26);                 
    std::iota(vec1.begin(), vec1.end(), 'a');

    // Print it using ostream iterator and copy
    std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<char>(std::cout, " "));
    std::cout  << "\n\n";



// Ex 2.2
    // Create string vector for cars and ifstream object
    std::vector<std::string> cars;
    std::ifstream inFile("cars.txt");

    // Fill cars vector using copy, istream_iterators and back_inserter
    std::copy(std::istream_iterator<std::string>(inFile), std::istream_iterator<std::string>(), std::back_inserter(cars));  

    // Sort cars
    std::sort(cars.begin(), cars.end());

    // Print cars
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
    // Define Predicate   
    std::string predicate("ABC");

    // Print if predicate fullfilled, using lambda function
    std::copy_if(cars.begin(), cars.end(), std::ostream_iterator<std::string>(std::cout, "\n"), 
        [&predicate](std::string car){return (predicate.find(car.at(0)) != std::string::npos);});
    std::cout  << "\n\n";

    // --> is this really more readable than a for-loop..?



// Ex 3
    // Create string vector for input text
    std::vector<std::string> textVec;

    // Copy from istream to the back of textVec
    std::cout << "Please enter some text (terminate with Ctrl-z on Windows): " << std::endl;
    std::istream_iterator<std::string> inIter(std::cin);
    std::istream_iterator<std::string> endOfInStream;
    std::copy(inIter, endOfInStream, std::back_inserter(textVec)); 

    // Sort vector and print only unique words
    std::sort(textVec.begin(), textVec.end());
    std::cout << "\nThe unique word list contains: " << std::endl;
    std::unique_copy(textVec.begin(), textVec.end(), std::ostream_iterator<std::string>(std::cout, " "));



// Ex 4 - CODE PROJECT
/*
    My project will be to represent a robot arm in 3D. The goal is to display a simple robot arm (consisting 
    of cylinders or other simple bodies) and to make the joints of the robot follow a given trajectory.
    Depending on the progress during the project, it might even be possible to implement some inverse kinematics (given 
    a target configuration, the robot finds the corresponding joint angles and moves accordingly).
*/

    return 0;
}

