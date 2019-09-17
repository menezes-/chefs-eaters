

#ifndef CANNIBALS_MUTEX_HPP
#define CANNIBALS_MUTEX_HPP
#include <vector>
#include <atomic>
class Mutex {
public:

    explicit Mutex(int nconsumers);

    int register_consumer();

    void acquire(int id);

    void release(int id);

private:
    std::atomic_int curr_consumer{1};
    std::atomic_int turn{0};
    std::vector<bool> consumers;

};


#endif //CANNIBALS_MUTEX_HPP
