#include "button.h"

Button::Button(ButtonType type, volatile bool *gButton) : isPressed_(gButton), type_(type)
{
    if (type_ == ButtonType::EXTERN)
    {
        *isPressed_ = 1;
    }

    activateExternalInterrupt();
}

void Button::activateExternalInterrupt()
{
    cli();

    EIMSK |= (1 << INT0);

    EICRA |= (1 << ISC00);

    sei();
}

bool Button::isPressed()
{
    if (type_ == ButtonType::EXTERN)
    {
        return !(*isPressed_);
    }
    else
    {
        return *isPressed_;
    }
}