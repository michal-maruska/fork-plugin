#pragma once

// I want the version string settable from the command line!!
#ifndef VERSION_STRING
# define VERSION_STRING "(unknown version)"
#endif

#define PLUGIN_VERSION 35


// use -DNDEBUG to avoid asserts!
// Trace + debug:
#define DEBUG 0

// I like colored tracing (in 256-color xterm)
#define USE_COLORS 1

/** What does the lock protect?
 * Access to machine queues, state, and configuration.
 * Prevents concurrent modifications from mouse/key signal handlers or timers
 * while state machine transitions or event processing are active.
 */
#define USE_LOCKING 1
#define MULTIPLE_CONFIGURATIONS 0


// Inside the X server: #define TIME_FORMAT PRIu32
#define TIME_FMT  "u"
#define SIZE_FMT  "lu"

// fixme: move in a common header
#ifdef UNREFERENCED_PARAMETER
#define UNUSED(x)   UNREFERENCED_PARAMETER(x)
#else
#define UNUSED(x)   (void)(x)
#endif
