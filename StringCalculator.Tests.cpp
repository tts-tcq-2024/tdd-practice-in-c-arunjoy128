#include <gtest/gtest.h>
#include "string.h"
#include "StringCalculator.h"

TEST(StringCalculatorAddTests, ReturnsZeroForEmptyInput) {
    ASSERT_EQ(calculateStringSum(""),0);
}

TEST(StringCalculatorAddTests, ReturnsZeroForSingleZeroInput) {
    ASSERT_EQ(calculateStringSum("0"),0);
}

TEST(StringCalculatorAddTests, ReturnsSumOfInputNumbersSeparatedByCommasOrNewLines) {
    ASSERT_EQ(calculateStringSum("1,2\n3"),6);
}

TEST(StringCalculatorAddTests, ReturnsSumOfInputNumbersSeparatedByCustomDelimiterOrNewLines) {
    ASSERT_EQ(calculateStringSum("//;;\n1;;2\n3"),6);
}

TEST(StringCalculatorAddTests, IgnoresCustomDelimiterWithoutCorrectFormat) {
    ASSERT_EQ(calculateStringSum("//;1;1;1"),111);
}

TEST(StringCalculatorAddTests, ReturnsSumOfOnlyInputNumbersLessThanThousand) {
    ASSERT_EQ(calculateStringSum("999,2"),1001);
    ASSERT_EQ(calculateStringSum("1000,2"),1002);
    ASSERT_EQ(calculateStringSum("1001,2"),2);
    ASSERT_EQ(calculateStringSum("1234,4567"),0);
}

TEST(StringCalculatorAddTests, ReturnsZeroIfInputStringDoesNotHaveNumbers) {
    ASSERT_EQ(calculateStringSum(",\n,"),0);
    ASSERT_EQ(calculateStringSum("Hello, world!"),0);
}

TEST(StringCalculatorAddTests, IgnoresInputCharactersThatAreNeitherNumbersNorDelimiters) {
    ASSERT_EQ(calculateStringSum("1,a,1"),2);
    ASSERT_EQ(calculateStringSum("1, 2*1"),22);
}

TEST(StringCalculatorAddTests, ThrowsExceptionForNegativeInputNumbers) {
    ASSERT_ANY_THROW(calculateStringSum("-1,1,-1"));
    try{
        calculateStringSum("-1,1,-1");
    } catch (const std::runtime_error& e) {
        ASSERT_STREQ(e.what(),"negative numbers not allowed: -1,-1");
    }
}
