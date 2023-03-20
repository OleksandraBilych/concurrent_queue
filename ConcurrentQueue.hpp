#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <iostream>
#include <queue>
#include <mutex>

class concurent_queue_exception : public std::runtime_error
{
public:
    concurent_queue_exception() : std::runtime_error("Queue is empty") {}
    concurent_queue_exception(const char *s) : std::runtime_error(s) {}
};

template <typename T>
class ConcurrentQueue {
public:
    ConcurrentQueue() = default;

    T& back() { return container.back(); };

    bool empty() const { return container.empty(); };

    void push ( const T& value );

    void pop(T& value);

    T& front() { return container.front(); };

    size_t size() { return container.size(); };

private:
    std::queue<T> container;
    std::mutex mt;
};

template <typename T>
void ConcurrentQueue<T>::push ( const T& value )
{
    std::cout << "ConcurrentQueue<T>::push" << std::endl;
    const std::lock_guard<std::mutex> lock(mt);
    container.push(value);
}

template <typename T>
void ConcurrentQueue<T>::pop(T& value)
{
    std::cout << "ConcurrentQueue<T>::pop" << std::endl;
    const std::unique_lock<std::mutex> lock(mt);

    if (empty())
    {
        throw concurent_queue_exception ("Queue is empty");
    }

    value = container.front();
    container.pop();
}

#endif
