#ifndef TYPEDEFS_H
#define TYPEDEFS_H

typedef uint8_t TimerExternalClock;
#define T0_FALLING_EDGE 0x06
#define T0_RISING_EDGE  0x07
#define T1_FALLING_EDGE 0x16
#define T1_RISING_EDGE  0x17


typedef uint8_t ShapeColor;
#define OCTOGON_RED    0x0
#define CIRCLE_GREEN   0x3
#define SQUARE_BLUE    0x2
#define NO_SHAPE_WHITE 0x1


typedef bool RotDir;
#define ROT_LEFT    true
#define ROT_RIGHT   false



typedef uint8_t Opcode;
#define NOP_OP 0x00 // No OPeration: Ne rien faire.
#define INI_OP 0x10 // INIt: Attendre que les 5 capteurs de ligne soient actifs, puis se déplacer en avant pendant une demi-seconde.
#define TNL_OP 0x20 // TurN Left: Au prochain embranchement, tourner à gauche.
#define TNR_OP 0x21 // TurN Right: Au prochain embranchement, tourner à droite.
#define MDL_OP 0x30 // MiDdLe: Se mettre au milieu de la pièce.
#define ENP_OP 0xF0 // ENd Path: Le chemin est terminé ; les prochaines instructions sont pour le chemin suivant.

#endif // TYPEDEFS_H