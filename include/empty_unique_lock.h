#pragma once

#include "config.h"

struct null_mutex {
    void lock() const noexcept {}
    void unlock() const noexcept {}
    bool try_lock() const noexcept { return true; }
};

template <typename Mutex>
class empty_unique_lock {
public:
    explicit empty_unique_lock(Mutex& m) {
        UNUSED(m);
    }
    ~empty_unique_lock() = default;

    empty_unique_lock(const empty_unique_lock&) = delete;
    empty_unique_lock& operator=(const empty_unique_lock&) = delete;
};
