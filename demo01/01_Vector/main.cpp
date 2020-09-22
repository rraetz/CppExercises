/*
//
// Author: Patrik Arnold
// Contact: patrik.arnold@bfh.ch
//
*/
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int main()
{

    vector<int> v;
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 1000; ++i)
        v.push_back(i);

    auto stop =  std::chrono::high_resolution_clock::now();

    cout << "No reserve: " << std::chrono::duration_cast<chrono::nanoseconds>(stop-start).count() << " ns" << endl;


    vector<int> v2;
    v2.resize(1000,0);

    auto start2 = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < 1000; ++i)
        v2[i] = i;

    auto stop2 = std::chrono::high_resolution_clock::now();
    cout << "Reserve: " << std::chrono::duration_cast<chrono::nanoseconds>(stop2-start2).count() << " ns" << endl;


    return 0;
}
