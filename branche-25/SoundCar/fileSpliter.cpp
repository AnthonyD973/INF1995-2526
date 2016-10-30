#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const unsigned int FILE_SIZE = 128;

int main(int argc, char **argv) {
    string   fileName;
    ifstream file1;
    ofstream file2;
    char* buffer;
    
    if (argc > 1) {
        fileName = argv[1];
        
        file1.open(("./"+fileName).c_str(), ios::in | ios::binary);
        if(file1.is_open()) {
            file1.seekg(0, ifstream::end);
            unsigned int size = file1.tellg();
            file1.seekg(0, ifstream::beg);
            unsigned int rest = size % FILE_SIZE;
            size /= FILE_SIZE;
            
            system(("mkdir ./"+fileName+"._out").c_str());
            
            for (unsigned int i = 0; i < size; ++i) {
                file2.open(("./"+fileName+"._out/"+fileName+"._"+to_string((long)i)+".bit").c_str(), ios::out | ios::binary);
                if (file2.is_open()) {
                    buffer = new char[FILE_SIZE];
                    file1.read(buffer, FILE_SIZE);
                    file2.write(buffer, FILE_SIZE);
                }
                file2.close();
                file2.clear();
            }
            if (rest != 0) {
                file2.open(("./"+fileName+"._out/"+fileName+"._"+to_string((long)size)+".bit").c_str(), ios::out | ios::binary);
                if (file2.is_open()) {
                    buffer = new char[rest];
                    file1.read(buffer, rest);
                    file2.write(buffer, rest);
                }
                file2.close();
            }
        }
        file1.close();
    }
    return 0;
}
