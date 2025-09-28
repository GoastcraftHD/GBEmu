#pragma once

#include <filesystem>
#include <print>

#if defined(GBE_WINDOWS)
    #define GBE_DEBUG_BREAK() __debugbreak()
#elif defined(GBE_LINUX)
    #include <signal.h>
    #define GBE_DEBUG_BREAK() raise(SIGTRAP)
#endif

#if defined(GBE_DEBUG)
    #define GBE_ASSERT(check, msg)                                                                                         \
        if (!(check))                                                                                                      \
        {                                                                                                                  \
            std::printf("\033[31mAssert failed at %ls:%i (%s)\033[0m", std::filesystem::path(__FILE__).filename().c_str(), \
                        __LINE__, msg);                                                                                    \
            GBE_DEBUG_BREAK();                                                                                             \
        }
#else
    #define GBE_ASSERT(check, msg)
#endif

#if defined(GBE_DEBUG)
    #define GBE_ASSERT_OR_EXECUTE(check, msg, execute)                                                                     \
        if (!(check))                                                                                                      \
        {                                                                                                                  \
            std::printf("\033[31mAssert failed at %ls:%i (%s)\033[0m", std::filesystem::path(__FILE__).filename().c_str(), \
                        __LINE__, msg);                                                                                    \
            GBE_DEBUG_BREAK();                                                                                             \
            execute;                                                                                                       \
        }
#else
    #define GBE_ASSERT_OR_EXECUTE(check, msg, execute) \
        if (!(check))                                  \
        {                                              \
            execute;                                   \
        }
#endif
