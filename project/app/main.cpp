/*
Giovanni Marven Alcena  
Adam Azrou  
Elliot Gareau  
Anis Feteh Benabderrahmane  

Point d'entrée principal du programme.  
Permet d'exécuter la navigation complète du robot à travers un parcours défini en appelant la méthode doPath().  
16 avril 2025  

Composantes :  
Utilisation de la classe Path pour gérer les mouvements et les décisions du robot.  
(Voir path.h et debug.h pour les définitions et outils de débogage)  
*/

#include "path.h"
#include "debug.h"

int main()
{
    Path path = Path();
    path.doPath();
}
