#pragma once

#include "config.h"

template <typename mutex>
class empty_unique_lock
{
public:
    explicit empty_unique_lock(const mutex& m) {
        UNUSED(m);
    }

    ~empty_unique_lock() = default;
};
