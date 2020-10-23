#ifndef DATAQUEUE_H
#define DATAQUEUE_H


#include <queue>
#include <mutex>
#include <iostream>
#include <condition_variable>



template<typename T>
class DataQueue
{
private:
    size_t m_bufferSize = 1000;
    std::queue<T> m_buffer;
    std::mutex m_mutex;
    std::condition_variable m_condVar;
//    std::lock_guard<std::mutex> m_locker;

public:
    DataQueue(size_t bufferSize) : m_bufferSize(bufferSize)
    {
        std::cout << "buffersize: " << m_bufferSize << std::endl;
    }

    void add(T newElement)
    {
        if (isFull())
        {
            std::cout << "Cannot add new element, buffer is full" << std::endl;
        }
        else
        {
//            std::cout << "New element added" << std::endl;
            // notify consumer
            {
                std::lock_guard<std::mutex> locker(m_mutex);
                m_buffer.push(newElement);
            }
            m_condVar.notify_one();
        }
    }


    T get()
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_condVar.wait(locker, [this]{return !isEmpty(); });

        T tmp = m_buffer.front();
        m_buffer.pop();
        return tmp;
        std::cout << "Element retrieved" << std::endl;
        // notify producer


//        if (isEmpty())
//        {
//            std::cout << "Cannot get element, buffer is empty" << std::endl;
//            return 0;
//        }
//        else
//        {
//            T tmp = m_buffer.front();
//            m_buffer.pop();
//            return tmp;
//            std::cout << "Element retrieved" << std::endl;
//            // notify producer
//        }
    }

    bool isFull()
    {
        return (m_buffer.size() >= m_bufferSize);
    }

    bool isEmpty()
    {
        return m_buffer.empty();
    }

};


#endif // DATAQUEUE_H
