# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes

Identification:
+ Travail    : Mise en commun du code et formation de librairies
+ Section #  : 1
+ Équipe #   : 1621
+ Correcteur : Kais Fallouh

# CODE

| Points importants                                        | Poids          |
| -------------------------------------------------------- | -------------- |
| La qualités et le choix de vos portions de code choisies | (3.2/5.0)      |
| La qualités de vos modifications aux Makefiles           | (4.7/5.0)      |
| __Résultat partiel__                                     | __(7.9/10.0)__ |

# RAPPORT

| Points importants                                                           | Poids         |
| --------------------------------------------------------------------------- | ------------- |
| Explications cohérentes par rapport au code retenu pour former la librairie | (1.8/2.0)     |
| Explications cohérentes par rapport aux Makefiles modifiés                  | (1.8/2.0)     |
| Explications claires avec un bon niveau de détails                          | (1.7/2.0)     |
| Bon français                                                                | (1.0/1.0)     |
| __Résultat partiel__                                                        | __(6.3/7.0)__ |

# GÉNÉRALITÉS
## Bonne soumission de l'ensemble du code et du rapport selon le format demandé

| Pénalité par erreur      | -0.5          |
| ------------------------ | ------------- |
| compilation sans erreurs |    -0.5       |
| etc                      |               |
| __Résultat partiel__     | __(2.5/3.0)__ |


# Résultat

__Total des points: 16.7/20__

# Commentaires du correcteur :

# GÉNÉRALITÉS
- (-0.5) Erreur de compilation pour la librairie

# RAPPORT
- (-0.1) L'ajout de $(TRG) et $(HEXROMTRG) ne compile pas uniquement la bibliothèque statique, mais également un exécutable (.elf) et un fichier .hex, ce qui est contradictoire avec l’objectif annoncé.
- (-0.1) Erreur dans la ligne : « LIBS=-L/../-llibstatic : Lien avec la bibliothèque statique libstatic.a. » Cette syntaxe est erronée et ne reflète pas le contenu réel du Makefile
- (-0.1) Appel inconditionnel à `activateExternalInterrupt()`, Cette fonction est appelée même si type_ == ButtonType::MOTHERBOARD, ce qui configure à tort l’interruption INT0, même pour un bouton non externe. Cela viole le comportement décrit dans le rapport.
- (-0.2) Aucune méthode pour arrêter ou désactiver les roues (wheels.h)
- (-0.1) Aucune méthode n'utilise delayTimer dans le constructeur de Wheels. Pourquoi ?

# CODE
- (-0.2) Dans le Makefile de la librairie, l’inclusion de $(TRG) (libstatic.elf) dans la cible all déclenche une tentative de génération d’un exécutable.
- (-0.1) La règle de création de $(TRG) contient une commande de linkage pour un exécutable qui nécessite main() — inadaptée pour une simple bibliothèque.
- (-0.5) Il manque les entêtes dans vos fichiers de codes
- (-0.3) Erreur critique dans timer0.cpp: Les registres TCCR1B, CS10, CS11, etc., appartiennent au Timer1, pas au Timer0.
- (-0.2) Attention à l'utilisation abusive des fonctions cli() et sei(), ca interrompt les interruptions globales de façon répétée
- (-0.1) dans timer2.cpp : Méthode setTimerMode() – erreur de configuration du mode CTC, Le mode CTC pour un timer 8 bits (comme Timer2) requiert que WGM21 soit à 1 et non à 0.
- (-0.2) Erreur critique : l’absence de break entraîne l’exécution en cascade (fallthrough) des trois cas. Peu importe la couleur, la LED finira dans l’état OFF dans led.cpp
- (-0.1) erreur dans `portsUtility_->setPinMode(PortMode::WRITE, port_, pinB);`, pinB n’est pas déclaré localement dans cette fonction. Le nom attendu est pinB_
- (-0.1) Dans Color::OFF, mauvaise broche manipulée deux fois, La broche pinB_ est oubliée
- (-0.1) Le nom de méthode lightUp() suggère uniquement un allumage, alors qu’elle gère aussi l’extinction.
- (-0.2) Erreur critique : l’absence de break dans chaque case entraîne une exécution en cascade, donc la valeur est écrite sur tous les ports jusqu’à D, peu importe celui spécifié. (ports.cpp)


# Basé sur le commit suivant
```
commit 4acd7cde23cd563f8ecc600210a96add5a72cec4
Author: Anis Feteh Benabderrahmane <anis-feteh.benabderrahmane@polymtl.ca>
Date:   Mon Mar 17 16:47:58 2025 -0400

    Modifications du rapport et version finale
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp7/lib`
```
make : on entre dans le répertoire « /home/gigl/Bureau/Correction/inf1900-grader/correction_tp7/1621/tp/tp7/lib »
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c button.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c can.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c debug.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c led.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c memoire_24.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c ports.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c rs232.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c timer0.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c timer1.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c timer2.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c wheels.cpp
ar -crs libstatic.a  button.o can.o debug.o led.o memoire_24.o ports.o rs232.o timer0.o timer1.o timer2.o wheels.o
avr-gcc -Wl,-Map,libstatic.elf.map -mmcu=atmega324pa -o libstatic.elf  button.o can.o debug.o led.o memoire_24.o ports.o rs232.o timer0.o timer1.o timer2.o wheels.o \
-lm 
/usr/lib/gcc/avr/14.1.0/../../../../avr/bin/ld: /usr/lib/gcc/avr/14.1.0/../../../../avr/lib/avr5/crtatmega324pa.o:(.init9+0x0): undefined reference to `main'
collect2: error: ld returned 1 exit status
make: *** [Makefile:146 : libstatic.elf] Erreur 1
make : on quitte le répertoire « /home/gigl/Bureau/Correction/inf1900-grader/correction_tp7/1621/tp/tp7/lib »

```

## Sortie de `make` dans `tp/tp7/exec`
```
make : on entre dans le répertoire « /home/gigl/Bureau/Correction/inf1900-grader/correction_tp7/1621/tp/tp7/exec »
avr-gcc -I. -I/usr/include/simavr -MMD -I/../lib -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c main.cpp
avr-gcc -Wl,-Map,makefileExec.elf.map -mmcu=atmega324pa -o makefileExec.elf  main.o \
-lm -L../lib -lstatic
avr-objcopy -j .text -j .data -O ihex makefileExec.elf makefileExec.hex
make : on quitte le répertoire « /home/gigl/Bureau/Correction/inf1900-grader/correction_tp7/1621/tp/tp7/exec »

```
