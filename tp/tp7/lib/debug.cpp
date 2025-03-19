#ifdef DEBUG_H
#include "debug.h"

void Debug::display(const char *message)
{
    RS232 writer = RS232();
    writer.write(message);
}

void Debug::display(const uint16_t x)
{
    RS232 writer = RS232();
    char buffer[50];
    sprintf(buffer, "debugging value: %d", x);
    writer.write(buffer);  
}

#endif