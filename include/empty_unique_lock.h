#pragma once

#include "config.h"

template <typename Mutex>
class empty_lock_guard
{
public:
    explicit empty_lock_guard(Mutex& m) {
        UNUSED(m);
    }
    ~empty_lock_guard() = default;

    empty_lock_guard(const empty_lock_guard&) = delete;
    empty_lock_guard& operator=(const empty_lock_guard&) = delete;
};

template <typename Mutex>
class empty_unique_lock
{
public:
    explicit empty_unique_lock(Mutex& m) {
        UNUSED(m);
    }
    ~empty_unique_lock() = default;

    empty_unique_lock(const empty_unique_lock&) = delete;
    empty_unique_lock& operator=(const empty_unique_lock&) = delete;

    void lock() {}
    void unlock() {}
    [[nodiscard]] bool owns_lock() const { return true; }
};
