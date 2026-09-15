#pragma once

#include "config.h"

template <typename Mutex>
class empty_unique_lock
{
public:
    explicit empty_unique_lock(Mutex& m) {
        UNUSED(m);
    }

    ~empty_unique_lock() = default;

    void lock() {}
    void unlock() {}
};
