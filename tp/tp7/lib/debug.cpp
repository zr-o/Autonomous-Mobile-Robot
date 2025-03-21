#include "debug.h"

static const uint8_t MAX_BUFFER_SIZE = 50; // Dont use too much memory

void Debug::display(const char *message)
{
    char buffer[MAX_BUFFER_SIZE];
    snprintf(buffer, MAX_BUFFER_SIZE, "%s\n", message);

    RS232::sendData((uint8_t*)buffer, strlen(buffer));
}

void Debug::display(const uint8_t x)
{
    char buffer[MAX_BUFFER_SIZE];
    snprintf(buffer, MAX_BUFFER_SIZE, "debugging value: %u\n", x);

    RS232::sendData((uint8_t*)buffer, strlen(buffer));
}

void Debug::display(const uint16_t x)
{
<<<<<<< HEAD
    char buffer[MAX_BUFFER_SIZE];
    snprintf(buffer, MAX_BUFFER_SIZE, "debugging value: %u\n", x);

    RS232::sendData((uint8_t*)buffer, strlen(buffer));
=======
    RS232 writer = RS232();
    char buffer[50];
    sprintf(buffer, "debugging value: %d", x);
    writer.write(buffer);  
>>>>>>> 648598c78ea985aaa4eb4b2367241a21fdc42fa0
}
