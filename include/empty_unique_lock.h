#pragma once

#include "config.h"

template <typename Mutex>
class empty_unique_lock
{
public:
    explicit empty_unique_lock(Mutex& m) {
        UNUSED(m);
    }
    explicit empty_unique_lock(const Mutex& m) {
        UNUSED(m);
    }

    ~empty_unique_lock() = default;

    void lock() {}
    void unlock() {}
    [[nodiscard]] bool owns_lock() const noexcept { return true; }
};
