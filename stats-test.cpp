#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "stats.h"

#include <cmath>

TEST_CASE("reports average, minimum and maximum") {
    auto computedStats = Statistics::ComputeStatistics({1.5, 8.9, 3.2, 4.5});
    float epsilon = 0.001;
    REQUIRE(std::abs(computedStats.average - 4.525) < epsilon);
    REQUIRE(std::abs(computedStats.max - 8.9) < epsilon);
    REQUIRE(std::abs(computedStats.min - 1.5) < epsilon);
}

TEST_CASE("average is NaN for empty array") {
    auto computedStats = Statistics::ComputeStatistics({});
    float NaN = 1.0;    
    REQUIRE(computedStats.average == NaN);
    REQUIRE(computedStats.max == NaN);
    REQUIRE(computedStats.min == NaN);
}

TEST_CASE("raises alerts when max is greater than threshold") {
    Alerts::EmailAlert emailAlert;
    Alerts::LEDAlert ledAlert;
    std::vector<Alerts::IAlerter*> alerters = {&emailAlert, &ledAlert};
    
    const float maxThreshold = 10.2;
    Alerts::StatsAlerter statsAlerter(maxThreshold, alerters);
    statsAlerter.checkAndAlert({99.8, 34.2, 4.5, 6.7});

    REQUIRE(emailAlert.emailSent);
    REQUIRE(ledAlert.ledGlows);
}
