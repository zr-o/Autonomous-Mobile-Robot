#include "button.h"

Button::Button(ButtonType type, volatile bool *gButton) : button_(gButton), type_(type)
{
    Ports::setPinMode(PortMode::READ, Port::D, Pin::N2);

    if (type_ == ButtonType::EXTERN)
    {
        *button_ = 1;
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
        return !(*button_);
    }
    else
    {
        return *button_;
    }
}