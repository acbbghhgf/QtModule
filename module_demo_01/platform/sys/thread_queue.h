#ifndef THREAD_QUEUE_H
#define THREAD_QUEUE_H
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
template <typename T, typename Container = std::queue<T>>
class thread_queue
{
public:
#if 0
    using container_type = Container;
    using value_type = typename Container::value_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using size_type = typename Container::size_type;
    using mutex_type = std::mutex;
    using condition_variable_type = std::condition_variable;
#endif

private:
    Container queue_;
    mutable std::mutex mutex_;
    std::condition_variable cond_;

public:
    thread_queue() = default;
    thread_queue(const thread_queue &) = delete;
    thread_queue &operator=(const thread_queue &) = delete;
    void pop(typename Container::reference elem)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [this]() { return !queue_.empty(); });
        elem = std::move(queue_.front());
        queue_.pop();
    }
    bool try_pop(typename Container::reference elem)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (queue_.empty())
        {
            return false;
        }
        elem = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    typename Container::size_type size() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    void push(const typename Container::value_type &elem)
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(elem);
        }
        cond_.notify_one();
    }
    void push(typename Container::value_type &&elem)
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(std::move(elem));
        }
        cond_.notify_one();
    }
};

#endif // THREAD_QUEUE_H
