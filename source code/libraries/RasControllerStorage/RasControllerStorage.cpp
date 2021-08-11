#include "RasControllerStorage.h"
#include "Arduino.h"
#include "EEPROM.h"

//=============================================================================t0
void RasControllerStorage::setT0On(uint32_t data)
{
   EEPROM.put(RasControllerStorage::T0_ON, data);
}
uint32_t RasControllerStorage::getT0On(void)
{
   uint32_t data;
   EEPROM.get(RasControllerStorage::T0_ON, data);
   return data;
}
//=============================================================================t0
void RasControllerStorage::setT0Time(uint32_t data)
{
   EEPROM.put(RasControllerStorage::T0_TIME, data);
}
uint32_t RasControllerStorage::getT0Time(void)
{
   uint32_t data;
   EEPROM.get(RasControllerStorage::T0_TIME, data);
   return data;
}
//=============================================================================t0
void RasControllerStorage::setT0Enabled(uint32_t data)
{
   EEPROM.put(RasControllerStorage::T0_ENABLED, data);
}
uint32_t RasControllerStorage::getT0Enabled(void)
{
   uint32_t data;
   EEPROM.get(RasControllerStorage::T0_ENABLED, data);
   return data;
}
//=============================================================================t0
void RasControllerStorage::setT0Invert(uint32_t data)
{
   EEPROM.put(RasControllerStorage::T0_INVERT, data);
}
uint32_t RasControllerStorage::getT0Invert(void)
{
   uint32_t data;
   EEPROM.get(RasControllerStorage::T0_INVERT, data);
   return data;
}
//=============================================================================
//=============================================================================t1
void RasControllerStorage::setT1On(uint32_t data)
{
   EEPROM.put(RasControllerStorage::T1_ON, data);
}
uint32_t RasControllerStorage::getT1On(void)
{
   uint32_t data;
   EEPROM.get(RasControllerStorage::T1_ON, data);
   return data;
}
//=============================================================================t1
void RasControllerStorage::setT1Time(uint32_t data)
{
   EEPROM.put(RasControllerStorage::T1_TIME, data);
}
uint32_t RasControllerStorage::getT1Time(void)
{
   uint32_t data;
   EEPROM.get(RasControllerStorage::T1_TIME, data);
   return data;
}
//=============================================================================t1
void RasControllerStorage::setT1Enabled(uint32_t data)
{
   EEPROM.put(RasControllerStorage::T1_ENABLED, data);
}
uint32_t RasControllerStorage::getT1Enabled(void)
{
   uint32_t data;
   EEPROM.get(RasControllerStorage::T1_ENABLED, data);
   return data;
}
//=============================================================================t1
void RasControllerStorage::setT1Invert(uint32_t data)
{
   EEPROM.put(RasControllerStorage::T1_INVERT, data);
}
uint32_t RasControllerStorage::getT1Invert(void)
{
   uint32_t data;
   EEPROM.get(RasControllerStorage::T1_INVERT, data);
   return data;
}
//=============================================================================
//=============================================================================t2
void RasControllerStorage::setT2On(uint32_t data)
{
   EEPROM.put(RasControllerStorage::T2_ON, data);
}
uint32_t RasControllerStorage::getT2On(void)
{
   uint32_t data;
   EEPROM.get(RasControllerStorage::T2_ON, data);
   return data;
}
//=============================================================================t2
void RasControllerStorage::setT2Time(uint32_t data)
{
   EEPROM.put(RasControllerStorage::T2_TIME, data);
}
uint32_t RasControllerStorage::getT2Time(void)
{
   uint32_t data;
   EEPROM.get(RasControllerStorage::T2_TIME, data);
   return data;
}
//=============================================================================t2
void RasControllerStorage::setT2Enabled(uint32_t data)
{
   EEPROM.put(RasControllerStorage::T2_ENABLED, data);
}
uint32_t RasControllerStorage::getT2Enabled(void)
{
   uint32_t data;
   EEPROM.get(RasControllerStorage::T2_ENABLED, data);
   return data;
}
//=============================================================================t2
void RasControllerStorage::setT2Invert(uint32_t data)
{
   EEPROM.put(RasControllerStorage::T2_INVERT, data);
}
uint32_t RasControllerStorage::getT2Invert(void)
{
   uint32_t data;
   EEPROM.get(RasControllerStorage::T2_INVERT, data);
   return data;
}
//=============================================================================
//=============================================================================t3
void RasControllerStorage::setT3On(uint32_t data)
{
   EEPROM.put(RasControllerStorage::T3_ON, data);
}
uint32_t RasControllerStorage::getT3On(void)
{
   uint32_t data;
   EEPROM.get(RasControllerStorage::T3_ON, data);
   return data;
}
//=============================================================================t3
void RasControllerStorage::setT3Time(uint32_t data)
{
   EEPROM.put(RasControllerStorage::T3_TIME, data);
}
uint32_t RasControllerStorage::getT3Time(void)
{
   uint32_t data;
   EEPROM.get(RasControllerStorage::T3_TIME, data);
   return data;
}
//=============================================================================t3
void RasControllerStorage::setT3Enabled(uint32_t data)
{
   EEPROM.put(RasControllerStorage::T3_ENABLED, data);
}
uint32_t RasControllerStorage::getT3Enabled(void)
{
   uint32_t data;
   EEPROM.get(RasControllerStorage::T3_ENABLED, data);
   return data;
}
//=============================================================================t3
void RasControllerStorage::setT3Invert(uint32_t data)
{
   EEPROM.put(RasControllerStorage::T3_INVERT, data);
}
uint32_t RasControllerStorage::getT3Invert(void)
{
   uint32_t data;
   EEPROM.get(RasControllerStorage::T3_INVERT, data);
   return data;
}
//=============================================================================
void RasControllerStorage::reset(void)
{
   EEPROM.put(RasControllerStorage::T0_ON, _t0_on);
   EEPROM.put(RasControllerStorage::T0_TIME, _t0_time);
   EEPROM.put(RasControllerStorage::T0_ENABLED, _t0_enabled);
   EEPROM.put(RasControllerStorage::T0_INVERT, _t0_invert);

   EEPROM.put(RasControllerStorage::T1_ON, _t1_on);
   EEPROM.put(RasControllerStorage::T1_TIME, _t1_time);
   EEPROM.put(RasControllerStorage::T1_ENABLED, _t1_enabled);
   EEPROM.put(RasControllerStorage::T1_INVERT, _t1_invert);

   EEPROM.put(RasControllerStorage::T2_ON, _t2_on);
   EEPROM.put(RasControllerStorage::T2_TIME, _t2_time);
   EEPROM.put(RasControllerStorage::T2_ENABLED, _t2_enabled);
   EEPROM.put(RasControllerStorage::T2_INVERT, _t2_invert);

   EEPROM.put(RasControllerStorage::T3_ON, _t3_on);
   EEPROM.put(RasControllerStorage::T3_TIME, _t3_time);
   EEPROM.put(RasControllerStorage::T3_ENABLED, _t3_enabled);
   EEPROM.put(RasControllerStorage::T3_INVERT, _t3_invert);
}