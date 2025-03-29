#include "button.h"

Button::Button(ButtonType type, Port port, Pin pin) : type_(type),
                                                      port_(port), pin_(pin)
{
    Ports::setPinMode(PortMode::READ, port, pin);
}

bool Button::isPressed()
{
    switch (type_)
    {
    case ButtonType::MOTHERBOARD:
        if (Ports::readPin(port_, pin_))
        {
            _delay_ms(DELAY_REBOUND_MS);

            if (Ports::readPin(port_, pin_))
            {
                buttonPressMemory_ = true;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }

    case ButtonType::EXTERN:
        if (!Ports::readPin(port_, pin_))
        {
            _delay_ms(DELAY_REBOUND_MS);

            if (!Ports::readPin(port_, pin_))
            {
                buttonPressMemory_ = true;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }

    default:
        return false;
    }
}

bool Button::wasPressed()
{
    return buttonPressMemory_;
}

void Button::resetPressMemory()
{
    buttonPressMemory_ = false;
}