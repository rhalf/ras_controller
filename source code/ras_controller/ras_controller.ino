#include<WatchDog.h>
//===================================================================Lcd
#include <U8g2lib.h>
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, /* clock=*/ 12, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 100);
const uint8_t BUTTON_UP = 4, BUTTON_DOWN = 5, BUTTON_RIGHT = 6,  BUTTON_LEFT = 7;
//===================================================================Helper
#include<Helper.h>
Helper helper;
//===================================================================Timer
#include<Timer.h>
Timer tDisplay(Timer::MILLIS);
Timer tInterrupt(Timer::MILLIS);
Timer tTerminals(Timer::SECONDS);
//===================================================================Buzzer
#include <Buzzer.h>
const uint8_t BUZZER_PIN = 13;
Buzzer buzzer = Buzzer(BUZZER_PIN, 440);
//===================================================================Terminal
#include <Terminal.h>
Terminal terminals[4] = {Terminal(A0), Terminal(A1), Terminal(A2), Terminal(A3)};
//===================================================================softSerial
#include<SoftwareSerial.h>
uint8_t SOFTSERIAL_RX = 9, SOFTSERIAL_TX = 8;
SoftwareSerial softSerial(SOFTSERIAL_RX, SOFTSERIAL_TX);
//===================================================================Global
#include<RasControllerStorage.h>
RasControllerStorage rcStorage;

const char title[] PROGMEM = {"RAS CONTROLLER"};
const char t0[] PROGMEM = {"T0"};
const char t1[] PROGMEM = {"T1"};
const char t2[] PROGMEM = {"T2"};
const char t3[] PROGMEM = {"T3"};

const char *msgYesNo = {" Yes \n No "};
const char *msgInvert = { "Invert?" };
const char *msgEnable = { "Enable?" };
const char *msgReset = { "Reset?" };

const char *listMenu =
  "T0\n"
  "T1\n"
  "T2\n"
  "T3\n"
  "Reset\n"
  "About";



const char *listTerm =
  "Back\n"
  "On\n"
  "Time\n"
  "Enabled\n"
  "Invert";;



char buff[20];

uint8_t
stateDisplay = 0,
menuSelection = 1;

uint32_t t0Time = 0, t1Time = 0, t2Time = 0, t3Time = 0;

void ring() {
  buzzer.play();
  delay(100);
  buzzer.stop();
}
//===================================================================Functions Display Rendering
void uiMain() {
  u8g2.firstPage();
  do {
    //--------------------------------------Title
    u8g2.setFontMode(1);
    u8g2.setDrawColor(2);

    u8g2.setCursor(0, 10);
    strcpy_P(buff, title);
    u8g2.print(buff);


    u8g2.drawHLine(0, 12, 128);
    //--------------------------------------t0
    u8g2.setCursor(0, 22);
    strcpy_P(buff, t0);
    u8g2.print(buff);

    u8g2.setCursor(18, 22);
    u8g2.print(helper.toUtf8Time(t0Time));

    u8g2.setCursor(70, 22);
    u8g2.print((terminals[0].getPinState() ? "ON" : "OFF"));

    u8g2.setCursor(95, 22);
    u8g2.print((rcStorage.getT0Enabled() ? "" : "[X]"));

    u8g2.setCursor(110, 22);
    u8g2.print((rcStorage.getT0Invert() ? "[!]" : ""));
    //--------------------------------------t1
    u8g2.setCursor(0, 32);
    strcpy_P(buff, t1);
    u8g2.print(buff);

    u8g2.setCursor(18, 32);
    u8g2.print(helper.toUtf8Time(t1Time));

    u8g2.setCursor(70, 32);
    u8g2.print((terminals[1].getPinState() ? "ON" : "OFF"));

    u8g2.setCursor(95, 32);
    u8g2.print((rcStorage.getT1Enabled() ? "" : "[X]"));

    u8g2.setCursor(110, 32);
    u8g2.print((rcStorage.getT1Invert() ? "[!]" : ""));
    //--------------------------------------t2
    u8g2.setCursor(0, 42);
    strcpy_P(buff, t2);
    u8g2.print(buff);

    u8g2.setCursor(18, 42);
    u8g2.print(helper.toUtf8Time(t2Time));

    u8g2.setCursor(70, 42);
    u8g2.print((terminals[2].getPinState() ? "ON" : "OFF"));

    u8g2.setCursor(95, 42);
    u8g2.print((rcStorage.getT2Enabled() ? "" : "[X]"));

    u8g2.setCursor(110, 42);
    u8g2.print((rcStorage.getT2Invert() ? "[!]" : ""));
    //--------------------------------------t3
    u8g2.setCursor(0, 52);
    strcpy_P(buff, t3);
    u8g2.print(buff);

    u8g2.setCursor(18, 52);
    u8g2.print(helper.toUtf8Time(t3Time));

    u8g2.setCursor(70, 52);
    u8g2.print((terminals[3].getPinState() ? "ON" : "OFF"));

    u8g2.setCursor(95, 52);
    u8g2.print((rcStorage.getT3Enabled() ? "" : "[X]"));

    u8g2.setCursor(110, 52);
    u8g2.print((rcStorage.getT3Invert() ? "[!]" : ""));
    //--------------------------------------running time
    u8g2.drawHLine(0, 54, 128);
    u8g2.setCursor(0, 64);
    //strcpy_P(buff, );
    u8g2.print(helper.toUtf8Time2(Timer::getSeconds()));

  } while (u8g2.nextPage());
}

