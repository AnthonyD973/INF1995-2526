#include <iostream>
#include <fstream>
#include <string>

#include "SongsData.h"

#define N_TONES_MAX 1024
using namespace std;

//enum Tones {O, C, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B};

struct Song {
    uint8_t  bps;
    uint16_t  nTones;
    Tone* tones;
};

struct SongFile {
    uint8_t  fileID[6];
    uint16_t nSongs;
    Song*    songs;
};

void initSongFile(SongFile& songFile) {
    songFile.fileID[0] = 'E';
    songFile.fileID[1] = 'M';
    songFile.fileID[2] = 'B';
    songFile.fileID[3] = 'E';
    songFile.fileID[4] = 'N';
    songFile.fileID[5] = 'D';
    
    songFile.nSongs = 8;
    songFile.songs = new Song[songFile.nSongs];
    songFile.songs[0].bps = beatDiv0;
    songFile.songs[0].nTones = nTones0;
    songFile.songs[0].tones = tones01;
    songFile.songs[1].bps = beatDiv1;
    songFile.songs[1].nTones = nTones1;
    songFile.songs[1].tones = tones11;
    songFile.songs[2].bps = beatDiv3;
    songFile.songs[2].nTones = nTones3;
    songFile.songs[2].tones = tones31;
    songFile.songs[3].bps = beatDiv4;
    songFile.songs[3].nTones = nTones4;
    songFile.songs[3].tones = tones41;
    songFile.songs[4].bps = tetrisBeatDiv;
    songFile.songs[4].nTones = tetrisNTones;
    songFile.songs[4].tones = tetrisTones1;
    songFile.songs[5].bps = beatDiv6;
    songFile.songs[5].nTones = nTones6;
    songFile.songs[5].tones = tones61;
    songFile.songs[6].bps = beatDiv5;
    songFile.songs[6].nTones = nTones5;
    songFile.songs[6].tones = tones51;
    songFile.songs[7].bps = beatDiv7;
    songFile.songs[7].nTones = nTones7;
    songFile.songs[7].tones = tones71;
}

void writeSong(ostream& os, Song& song) {
    os.write((char*)&song.bps, sizeof(song.bps));
    os.write((char*)&song.nTones, sizeof(song.nTones));
    os.write((char*)song.tones, song.nTones*sizeof(*song.tones));
}

void writeSongFile(ostream& os, SongFile& songFile) {
    os.write((char*)songFile.fileID, 6*sizeof(*songFile.fileID));
    os.write((char*)&songFile.nSongs, sizeof(songFile.nSongs));
    for (unsigned int i = 0; i < songFile.nSongs; ++i) {
        writeSong(os, songFile.songs[i]);
    }
}

int main(int argc, char **argv) {
    string   fileName;
    ofstream file;
    
    SongFile songFile;
    initSongFile(songFile);
    
    if (argc > 1) {
        file.open(argv[1], ofstream::out | ofstream::binary);
        if(file.is_open()) {
            writeSongFile(file, songFile);
        }
        file.close();
    }
    return 0;
}
