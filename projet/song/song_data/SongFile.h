#ifndef SONGFILE_H
#define SONGFILE_H // Include guard

#include <cstdint>

const uint8_t
    _1_32 = 1, // Seizuple-croche ?
    _1_16 = 2, // Huituple-croche ?
    _1_8  = 3, // Quadruple-croche
    _1_4  = 4, // Double-croche
    _1_2  = 5, // Croche
    _1_1  = 6, // Noire
    _2_1  = 7, // Blanche
    _4_1  = 8; // Ronde

struct Note {
    uint8_t duration; // 1 = 1/32 d'une noire (à 60 bpm); 2 = 1/16; 3 = 1/8; ...
    uint8_t midiTone; // La note elle-même, noté selon le format midi (de 24 à 127). Une note à l'extérieur de cet interval est considéré comme un silence.
};

struct SongFile {
    uint16_t fileSize; // La taille en octets du fichier, incluant le fileSize.
    uint16_t noteCount; // Le nombre de notes.
    Note* tones; // Le tableau contenant les notes.
};

#endif // SONGFILE_H
