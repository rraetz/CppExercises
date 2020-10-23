#ifndef DATAQUEUE_H
#define DATAQUEUE_H


#include <queue>
#include <mutex>
#include <iostream>


template<typename T>
class DataQueue
{
private:
    size_t m_bufferSize;
    std::queue<T> m_buffer;
    std::mutex m_mutex;

public:
    DataQueue(size_t bufferSize) : m_bufferSize(bufferSize){}

    void add(T newElement)
    {
        if (isFull())
        {
            std::cout << "Cannot add new element, buffer is full" << std::endl;
        }
        else
        {
            m_buffer.push(newElement);
            std::cout << "New element added" << std::endl;
        }
    }


    T get()
    {
        if (isEmpty())
        {
            std::cout << "Cannot get element, buffer is empty" << std::endl;
            return 0;
        }
        else
        {
            T tmp = m_buffer.front();
            m_buffer.pop();
            return tmp;
            std::cout << "Element retrieved" << std::endl;
        }
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

/*
 * TODO:
 * - initialize buffer with bufferSize
 */



#endif // DATAQUEUE_H
