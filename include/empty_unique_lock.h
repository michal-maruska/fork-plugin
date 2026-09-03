#pragma once

#include "config.h"

template <typename mutex>
class empty_unique_lock
{
public:
    explicit empty_unique_lock(mutex& m) {
        UNUSED(m);
    }

    ~empty_unique_lock() {}

    void lock() {}
    void unlock() {}
    bool owns_lock() const { return true; }
};
