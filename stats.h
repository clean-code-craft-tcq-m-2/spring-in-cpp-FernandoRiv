#ifndef _STATS_H
#define _STATS_H

#include <vector>

// ==== Statistics ====

namespace Statistics {
    class Stats{
        public:
        float average = 0; 
        float max = 0; 
        float min = 0;
    };
    
    Stats ComputeStatistics(const std::vector<float>& );
    float CalculateAverage(const std::vector<float>& );
    float GetMin(const std::vector<float>& values);
    float GetMax(const std::vector<float>& values);
    void  NanReturn(Stats& stats);
}

// ==== Alerts ====

namespace Alerts{
    class IAlerter
    {
        public:
            virtual ~IAlerter();
            virtual void SetAlert(bool) = 0;
    };

    class EmailAlert: public IAlerter
    {
        public:
            bool emailSent = false;

            virtual void SetAlert(bool setAlert){
                emailSent = setAlert;
            }
    };

    class LEDAlert: public IAlerter
    {
        public:
            bool ledGlows = false;

            virtual void SetAlert(bool setAlert){
                ledGlows = setAlert;
            }
    };

    class StatsAlerter
    {
        public:
            StatsAlerter(const float threshold, std::vector<Alerts::IAlerter*> alerters):
                mThreshold(threshold),
                mAlerters(alerters) {}

            void checkAndAlert(const std::vector<float>& data);

        private:
            float mThreshold;
            std::vector<Alerts::IAlerter*> mAlerters;
    };
}

#endif // _STATS_H