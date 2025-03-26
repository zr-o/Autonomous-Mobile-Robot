#ifndef BUTTON_H
#define BUTTON_H

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
    Button(ButtonType type, volatile bool *gButton);
    bool isPressed();

private:
    volatile bool *button_;
    void activateExternalInterrupt();
    ButtonType type_;
};

#endif