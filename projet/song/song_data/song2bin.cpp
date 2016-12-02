#include <iostream>
#include <fstream>

#include <cstdint>
#include "NeverGonnaGiveYouUp.h"
//#include "Tetris.h"

void writeSong(std::ofstream& ofs, SongFile& sf) {
    ofs.write((char*)&(sf.fileSize), sizeof(sf.fileSize));
    ofs.write((char*)(&sf.noteCount), sizeof(sf.noteCount));
    for (unsigned int i = 0; i < sf.noteCount; ++i) {
        ofs.write((char*)&(sf.tones[i].duration), sizeof(sf.tones[i].duration));
        ofs.write((char*)&(sf.tones[i].midiTone), sizeof(sf.tones[i].midiTone));
    }
}

int main(int argc, char* argv[]) {
    SongFile sf;
    
    if (argc <= 1) {
        std::cerr << "Il faut spécifier dans quel fichier on écrit la chanson." << std::endl;
        return 1;
    }
    
    std::ofstream ofs;
    ofs.open(argv[1], std::ios::binary | std::ios::out);
    
    if (ofs.is_open()) {
        makeSong(sf);
        writeSong(ofs, sf);
        ofs.flush();
    }
    else {
        std::cout << "Le fichier n'a pas pu être ouvert." << std::endl;
    }
    ofs.close();
    
    return 0;
}
