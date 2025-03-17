#include "debug.h"

void DEBUG::DebugToRs232(const char* message) {
    RS232 writer = RS232();
    writer.write(message);  // Envoie directement la chaîne
}

// Fonction qui prend un entier
void DEBUG::DebugToRs232(int x) {
    RS232 writer = RS232();
    char buffer[50];
    sprintf(buffer, "%d", x);  // Convertit l'entier en chaîne
    writer.write(buffer);  // Envoie la chaîne convertie
}
