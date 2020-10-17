#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <vector>
#include <random>
#include <mutex>


class ThreadLogFile
{
private:
    std::ofstream m_stream;
    std::mutex m_mu;
    std::once_flag m_headerIsPrinted;

public:
    ThreadLogFile(const std::string &outputFile): m_stream(outputFile){}
    ~ThreadLogFile()
    {
        m_stream.close();
    }

    void print(const std::thread::id ID, const int value)
    {
        // Print header only once
        std::call_once(m_headerIsPrinted, [this]{m_stream << "This is a header...\n\n"; });

        // Lock guard
        std::lock_guard<std::mutex> lockGuard(m_mu);

        // Stream to file
        m_stream << "Log from thread: " << ID << " with value: " << value << "\n";
    }
};



void logToFile(ThreadLogFile &logger, int value)
{
    // Make sure that they gonna mess up...
    using namespace std::chrono_literals;
    int delay = std::rand() % 50;
    std::this_thread::sleep_for(delay * 1ms);

    // Call print function
    logger.print(std::this_thread::get_id(), value);
}



int main()
{
    // Create logger and try it
    ThreadLogFile logger("threadLog.txt");
    logToFile(logger, 1);

    // Create new thread and join
    std::thread t1{logToFile, std::ref(logger), 2};
    t1.join();

    // Vector of threads
    int N = 10*std::thread::hardware_concurrency();
    std::vector<std::thread> threadVec(N);
    for (int i = 0; i < N; ++i)
    {
        threadVec.at(i) = std::thread(logToFile, std::ref(logger), i);
    }

    // Join threads in vector
    for (auto it = threadVec.begin(); it != threadVec.end(); ++it)
    {
        it->join();
    }

    return 0;
}
