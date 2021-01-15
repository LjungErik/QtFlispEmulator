#include "semaphore.h"

Semaphore::Semaphore(int count, int max_count): 
    m_count(count),
    m_max_count(max_count)
{}

void Semaphore::notify()
{
    std::unique_lock<std::mutex> lock(m_mtx);
    if (m_count < m_max_count)
    {
        m_count++;
        m_cv.notify_one();
    }
}

void Semaphore::wait()
{
    std::unique_lock<std::mutex> lock(m_mtx);
    while(m_count == 0) {
        m_cv.wait(lock);
    }
    m_count--;
}