#pragma once

#include "config.h"

template <typename mutex_t>
class empty_unique_lock
{
public:
    explicit empty_unique_lock(mutex_t& m) {
        UNUSED(m);
    }

    ~empty_unique_lock() = default;
};
