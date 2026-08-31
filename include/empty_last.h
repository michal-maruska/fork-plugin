#pragma once

#ifndef KERNEL
#include <vector>
#endif

extern "C" {
#include "stddef.h"
}


#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(x)   (void)(x)
#endif

// let's make one without any:
template <typename event>
class empty_last_events_t
{
public:
    void push_back(const event& __x) { UNREFERENCED_PARAMETER(__x); }
    void set_capacity(const int& n) { UNREFERENCED_PARAMETER(n); }
    size_t size() const { return 0; }
    bool full() const { return false; }
    const event* begin() const { return nullptr; }
    const event* end() const { return nullptr; }
    event* begin() { return nullptr; }
    event* end() { return nullptr; }
};
