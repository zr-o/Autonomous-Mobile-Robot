#ifndef BUTTON_H
#define BUTTON_H

#include "global_defines.h"

#include <util/delay.h>
#include <avr/interrupt.h>
#include "ports.h"

enum class ButtonType
{
    MOTHERBOARD,
    EXTERN
};

class Button
{
public:
    Button(ButtonType type, Port port, Pin pin);
    bool isPressed();
    bool wasPressed();
    void resetPressMemory();

private:
    ButtonType type_;
    Port port_;
    Pin pin_;
    bool buttonPressMemory_ = false;
};

#endif