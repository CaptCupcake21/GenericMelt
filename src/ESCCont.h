/**
 * This Class is to abstract Dshot or Oneshot Comunication
 * 
 * Author: James Rector
*/
#ifndef _ESCConf_
#define _ESCConf_

#include <Arduino.h>
#include <DShotESC.h>

float fconstrain(float x, float min, float max);

class OneShot125 {
    public:
        bool begin(uint8_t pin, uint8_t channel); // Channels: 0 thru 7

        // From -1...1
        void set_percent(float);
        void stop();
        void setReversed(bool isReversed) {reversed = isReversed; };
    private:
        uint8_t channel;
        uint16_t pin;
        bool reversed;
        static const int PWM_FREQUENCY = 400; // Hz
        static const int PWM_RESOLUTION = 12; // bits
};

class ESCCont {
    public:
        void ESCContInit(uint8_t pin, uint8_t channel, bool DShot, bool reversed);
        void setReversed(bool reversed);
        void setSpeedPercent(float percent);
        void setSpeed3D(int16_t throttle);
        void beep(uint8_t tone);
        void stop();

    private:
        bool DShot;
        DShotESC mDshot;
        OneShot125 mOneShot;
};

#endif