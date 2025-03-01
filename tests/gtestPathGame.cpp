/*
    Egor Shastin st129457@student.spbu.ru
    This is code for testing all classes by using Google Test
*/

#include <gtest/gtest.h>
#include "baseGameRule.h"
#include "pathGame.h"
#include "bots.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
