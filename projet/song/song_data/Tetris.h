#ifndef TETRIS_H
#define TETRIS_H // Include guard

#include "SongFile.h"

SongFile makeSong(SongFile& sf) {
    sf.noteCount = 74;
    sf.tones = new Note[sf.noteCount] {
        {_1_2,64},{_1_4,59},{_1_4,60},
        {_1_4,62},{_1_8,64},{_1_8,62},{_1_4,60},{_1_4,59},
        {_1_4,57},{_1_8,57},{_1_8, 0},{_1_4,57},{_1_4,60},
        {_1_2,64},{_1_4,62},{_1_4,60},
        {_1_4,59},{_1_8,59},{_1_8, 0},{_1_4,59},{_1_4,60},
        {_1_2,62},{_1_2,64},
        {_1_2,60},{_1_4,57},{_1_8,57},{_1_8, 0},
        {_1_2,57},{_1_2, 0}, // 29
        {_1_4,62},{_1_8,62},{_1_8, 0},{_1_4,62},{_1_4,65},
        {_1_2,69},{_1_4,67},{_1_4,65},
        {_1_2,64},{_1_4,64},{_1_4, 0},{_1_4,60},
        {_1_2,64},{_1_4,62},{_1_4,60},
        {_1_4,59},{_1_8,59},{_1_8, 0},{_1_4,59},{_1_4,60},
        {_1_2,62},{_1_2,64},
        {_1_2,60},{_1_4,57},{_1_8,57},{_1_8, 0},
        {_1_2,57},{_1_2, 0}, // 57
        {_1_1,64},{_1_1,60},
        {_1_1,62},{_1_1,59},
        {_1_1,60},{_1_1,57},
        {_1_1,56},{_1_1,59},
        {_1_1,64},{_1_1,60},
        {_1_1,62},{_1_1,59},
        {_1_2,57},{_1_2,60},
        {_1_1,69},{_1_1,68},
        {_1_1, 0} // 74
    };
    sf.fileSize = sizeof(sf.fileSize) + sizeof(sf.noteCount) + sf.noteCount*sizeof(sf.tones[0]);
}

#endif // TETRIS_H
