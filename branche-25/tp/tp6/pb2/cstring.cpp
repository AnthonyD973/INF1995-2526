#include "cstring.h"

/**
 * @brief Compare deux chaînes C.
 * @param[in] str1 Chaîne à comparer.
 * @param[in] str2 Chaîne à comparer.
 * @return true si le test est concluant.
 */
bool strcmp(uint8_t* str1, uint8_t* str2) {
  size_t i = 0;
  bool areEqual = true;
  
  while (str1[i] != '\0' && str2[i] != '\0') {
	if (str1[i] != str2[i]) {
	  areEqual = false;
	  break;
	}
	++i;
  }
  
  // Traiter le cas où les chaînes sont de longueurs différentes.
  if (str1[i] != str2[i]) {
	areEqual = false;
  }
  
  return areEqual;
}

/**
 * @brief Détermine la longueur d'une chaîne C.
 * @param[in] str Chaîne à parcourir.
 * @return La longueur de la chaîne (sans compter l'octet zéro).
 */
size_t strlen(uint8_t* str) {
  size_t len = 0;
  while (str[len] != '\0') {
	++len;
  }
  
  return len;
}