/*
    Egor Shastin st129457@student.spbu.ru
    This code containe main function for using Google Test
*/

#include <gtest/gtest.h>


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
