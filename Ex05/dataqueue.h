#ifndef DATAQUEUE_H
#define DATAQUEUE_H


#include <queue>
#include <mutex>
#include <condition_variable>


template<typename T>
class DataQueue
{
private:
    size_t m_bufferSize = 1000;
    std::queue<T> m_buffer;
    std::mutex m_mutex;
    std::condition_variable m_condVar;


public:
    DataQueue(size_t bufferSize) : m_bufferSize(bufferSize){}


    // Adds a new element to the FIFO
    void add(T newElement)
    {
        // Scope for unique_lock object
        {
            // Wait until FIFO is not full anymore, then push new element
            std::unique_lock<std::mutex> locker(m_mutex);
            m_condVar.wait(locker, [this]{return !isFull(); });
            m_buffer.push(newElement);
        }
        // Notify consumer
        m_condVar.notify_one();
    }


    // Reads and removes the oldest element of the FIFO
    T get()
    {
        T tmpBufferData;
        // Scope for unique_lock object
        {
            // Wait until FIFO is not empty anymore, then pull element
            std::unique_lock<std::mutex> locker(m_mutex);
            m_condVar.wait(locker, [this]{return !isEmpty(); });
            tmpBufferData = m_buffer.front();
            m_buffer.pop();
        }
        // Notify consumer
        m_condVar.notify_one();
        return tmpBufferData;
    }


    // Check whether FIFO is full
    bool isFull() {return (m_buffer.size() >= m_bufferSize);}


    // Check whether FIFO is empty
    bool isEmpty() {return m_buffer.empty();}

};


#endif // DATAQUEUE_H
