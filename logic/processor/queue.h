#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <cstdint>
#include <queue>
#include <mutex>
#include "semaphore.h"

template <typename T>
class Queue
{
public:
    Queue();
    ~Queue();

    void push(T* element);

    T* pop();
    void waitForNext();
private:
    std::queue<T*> m_queue;
    Semaphore m_sem;
    std::mutex m_lock;
};

template <typename T>
Queue<T>::Queue():
    m_sem(0, 1),
    m_lock()
{
}

template <typename T>
Queue<T>::~Queue()
{
    m_lock.lock();
    while(!m_queue.empty()) {
        T* element = m_queue.front();
        m_queue.pop();
        delete element;
    }
    m_lock.unlock();
}

template <typename T>
void Queue<T>::push(T* element)
{
    m_lock.lock();
    m_queue.push(element);
    m_sem.notify();
    m_lock.unlock();
}

template <typename T>
T* Queue<T>::pop()
{
    T* element = nullptr;
    m_lock.lock();

    if (!m_queue.empty())
    {
        element = m_queue.front();
        m_queue.pop();
    }
    
    m_lock.unlock();
    return element;
}

template <typename T>
void Queue<T>::waitForNext()
{
    m_lock.lock();
    bool isEmpty = m_queue.empty();
    m_lock.unlock();
    if (isEmpty) {
        // Signal that we are waiting for semaphore locks
        m_sem.wait();
    }
}

#endif // THREAD_SAFE_QUEUE_H
