#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>
#include <avr/interrupt.h>


enum class ButtonType{
    MOTHERBOARD,
    EXTERN
};

class Button {

    public:
    Button(ButtonType type, volatile bool* gButton);
    bool isPressed();

    private:
    volatile bool* isPressed_;
    void activateExternalInterrupt();
    ButtonType type_;
};

#endif