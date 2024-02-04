#include "ESCCont.h"
/**
 * This Class is to abstract Dshot or Oneshot Comunication
 * 
 * Author: James Rector
*/

float fconstrain(float x, float min, float max) {
   return x > max ? max : (x < min ? min : x);
}

bool OneShot125::begin(uint8_t pin, uint8_t channel) {
    this->pin = pin;
    this->channel = channel;
    
    ledcSetup(channel, PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(pin, channel);

    for (float power = 0; power <= 1; power += 0.001) set_percent(power);
    for (float power = 1; power >= 0; power -= 0.001) set_percent(power);
    stop();
    return true;
}

void OneShot125::set_percent(float percent) {
    percent = fconstrain(percent, 1, 1); // Constrain -1...1
    percent *= (reversed ? -1 : 1);
    percent = (percent / 40.0f) + 0.075f; // Map -1...1 to 0.05...0.1
    ledcWrite(channel, percent * (1 << PWM_RESOLUTION));
}

void OneShot125::stop() {
    set_percent(0);
}

void ESCCont::ESCContInit(uint8_t pin, uint8_t channel, bool DShot, bool reversed)
{
    this->DShot = DShot;
    if(DShot)
    {
        mDshot.install((gpio_num_t)pin, (rmt_channel_t)channel);
        mDshot.init();
        mDshot.setReversed(reversed);
        mDshot.set3DMode(true);
        mDshot.beep();
    }
    else
    {
        mOneShot.begin(pin, channel);
        mOneShot.setReversed(reversed);
    }
}

void ESCCont::setReversed(bool reversed)
{
    if(DShot)
    {
        mDshot.setReversed(reversed);
    }
    else
    {
        mOneShot.setReversed(reversed);
    }
}

void ESCCont::setSpeedPercent(float percent)
{
    if(DShot)
    {
        mDshot.sendThrottle3D(int(999*percent));
    }
    else
    {
        mOneShot.set_percent(percent);
    }
}

void ESCCont::setSpeed3D(int16_t throttle)
{
    if(DShot)
    {
        mDshot.sendThrottle3D(throttle);
    }
    else
    {
        mOneShot.set_percent(float(throttle/999));
    }
}

void ESCCont::stop()
{
    if(DShot)
    {
        mDshot.sendMotorStop();
    }
    else
    {
        mOneShot.stop();
    }
}

void ESCCont::beep(uint8_t tone)
{
    if(DShot)
        mDshot.beep(tone);
}

