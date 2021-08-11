#ifndef _RAS_CONTROLLER_STORAGE_H
#define _RAS_CONTROLLER_STORAGE_H

#include "Arduino.h"
#include "EEPROM.h"

/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>

class RasControllerStorage
{
public:
    static const uint8_t OFFSET = sizeof(uint32_t) + 0;

    static const uint8_t T0_ON = OFFSET * 1;
    static const uint8_t T0_TIME = OFFSET * 2;
    static const uint8_t T0_ENABLED = OFFSET * 3;
    static const uint8_t T0_INVERT = OFFSET * 4;

    static const uint8_t T1_ON = OFFSET * 5;
    static const uint8_t T1_TIME = OFFSET * 6;
    static const uint8_t T1_ENABLED = OFFSET * 7;
    static const uint8_t T1_INVERT = OFFSET * 8;

    static const uint8_t T2_ON = OFFSET * 9;
    static const uint8_t T2_TIME = OFFSET * 10;
    static const uint8_t T2_ENABLED = OFFSET * 11;
    static const uint8_t T2_INVERT = OFFSET * 12;

    static const uint8_t T3_ON = OFFSET * 13;
    static const uint8_t T3_TIME = OFFSET * 14;
    static const uint8_t T3_ENABLED = OFFSET * 15;
    static const uint8_t T3_INVERT = OFFSET * 16;

    void setT0On(uint32_t data);
    uint32_t getT0On(void);
    void setT0Time(uint32_t data);
    uint32_t getT0Time(void);
    void setT0Enabled(uint32_t data);
    uint32_t getT0Enabled(void);
    void setT0Invert(uint32_t data);
    uint32_t getT0Invert(void);

    void setT1On(uint32_t data);
    uint32_t getT1On(void);
    void setT1Time(uint32_t data);
    uint32_t getT1Time(void);
    void setT1Enabled(uint32_t data);
    uint32_t getT1Enabled(void);
    void setT1Invert(uint32_t data);
    uint32_t getT1Invert(void);

    void setT2On(uint32_t data);
    uint32_t getT2On(void);
    void setT2Time(uint32_t data);
    uint32_t getT2Time(void);
    void setT2Enabled(uint32_t data);
    uint32_t getT2Enabled(void);
    void setT2Invert(uint32_t data);
    uint32_t getT2Invert(void);

    void setT3On(uint32_t data);
    uint32_t getT3On(void);
    void setT3Time(uint32_t data);
    uint32_t getT3Time(void);
    void setT3Enabled(uint32_t data);
    uint32_t getT3Enabled(void);
    void setT3Invert(uint32_t data);
    uint32_t getT3Invert(void);

    void reset(void);

private:
    // uint32_t _t0_on = 900, _t0_time = 1200, _t0_enabled = true; //on = 15mins, time = 20mins, enabled = true
    // uint32_t _T0_on = 900, _T0_time = 1200, _T0_enabled = true; //on = 15mins, time = 20mins, enabled = true
    // uint32_t _T1_on = 900, _T1_time = 1200, _T1_enabled = true; //on = 15mins, time = 20mins, enabled = true
    // uint32_t _T2_on = 900, _T2_time = 1200, _T2_enabled = true; //on = 15mins, time = 20mins, enabled = true

    uint32_t _t0_on = 70, _t0_time = 60 * 10, _t0_enabled = true, _t0_invert = false; //on = 15mins, time = 20mins, enabled = true
    uint32_t _t1_on = 70, _t1_time = 60 * 10, _t1_enabled = true, _t1_invert = false; //on = 15mins, time = 20mins, enabled = true
    uint32_t _t2_on = 70, _t2_time = 60 * 10, _t2_enabled = true, _t2_invert = false; //on = 15mins, time = 20mins, enabled = true
    uint32_t _t3_on = 70, _t3_time = 60 * 10, _t3_enabled = true, _t3_invert = false; //on = 15mins, time = 20mins, enabled = true
};
#endif // _RAS_CONTROLLER_STORAGE_H
