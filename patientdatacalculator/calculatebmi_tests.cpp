#include <gtest/gtest.h>
#include <patientdatacalculator.h>
#include <cmath>

TEST(ValidValues, Integer){
    EXPECT_FLOAT_EQ(25,PatientDataCalculator::calculateBmi(2,100));
    EXPECT_FLOAT_EQ(15,PatientDataCalculator::calculateBmi(2,60));
    EXPECT_FLOAT_EQ(0.04, PatientDataCalculator::calculateBmi(5, 1));
}

TEST(ValidValues, Float){
    EXPECT_EQ(std::abs(24.93 - PatientDataCalculator::calculateBmi(1.9, 90)) <= 0.001, true);
    EXPECT_EQ(std::abs(25.79 - PatientDataCalculator::calculateBmi(1.65, 70.2)) <= 0.001, true);
}

TEST(NegativeValues, NegativeValues){
    EXPECT_FLOAT_EQ(25, PatientDataCalculator::calculateBmi(2,-100));
    EXPECT_FLOAT_EQ(25, PatientDataCalculator::calculateBmi(-2, 100));
    EXPECT_FLOAT_EQ(25, PatientDataCalculator::calculateBmi(-2, -100));
}

