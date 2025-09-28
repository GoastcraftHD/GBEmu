#pragma once

#if defined(GBE_TESTS)
// Adds this class as a friend for google tests
    #define FRIEND_TEST(test_case_name, test_name) friend class test_case_name##_##test_name##_Test;
#else
    #define FRIEND_TEST(test_case_name, test_name)
#endif
