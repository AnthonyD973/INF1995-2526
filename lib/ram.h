/**
 * @file    ram.h
 * 
 * @brief   Définition de RAM, qui permet d'écrire et de lire en mémoire externe.
 * 
 * @authors Lauzier, Isidore
 * @authors Collin, Jerome
 * 
 * @date 2005-2008
 *
 * @copyright Code qui n'est sous aucune license.
 */

#ifndef RAM_H
#define RAM_H

#include "lib.h"

/**
 * @brief   Cet exemple d'utilisation d'une mémoire eeprom i2c est une modification du
 * programme de Joerg Wunsch twitest.c fourni avec Winavr. Il est compatible
 * aux eeprom 24C128, 24C256 et 24c512. Ce programme a été simplifié afin
 * d'illustrer la programmation du bus TWI et des memoires I2C.
 * 
 * @note    Le protocole I2C utilise les broches C0 et C1 sur un
 *      microcontrôleur Atmel ATMega324PA.
 */
class RAM
{
    /** @cond FALSE */ // Ne pas documenter cette classe : nous l'avons
                       // quasiment copiée du site du cours, comme suggéré par
                       // le professeur.
public:
   // procedure d'initialisation - a appeler avant lecture ou ecriture
   static void init();
   
   // la procedure init() initialize a zero le "memory bank". 
   // appeler cette methode uniquement si l'adresse doit changer
   static uint8_t chooseBank(const uint8_t bank);
   
   // deux variantes pour la lecture, celle-ci et la suivante
   static uint8_t read(const uint16_t address, uint8_t *data);

   // length doit etre de 127 et moins
   static uint8_t read(const uint16_t address, uint8_t *data, const uint8_t length);

   // deux variantes pour la l'ecriture egalement
   static uint8_t write(const uint16_t address, const uint8_t data);
   static uint8_t write(const uint16_t address, uint8_t *data, const uint8_t length);

private:
   // pour l'ecriture
   static uint8_t _writePage(const uint16_t address, uint8_t *data, const uint8_t length);

   // donnees membres
   static uint8_t _mDeviceAddress;
   static const uint8_t _PAGE_SIZE;
   /** @endcond */
};

#endif // RAM_H