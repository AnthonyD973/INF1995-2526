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

#ifndef TYPEDEFS_H
#define TYPEDEFS_H


/**
 * @brief Type de valeurs qui expriment si l'UART doit transmettre/recevoir par
 *      scrutation ou par interruption.
 * 
 * <b>Valeurs possibles:</b>
 * <ul>
 *     <li>#UART_POLLING  </li>
 *     <li>#UART_INTERRUPT</li>
 * </ul>
 */
typedef bool CommMode;
#define UART_POLLING    true  /**< @brief L'UART doit transmettre/recevoir par
                                         scrutation. */
#define UART_INTERRUPT  false /**< @brief L'UART doit transmettre/recevoir par
                                         interruption. */

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
#define    LED_OFF   0x00 /**< @brief LED éteinte. */
#define    LED_GREEN 0x01 /**< @brief LED verte.   */
#define    LED_RED   0x02 /**< @brief LED rouge.   */
#define    LED_AMBER 0xFF /**< @brief LED ambre.   */


/**
 * @brief Type de valeurs qui expriment la position d'une LED.
 * 
 * Une LED doit toujours avoir son pôle positif sur le bit de poids fort pour
 * avoir la bonne couleur.
 * 
 * <b>Valeurs possibles:</b>
 * <ul>
 *     <li>#A0_A1</li>
 *     <li>#A2_A3</li>
 *     <li>#A4_A5</li>
 *     <li>#A6_A7</li>
 *     <li>#B0_B1</li>
 *     <li>#B2_B3</li>
 *     <li>#B4_B5</li>
 *     <li>#B6_B7</li>
 *     <li>#C0_C1</li>
 *     <li>#C2_C3</li>
 *     <li>#C4_C5</li>
 *     <li>#C6_C7</li>
 *     <li>#D0_D1</li>
 *     <li>#D2_D3</li>
 *     <li>#D4_D5</li>
 *     <li>#D6_D7</li>
 * </ul>
 */
typedef uint8_t LedPosition;
#define    A0_A1 0  /**< @brief La LED est placée sur les broches A0 et A1. */
#define    A2_A3 2  /**< @brief La LED est placée sur les broches A2 et A3. */
#define    A4_A5 4  /**< @brief La LED est placée sur les broches A4 et A5. */
#define    A6_A7 6  /**< @brief La LED est placée sur les broches A6 et A7. */
#define    B0_B1 8  /**< @brief La LED est placée sur les broches B0 et B1. */
#define    B2_B3 10 /**< @brief La LED est placée sur les broches B2 et B3. */
#define    B4_B5 12 /**< @brief La LED est placée sur les broches B4 et B5. */
#define    B6_B7 14 /**< @brief La LED est placée sur les broches B6 et B7. */
#define    C0_C1 16 /**< @brief La LED est placée sur les broches C0 et C1. */
#define    C2_C3 18 /**< @brief La LED est placée sur les broches C2 et C3. */
#define    C4_C5 20 /**< @brief La LED est placée sur les broches C4 et C5. */
#define    C6_C7 22 /**< @brief La LED est placée sur les broches C5 et C7. */
#define    D0_D1 24 /**< @brief La LED est placée sur les broches D0 et D1. */
#define    D2_D3 26 /**< @brief La LED est placée sur les broches D2 et D3. */
#define    D4_D5 28 /**< @brief La LED est placée sur les broches D4 et D5. */
#define    D6_D7 30 /**< @brief La LED est placée sur les broches D6 et D7. */


/**
 * @brief   Type de valeurs qui expriment la valeur de division d'horloge d'un
 *      Timer0 ou d'un Timer1.
 * 
 * <b>Valeurs possibles:</b>
 * <ul>
 *     <li>#P01_NO_CLK </li>
 *     <li>#P01_CLK1   </li>
 *     <li>#P01_CLK8   </li>
 *     <li>#P01_CLK64  </li>
 *     <li>#P01_CLK256 </li>
 *     <li>#P01_CLK1024</li>
 *     <li>#P01_EXT_CLK_FALLING_EDGE <b style="color:#A00">!!Nouvelle valeur comparé à #Prescale2!!</b></li>
 *     <li>#P01_EXT_CLK_RISING_EDGE  <b style="color:#A00">!!Nouvelle valeur comparé à #Prescale2!!</b></li>
 * </ul>
 */
typedef uint8_t Prescale01;
#define    P01_NO_CLK  0x0
#define    P01_CLK1    0x1
#define    P01_CLK8    0x2
#define    P01_CLK64   0x3
#define    P01_CLK256  0x4
#define    P01_CLK1024 0x5
#define    P01_EXT_CLK_FALLING_EDGE 0x6
#define    P01_EXT_CLK_RISING_EDGE 0x7


/**
 * @brief   Type de valeurs qui expriment la valeur de division d'horloge d'un
 *      Timer2.
 * 
 * <b>Valeurs possibles:</b>
 * <ul>
 *     <li>#P2_NO_CLK </li>
 *     <li>#P2_CLK1   </li>
 *     <li>#P2_CLK8   </li>
 *     <li>#P2_CLK32  <b style="color:#A00">!!Nouvelle valeur comparé à #Prescale01!!</b></li>
 *     <li>#P2_CLK64  </li>
 *     <li>#P2_CLK128 <b style="color:#A00">!!Nouvelle valeur comparé à #Prescale01!!</b></li>
 *     <li>#P2_CLK256 </li>
 *     <li>#P2_CLK1024</li>
 * </ul>
 */
typedef uint8_t Prescale2;
#define    P2_NO_CLK  0x0
#define    P2_CLK1    0x1
#define    P2_CLK8    0x2
#define    P2_CLK32   0x3
#define    P2_CLK64   0x4
#define    P2_CLK128  0x5
#define    P2_CLK256  0x6
#define    P2_CLK1024 0x7

/**
 * @brief   COM : '<i>Compare Output Mode</i>'. Type de valeurs qui expriment
 *      la manière dont le signal de sortie du @link Timer TimerN @endlink
 *      réagit à une égalité entre OcrNX et TnctN.
 * 
 * <b>Valeurs possibles:</b>
 * <ul>
 *     <li>#DISCONNECTED</li>
 *     <li>#TOGGLE</li>
 *     <li>#CLEAR</li>
 *     <li>#SET</li>
 * </ul>
 */
typedef uint8_t ComNX;
#define    DISCONNECTED 0x0
#define    TOGGLE       0x1   // ATTENTION: Dans certains modes (ex: Fast-PWM et PC-PWM du Timer0 avec WGM02 = 0), TOGGLE est équivalent à DISCONNECTED.
                              // Également, pour COMNB, TOGGLE peut ne pas être supporté par le microcontrôleur.
#define    CLEAR        0x2
#define    SET          0x3


typedef uint8_t WGMode; // Waveform Generation Mode

#endif // TYPEDEFS_H