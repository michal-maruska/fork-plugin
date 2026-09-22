#pragma once

#include "config.h"

template <typename Mutex>
class empty_unique_lock
{
public:
    template <typename... Args>
    explicit empty_unique_lock(Args&&...) {}

    ~empty_unique_lock() {}

    void lock() {}
    void unlock() {}
};
