/*
Giovanni Marven Alcena  
Adam Azrou  
Elliot Gareau  
Anis Feteh Benabderrahmane  

Contient une fonction utilitaire permettant de générer un délai variable en millisecondes.  
Utilisé pour contrôler le temps d'attente dans diverses opérations du microcontrôleur ATmega324PA.  
16 avril 2025  

Composantes :  
Utilisation de la librairie <util/delay.h> pour effectuer des délais précis.  
(Voir lib_defines.h pour les définitions utilisées)  
*/

#ifndef GENERAL_FUNCTIONS_H
#define GENERAL_FUNCTIONS_H

#include "lib_defines.h"
#include <util/delay.h>

void variableDelayMs(uint16_t delay);

#endif