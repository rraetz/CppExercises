#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;
mutex mu;
void printMe(int ID)
{
    lock_guard<mutex> guard(mu);
    cout << "Message from Thread " << ID
         << " from thread: " << this_thread::get_id() << endl;
}

int main()
{
    // 1)  Call print from main thread
    printMe(1);
    // 2)  Call print from an additional thread
    thread t1{printMe, 2};
    if(t1.joinable())
        t1.join();

    // 3)  Create vector of threads, call printMe number-of-cores times and join them.
    size_t N = thread::hardware_concurrency();
    std::vector<thread> threads;
    for (size_t threadNbr = 0; threadNbr < N; ++threadNbr)
    {
        threads.push_back(thread(printMe, threadNbr));
    }

    for(auto& t : threads)
    {
        if(t.joinable())
            t.join(); // Blocking call which waits for the thread
    }
    // 4) Protect cout with a lock guard
    return 0;
}
















