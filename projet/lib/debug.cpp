#include "debug.h"

static const uint8_t MAX_BUFFER_SIZE = 50;

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
    char buffer[MAX_BUFFER_SIZE];
    snprintf(buffer, MAX_BUFFER_SIZE, "debugging value: %u\n", x);

    RS232::sendData((uint8_t*)buffer, strlen(buffer));
}

void Debug::display(const int8_t x)
{
    char buffer[MAX_BUFFER_SIZE];
    snprintf(buffer, MAX_BUFFER_SIZE, "debugging value: %d\n", x);

    RS232::sendData((uint8_t*)buffer, strlen(buffer));
}
