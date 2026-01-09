#ifndef INPUT_H
#define INPUT_H

#include "config.h"

class Input {
public:
    void begin() {
        pinMode(BTN_UP, INPUT_PULLUP);
        pinMode(BTN_DOWN, INPUT_PULLUP);
        pinMode(BTN_LEFT, INPUT_PULLUP);
        pinMode(BTN_RIGHT, INPUT_PULLUP);
        pinMode(BTN_SELECT, INPUT_PULLUP);
    }

    bool isUpPressed() { return checkBtn(BTN_UP); }
    bool isDownPressed() { return checkBtn(BTN_DOWN); }
    bool isLeftPressed() { return checkBtn(BTN_LEFT); }
    bool isRightPressed() { return checkBtn(BTN_RIGHT); }
    bool isSelectPressed() { return checkBtn(BTN_SELECT); }

private:
    unsigned long lastPressTime = 0;
    const unsigned long debounceDelay = 200;

    bool checkBtn(int pin) {
        if (digitalRead(pin) == LOW) {
            if (millis() - lastPressTime > debounceDelay) {
                lastPressTime = millis();
                return true;
            }
        }
        return false;
    }
};

extern Input input;

#endif
