#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore(int count, int max_count);

    void notify();
    void wait();
private:
    std::mutex m_mtx;
    std::condition_variable m_cv;
    int m_count;
    int m_max_count;
};

#endif // SEMAPHORE_H