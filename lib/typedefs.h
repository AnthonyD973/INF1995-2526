/**
 * @file    typedefs.h
 * 
 * @brief   Définition des typedefs et de leurs valeurs possibles.
 *
 * @authors Belhaddad, Emir Khaled
 * @authors Dandenault, Vincent
 * @authors Dentinger, Anthony
 * @authors Younis, Gergi
 * 
 * @date Automne 2016
 *
 * @copyright Code qui n'est sous aucune license.
 */

/**
 * @brief Type de valeurs qui expriment la couleur d'une LED.
 * 
 * <b>Valeurs possibles:</b>
 * <ul>
 *     <li>#LED_OFF  </li>
 *     <li>#LED_GREEN</li>
 *     <li>#LED_RED  </li>
 *     <li>#LED_AMBER</li>
 * </ul>
 */
typedef uint8_t LedColor;
#define    LED_OFF   0x00
#define    LED_GREEN 0x01
#define    LED_RED   0x02
#define    LED_AMBER 0xFF


/**
 * @brief Type de valeurs qui expriment la position d'une LED.
 * 
 * <b>Valeurs possibles:</b>
 * <ul>
 *     <li>#LED_OFF  </li>
 *     <li>#LED_GREEN</li>
 *     <li>#LED_RED  </li>
 *     <li>#LED_AMBER</li>
 * </ul>
 */
typedef uint8_t LedPosition;
#define    A0_A1 0
#define    A2_A3 2
#define    A4_A5 4
#define    A6_A7 6
#define    B0_B1 8
#define    B2_B3 10
#define    B4_B5 12
#define    B6_B7 14
#define    C0_C1 16
#define    C2_C3 18
#define    C4_C5 20
#define    C6_C7 22
#define    D0_D1 24
#define    D2_D3 26
#define    D4_D5 28
#define    D6_D7 30