void uiT0() {
  uint8_t result = 0, value = 0;
  strcpy_P(buff, t0);
  while (true) {
    uint8_t subMenuSelection = u8g2.userInterfaceSelectionList(
                                 buff,
                                 subMenuSelection,
                                 listTerm);
    ring();
    switch (subMenuSelection) {
      case 1:
        return;
        break;
      case 2:
        value = rcStorage.getT0On();
        u8g2.userInterfaceInputValue(
          "",
          "percent=",
          &value,
          0,
          100,
          3,
          "");
        rcStorage.setT0On(value);
        break;
      case 3:
        value = rcStorage.getT0Time() / 60;
        u8g2.userInterfaceInputValue(
          "",
          "minute=",
          &value,
          0,
          999,
          3,
          "");
        rcStorage.setT0Time(value * 60);
        break;
      case 4:
        result = u8g2.userInterfaceMessage(
                   "",
                   msgEnable,
                   "",
                   msgYesNo);
        if (result == 1)
          rcStorage.setT0Enabled(1);
        else
          rcStorage.setT0Enabled(0);
        break;
      case 5:
        result = u8g2.userInterfaceMessage(
                   "",
                   msgInvert,
                   "",
                   msgYesNo);
        if (result == 1)
          rcStorage.setT0Invert(1);
        else
          rcStorage.setT0Invert(0);
        break;
    }
  }
}
void uiT1() {
  uint8_t result = 0, value = 0;
  strcpy_P(buff, t1);
  while (true) {
    uint8_t subMenuSelection = u8g2.userInterfaceSelectionList(
                                 buff,
                                 subMenuSelection,
                                 listTerm);
    ring();
    switch (subMenuSelection) {
      case 1:
        return;
        break;
      case 2:
        value = rcStorage.getT1On();
        u8g2.userInterfaceInputValue(
          "",
          "percent=",
          &value,
          0,
          100,
          3,
          "");
        rcStorage.setT1On(value);
        break;
      case 3:
        value = rcStorage.getT1Time() / 60;
        u8g2.userInterfaceInputValue(
          "",
          "minute=",
          &value,
          0,
          999,
          3,
          "");
        rcStorage.setT1Time(value * 60);
        break;
      case 4:
        result = u8g2.userInterfaceMessage(
                   "",
                   msgEnable,
                   "",
                   msgYesNo);

        if (result == 1)
          rcStorage.setT1Enabled(1);
        else
          rcStorage.setT1Enabled(0);
        break;
      case 5:
        result = u8g2.userInterfaceMessage(
                   "",
                   msgInvert,
                   "",
                   msgYesNo);
        if (result == 1)
          rcStorage.setT1Invert(1);
        else
          rcStorage.setT1Invert(0);
        break;
    }
  }
}
void uiT2() {
  uint8_t result = 0, value = 0;
  strcpy_P(buff, t2);
  while (true) {
    uint8_t subMenuSelection = u8g2.userInterfaceSelectionList(
                                 buff,
                                 subMenuSelection,
                                 listTerm);
    ring();
    switch (subMenuSelection) {
      case 1:
        return;
        break;
      case 2:
        value = rcStorage.getT2On();
        u8g2.userInterfaceInputValue(
          "",
          "percent=",
          &value,
          0,
          100,
          3,
          "");
        rcStorage.setT2On(value );
        break;
      case 3:
        value = rcStorage.getT2Time() / 60;
        u8g2.userInterfaceInputValue(
          "",
          "minute=",
          &value,
          0,
          999,
          3,
          "");
        rcStorage.setT2Time(value * 60);
        break;
      case 4:
        result = u8g2.userInterfaceMessage(
                   "",
                   msgEnable,
                   "",
                   msgYesNo);
        if (result == 1)
          rcStorage.setT2Enabled(1);
        else
          rcStorage.setT2Enabled(0);
        break;
      case 5:
        result = u8g2.userInterfaceMessage(
                   "",
                   msgInvert,
                   "",
                   msgYesNo);
        if (result == 1)
          rcStorage.setT2Invert(1);
        else
          rcStorage.setT2Invert(0);
        break;
    }
  }
}
void uiT3() {
  uint8_t result = 0, value = 0;
  strcpy_P(buff, t3);
  while (true) {
    uint8_t subMenuSelection = u8g2.userInterfaceSelectionList(
                                 buff,
                                 subMenuSelection,
                                 listTerm);
    ring();
    switch (subMenuSelection) {
      case 1:
        return;
        break;
      case 2:
        value = rcStorage.getT3On();
        u8g2.userInterfaceInputValue(
          "",
          "percent=",
          &value,
          0,
          100,
          3,
          "");
        rcStorage.setT3On(value);
        break;
      case 3:
        value = rcStorage.getT3Time() / 60;
        u8g2.userInterfaceInputValue(
          "",
          "minute=",
          &value,
          0,
          999,
          3,
          "");
        rcStorage.setT3Time(value * 60);
        break;
      case 4:
        result = u8g2.userInterfaceMessage(
                   "",
                   msgEnable,
                   "",
                   msgYesNo);

        if (result == 1)
          rcStorage.setT3Enabled(1);
        else
          rcStorage.setT3Enabled(0);
        break;
      case 5:
        result = u8g2.userInterfaceMessage(
                   "",
                   msgInvert,
                   "",
                   msgYesNo);
        if (result == 1)
          rcStorage.setT3Invert(1);
        else
          rcStorage.setT3Invert(0);
        break;
    }
  }
}
void uiMenu() {
  uint8_t result = 0;
  ring();
  strcpy_P(buff, title);
  menuSelection = u8g2.userInterfaceSelectionList(
                    buff,
                    menuSelection,
                    listMenu);

  ring();
  switch (menuSelection) {
    case 1:
      uiT0();
      break;
    case 2:
      uiT1();
      break;
    case 3:
      uiT2();
      break;
    case 4:
      uiT3();
      break;
    case 5:
      result = u8g2.userInterfaceMessage(
                 "",
                 msgReset,
                 "",
                 msgYesNo);
      if (result == 1) {
        rcStorage.reset();
      }
      break;
    case 6:
      result = u8g2.userInterfaceMessage(
                 "v0.1 (20210806)",
                 "",
                 "09176088771",
                 "rhalfcaacbay@gmail.com");
      break;
  }
  ring();
}
//===================================================================Functions Terminals
void cbTerminals() {
  if (rcStorage.getT0Enabled()) {
    t0Time = Timer::getSeconds() % rcStorage.getT0Time();
    uint32_t on0 = (rcStorage.getT0On() / 100.0 ) * rcStorage.getT0Time();

    if (rcStorage.getT0Invert() == 0) {
      if (t0Time < on0) terminals[0].on();
      else terminals[0].off();
    } else {
      if ((rcStorage.getT0Time() - on0) < t0Time) terminals[0].on();
      else terminals[0].off();
    }
  } else {
    t0Time = 0;
    terminals[0].off();
  }

  if (rcStorage.getT1Enabled()) {
    t1Time = Timer::getSeconds() % rcStorage.getT1Time();
    uint32_t on1 = (rcStorage.getT1On() / 100.0 ) * rcStorage.getT1Time();

    if (rcStorage.getT1Invert() == 0) {
      if (t1Time < on1) terminals[1].on();
      else terminals[1].off();
    } else {
      if ((rcStorage.getT1Time() - on1) < t1Time) terminals[1].on();
      else terminals[1].off();
    }
  } else {
    t1Time = 0;
    terminals[1].off();
  }

  if (rcStorage.getT2Enabled()) {
    t2Time = Timer::getSeconds() % rcStorage.getT2Time();
    uint32_t on2 = (rcStorage.getT2On() / 100.0 ) * rcStorage.getT2Time();

    if (rcStorage.getT2Invert() == 0) {
      if (t2Time < on2) terminals[2].on();
      else terminals[2].off();
    } else {
      if ((rcStorage.getT2Time() - on2) < t2Time) terminals[2].on();
      else terminals[2].off();
    }
  } else {
    t2Time = 0;
    terminals[2].off();
  }

  if (rcStorage.getT3Enabled()) {
    t3Time = Timer::getSeconds() % rcStorage.getT3Time();
    uint32_t on3 = (rcStorage.getT3On() / 100.0 ) * rcStorage.getT3Time();

    if (rcStorage.getT3Invert() == 0) {
      if (t3Time < on3) terminals[3].on();
      else terminals[3].off();
    } else {
      if ((rcStorage.getT3Time() - on3) < t3Time) terminals[3].on();
      else terminals[3].off();
    }
  } else {
    t3Time = 0;
    terminals[3].off();
  }
}
//===================================================================Functions Display
void cbDisplay() {
  uiMain();
}
//===================================================================Functions Interrupt
void cbInterrupt() {
  uint8_t key = u8g2.getMenuEvent();
  switch (key) {
    case U8X8_MSG_GPIO_MENU_SELECT:
      WatchDog::disable();
      uiMenu();
      WatchDog::enable(WatchDog::S002);
      break;
    case U8X8_MSG_GPIO_MENU_NEXT:
      break;
    case U8X8_MSG_GPIO_MENU_PREV:
      break;
    case U8X8_MSG_GPIO_MENU_HOME:
      break;
    case U8X8_MSG_GPIO_MENU_UP:
      break;
    case U8X8_MSG_GPIO_MENU_DOWN:
      break;
  }
  //  Serial.print("Key : ");
  //  Serial.println(key);
}

void setup(void) {
  Serial.begin(9600);
  softSerial.begin(9600);

  u8g2.begin(/*Select=*/ BUTTON_UP, /*Right/Next=*/ BUTTON_RIGHT, /*Left/Prev=*/BUTTON_LEFT , /*Up=*/ -1, /*Down=*/ -1, /*Home/Cancel=*/ BUTTON_DOWN); // Arduboy DevKit
  u8g2.setFont(u8g2_font_profont11_tf);
  u8g2.enableUTF8Print();

  tDisplay.begin(Timer::FOREVER, 250, cbDisplay);
  tDisplay.start();

  tInterrupt.begin(Timer::FOREVER, 1, cbInterrupt);
  tInterrupt.start();

  tTerminals.begin(Timer::FOREVER, 1, cbTerminals);
  tTerminals.start();

  WatchDog::enable(WatchDog::S002);
}

void loop(void) {
  tInterrupt.run();
  tDisplay.run();
  tTerminals.run();

  WatchDog::reset();
}
