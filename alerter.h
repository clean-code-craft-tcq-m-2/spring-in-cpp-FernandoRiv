#ifndef _ALERTER_H
#define _ALERTER_H

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

#endif // _ALERTER_H