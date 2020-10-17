#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;
mutex mu;

void printMe(int ID)
{
    lock_guard<mutex> guard(mu); // Make cout thread safe
    cout << "Message from Thread " << ID
         << " from thread: " << this_thread::get_id() << endl;
}

int main()
{
    // 1)  Call print from main thread
    // printMe(1);

    // 2)  Call print from an additional thread
    // thread t2(printMe, 2);
    // if(t2.joinable())
    // {
    //     t2.join();
    // }

    // 3)  Create vector of threads, call printMe number-of-cores times and join them.
    auto threadNbr = thread::hardware_concurrency();
    vector<thread> threads(threadNbr);
    for (size_t i = 0; i<threadNbr; ++i)
    {
        threads.push_back(thread(printMe, i));
    }

    for (auto& e:threads)
    {
      if (e.joinable())
      {
          e.join();
      }
    }


    // 4) Protect cout with a lock guard
    return 0;
}
















