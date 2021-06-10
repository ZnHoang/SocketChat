#ifndef MY_QUEUE_HPP
#define MY_QUEUE_HPP

#include <queue>
#include <mutex>

using ulm = std::unique_lock<std::mutex>;

template <typename T>
class MyQueue
{
public:
    void Push(const T& data);
    void Push(const T&& data);
    T Pop();
    bool tryPop();
private:
    bool isEmpty();

    std::queue<T> q;
    std::mutex mt;
};

template <typename T>
void MyQueue<T>::Push(const T& data)
{
    ulm lk(mt);
    q.push(data);    
}

template <typename T>
void MyQueue<T>::Push(const T&& data)
{
    ulm lk(mt);
    q.push(data);    
}

template <typename T>
T MyQueue<T>::Pop()
{
    ulm lk(mt);
    if(isEmpty())
    {
        return "";
    }
    T data = q.front();
    q.pop();
    return data;
}

template <typename T>
bool MyQueue<T>::tryPop()
{
    ulm lk(mt);
    return !isEmpty();
}

template <typename T>
bool MyQueue<T>::isEmpty()
{
    return q.empty();
}

#endif