#include "stats.h"

// ==== Statistics ====

Statistics::Stats Statistics::ComputeStatistics(const std::vector<float>& values) {
    //Implement statistics here
    Stats retVal;
    retVal.average = CalculateAverage(values);
    if(retVal.average < 0){
        retVal.max = GetMax(values);
        retVal.min = GetMin(values);
    }
    else{
        NanReturn(retVal);
    }
    return retVal;
}

float Statistics::CalculateAverage(const std::vector<float>& values){
    float sum = 0.0;
    float elementCount = 0.0;
    for(float i: values){
         sum += i;
         elementCount++;
    }
    if(elementCount>0)
        return sum/elementCount;
    else
        return -1.0;
}

float Statistics::GetMin(const std::vector<float>& values){
    float min = values[0];
    for(float i:values){
        min = min<i? min : i;
    }
    return min;
}

float Statistics::GetMax(const std::vector<float>& values){
    float max = 0;
    for(float i:values){
        max = max<i? i : max;
    }
    return max;
}

void Statistics::NanReturn(Stats& stats){
    stats.average = 1;
    stats.min = 1;
    stats.max = 1;
}

// ==== Alerts ====

void Alerts::StatsAlerter::checkAndAlert(const std::vector<float>& data){
    if(Statistics::GetMax(data) > mThreshold){
        for(IAlerter *alerter: mAlerters){
            alerter->SetAlert(true);
        }
    }
    else{
        for(IAlerter *alerter: mAlerters){
            alerter->SetAlert(false);
        }
    }
}