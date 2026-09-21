#pragma once

#include "config.h"

template <typename Mutex>
class empty_unique_lock
{
public:
    explicit empty_unique_lock(const Mutex& m) {
        UNUSED(m);
    }

    void lock() {}
    void unlock() {}

    ~empty_unique_lock() = default;
};
