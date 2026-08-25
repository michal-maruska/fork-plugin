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

    empty_unique_lock(const empty_unique_lock&) = delete;
    empty_unique_lock& operator=(const empty_unique_lock&) = delete;
};
