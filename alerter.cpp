#include "alerter.h"
#include "stats.h"

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