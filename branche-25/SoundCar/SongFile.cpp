#include "SongFile.h"

SongFile::SongFile(const uint16_t& nSongs_) : nSongs(nSongs_) {
    if(nSongs_ > 0) {
        Song tmp[nSongs_];
        songs = tmp;
    }
}

SongFile::~SongFile() {
}

