/*
//
// Author: Patrik Arnold
// Contact: patrik.arnold@bfh.ch
//
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


using namespace std;

int main()
{
    vector<int> vec = {9,60,69,90,8,45,87,90,69,69,55,7};

    // Non-modifying

    // 1. Counting all values 69, cout how many
    int values = count(vec.begin(), vec.end(), 69);
    cout << "Count is: " << values << endl;

    // 2. Count values larger than thres, cout how many
    int thres = 50;
    values = count_if(vec.begin(), vec.end(), [thres](int x){return x>thres; });
    cout << "Count is: " << values << endl;

    // 3.  Find first min, last max and first max in vector, cout value and position (distance)
    auto firstMaxValue = max_element(vec.begin(), vec.end());
    auto minMaxValue = minmax_element(vec.begin(), vec.end());
    auto dist = distance(vec.begin(), minMaxValue.first);
    cout << "First min: " << *minMaxValue.first << " at position: " << dist << endl;
    cout << "First max: " << *firstMaxValue << endl;
    cout << "Last max: " << *minMaxValue.second << endl;


    // Modifying

    // 4) Mutliply each element with factor (transform), cout vector (copy)
    int factor = 10;
    transform(vec.begin(), vec.end(), vec.begin(), [factor](int x){return x*factor; });
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << "\n";

    // 5) Calculate elementwise product and save in result and cout result
    vector<int> result;
    transform(vec.begin(), vec.end(), back_inserter(result), [factor](int x){return x*x; });
    copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
    cout << "\n";


    // 6) Replace all 690's in vec with 0 and cout
    replace(vec.begin(), vec.end(), 690, 0);
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << "\n";

    // 7) Remove all 0's from vec and cout
    auto removedItr = remove(vec.begin(), vec.end(), 0);
    copy(vec.begin(), removedItr, ostream_iterator<int>(cout, " "));
    cout << "\n";

    // 8) Rotate such that vector starts with max value 450  and cout
    auto maxIter = max_element(vec.begin(), vec.end());
    rotate(vec.begin(), maxIter, vec.end());
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << "\n";


    // 9) Partition elements such that values less than 450 appear first preseving the original order and cout
    partition(vec.begin(), vec.end(), [](int x){return x < 450; });
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << "\n";

    return 0;
}
