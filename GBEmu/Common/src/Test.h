#pragma once

#if defined(GBE_TESTS)
// Adds this class as a friend for google tests
    #define FRIEND_TEST(test_case_name, test_name) friend class test_case_name##_##test_name##_Test;
#else
    #define FRIEND_TEST(test_case_name, test_name)
#endif

#define CPU_TESTS                            \
    FRIEND_TEST(CPUTests, Test_NOP);         \
    FRIEND_TEST(CPUTests, Test_0_JR_NZ_8);   \
    FRIEND_TEST(CPUTests, Test_1_JR_NZ_8);   \
    FRIEND_TEST(CPUTests, Test_2_JR_NZ_8);   \
    FRIEND_TEST(CPUTests, Test_0_DEC_B);     \
    FRIEND_TEST(CPUTests, Test_1_DEC_B);     \
    FRIEND_TEST(CPUTests, Test_LD_B_8);      \
    FRIEND_TEST(CPUTests, Test_LD_C_8);      \
    FRIEND_TEST(CPUTests, Test_LD_HL_16);    \
    FRIEND_TEST(CPUTests, Test_LD_HL_NEG_A); \
    FRIEND_TEST(CPUTests, Test_XOR_A_A);     \
    FRIEND_TEST(CPUTests, Test_0_CP_A_HL);   \
    FRIEND_TEST(CPUTests, Test_1_CP_A_HL);   \
    FRIEND_TEST(CPUTests, Test_JP_8);
